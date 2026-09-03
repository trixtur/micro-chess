#include <QApplication>
#include <QGridLayout>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QLocalServer>
#include <QLocalSocket>
#include <QMessageBox>
#include <QPushButton>
#include "microChess.h"
#include "../game_api.h"

namespace { constexpr auto serverName = "microchess"; }

microChess::microChess(QMainWindow *parent)
	: QMainWindow(parent)
{
	setupUi(this);	//this sets up the GUI
	setCentralWidget(new QWidget(this));
	auto *layout = new QGridLayout(centralWidget());
	layout->setSpacing(0);
	for (int row = 0; row < 8; ++row) {
		for (int column = 0; column < 8; ++column) {
			auto *button = new QPushButton(centralWidget());
			button->setMinimumSize(64, 64);
			button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
			button->setAccessibleName(QStringLiteral("square-%1-%2").arg(row).arg(column));
			m_squares[row][column] = button;
			layout->addWidget(button, row, column);
			connect(button, &QPushButton::clicked, this, [this, row, column] { handleSquare(row, column); });
		}
	}

	connect( actionE_xit, SIGNAL(triggered() ), this, SLOT(Exit()));
	connect( action_About, SIGNAL(triggered() ), this, SLOT(About()));
	connect( action_New, &QAction::triggered, this, &microChess::NewGame);
	startApiServer();
	renderBoard();

}

void microChess::startApiServer()
{
	QLocalServer::removeServer(QString::fromLatin1(serverName));
	m_apiServer = new QLocalServer(this);
	if (!m_apiServer->listen(QString::fromLatin1(serverName))) {
		qWarning() << "event=api_server_failed error=" << m_apiServer->errorString();
		return;
	}
	qInfo() << "event=api_server_listening name=" << serverName;
	connect(m_apiServer, &QLocalServer::newConnection, this, [this] {
		while (m_apiServer->hasPendingConnections()) {
			auto *socket = m_apiServer->nextPendingConnection();
			connect(socket, &QLocalSocket::readyRead, this, [this, socket] {
				while (socket->canReadLine()) {
					QJsonParseError parseError;
					const QJsonDocument request = QJsonDocument::fromJson(socket->readLine(), &parseError);
					QJsonObject response;
					if (parseError.error != QJsonParseError::NoError || !request.isObject())
						response = QJsonObject{{QStringLiteral("ok"), false}, {QStringLiteral("error"), QStringLiteral("expected one JSON object per line")}};
					else
						response = processGameCommand(m_board, request.object());
					qInfo() << "event=api_command_processed status=" << response.value(QStringLiteral("status")).toString();
					renderBoard();
					socket->write(QJsonDocument(response).toJson(QJsonDocument::Compact) + '\n');
					socket->flush();
				}
			});
			connect(socket, &QLocalSocket::disconnected, socket, &QLocalSocket::deleteLater);
		}
	});
}

void microChess::NewGame()
{
	m_board.reset();
	m_hasSelection = false;
	renderBoard();
	statusBar()->showMessage(statusText());
}

QString microChess::pieceLabel(const Pieces *piece) const
{
	if (!piece) return {};
	static const QString whitePieces[] = {QStringLiteral("♙"), QStringLiteral("♖"), QStringLiteral("♘"), {}, QStringLiteral("♕"), QStringLiteral("♔")};
	static const QString blackPieces[] = {QStringLiteral("♟"), QStringLiteral("♜"), QStringLiteral("♞"), {}, QStringLiteral("♛"), QStringLiteral("♚")};
	return (piece->GetColor() == white ? whitePieces : blackPieces)[piece->GetType()];
}

QString microChess::statusText() const
{
	switch (m_board.status()) {
	case GameStatus::WhiteWon: return tr("White wins");
	case GameStatus::BlackWon: return tr("Black wins");
	case GameStatus::Draw: return tr("Draw");
	case GameStatus::InProgress: return m_board.currentTurn() == white ? tr("White to move") : tr("Black to move");
	}
	return {};
}

void microChess::renderBoard()
{
	for (int row = 0; row < 8; ++row) {
		for (int column = 0; column < 8; ++column) {
			auto *button = m_squares[row][column];
			button->setText(pieceLabel(m_board.pieceAt({row, column})));
			button->setStyleSheet(QStringLiteral("QPushButton { background: %1; font-size: 32px; } QPushButton:pressed { background: #9ec5fe; }")
				.arg((row + column) % 2 == 0 ? QStringLiteral("#f0d9b5") : QStringLiteral("#b58863")));
			if (m_hasSelection && m_selected.row == row && m_selected.column == column)
				button->setStyleSheet(button->styleSheet() + QStringLiteral("QPushButton { border: 4px solid #2b6cb0; }"));
		}
	}
	statusBar()->showMessage(statusText());
}

void microChess::handleSquare(int row, int column)
{
	const Position clicked{row, column};
	const Pieces *piece = m_board.pieceAt(clicked);
	if (!m_hasSelection) {
		if (!piece || piece->GetColor() != m_board.currentTurn()) {
			statusBar()->showMessage(tr("Select a piece belonging to the side to move"));
			return;
		}
		m_selected = clicked;
		m_hasSelection = true;
		renderBoard();
		return;
	}
	if (clicked.row == m_selected.row && clicked.column == m_selected.column) {
		m_hasSelection = false;
		renderBoard();
		return;
	}
	if (piece && piece->GetColor() == m_board.currentTurn()) {
		m_selected = clicked;
		renderBoard();
		return;
	}
	if (!m_board.move(m_selected, clicked)) {
		statusBar()->showMessage(QString::fromStdString(m_board.lastError()));
		return;
	}
	m_hasSelection = false;
	renderBoard();
}

void microChess::About()
{
	QMessageBox::about(this, "About microChess",
			"      microChess is an Open Source project \n\tcreated by:\n"
			"  decriptor (Stephen Shaw sshaw@decriptor.com)\n"
			"    trixtur (Ben Payne trixtur@pyrous.net)\n\n"
			"   Copyright (c) 2008, Released Under GPLv2");
}

void microChess::Exit()
{
//	this->quit();
	QApplication::closeAllWindows();
}
