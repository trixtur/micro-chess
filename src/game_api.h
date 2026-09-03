#ifndef GAME_API_H
#define GAME_API_H

#include <QJsonObject>

#include "board.h"

QJsonObject processGameCommand(ChessBoard &board, const QJsonObject &request);

#endif
