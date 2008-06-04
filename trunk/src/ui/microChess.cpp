#include <QtGui>
#include "microChess.h"

microChess::microChess(QMainWindow *parent)
{
	setupUi(this);	//this sets up the GUI

	connect( actionE_xit, SIGNAL(triggered() ), this, SLOT(Exit()));
	connect( action_About, SIGNAL(triggered() ), this, SLOT(About()));

}

void microChess::About()
{
	QMessageBox::about(this, "About microChess",
			"      microChess is an Open Source project \n\tcreated by:\n"
			"  decriptor (Stephen Shaw sshaw@decriptor.com)\n"
			"    trixtur (Ben Payne trixtur@pyrous.net)\n\n"
			"   Copyright (c) 2008, Released Under GPLv2");
}

void microChess::Exit()
{
//	this->quit();
	QApplication::closeAllWindows();
}
