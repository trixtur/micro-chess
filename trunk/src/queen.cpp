// File:   queen.cpp
// Author: Sephen Shaw
// Created on May 12, 2008
//

#include <iostream>
#include "pieces.h"
using namespace std;


Queen::Queen( int color )
{
	m_color = color;
	m_type = pawn;
}

Queen::~Queen()
{

}

int
Queen::GetColor()	
{
	return m_color;
}

int
Queen::GetType()
{
	return m_type;
}

int
Queen::GetMoves()
{
	return m_moves;
}

void
Queen::IncrementMoveCount()
{
	m_moves++;
}

bool
Queen::IsValidMove( int currentX, int currentY, int newX, int newY )
{
	if((currentX == newX) || (currentY == newY))
		return true;
	if(abs(currentX - newX) == abs(currentY - newY))
		return true;
	
	return false;
}
