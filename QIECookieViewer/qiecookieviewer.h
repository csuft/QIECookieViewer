#ifndef QIECOOKIEVIEWER_H
#define QIECOOKIEVIEWER_H

#include <QtWidgets/QWidget>
#include <QStandardItemModel>
#include <QSortFilterProxyModel>
#include <QHeaderView>
#include <QAbstractItemModel>
#include <QAbstractItemView>
#include <QItemSelectionModel>
#include <QRegExp>
#include <QStringList>
#include <QToolTip>

#include "ui_qiecookieviewer.h"
#include "CookieHelper.h"

typedef struct _cookieEntry
{
	char m_key[32];
	char m_value[1024];
	char m_domain[32];
	char m_flag[8];
	char m_expiration[32];
	char m_creation[32];
	char m_creator[8];
}CookieEntry, *lpCookieEntry;

class QIECookieViewer : public QWidget
{
	Q_OBJECT

public:
	QIECookieViewer(QWidget *parent = 0);
	~QIECookieViewer();

private slots:
	void onFilterExpChanged(const QString& text);
	void onPrevClicked();
	void onNextClicked();
	void onCleanClicked();
	void onTableViewClicked(const QModelIndex& index);
	void onOpenClicked();
	void onRefreshClicked();
	void onFilterColChanged(int index);
	void onViewSortChecked(int i);
	void onCaseSensitiveChecked(int i);
	void showToolTips(const QModelIndex& index);
private:
	QIECookieViewer(const QIECookieViewer& obj);
	QIECookieViewer& operator=(const QIECookieViewer& obj);

	void createHeader();
	void createCookieModel();
	void recreateCookieModel();
	void resolveCookies(const char* fileName);
	void createDetailsView(const vector<CookieEntry>& vc);
	void transformTime(const char* low, const char* high, char* dst);
	const char* setCreator(const char* flag);
private:
	Ui::QIECookieViewerClass ui;
	QStandardItemModel* m_model;
	QSortFilterProxyModel* m_proxyModel;
};

#endif // QIECOOKIEVIEWER_H
