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
	m_moves = 0;
}

Pawn::~Pawn()
{
    
}

int
Pawn::GetColor() const
{
	return m_color;
}

int
Pawn::GetType() const
{
	return m_type;
}

int
Pawn::GetMoves() const
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
	const int direction = m_color == white ? 1 : -1;
	const int distance = newX - currentX;
	if((distance == 2 * direction) && (m_moves == 0)  && (currentY == newY))
		return true;
	if((distance == direction && currentY == newY))
		return true;
	if((distance == direction) && (abs(currentY - newY) == 1 ))
		return true;
	
	return false;	
}
