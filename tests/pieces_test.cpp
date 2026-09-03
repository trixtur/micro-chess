#include <cstdlib>
#include <iostream>

#include "pieces.h"

namespace {
void expect(bool condition, const char *message)
{
    if (!condition) {
        std::cerr << "FAIL: " << message << '\n';
        std::exit(EXIT_FAILURE);
    }
}
}

int main()
{
    Pawn whitePawn(white);
    expect(whitePawn.GetType() == pawn, "pawn reports pawn type");
    expect(whitePawn.GetMoves() == 0, "pawn starts with zero moves");
    expect(whitePawn.IsValidMove(1, 1, 2, 1), "white pawn moves forward");
    whitePawn.IncrementMoveCount();
    expect(whitePawn.GetMoves() == 1, "pawn move count increments");

    Rook rookPiece(black);
    expect(rookPiece.GetType() == rook, "rook reports rook type");
    expect(rookPiece.IsValidMove(2, 2, 2, 5), "rook moves along a rank");
    expect(!rookPiece.IsValidMove(2, 2, 2, 2), "rook rejects zero-distance moves");

    Knight knightPiece(white);
    expect(knightPiece.GetType() == knight, "knight reports knight type");
    expect(knightPiece.IsValidMove(2, 2, 4, 3), "knight makes an L move");
    expect(!knightPiece.IsValidMove(2, 2, 4, 4), "knight rejects non-L moves");

    Queen queenPiece(black);
    expect(queenPiece.GetType() == queen, "queen reports queen type");
    expect(queenPiece.IsValidMove(2, 2, 5, 5), "queen moves diagonally");

    King kingPiece(white);
    expect(kingPiece.GetType() == king, "king reports king type");
    expect(kingPiece.IsValidMove(2, 2, 3, 3), "king moves one square");
    expect(!kingPiece.IsValidMove(2, 2, 2, 2), "king rejects zero-distance moves");
    kingPiece.IncrementMoveCount();
    expect(kingPiece.GetMoves() == 1, "king move count increments");
}
