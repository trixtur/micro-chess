#include "board.h"

#include <cmath>

ChessBoard::ChessBoard(int rows, int columns)
    : m_rows(rows), m_columns(columns), m_turn(white), m_status(GameStatus::InProgress)
{
    m_board.resize(m_rows);
    for (auto &row : m_board) row.resize(m_columns);
    reset();
}

ChessBoard::ChessBoard(const ChessBoard &other)
    : m_rows(other.m_rows), m_columns(other.m_columns), m_turn(other.m_turn),
      m_status(other.m_status), m_lastError(other.m_lastError)
{
    m_board.resize(m_rows);
    for (auto &row : m_board) row.resize(m_columns);
    copyFrom(other);
}

ChessBoard &ChessBoard::operator=(const ChessBoard &other)
{
    if (this != &other) {
        m_rows = other.m_rows;
        m_columns = other.m_columns;
        m_turn = other.m_turn;
        m_status = other.m_status;
        m_lastError = other.m_lastError;
        m_board.clear();
        m_board.resize(m_rows);
        for (auto &row : m_board) row.resize(m_columns);
        copyFrom(other);
    }
    return *this;
}

std::unique_ptr<Pieces> ChessBoard::makePiece(int type, int color)
{
    switch (type) {
    case pawn: return std::make_unique<Pawn>(color);
    case rook: return std::make_unique<Rook>(color);
    case knight: return std::make_unique<Knight>(color);
    case queen: return std::make_unique<Queen>(color);
    case king: return std::make_unique<King>(color);
    default: return nullptr;
    }
}

void ChessBoard::copyFrom(const ChessBoard &other)
{
    for (int row = 0; row < m_rows; ++row)
        for (int column = 0; column < m_columns; ++column) {
            const Pieces *piece = other.pieceAt({row, column});
            if (piece) {
                auto copy = makePiece(piece->GetType(), piece->GetColor());
                for (int move = 0; move < piece->GetMoves(); ++move) copy->IncrementMoveCount();
                m_board[row][column] = std::move(copy);
            }
        }
}

void ChessBoard::clearBoard()
{
    for (auto &row : m_board) for (auto &piece : row) piece.reset();
}

void ChessBoard::place(std::unique_ptr<Pieces> piece, Position position)
{
    if (isInside(position)) m_board[position.row][position.column] = std::move(piece);
}

void ChessBoard::reset()
{
    clearBoard();
    m_turn = white;
    m_status = GameStatus::InProgress;
    m_lastError.clear();

    // Bishops are omitted from the reduced setup.
    const int backRank[] = {rook, knight, -1, queen, king, -1, knight, rook};
    for (int column = 0; column < m_columns && column < 8; ++column) {
        if (backRank[column] >= 0) {
            place(makePiece(backRank[column], white), {0, column});
            place(makePiece(backRank[column], black), {m_rows - 1, column});
        }
        place(makePiece(pawn, white), {1, column});
        place(makePiece(pawn, black), {m_rows - 2, column});
    }
}

void ChessBoard::clearPosition()
{
    clearBoard();
    m_turn = white;
    m_status = GameStatus::InProgress;
    m_lastError.clear();
}

bool ChessBoard::addPiece(int type, int color, Position position)
{
    if (!isInside(position) || !makePiece(type, color) || pieceAt(position)) return false;
    place(makePiece(type, color), position);
    return true;
}

void ChessBoard::setTurn(int color)
{
    if (color == white || color == black) m_turn = color;
}

bool ChessBoard::isInside(Position position) const
{
    return position.row >= 0 && position.row < m_rows && position.column >= 0 && position.column < m_columns;
}

const Pieces *ChessBoard::pieceAt(Position position) const
{
    return isInside(position) ? m_board[position.row][position.column].get() : nullptr;
}

bool ChessBoard::pathIsClear(Position from, Position to) const
{
    const int rowStep = (to.row > from.row) - (to.row < from.row);
    const int columnStep = (to.column > from.column) - (to.column < from.column);
    Position current{from.row + rowStep, from.column + columnStep};
    while (current.row != to.row || current.column != to.column) {
        if (pieceAt(current)) return false;
        current.row += rowStep;
        current.column += columnStep;
    }
    return true;
}

