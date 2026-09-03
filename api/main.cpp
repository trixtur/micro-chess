#include <QCoreApplication>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QLoggingCategory>
#include <QLocalSocket>
#include <QTextStream>

#include "../src/game_api.h"

namespace { constexpr auto serverName = "microchess"; }

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    QLoggingCategory loggingCategory("microchess.api");
    ChessBoard localBoard;
    QLocalSocket socket;
    socket.connectToServer(QString::fromLatin1(serverName));
    const bool connectedToApp = socket.waitForConnected(250);
    qCInfo(loggingCategory).noquote() << "event=api_mode mode=" << (connectedToApp ? "qt_app" : "standalone");

    QTextStream input(stdin);
    QTextStream output(stdout);
    QString line;
    while (input.readLineInto(&line)) {
        QJsonParseError parseError;
        const QJsonDocument document = QJsonDocument::fromJson(line.toUtf8(), &parseError);
        QJsonObject response;
        if (parseError.error != QJsonParseError::NoError || !document.isObject()) {
            response = QJsonObject{{QStringLiteral("ok"), false}, {QStringLiteral("error"), QStringLiteral("expected one JSON object per line")}};
        } else if (connectedToApp) {
            socket.write(line.toUtf8() + '\n');
            socket.flush();
            if (!socket.waitForReadyRead(5000)) {
                response = QJsonObject{{QStringLiteral("ok"), false}, {QStringLiteral("error"), QStringLiteral("Qt application did not respond")}};
            } else {
                response = QJsonDocument::fromJson(socket.readLine()).object();
            }
        } else {
            const QString command = document.object().value(QStringLiteral("command")).toString();
            qCInfo(loggingCategory).noquote() << "event=api_command command=" << command;
            response = processGameCommand(localBoard, document.object());
        }
        output << QJsonDocument(response).toJson(QJsonDocument::Compact) << Qt::endl;
    }
    return 0;
}
