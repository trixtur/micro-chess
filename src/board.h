#ifndef BOARD_H
#define BOARD_H

#include <memory>
#include <string>
#include <vector>

#include "pieces.h"

struct Position { int row; int column; };
struct Move { Position from; Position to; };

enum class GameStatus { InProgress, WhiteWon, BlackWon, Draw };

class ChessBoard {
public:
    ChessBoard(int rows = 8, int columns = 8);
    ChessBoard(const ChessBoard &other);
    ChessBoard &operator=(const ChessBoard &other);

    bool move(Position from, Position to);
    bool isLegalMove(Position from, Position to) const;
    std::vector<Move> legalMoves(int color) const;
    void reset();
    void clearPosition();
    bool addPiece(int type, int color, Position position);
    void setTurn(int color);
    const Pieces *pieceAt(Position position) const;
    bool isInCheck(int color) const;
    bool isInside(Position position) const;
    int currentTurn() const { return m_turn; }
    GameStatus status() const { return m_status; }
    const std::string &lastError() const { return m_lastError; }

private:
    std::vector<std::vector<std::unique_ptr<Pieces>>> m_board;
    int m_rows;
    int m_columns;
    int m_turn;
    GameStatus m_status;
    std::string m_lastError;

    static std::unique_ptr<Pieces> makePiece(int type, int color);
    void copyFrom(const ChessBoard &other);
    void clearBoard();
    void place(std::unique_ptr<Pieces> piece, Position position);
    bool isPseudoLegal(Position from, Position to, bool forAttack = false) const;
    bool pathIsClear(Position from, Position to) const;
    bool applyMove(Position from, Position to);
    void updateStatus();
};

#endif
