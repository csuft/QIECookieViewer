#include "qiecookieviewer.h"

QIECookieViewer::QIECookieViewer(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	ui.nextBtn->setDisabled(true);
	ui.nextBtn->setDisabled(true);
	ui.filterExpLineEdit->setPlaceholderText(QStringLiteral("Filter Expression"));
	ui.colComboBox->addItem(QStringLiteral("By Website"), 0);
	ui.colComboBox->addItem(QStringLiteral("By Cookie"), 4);
	ui.caseCheckBox->setCheckState(Qt::Checked);
	ui.sortCheckBox->setCheckState(Qt::Checked);
	ui.tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
	ui.tableView->setSelectionMode(QAbstractItemView::SingleSelection);
	ui.tableView->horizontalHeader()->setStretchLastSection(true);
	ui.tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
	ui.tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
	// set mouse tracking mode.
	ui.tableView->setMouseTracking(true);
	ui.tableView->setWordWrap(false);
	m_model = new QStandardItemModel(0, 9, this);
	createHeader();
	createCookieModel();
	m_proxyModel = new QSortFilterProxyModel(this);
	m_proxyModel->setSourceModel(m_model);
	ui.tableView->setModel(m_proxyModel);

	connect(ui.caseCheckBox, SIGNAL(stateChanged(int)), this, SLOT(onCaseSensitiveChecked(int)));
	connect(ui.sortCheckBox, SIGNAL(stateChanged(int)), this, SLOT(onViewSortChecked(int)));
	connect(ui.filterExpLineEdit, SIGNAL(textChanged(const QString&)), this, SLOT(onFilterExpChanged(const QString&)));
	connect(ui.colComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(onFilterColChanged(int)));
	connect(ui.cleanBtn, SIGNAL(clicked()), this, SLOT(onCleanClicked()));
	connect(ui.closeBtn, SIGNAL(clicked()), this, SLOT(close()));
	connect(ui.refreshBtn, SIGNAL(clicked()), this, SLOT(onRefreshClicked()));
	connect(ui.openBtn, SIGNAL(clicked()), this, SLOT(onOpenClicked()));
	connect(ui.prevBtn, SIGNAL(clicked()), this, SLOT(onPrevClicked()));
	connect(ui.nextBtn, SIGNAL(clicked()), this, SLOT(onNextClicked()));
	connect(ui.tableView, SIGNAL(clicked(const QModelIndex&)), this, SLOT(onTableViewClicked(const QModelIndex&)));
	connect(ui.tableView, SIGNAL(entered(const QModelIndex&)), this, SLOT(showToolTips(const QModelIndex&)));
}

QIECookieViewer::~QIECookieViewer()
{

}

void QIECookieViewer::createHeader()
{
	// for View/Model architecture
	m_model->setHeaderData(0, Qt::Horizontal, QStringLiteral("Website"));
	m_model->setHeaderData(1, Qt::Horizontal, QStringLiteral("Hits"));
	m_model->setHeaderData(2, Qt::Horizontal, QStringLiteral("Last Access"));
	m_model->setHeaderData(3, Qt::Horizontal, QStringLiteral("Last Modified"));
	m_model->setHeaderData(4, Qt::Horizontal, QStringLiteral("Cookie File"));
	m_model->setHeaderData(5, Qt::Horizontal, QStringLiteral("Size"));
	m_model->setHeaderData(6, Qt::Horizontal, QStringLiteral("User"));
	m_model->setHeaderData(7, Qt::Horizontal, QStringLiteral("Order"));
	m_model->setHeaderData(8, Qt::Horizontal, QStringLiteral("Local Path"));
	
	// for Table view widget
	QStringList labelList;
	labelList << "Key" << "Value" << "Domain" << "Expiration" << "Creation" << "Creator";
	ui.cookieDetailsView->setColumnCount(6);
	ui.cookieDetailsView->setHorizontalHeaderLabels(labelList);
	ui.cookieDetailsView->setWordWrap(false);
	ui.cookieDetailsView->setSelectionBehavior(QAbstractItemView::SelectRows);
	ui.cookieDetailsView->setSelectionMode(QAbstractItemView::SingleSelection);
}

