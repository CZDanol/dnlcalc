#include "gui/calcwindow.h"

#include "global.h"

int main(int argc, char *argv[]) {
	QApplication app(argc, argv);

	global.init();

	CalcWindow wnd;
	wnd.show();

	return app.exec();
}
