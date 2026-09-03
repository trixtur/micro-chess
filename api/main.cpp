#include <QCoreApplication>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QLoggingCategory>
#include <QTextStream>

#include "board.h"

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

QString colorName(int color)
{
    return color == white ? QStringLiteral("white") : QStringLiteral("black");
}

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
    return QJsonObject{{QStringLiteral("turn"), colorName(board.currentTurn())},
                       {QStringLiteral("status"), statusName(board.status())},
                       {QStringLiteral("white_in_check"), board.isInCheck(white)},
                       {QStringLiteral("black_in_check"), board.isInCheck(black)},
                       {QStringLiteral("pieces"), pieces}};
}

QJsonObject error(const QString &message)
{
    return QJsonObject{{QStringLiteral("ok"), false}, {QStringLiteral("error"), message}};
}
}

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    QLoggingCategory loggingCategory("microchess.api");
    ChessBoard board;
    QTextStream input(stdin);
    QTextStream output(stdout);
    QString line;
    while (input.readLineInto(&line)) {
        QJsonParseError parseError;
        const QJsonDocument document = QJsonDocument::fromJson(line.toUtf8(), &parseError);
        QJsonObject response;
        if (parseError.error != QJsonParseError::NoError || !document.isObject()) {
            response = error(QStringLiteral("expected one JSON object per line"));
        } else {
            const QJsonObject request = document.object();
            const QString command = request.value(QStringLiteral("command")).toString();
            qCInfo(loggingCategory).noquote() << "event=api_command command=" << command;
            if (command == QStringLiteral("state")) {
                response = state(board);
                response.insert(QStringLiteral("ok"), true);
            } else if (command == QStringLiteral("reset")) {
                board.reset();
                response = state(board);
                response.insert(QStringLiteral("ok"), true);
            } else if (command == QStringLiteral("move")) {
                const QJsonObject from = request.value(QStringLiteral("from")).toObject();
                const QJsonObject to = request.value(QStringLiteral("to")).toObject();
                const Position source{from.value(QStringLiteral("row")).toInt(-1), from.value(QStringLiteral("column")).toInt(-1)};
                const Position target{to.value(QStringLiteral("row")).toInt(-1), to.value(QStringLiteral("column")).toInt(-1)};
                if (!board.move(source, target)) response = error(QString::fromStdString(board.lastError()));
                else { response = state(board); response.insert(QStringLiteral("ok"), true); }
            } else if (command == QStringLiteral("clear")) {
                board.clearPosition();
                response = state(board);
                response.insert(QStringLiteral("ok"), true);
            } else if (command == QStringLiteral("add_piece")) {
                const int type = typeValue(request.value(QStringLiteral("type")).toString());
                const int color = colorValue(request.value(QStringLiteral("color")).toString());
                const Position position{request.value(QStringLiteral("row")).toInt(-1), request.value(QStringLiteral("column")).toInt(-1)};
                if (type < 0 || color < 0 || !board.addPiece(type, color, position)) response = error(QStringLiteral("invalid or occupied piece position"));
                else { response = state(board); response.insert(QStringLiteral("ok"), true); }
            } else if (command == QStringLiteral("set_turn")) {
                const int color = colorValue(request.value(QStringLiteral("color")).toString());
                if (color < 0) response = error(QStringLiteral("color must be white or black"));
                else { board.setTurn(color); response = state(board); response.insert(QStringLiteral("ok"), true); }
            } else {
                response = error(QStringLiteral("unknown command"));
            }
        }
        output << QJsonDocument(response).toJson(QJsonDocument::Compact) << Qt::endl;
    }
    return 0;
}
