/* 
 * File:   common.h
 * Author: stephenshaw
 *
 * Created on May 19, 2008, 10:19 PM
 */

#ifndef _COMMON_H
#define	_COMMON_H

enum pieces{
    pawn = 0,
    rook,
    knight,
    bishop,
    queen,
    king
};

enum Color {
    black = 0,
    white = 1
};

#define ISPAWN(p)		(p == 0)
#define ISROOK(p)		(p == 1)
#define ISKNIGHT(p)		(p == 2)
#define ISBISHOP(p)		(p == 3)
#define ISQUEEN(p)		(p == 4)
#define ISKING(p)		(p == 5)

#endif	/* _COMMON_H */

