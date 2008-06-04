// File:   pieces.h
// Author: Stephen Shaw
// Created on April 10, 2008
//

#ifndef _PIECES_H
#define	_PIECES_H

#include "common.h"


class Pieces
{
    public:
	Pieces();
	virtual ~Pieces();
	virtual bool IsValidMove( int currentX, int currentY, int newX, int newY ) = 0;
	virtual int GetMoves() = 0;
	virtual int GetType() = 0;
	virtual int GetColor() = 0;
	virtual void IncrementMoveCount() = 0;
       
    private:

};

class Pawn : virtual public Pieces
{
    public:
		Pawn( int color );
		~Pawn();
		bool IsValidMove( int currentX, int currentY, int newX, int newY );
		int GetMoves();
		int GetType();
		int GetColor();
		void IncrementMoveCount();
	
    private:
		int m_type;
		int m_moves;
		int m_color;

};

class Rook : virtual public Pieces
{   
    public:
		Rook( int color );
		~Rook();
		bool IsValidMove( int currentX, int currentY, int newX, int newY );
		int GetMoves();
		int GetType();
		int GetColor();
		void IncrementMoveCount();
	
    private:
		int m_type;
		int m_moves;
		int m_color;
	
};

class Knight : virtual public Pieces
{
    public:
		Knight( int color );
		~Knight();
		bool IsValidMove( int currentX, int currentY, int newX, int newY );
		int GetMoves();
		int GetType();
		int GetColor();
		void IncrementMoveCount();
	
    private:
		int m_type;
		int m_moves;
		int m_color;

};

class Bishop : virtual public Pieces
{
    public:
		Bishop( int color );
		~Bishop();
		bool IsValidMove( int currentX, int currentY, int newX, int newY );
		int GetMoves();
		int GetType();
		int GetColor();
		void IncrementMoveCount();
	
    private:
		int m_type;
		int m_moves;
		int m_color;
};

class Queen : virtual public Pieces
{
    public:
		Queen( int color );
		~Queen();
		bool IsValidMove( int currentX, int currentY, int newX, int newY );
		int GetMoves();
		int GetType();
		int GetColor();
		void IncrementMoveCount();
	
    private:
		int m_type;
		int m_moves;
		int m_color;

};

class King : virtual public Pieces
{
    public:
		King( int color );
		~King();
		bool IsValidMove( int currentX, int currentY, int newX, int newY );
		int GetMoves();
		int GetType();
		int GetColor();
		void IncrementMoveCount();
	
    private:
		int m_type;
		int m_moves;
		int m_color;

};

#endif	/* _PIECES_H */