bool ChessBoard::isPseudoLegal(Position from, Position to, bool forAttack) const
{
    const Pieces *piece = pieceAt(from);
    if (!piece || !isInside(to) || (from.row == to.row && from.column == to.column)) return false;
    const Pieces *target = pieceAt(to);
    if (!forAttack && target && target->GetColor() == piece->GetColor()) return false;
    if (!forAttack && target && target->GetType() == king && target->GetColor() != piece->GetColor()) return false;

    const int rowDelta = to.row - from.row;
    const int columnDelta = to.column - from.column;
    const int absRow = std::abs(rowDelta);
    const int absColumn = std::abs(columnDelta);
    switch (piece->GetType()) {
    case pawn: {
        const int direction = piece->GetColor() == white ? 1 : -1;
        if (forAttack) return rowDelta == direction && absColumn == 1;
        if (columnDelta == 0 && rowDelta == direction && !target) return true;
        if (columnDelta == 0 && rowDelta == 2 * direction && piece->GetMoves() == 0 && !target &&
            !pieceAt({from.row + direction, from.column})) return true;
        return rowDelta == direction && absColumn == 1 && target && target->GetColor() != piece->GetColor();
    }
    case rook: return (rowDelta == 0 || columnDelta == 0) && pathIsClear(from, to);
    case knight: return (absRow == 2 && absColumn == 1) || (absRow == 1 && absColumn == 2);
    case queen: return (rowDelta == 0 || columnDelta == 0 || absRow == absColumn) && pathIsClear(from, to);
    case king: return absRow <= 1 && absColumn <= 1;
    default: return false;
    }
}

bool ChessBoard::isInCheck(int color) const
{
    Position kingPosition{-1, -1};
    for (int row = 0; row < m_rows; ++row)
        for (int column = 0; column < m_columns; ++column) {
            const Pieces *piece = pieceAt({row, column});
            if (piece && piece->GetType() == king && piece->GetColor() == color)
                kingPosition = {row, column};
        }
    if (kingPosition.row < 0) return true;
    const int opponent = color == white ? black : white;
    for (int row = 0; row < m_rows; ++row)
        for (int column = 0; column < m_columns; ++column) {
            const Pieces *piece = pieceAt({row, column});
            if (piece && piece->GetColor() == opponent && isPseudoLegal({row, column}, kingPosition, true)) return true;
        }
    return false;
}

bool ChessBoard::isLegalMove(Position from, Position to) const
{
    const Pieces *piece = pieceAt(from);
    if (!piece || piece->GetColor() != m_turn || m_status != GameStatus::InProgress) return false;
    if (!isPseudoLegal(from, to)) return false;
    ChessBoard trial(*this);
    trial.applyMove(from, to);
    return !trial.isInCheck(piece->GetColor());
}

std::vector<Move> ChessBoard::legalMoves(int color) const
{
    std::vector<Move> moves;
    if (m_status != GameStatus::InProgress) return moves;
    ChessBoard position(*this);
    position.m_turn = color;
    for (int row = 0; row < m_rows; ++row)
        for (int column = 0; column < m_columns; ++column) {
            const Pieces *piece = pieceAt({row, column});
            if (!piece || piece->GetColor() != color) continue;
            for (int targetRow = 0; targetRow < m_rows; ++targetRow)
                for (int targetColumn = 0; targetColumn < m_columns; ++targetColumn)
                    if (position.isLegalMove({row, column}, {targetRow, targetColumn}))
                        moves.push_back({{row, column}, {targetRow, targetColumn}});
        }
    return moves;
}

bool ChessBoard::applyMove(Position from, Position to)
{
    auto &source = m_board[from.row][from.column];
    auto &destination = m_board[to.row][to.column];
    destination = std::move(source);
    destination->IncrementMoveCount();
    return true;
}

void ChessBoard::updateStatus()
{
    const int nextPlayer = m_turn;
    if (!legalMoves(nextPlayer).empty()) return;
    m_status = isInCheck(nextPlayer)
        ? (nextPlayer == black ? GameStatus::WhiteWon : GameStatus::BlackWon)
        : GameStatus::Draw;
}

bool ChessBoard::move(Position from, Position to)
{
    m_lastError.clear();
    if (!isInside(from) || !isInside(to)) { m_lastError = "Position is outside the board"; return false; }
    if (!pieceAt(from)) { m_lastError = "There is no piece at the source square"; return false; }
    if (!isLegalMove(from, to)) { m_lastError = "That move is not legal"; return false; }
    applyMove(from, to);
    m_turn = m_turn == white ? black : white;
    updateStatus();
    return true;
}
