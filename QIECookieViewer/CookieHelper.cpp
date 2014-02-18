#include "CookieHelper.h"


CookieHelper::CookieHelper(void)
{
	// Need to be fixed
	const string fileName = getCookiePath("index.dat");
	// create a kernel file object
	m_hFile = CreateFileA(fileName.c_str(), GENERIC_READ, FILE_SHARE_READ|FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_HIDDEN|FILE_ATTRIBUTE_READONLY, NULL);
	if (m_hFile == INVALID_HANDLE_VALUE)
	{
		MessageBoxA(NULL, "Error", "Can't open the index.dat file.", MB_OKCANCEL);
		return;
	}

	// create a kernel file mapping object
	m_hMapping = CreateFileMappingA(m_hFile, NULL, PAGE_READONLY, 0, 0, NULL);
	if (m_hMapping == NULL)
	{
		MessageBoxA(NULL, "Error", "Can't create file mapping object.", MB_OKCANCEL);
		CloseHandle(m_hFile);
		m_hFile = NULL;
		return ;
	}

	m_startAddr = (LPSTR)MapViewOfFile(m_hMapping, FILE_MAP_READ, 0, 0, 0);
	if (m_startAddr == NULL)
	{
		MessageBoxA(NULL, "Error", "Can't mappping the index.dat file.", MB_OKCANCEL);
		CloseHandle(m_hFile);
		m_hFile = NULL;
		CloseHandle(m_hMapping);
		m_hMapping = NULL;
		return;
	}
	initializeEntriesVec();
}

CookieHelper::~CookieHelper(void)
{
	if (m_startAddr) UnmapViewOfFile((PBYTE)m_startAddr);
	if (m_hMapping) CloseHandle(m_hMapping);
	if (m_hFile) CloseHandle(m_hFile);
}

void CookieHelper::initializeEntriesVec()
{
	const int PATH_LEN = 256;
	char path_buf[PATH_LEN] = {L'\0'};
	// the flag indicates whether subdirectories exist.
	int isSubDirExist = 0;
	// retrieve the index.dat header
	LPMEMMAP_HEADER_SMALL lpsmallHead = (LPMEMMAP_HEADER_SMALL)m_startAddr;

	// If none hash header exists in this .dat file, simply return.
	if (lpsmallHead->dwHashTableOffset == 0) 
	{
		return ;
	}
	char subdirNames[16][8] = {'\0'};
	// If there exist subdirectories...
	if (lpsmallHead->nDirCount)
	{
		isSubDirExist = 1; 
		// jump to the beginning of the subdir entries.
		LPSTR subdirBeginAddr = (LPSTR)lpsmallHead + 76; 
		int subdirCount = 0;
		while (subdirCount < lpsmallHead->nDirCount)
		{
			subdirBeginAddr += 4; // skip the items count in the subdir, 4 byte 
			strncpy(subdirNames[subdirCount], subdirBeginAddr, 8);
			subdirBeginAddr += 8; // skip the next subdirectory entry.
			subdirCount++;
		}
	}

	LPHASH_ITEM lphashItem = NULL;
	HASH_ITEM hashItem;
	HASH_FILEMAP_ENTRY hashEntry;
	LPIE5_URL_FILEMAP_ENTRY lpie5Record = NULL;
	IE5_URL_FILEMAP_ENTRY ie5Record;
	CacheEntry record;
	int ordNum;
	// get the first hash table.
	LPHASH_FILEMAP_ENTRY lphashHeader = (LPHASH_FILEMAP_ENTRY)(m_startAddr + lpsmallHead->dwHashTableOffset);
	while (lphashHeader)
	{
		ordNum = 1;
		memcpy(&hashEntry, lphashHeader, sizeof(HASH_FILEMAP_ENTRY));
		// iterate through all hash items
		lphashItem = (LPHASH_ITEM)(lphashHeader + 1);
		memcpy(&hashItem, lphashItem, sizeof(HASH_ITEM));
		// Terminated when the URL entry offset is 0xDEADBEEF
		while (ordNum <= (hashEntry.nBlocks*0x80-16)/8 && hashItem.dwOffset != 0xDEADBEEF)
		{
			// skip the holes in the hash section until the end of hash section.
			if (hashItem.dwHash != 0x0 && hashItem.dwHash != 0x3)
			{
				lpie5Record = (LPIE5_URL_FILEMAP_ENTRY)(m_startAddr + hashItem.dwOffset);
				memcpy(&ie5Record, lpie5Record, sizeof(IE5_URL_FILEMAP_ENTRY));
				record.m_lastAccess = transformTimeFormat(ie5Record.LastAccessedTime);
				record.m_lastModified = transformTimeFormat(ie5Record.LastModifiedTime);
				record.m_hits = ie5Record.NumAccessed;
				record.m_cookieSize = ie5Record.dwFileSize;
				if (isSubDirExist)
				{
					// generate the local path of the cookie file.
					record.m_localPath = getCookiePath(subdirNames[ie5Record.DirIndex]);
				}
				else
				{
					record.m_localPath = getCookiePath("");
				}
				record.m_fileName = string((char*)lpie5Record + lpie5Record->InternalFileNameOffset);
				splitCookieURL((char*)lpie5Record + lpie5Record->UrlNameOffset, record);
				record.m_recordNum = ordNum;
				
				m_recordsVec.push_back(record);
			}
			lphashItem += 1;  // skip to the next hash item.
			memcpy(&hashItem, lphashItem, sizeof(HASH_ITEM));
			ordNum++;
		}

		lphashHeader = hashEntry.dwNext?(LPHASH_FILEMAP_ENTRY)(m_startAddr + hashEntry.dwNext):NULL;
	}

}

