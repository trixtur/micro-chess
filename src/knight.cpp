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
	m_type = knight;
	m_moves = 0;
}

Knight::~Knight()
{

}

int
Knight::GetColor() const
{
	return m_color;
}

int
Knight::GetType() const
{
	return m_type;
}

int
Knight::GetMoves() const
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
	const int dx = abs(currentX - newX);
	const int dy = abs(currentY - newY);
	return (dx == 2 && dy == 1) || (dx == 1 && dy == 2);
}
