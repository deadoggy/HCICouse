

#include "hci.h"
#include <QtWidgets/QApplication>


#ifdef _WIN64
#pragma comment(lib,"lib/msc_x64.lib")
#else
#pragma comment(lib,"lib/msc.lib")
#endif
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	HCI w;
	//w.setWindowFlags(Qt::FramelessWindowHint);
	QObject::connect(w.getUI()->pushButton_4, SIGNAL(clicked()), &a, SLOT(quit()));
	w.show();
	return a.exec();
}
