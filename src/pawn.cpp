// File:   pawn.cpp
// Author: Sephen Shaw
// Created on May 12, 2008
//

#include <iostream>
#include "pieces.h"
using namespace std;


Pawn::Pawn( int color )
{
	m_color = color;
	m_type = pawn;
}

Pawn::~Pawn()
{
    
}

int
Pawn::GetColor()	
{
	return m_color;
}

int
Pawn::GetType()
{
	return m_type;
}

int
Pawn::GetMoves()
{
	return m_moves;
}

void
Pawn::IncrementMoveCount()
{
	m_moves++;
}

bool
Pawn::IsValidMove( int currentX, int currentY, int newX, int newY )
{
	if(currentX < newX)
		return false;
	if((currentX + 2 == newX) && (m_moves == 0)  && (currentY == newY))
		return true;
	if((currentX + 1 == newX && currentY == newY))
		return true;
	if((currentX + 1 == newX) && (abs(currentY - newY) == 1 ))
		return true;
	
	return false;	
}