const string CookieHelper::transformTimeFormat(LONGLONG dtime)
{
	SYSTEMTIME st;
	FILETIME ft;
	FILETIME tmp;
	const int TIMEBUFFER = 32;
	char chDateTime[TIMEBUFFER] = {'\0'};

	memcpy(&tmp, &dtime, sizeof(LONGLONG)); 
	if (tmp.dwHighDateTime == 0 && tmp.dwLowDateTime == 0)
	{
		_snprintf(chDateTime, TIMEBUFFER, "N/A");
	}
	else
	{
		FileTimeToLocalFileTime(&tmp, &ft);
		FileTimeToSystemTime(&ft, &st);
		_snprintf(chDateTime, TIMEBUFFER, "%04d-%02d-%02d %02d:%02d:%02d", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);
	}

	return string(chDateTime);
}
/*
 * Return different path prefixes depend on the type of 
 * the underlying Operating System
 */
const string CookieHelper::getCookiePath(const char* appendice)
{
	DWORD len;
	const int BUFSIZE = 1024;
	char windir[BUFSIZE] = {'\0'};
	char paths[BUFSIZE] = {'\0'};
	GetWindowsDirectoryA(windir, BUFSIZE);
	QSysInfo sysinfo;
	if (QSysInfo::WV_WINDOWS7 == sysinfo.windowsVersion())  // For Windows 7.
	{
		char uname[BUFSIZE] = {'\0'};
		GetUserNameA(uname, &len);
		_snprintf(paths, 256, "%c:\\Users\\%s\\AppData\\Roaming\\Microsoft\\Windows\\Cookies\\%s", windir[0], uname, appendice);
	}
	else if (QSysInfo::WV_XP == sysinfo.windowsVersion())  // For Windows XP.
	{
		_snprintf(paths, 256, "%c\\Documents and Settings\\Administrator\\Cookies\\%s", windir[0], appendice);
	}
	else // For other Windows versions.
	{
		_snprintf(paths, 256, "");
	}
	return paths;
}

void CookieHelper::splitCookieURL(char* url, CacheEntry& obj)
{
	char* chPtrStart = NULL;
	char* chPtrEnd = NULL;
	const int BUFSIZE = 128;
	char  tmp[BUFSIZE] = {'\0'};

	chPtrStart = strchr(url, ':');
	chPtrEnd = strchr(url, '@');
	strncpy(tmp, chPtrStart+1, chPtrEnd - chPtrStart - 1);
	obj.m_user = tmp;

	memset(tmp, 0, BUFSIZE);
	chPtrStart = chPtrEnd;
	strncpy(tmp, chPtrStart+1, strlen(chPtrStart+1));
	obj.m_website = tmp;
}