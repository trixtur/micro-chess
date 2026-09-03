#include "game_api.h"

#include <QJsonArray>

namespace {
QString typeName(int type)
{
    switch (type) {
    case pawn: return QStringLiteral("pawn");
    case rook: return QStringLiteral("rook");
    case knight: return QStringLiteral("knight");
    case queen: return QStringLiteral("queen");
    case king: return QStringLiteral("king");
    default: return QStringLiteral("unknown");
    }
}
QString colorName(int color) { return color == white ? QStringLiteral("white") : QStringLiteral("black"); }
int typeValue(const QString &type)
{
    if (type == QStringLiteral("pawn")) return pawn;
    if (type == QStringLiteral("rook")) return rook;
    if (type == QStringLiteral("knight")) return knight;
    if (type == QStringLiteral("queen")) return queen;
    if (type == QStringLiteral("king")) return king;
    return -1;
}
int colorValue(const QString &color)
{
    if (color == QStringLiteral("white")) return white;
    if (color == QStringLiteral("black")) return black;
    return -1;
}
QString statusName(GameStatus status)
{
    switch (status) {
    case GameStatus::WhiteWon: return QStringLiteral("white_won");
    case GameStatus::BlackWon: return QStringLiteral("black_won");
    case GameStatus::Draw: return QStringLiteral("draw");
    case GameStatus::InProgress: return QStringLiteral("in_progress");
    }
    return QStringLiteral("unknown");
}
QJsonObject error(const QString &message)
{
    return QJsonObject{{QStringLiteral("ok"), false}, {QStringLiteral("error"), message}};
}
QJsonObject state(const ChessBoard &board)
{
    QJsonArray pieces;
    for (int row = 0; row < 8; ++row)
        for (int column = 0; column < 8; ++column)
            if (const Pieces *piece = board.pieceAt({row, column}))
                pieces.append(QJsonObject{{QStringLiteral("type"), typeName(piece->GetType())},
                                          {QStringLiteral("color"), colorName(piece->GetColor())},
                                          {QStringLiteral("row"), row},
                                          {QStringLiteral("column"), column},
                                          {QStringLiteral("moves"), piece->GetMoves()}});
    return QJsonObject{{QStringLiteral("ok"), true},
                       {QStringLiteral("turn"), colorName(board.currentTurn())},
                       {QStringLiteral("status"), statusName(board.status())},
                       {QStringLiteral("white_in_check"), board.isInCheck(white)},
                       {QStringLiteral("black_in_check"), board.isInCheck(black)},
                       {QStringLiteral("pieces"), pieces}};
}
}

QJsonObject processGameCommand(ChessBoard &board, const QJsonObject &request)
{
    const QString command = request.value(QStringLiteral("command")).toString();
    if (command == QStringLiteral("state")) return state(board);
    if (command == QStringLiteral("reset")) { board.reset(); return state(board); }
    if (command == QStringLiteral("move")) {
        const QJsonObject from = request.value(QStringLiteral("from")).toObject();
        const QJsonObject to = request.value(QStringLiteral("to")).toObject();
        const Position source{from.value(QStringLiteral("row")).toInt(-1), from.value(QStringLiteral("column")).toInt(-1)};
        const Position target{to.value(QStringLiteral("row")).toInt(-1), to.value(QStringLiteral("column")).toInt(-1)};
        if (!board.move(source, target)) return error(QString::fromStdString(board.lastError()));
        return state(board);
    }
    if (command == QStringLiteral("clear")) { board.clearPosition(); return state(board); }
    if (command == QStringLiteral("add_piece")) {
        const int type = typeValue(request.value(QStringLiteral("type")).toString());
        const int color = colorValue(request.value(QStringLiteral("color")).toString());
        const Position position{request.value(QStringLiteral("row")).toInt(-1), request.value(QStringLiteral("column")).toInt(-1)};
        if (type < 0 || color < 0 || !board.addPiece(type, color, position)) return error(QStringLiteral("invalid or occupied piece position"));
        return state(board);
    }
    if (command == QStringLiteral("set_turn")) {
        const int color = colorValue(request.value(QStringLiteral("color")).toString());
        if (color < 0) return error(QStringLiteral("color must be white or black"));
        board.setTurn(color);
        return state(board);
    }
    return error(QStringLiteral("unknown command"));
}
