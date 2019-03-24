#include "AlgGui.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	//QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
	QApplication a(argc, argv);
	//qDebug() << "test" << endl;	
	AlgGui w;
	w.show();
	return a.exec();
}
