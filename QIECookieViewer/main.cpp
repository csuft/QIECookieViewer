#include "qiecookieviewer.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	QIECookieViewer win;
	win.show();

	return app.exec();
}
