#include <cstdlib>
#include <iostream>

#include "board.h"
#include "game_api.h"
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

    ChessBoard board;
    expect(board.pieceAt({0, 0})->GetType() == rook, "white rook is placed on the board");
    expect(board.pieceAt({7, 4})->GetType() == king, "black king is placed on the board");
    expect(board.currentTurn() == white, "white starts the game");
    expect(!board.move({0, 0}, {0, 1}), "a blocked rook cannot move");
    expect(board.move({1, 4}, {3, 4}), "white pawn can move two squares initially");
    expect(board.move({6, 4}, {4, 4}), "black pawn can move two squares initially");
    expect(board.move({0, 3}, {4, 7}), "white queen can move along a clear diagonal");
    expect(board.move({6, 6}, {5, 6}), "black can make a reply move");
    expect(board.move({4, 7}, {4, 4}), "white queen can capture an opposing piece");
    expect(board.isInCheck(black), "the board detects check");
    expect(board.status() == GameStatus::InProgress, "check does not end the game by itself");

    ChessBoard checkmate;
    checkmate.clearPosition();
    expect(checkmate.addPiece(king, white, {5, 5}), "white checkmate king can be placed");
    expect(checkmate.addPiece(queen, white, {5, 6}), "white checkmate queen can be placed");
    expect(checkmate.addPiece(king, black, {7, 7}), "black checkmate king can be placed");
    expect(checkmate.move({5, 6}, {6, 6}), "white can deliver checkmate");
    expect(checkmate.status() == GameStatus::WhiteWon, "checkmate produces a white win");

    ChessBoard stalemate;
    stalemate.clearPosition();
    expect(stalemate.addPiece(king, white, {0, 0}), "white stalemate king can be placed");
    expect(stalemate.addPiece(queen, white, {6, 4}), "white stalemate queen can be placed");
    expect(stalemate.addPiece(king, black, {7, 7}), "black stalemate king can be placed");
    expect(stalemate.move({6, 4}, {6, 5}), "white can create stalemate");
    expect(stalemate.status() == GameStatus::Draw, "stalemate produces a draw");

    ChessBoard apiBoard;
    const QJsonObject apiResponse = processGameCommand(apiBoard, QJsonObject{
        {QStringLiteral("command"), QStringLiteral("move")},
        {QStringLiteral("from"), QJsonObject{{QStringLiteral("row"), 1}, {QStringLiteral("column"), 4}}},
        {QStringLiteral("to"), QJsonObject{{QStringLiteral("row"), 3}, {QStringLiteral("column"), 4}}}
    });
    expect(apiResponse.value(QStringLiteral("ok")).toBool(), "API command moves a piece");
    expect(apiBoard.pieceAt({3, 4}) != nullptr, "API command updates board state");
}
