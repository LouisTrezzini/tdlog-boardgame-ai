#include <random>
#include <exception>

#include "Game.h"

Game::Game(int size, IPlayer* whitePlayer, IPlayer* blackPlayer)
        : gameState(Board(size), Color::BLACK),
          whitePlayer(whitePlayer),
          blackPlayer(blackPlayer)
{

    whitePlayer->setColor(Color::WHITE);
    blackPlayer->setColor(Color::BLACK);
}


const GameState& Game::getGameState() const {
    return gameState;
}

Color Game::pieceAt(int i, int j) const {
    return getGameState().getBoard().pieceAt(i, j);
}

void Game::playGame() {
    std::cout << toString() << std::endl;

    while (getWinner(gameState) == Color::EMPTY) {
        Move pickedMove = pickMove(gameState);
        playMove(pickedMove);

        std::cout << toString() << std::endl;
    }
}

void Game::playGameWithoutDisplay() {
    while (getWinner(gameState) == Color::EMPTY) {
        Move pickedMove = pickMove(gameState);
        applyMove(gameState, pickedMove);
    }
}

void Game::playGameWithoutDisplayStoringTime(std::vector<double> &timeNeededToPlay) {
    while (getWinner(gameState) == Color::EMPTY) {
        Move pickedMove = pickMoveStoringTime (gameState, timeNeededToPlay);
        applyMove(gameState, pickedMove);
    }
}

Move Game::pickMove(const GameState& gameState) const {
    Color color = gameState.getColorPlaying();

    if (color == Color::WHITE) {
        return whitePlayer->getAction(gameState);
    }
    else if (color == Color::BLACK) {
        return blackPlayer->getAction(gameState);
    }
    // TODO
    else {
        throw std::exception();
    }
}

Move Game::pickMoveStoringTime(const GameState& gameState, std::vector<double> &timeNeededToPlay) const {
    Color color = gameState.getColorPlaying();

    if (color == Color::WHITE) {
        return whitePlayer->getActionStoringTime(gameState, timeNeededToPlay);
    }
    else if (color == Color::BLACK) {
        return blackPlayer->getActionStoringTime(gameState, timeNeededToPlay);
    }
        // TODO
    else {
        throw std::exception();
    }
}


Move Game::getRandomMove(const GameState& gameState) {
    std::vector<Move> legalMoves = getLegalMoves(gameState);

//    std::random_device rd;
//    std::mt19937 gen(rd());
//    std::uniform_int_distribution<std::size_t> distrib(0, legalMoves.size() - 1);
//    return legalMoves[distrib(gen)];

    return legalMoves[rand() % legalMoves.size()];
}

bool Game::hasLegalMoves(const GameState& gameState) {
    if (gameState.getBoard().isFull())
        return false;

    for (int i = 0; i < gameState.getBoard().getSize(); i++) {
        for (int j = 0; j < gameState.getBoard().getSize(); j++) {
            Move move(i, j);

            if (isValidMove(gameState, move))
                return true;
        }
    }

    return false;
}

std::vector<Move> Game::getLegalMovesForColor(const GameState& gameState, Color color) {
    std::vector<Move> moves;

    if (gameState.getBoard().isFull())
        return moves;

    for (int i = 0; i < gameState.getBoard().getSize(); i++) {
        for (int j = 0; j < gameState.getBoard().getSize(); j++) {
            Move move(i, j);

            if (isValidMoveForColor(gameState, move, color))
                moves.push_back(move);
        }
    }

    if (moves.empty()) {
        moves.push_back(Move::passing());
    }

    return moves;
}

std::vector<Move> Game::getLegalMoves(const GameState& gameState) {
    return getLegalMovesForColor(gameState, gameState.getColorPlaying());
}


bool Game::isValidMoveForColor(const GameState& gameState, const Move& move, Color color) {
    // Cas où le mouvement est de passer
    if (move == Move::passing()) {
        return (getLegalMovesForColor(gameState, color)[0] == move);
    }

    int x = move.getX();
    int y = move.getY();

    const Board& board = gameState.getBoard();

    const Color& piece = board.pieceAt(x, y);

    if (piece != Color::EMPTY)
        return false;

    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            if (dx == 0 && dy == 0)
                continue;

            int distance = 1;
            int xp = x + distance * dx;
            int yp = y + distance * dy;

            while (board.inBounds(xp, yp) && board.pieceAt(xp, yp) == colorOpponent(color)) {
                distance++;
                xp = x + distance * dx;
                yp = y + distance * dy;
            };

            if (distance > 1 && board.inBounds(xp, yp) && board.pieceAt(xp, yp) == color) {
                return true;
            }
        }
    }

    return false;
}

bool Game::isValidMove(const GameState& gameState, const Move& move) {
    return isValidMoveForColor(gameState, move, gameState.getColorPlaying());
}

// TODO
void Game::applyMove(GameState& gameState, const Move& move) {
    Color colorPlaying = gameState.getColorPlaying();
    Color opponent = colorOpponent(colorPlaying);

    if(move.isPassing()) {
        gameState.setColorPlaying(opponent);
        return;
    }

    int x = move.getX();
    int y = move.getY();
    Board& board = gameState.getBoard();

    board.placeStoneAt(x, y, colorPlaying);

    std::vector<Move> toFlip;

    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            if (dx == 0 && dy == 0)
                continue;

            std::vector<Move> flipCandidates;

            int distance = 1;
            int xp = x + distance * dx;
            int yp = y + distance * dy;

            while (board.inBounds(xp, yp) && board.pieceAt(xp, yp) == opponent) {
                flipCandidates.emplace_back(xp, yp);
                distance++;
                xp = x + distance * dx;
                yp = y + distance * dy;
            };

            if (distance > 1 && board.inBounds(xp, yp) && board.pieceAt(xp, yp) == colorPlaying) {
                toFlip.insert(toFlip.end(), flipCandidates.begin(), flipCandidates.end());
            }
        }
    }

    for(auto it = toFlip.begin(); it != toFlip.end(); it++){
        board.flipStoneAt(it->getX(), it->getY());
    }

    gameState.setColorPlaying(opponent);
}

void Game::playMove(const Move& move) {
    std::cout << gameState.getColorPlaying() << " plays at " << move.toString() << std::endl;

    applyMove(gameState, move);
}

Color Game::getWinner(const GameState& gameState) {
    const Board& board = gameState.getBoard();

    if (board.isFull() ||
            !hasLegalMoves(GameState(board, Color::WHITE)) && !hasLegalMoves(GameState(board, Color::BLACK))
        )
    {
        if (board.getBlackStones() > board.getWhiteStones()) {
            return Color::BLACK;
        }

        // ties go to white
        else {
            return Color::WHITE;
        }
    }
    else {
        return Color::EMPTY;
    }
}


std::string Game::toString() const {
    return gameState.getBoard().toString();
}