void QIECookieViewer::createCookieModel()
{
	int count = 0;
	const int ROW = 0;
	CookieHelper chelper;
	vector<CacheEntry> vc = chelper.getCacheEntVec();
	for (vector<CacheEntry>::const_iterator ci = vc.cbegin(); ci != vc.cend(); ++ci)
	{
		count += 1;
		m_model->insertRow(0);
		m_model->setData(m_model->index(ROW, 0), (*ci).m_website.c_str());
		m_model->setData(m_model->index(ROW, 1), (*ci).m_hits);
		m_model->setData(m_model->index(ROW, 2), (*ci).m_lastAccess.c_str());
		m_model->setData(m_model->index(ROW, 3), (*ci).m_lastModified.c_str());
		m_model->setData(m_model->index(ROW, 4), (*ci).m_fileName.c_str());
		m_model->setData(m_model->index(ROW, 5), (*ci).m_cookieSize);
		m_model->setData(m_model->index(ROW, 6), (*ci).m_user.c_str());
		m_model->setData(m_model->index(ROW, 7), (*ci).m_recordNum);
		m_model->setData(m_model->index(ROW, 8), (*ci).m_localPath.c_str());
	}
	ui.totalLabel->setText(QStringLiteral("%1 items").arg(count));
	ui.tableView->selectRow(0);
	ui.locationLabel->setText(QStringLiteral("0"));
}

void QIECookieViewer::recreateCookieModel()
{
	m_model->removeRows(0, m_model->rowCount());
	createCookieModel();
}
// show tooltip box when the mouse is in the range of 
void QIECookieViewer::showToolTips(const QModelIndex& index)
{
	if (index.isValid())
	{
		QToolTip::showText(QCursor::pos(), index.data().toString());
	}
}

void QIECookieViewer::onFilterExpChanged(const QString& text)
{
	Qt::CaseSensitivity cs = ui.caseCheckBox->isChecked()?Qt::CaseSensitive:Qt::CaseInsensitive;
	QRegExp regexp(ui.filterExpLineEdit->text(), cs, QRegExp::FixedString);
	m_proxyModel->setFilterRegExp(regexp);
}

void QIECookieViewer::onPrevClicked()
{
	QItemSelectionModel* selModel = ui.tableView->selectionModel();
	if (selModel->hasSelection())
	{
		QModelIndex curIndex = selModel->currentIndex();
		ui.tableView->selectRow(curIndex.row()-1);  // move the selected row
		onTableViewClicked(m_model->index(curIndex.row()-1, curIndex.column()));
	}
}

void QIECookieViewer::onNextClicked()
{
	QItemSelectionModel* selModel = ui.tableView->selectionModel();
	if (selModel->hasSelection())
	{
		QModelIndex curIndex = selModel->currentIndex();
		ui.tableView->selectRow(curIndex.row()+1); // move the selected row
		onTableViewClicked(m_model->index(curIndex.row()+1, curIndex.column()));
	}
}

void QIECookieViewer::onTableViewClicked(const QModelIndex& index)
{
	ui.prevBtn->setEnabled(index.row() > 0);
	ui.nextBtn->setEnabled(index.row() < m_proxyModel->rowCount()-1);
	// update text labels and cookie details view
	ui.locationLabel->setText(QStringLiteral("%1").arg(index.row()));
	// Retrieve the cookie file name from the fifth column
	QString cookieName = m_proxyModel->data(m_proxyModel->index(index.row(), 4)).toString();
	resolveCookies(cookieName.toStdString().c_str());
}

void QIECookieViewer::onCleanClicked()
{

}

void QIECookieViewer::onOpenClicked()
{

}

void QIECookieViewer::onRefreshClicked()
{
	recreateCookieModel();
}

void QIECookieViewer::onFilterColChanged(int index)
{
	m_proxyModel->setFilterKeyColumn(ui.colComboBox->itemData(index).toInt());
}

void QIECookieViewer::onViewSortChecked(int i)
{

	ui.tableView->setSortingEnabled(ui.sortCheckBox->isChecked());
}

void QIECookieViewer::onCaseSensitiveChecked(int i)
{
	onFilterExpChanged(QStringLiteral(""));
}

