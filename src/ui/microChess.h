#ifndef MICROCHS_H
#define MICROCHS_H

#include "ui_microChess.h"
#include "../board.h"

class QPushButton;
class QLocalServer;

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
	void NewGame();

private:
	void handleSquare(int row, int column);
	void renderBoard();
	void startApiServer();
	QString pieceLabel(const Pieces *piece) const;
	QString statusText() const;

	ChessBoard m_board;
	QPushButton *m_squares[8][8]{};
	Position m_selected{-1, -1};
	bool m_hasSelection = false;
	QLocalServer *m_apiServer = nullptr;
};


#endif
