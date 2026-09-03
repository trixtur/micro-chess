# micro-chess

`micro-chess` is a small, reduced chess environment intended as a testbed for
machine-learning experiments. Its limited board and piece rules are designed
to make gameplay and evaluation easier to inspect than full chess while still
providing meaningful move-selection problems.

The project currently contains:

- A Qt desktop application shell
- C++ piece models for pawns, rooks, knights, queens, and kings
- A small engine test program covering the implemented piece behavior
- A qmake project that builds with Qt 6

The game model is intentionally kept small. The application UI and board
controller are the next integration points for interactive play, automated
episodes, and machine-learning agents.

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

## Machine-learning direction

The intended long-term use is to provide a compact environment for training
and comparing move-selection strategies. Useful future additions include:

- A board state representation that can be serialized for training data
- Legal move generation and game termination detection
- A deterministic, non-UI game loop for self-play
- Agent and opponent interfaces
- Reproducible seeds and episode-level metrics
- Exported datasets and evaluation tooling

Keep UI code separate from the game model so agents can run quickly without a
desktop session. New rules or piece behavior should be covered by tests before
being used in training experiments.

## Continuous integration

GitHub Actions builds the Qt application and runs the engine tests for pull
requests and updates to `master`. See `.github/workflows/ci.yml`.
