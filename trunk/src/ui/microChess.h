#ifndef MICROCHS_H
#define MICROCHS_H

#include "ui_microChess.h"

class microChess : public QMainWindow, private Ui::MainWindow
{
	Q_OBJECT

public:
	microChess(QMainWindow *parent = 0);

public slots:
	//void getPath();
	//void doSomething();
	//void clear();
	void Exit();
	void About();
};


#endif

