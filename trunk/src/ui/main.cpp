#include <QApplication>

#include "microChess.h"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	microChess *dialog = new microChess;

	dialog->show();
	return app.exec();
}
