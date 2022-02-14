#include "gui/calcwindow.h"

#include "global.h"

int main(int argc, char *argv[]) {
#ifdef _WIN32
#ifndef QT_DEBUG
	if(AttachConsole(ATTACH_PARENT_PROCESS) || AllocConsole()) {
		freopen("CONOUT$", "w", stdout);
		freopen("CONOUT$", "w", stderr);
	}
#endif
#endif

	QApplication app(argc, argv);

	global.init();

	CalcWindow wnd;
	wnd.show();

	return app.exec();
}