void QIECookieViewer::resolveCookies(const char* fileName)
{
	CookieEntry entry;
	vector<CookieEntry> vc;
	char buffer[1024] = {'\0'};
	char low[16] = {'\0'};
	char high[16] = {'\0'};
	char* chStart = NULL;
	char* chEnd = NULL;
	ifstream cookie(CookieHelper::getCookiePath(fileName));
	while (cookie.getline(buffer, 1024, '*'))
	{
		memset(&entry, 0, sizeof(CookieEntry));
		// key
		chStart = buffer;
		chEnd = strchr(chStart, '\n');
		strncpy(entry.m_key, chStart, chEnd-chStart);
		// value
		chStart = chEnd + 1;  // skip the single newline
		chEnd = strchr(chStart, '\n');
		strncpy(entry.m_value, chStart, chEnd-chStart);
		// domain
		chStart = chEnd + 1;
		chEnd = strchr(chStart, '\n');
		strncpy(entry.m_domain, chStart, chEnd-chStart);
		// flag
		chStart = chEnd + 1;
		chEnd = strchr(chStart, '\n');
		strncpy(entry.m_flag, chStart, chEnd-chStart);
		// the length of "Server" is the same as "Client", 6 bytes.
		strncpy(entry.m_creator, setCreator(entry.m_flag), 6);
		// low expiration time
		chStart = chEnd + 1;
		chEnd = strchr(chStart, '\n');
		strncpy(low, chStart, chEnd-chStart);
		// high expiration time
		chStart = chEnd + 1;
		chEnd = strchr(chStart, '\n');
		strncpy(high, chStart, chEnd-chStart);
		transformTime(low, high, entry.m_expiration);
		// low creation time
		memset(low, 0, 16);
		memset(high, 0, 16);
		chStart = chEnd + 1;
		chEnd = strchr(chStart, '\n');
		strncpy(low, chStart, chEnd-chStart);
		// low creation time
		chStart = chEnd + 1;
		chEnd = strchr(chStart, '\n');
		strncpy(high, chStart, chEnd-chStart);
		transformTime(low, high, entry.m_creation);

		vc.push_back(entry);
		memset(buffer, 0, 512);
		cookie.ignore();
	}
	cookie.close();
	createDetailsView(vc);
}

void QIECookieViewer::createDetailsView(const vector<CookieEntry>& vc)
{
	int index = 0;
	int total = vc.size();
	ui.cookieDetailsView->clearContents();
	ui.cookieDetailsView->setRowCount(total);
	for (vector<CookieEntry>::const_iterator ci = vc.cbegin(); ci != vc.cend(); ++ci, ++index)
	{
		ui.cookieDetailsView->setItem(index, 0, new QTableWidgetItem(QString((*ci).m_key)) );
		ui.cookieDetailsView->setItem(index, 1, new QTableWidgetItem(QString((*ci).m_value)) );
		ui.cookieDetailsView->setItem(index, 2, new QTableWidgetItem(QString((*ci).m_domain)) );
		ui.cookieDetailsView->setItem(index, 3, new QTableWidgetItem(QString((*ci).m_expiration)) );
		ui.cookieDetailsView->setItem(index, 4, new QTableWidgetItem(QString((*ci).m_creation)) );
		ui.cookieDetailsView->setItem(index, 5, new QTableWidgetItem(QString((*ci).m_creator)) );
	}
}

void QIECookieViewer::transformTime(const char* low, const char* high, char* dst)
{
	FILETIME ft;
	SYSTEMTIME st;
	const int BUFFER_SIZE = 32;
	char chBuffer[BUFFER_SIZE] = {'\0'};

	ft.dwLowDateTime = atol(low);
	ft.dwHighDateTime = atol(high);
	FileTimeToLocalFileTime(&ft, &ft);
	FileTimeToSystemTime(&ft, &st);
	_snprintf(chBuffer, BUFFER_SIZE,"%04d-%02d-%02d %02d:%02d:%02d", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);
	strncpy(dst, chBuffer, BUFFER_SIZE);
}

const char* QIECookieViewer::setCreator(const char* flag)
{
	long val = atol(flag);
	// if the remainder is nonzero, then the cookie is created by browser scripts(such as js, vb).
	// Otherwise, it is created by web server.
	return val%0x100?"Client":"Server";
}
