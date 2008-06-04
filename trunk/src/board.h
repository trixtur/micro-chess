// File:   board.h
// Author: Sephen Shaw
// Created on April 10, 2008
//

#ifndef _BOARD_H
#define	_BOARD_H

#include <vector>
#include "common.h"
#include "pieces.h"
using namespace std;

struct Square {
    bool occupied;
    int color;
    Pieces *p;
};

class ChessBoard {
public:
    ChessBoard(int x, int y);
    ~ChessBoard();
    //int addGamePiece(int piece, int x, int y, int color);
    //int addGamePieces( vector<Pieces> );

protected:
    vector< vector<Square> > *board;

private:
    int m_xMax;
    int m_yMax;
	void PrintBoard();
    void ClearBoard();
};

#endif	/* _BOARD_H */


