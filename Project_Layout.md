This page contains a project overview layout of MicroChess.

# Introduction #

MicroChess -- is a project that makes an attempt to simplify the process of a dynamic modular gaming system (mostly for chess). Initial objectives are to be able to call specific setups in terms of pieces an board size, and build external controllers onto them (in other words an AI).

Game Driver -- does not necessarily need to be chess. One should be able to define pieces and specify their moves within the piece object, then write a chess engine that can snap into the Application Layer.


# Details #

Layout

|Application Layer| | |
|:----------------|:|:|
|**Game Driver**| | |
|UI|Board|Pieces|