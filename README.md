# micro-chess

`micro-chess` is a small, reduced chess environment intended as a testbed for
machine-learning experiments. Its limited board and piece rules are designed
to make gameplay and evaluation easier to inspect than full chess while still
providing meaningful move-selection problems.

The project currently contains:

- A playable Qt desktop application
- C++ piece models for pawns, rooks, knights, queens, and kings
- A playable 8x8 board using pawns, rooks, knights, queens, and kings
- Turn handling, captures, check, checkmate, and stalemate draws
- A small engine test program covering the implemented piece behavior
- A qmake project that builds with Qt 6

The game model is intentionally kept small. Bishops, castling, en passant,
and promotion are not part of this variant. The board controller is usable
from both the interactive application and automated machine-learning episodes.

## Build the application

The application requires Qt 6 with `qmake6` and a C++17 compiler.

```sh
mkdir -p build-app
qmake6 src/ui/microChess.pro -o build-app/Makefile
make -C build-app
```

On macOS, the application is produced at:

```text
build-app/microChess.app
```

## Run the engine tests

```sh
mkdir -p build-tests
qmake6 tests/pieces_test.pro -o build-tests/Makefile
make -C build-tests
build-tests/pieces_test
```

## External control API

`api/microchess_api.pro` builds a JSON-lines process for agents and other
programs. Start it, then send one JSON command per line on standard input.
Each command returns one JSON object on standard output.

```sh
mkdir -p build-api
qmake6 api/microchess_api.pro -o build-api/Makefile
make -C build-api
printf '%s\n' '{"command":"state"}' \
  '{"command":"move","from":{"row":1,"column":4},"to":{"row":3,"column":4}}' \
  | build-api/microchess_api
```

Supported commands are `state`, `reset`, `clear`, `move`, `add_piece`, and
`set_turn`. `clear` plus `add_piece` makes deterministic positions available
to training harnesses and evaluation programs. A state includes the turn,
game status, check flags, and every piece with its position and move count.

## Machine-learning direction

The intended long-term use is to provide a compact environment for training
and comparing move-selection strategies. Useful future additions include:

- A board state representation that can be serialized for training data
- Agent and opponent interfaces built on the external control API
- Agent and opponent interfaces
- Reproducible seeds and episode-level metrics
- Exported datasets and evaluation tooling

Keep UI code separate from the game model so agents can run quickly without a
desktop session. New rules or piece behavior should be covered by tests before
being used in training experiments.

## Continuous integration

GitHub Actions builds the Qt application and runs the engine tests for pull
requests and updates to `master`. See `.github/workflows/ci.yml`.
