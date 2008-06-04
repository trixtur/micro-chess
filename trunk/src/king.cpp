// File:   king.cpp
// Author: Sephen Shaw
// Created on May 12, 2008
//

#include <iostream>
#include "pieces.h"
using namespace std;


King::King( int color )
{
	m_color = color;
	m_type = pawn;
}

King::~King()
{

}

int
King::GetColor()	
{
	return m_color;
}

int
King::GetType()
{
	return m_type;
}

int
King::GetMoves()
{
	return m_moves;
}

bool
King::IsValidMove( int currentX, int currentY, int newX, int newY )
{
	if( abs(currentX - newX) <= 1 && abs(currentY - newY) <= 1)
		return true;
	return false;
}





