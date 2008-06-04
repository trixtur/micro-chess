// File:   rook.cpp
// Author: Sephen Shaw
// Created on May 12, 2008
//

#include <iostream>
#include "pieces.h"
using namespace std;


Rook::Rook( int color )
{
	m_color = color;
	m_type = pawn;
}

Rook::~Rook()
{

}

int
Rook::GetColor()	
{
	return m_color;
}

int
Rook::GetType()
{
	return m_type;
}

int
Rook::GetMoves()
{
	return m_moves;
}

void
Rook::IncrementMoveCount()
{
	m_moves++;
}

bool
Rook::IsValidMove( int currentX, int currentY, int newX, int newY )
{
	if(currentX == newX || currentY == newY)
		return true;
	return false;
}
