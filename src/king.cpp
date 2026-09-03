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
	m_type = king;
	m_moves = 0;
}

King::~King()
{

}

int
King::GetColor() const
{
	return m_color;
}

int
King::GetType() const
{
	return m_type;
}

int
King::GetMoves() const
{
	return m_moves;
}

bool
King::IsValidMove( int currentX, int currentY, int newX, int newY )
{
	return (currentX != newX || currentY != newY) &&
	       abs(currentX - newX) <= 1 && abs(currentY - newY) <= 1;
}

void
King::IncrementMoveCount()
{
	m_moves++;
}



