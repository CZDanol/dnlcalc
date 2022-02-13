#include <QApplication>

#include "gui/calcwindow.h"

int main(int argc, char *argv[]) {
	QApplication app(argc, argv);

	CalcWindow wnd;
	wnd.show();

	return app.exec();
}
