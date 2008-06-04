// File:   knight.cpp
// Author: Sephen Shaw
// Created on May 12, 2008
//

#include <iostream>
#include "pieces.h"
using namespace std;


Knight::Knight( int color )
{
	m_color = color;
	m_type = pawn;
}

Knight::~Knight()
{

}

int
Knight::GetColor()	
{
	return m_color;
}

int
Knight::GetType()
{
	return m_type;
}

int
Knight::GetMoves()
{
	return m_moves;
}

void
Knight::IncrementMoveCount()
{
	m_moves++;
}

bool
Knight::IsValidMove( int currentX, int currentY, int newX, int newY )
{
	if(abs(currentX - newX) == 2*(abs(currentY - newY)))
		return true;
	if(2*(abs(currentX - newX)) == abs(currentY - newY))
		return true;
	
	return false;
}


