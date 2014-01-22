QIECookieViewer
===============

A simple cookie viewer designed for IEs.
1. Introduction
---------------
This sub-project is derived from ```QTrojanAccessment``` project. QIECookieViewer is inspired by a brilliant tool developed by [Nir Sofer](http://www.nirsoft.net  "Nir Sofer"). So, I call it as QIECookieViewer since it was developed using Qt framework.   
QIECookieViewer retrieve meta information from index.dat file, which is used by Windows Operating System to store cookies record. Even you delete all cookie files stored under the same folder, the records in index.dat file ramain as usual. That is to say, a hacker or spy can easily steal your privacy. But for me, it is not so bad.  
**Cookie Path**:  
>For ```Windows 2000/XP```:
```bash
C:/Documents and Settings/Administrator/Cookies/
```
For Windows Vista/7:
```bash
C:/Users/Administrator/AppData/Roaming/Microsoft/Windows/Cookies/
```
and:
```bash
C:/Users/Administrator/AppData/Roaming/Microsoft/Windows/Cookies/Low/
```  

**index.dat File Structure**  
index.dat has its own structure to store cache entries, which I have discovered in detail in my personal blog. For more information, please visit: [How to implement a cookie viewer](http://www.cnblogs.com/csuftzzk "How to implement a cookie viewer")  
**Cookie file Structure**   
Cookies were used by websites to enhance the user experiences when we browse those sites. A website can possess more than one cookie file. Generally speaking, a website can generate a cookie file for each ```sub-domain```.   
The structure of a cookie file is simple and the privacy is presented as ascii strings. In cookie file, every record is separated by a ```asterisk``` and all fields are separated by a ```newline```('\n').   
**Cookie Record Structure**   
A cookie record has 8 fields. It can be defined as follows:   
```c
typedef struct _COOKIE_FIELD
{
	char      m_szKey[256];        // cookie key
	char      m_szValue[1024];     // cookie value, can be very long
	char      m_szDomain[32];      // the domain for which this cookie was created
	char      m_szFlag[16];        // flags, the meaning is unknown
	char      m_szLowExpire[16];   // cookie expiration time
	char      m_szHighExpire[16]; 
	char      m_szLowCreate[16];   // cookie creation time
	char      m_szHighCreate[16]; 
} COOKIE_FIELD, *LPCOOKIE_FIELD;   
```
All we have to do is extract responding fields and transform to proper format to insert into ```QTableView``` or ```QTableWidget```.   
**Some Tricks**   
* Datetime Transform:   

```cpp
	FILETIME ft;
	SYSTEMTIME st;
	const int BUFFER_SIZE = 32;
	char chBuffer[BUFFER_SIZE] = {'\0'};

	ft.dwLowDateTime = atol(low);       // ascii to long int, low part
	ft.dwHighDateTime = atol(high);     // ascii to long int, high part
	FileTimeToLocalFileTime(&ft, &ft);  // time zone transformation
	FileTimeToSystemTime(&ft, &st);     // long int struct to human-readable format
	_snprintf(chBuffer, BUFFER_SIZE,"%04d-%02d-%02d %02d:%02d:%02d", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);
```
* Determine Cookie Creator  
```c
	long val = atol(flag);      
	  
	return val%0x100?"Client":"Server";   
```
Why did this work? I have searched the internet using Google search engine and Bing for a while. I can't find anything related with the meaning of flags in cookie record. So I opened my cookies folder and checked almost all cookie files. With the comparison between the flag value and the presentation showed in [IECookieViewer](http://www.nirsoft.net/utils/iecookies.html "IECookieViewer"), a result showed in my mind, which I have discribed above.
2. Get Source Code
------------------
Open your git bash and change to the directory into which you want to save the source code, and type the following command:
```bash
$ git clone git@github.com:csuft/QIECookieViewer.git .
```
When the command finished, you can find a newly created sub directory in the path you choosed.
3. Screen Shots
---------------
Overview 1  
![MethodOne.jpg](https://github.com/csuft/QIECookieViewer/raw/master/captures/Schirmfoto_2014-01-22_113243.png "")  
Overview 2  
![MethodOne.jpg](https://github.com/csuft/QIECookieViewer/raw/master/captures/Schirmfoto_2014-01-22_113338.png "")
4. To Do List
-------------
1. UI experience enhanced
2. Windows 7 support
3. Compatible with IE 10

5. Copyright
------------
No permissions need to be granted.
