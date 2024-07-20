#include <iostream>
#include "ClassBoard.h"
#include "ClassPieces.h"

using namespace std;


/*
Basic values of each piece:
Pawn = 100
Knight = 320
Bishop = 330
Rook = 500
Queen = 900
King = 20000

Basic things taken in account to evaluate a position:
 - Position of each piece on the chessboard
 -

 */

// ================== EVALUATION GRID FOR WHITE ==================
// Evaluation grid for a pawn
vector<vector<int>> evPawnW = {
        {0,  0,  0,  0,  0,  0,  0,  0},
        {50, 50, 50, 50, 50, 50, 50, 50},
        {10, 10, 20, 30, 30, 20, 10, 10},
        {5,  5, 10, 25, 25, 10,  5,  5},
        {0,  0,  0, 20, 20,  0,  0,  0},
        {5, -5,-10,  0,  0,-10, -5,  5},
        {5, 10, 10,-20,-20, 10, 10,  5},
        {0,  0,  0,  0,  0,  0,  0,  0}
};

// Evaluation grid for a Bishop
vector<vector<int>> evBishopW = {
        {-20, -10, -10, -10, -10, -10, -10, -20},
        {-10, 0, 0, 0, 0, 0, 0, -10},
        {-10, 0, 5, 10, 10, 5, 0, -10},
        {-10, 5, 5, 10, 10, 5, 5, -10},
        {-10, 0, 10, 10, 10, 10, 0, -10},
        {-10, 10, 10, 10, 10, 10, 10, -10},
        {-10, 5, 0, 0, 0, 0, 5, -10},
        {-20, -10, -10, -10, -10, -10, -10, -20}
};

// Evaluation grid for a knight
vector<vector<int>> evKnightW = {
        {-50,-40,-30,-30,-30,-30,-40,-50},
        {-40,-20,  0,  0,  0,  0,-20,-40},
        {-30,  0, 10, 15, 15, 10,  0,-30},
        {-30,  5, 15, 20, 20, 15,  5,-30},
        {-30,  0, 15, 20, 20, 15,  0,-30},
        {-30,  5, 10, 15, 15, 10,  5,-30},
        {-40,-20,  0,  5,  5,  0,-20,-40},
        {-50,-40,-30,-30,-30,-30,-40,-50}
};

// Evaluation grid for a Rook
vector<vector<int>> evRookW = {
        {0,  0,  0,  0,  0,  0,  0, 0},
        {5, 10, 10, 10, 10, 10, 10, 5},
        {-5, 0,  0,  0,  0,  0,  0,-5},
        {-5, 0, 0, 0, 0, 0, 0, -5},
        {-5, 0, 0, 0, 0, 0, 0, -5},
        {-5, 0, 0, 0, 0, 0, 0, -5},
        {-5, 0, 0, 0, 0, 0, 0, -5},
        {0, 0, 0, 5, 5, 0, 0, 0}
};

// Evaluation grid for a Queen
vector<vector<int>> evQueenW = {
        {-20,-10,-10, -5, -5,-10,-10,-20},
        {-10,  0,  0,  0,  0,  0,  0,-10},
        {-10,  0,  5,  5,  5,  5,  0,-10},
        {-5,   0,  5,  5,  5,  5,  0, -5},
        {-5,   0,  5,  5,  5,  5,  0, -5},
        {-10,  5,  5,  5,  5,  5,  0,-10},
        {-10,  0,  5,  0,  0,  0,  0,-10},
        {-20,-10,-10, -5, -5,-10,-10,-20}
};

// Evaluation grid for a king middle game
vector<vector<int>> evKingWMG = {
        {-30,-40,-40,-50,-50,-40,-40,-30},
        {-30,-40,-40,-50,-50,-40,-40,-30},
        {-30,-40,-40,-50,-50,-40,-40,-30},
        {-30,-40,-40,-50,-50,-40,-40,-30},
        {-20,-30,-30,-40,-40,-30,-30,-20},
        {-10,-20,-20,-20,-20,-20,-20,-10},
        {20, 20,   0,  0,  0,  0, 20, 20},
        {20, 30,  10,  0,  0, 10, 30, 20}
};

// Evaluation grid for a king end game
vector<vector<int>> evKingWEG = {
        {-50,-40,-30,-20,-20,-30,-40,-50},
        {-30,-20,-10,  0,  0,-10,-20,-30},
        {-30,-10, 20, 30, 30, 20,-10,-30},
        {-30,-10, 30, 40, 40, 30,-10,-30},
        {-30,-10, 30, 40, 40, 30,-10,-30},
        {-30,-10, 20, 30, 30, 20,-10,-30},
        {-30,-30,  0,  0,  0,  0,-30,-30},
        {-50,-30,-30,-30,-30,-30,-30,-50}
};


// ================== EVALUATION GRID FOR BLACK ==================
// Evaluation grid for a black pawn
vector<vector<int>> evPawnB = {
        {0,  0,  0,  0,  0,  0,  0,   0},
        {5, 10, 10,-20,-20, 10, 10,   5},
        {5, -5,-10,  0,  0,-10, -5,   5},
        {0,  0,  0, 20, 20,  0,  0,   0},
        {5,  5, 10, 25, 25, 10,  5,   5},
        {10, 10, 20, 30, 30, 20, 10, 10},
        {50, 50, 50, 50, 50, 50, 50, 50},
        {0,  0,  0,  0,  0,  0,  0,   0}
};

// Evaluation grid for a black Bishop
vector<vector<int>> evBishopB = {
        {-20, -10, -10, -10, -10, -10, -10, -20},
        {-10,   5,   0,   0,   0,   0,   5, -10},
        {-10,  10,  10,  10,  10,  10,  10, -10},
        {-10,   0,  10,  10,  10,  10,   0, -10},
        {-10,   5,   5,  10,  10,   5,   5, -10},
        {-10,   0,   5,  10,  10,   5,   0, -10},
        {-10,   0,   0,   0,   0,   0,   0, -10},
        {-20, -10, -10, -10, -10, -10, -10, -20}
};

// Evaluation grid for a black knight
vector<vector<int>> evKnightB = {
        {-50,-40,-30,-30,-30,-30,-40,-50},
        {-40,-20,  0,  5,  5,  0,-20,-40},
        {-30,  5, 10, 15, 15, 10,  5,-30},
        {-30,  0, 15, 20, 20, 15,  0,-30},
        {-30,  5, 10, 15, 15, 10,  5,-30},
        {-30,  0, 15, 20, 20, 15,  0,-30},
        {-40,-20,  0,  5,  5,  0,-20,-40},
        {-50,-40,-30,-30,-30,-30,-40,-50}
};

// Evaluation grid for a Rook
vector<vector<int>> evRookB = {
        {0,  0,  0,  5,  5,  0, 0,  0},
        {-5, 0,  0,  0,  0,  0, 0, -5},
        {-5, 0,  0,  0,  0,  0, 0, -5},
        {-5, 0,  0,  0,  0,  0, 0, -5},
        {-5, 0,  0,  0,  0,  0, 0, -5},
        {-5, 0,  0,  0,  0,  0, 0, -5},
        {5, 10, 10, 10, 10, 10, 10, 5},
        {0,  0,  0,  0,  0,  0,  0, 0},
};

// Evaluation grid for a Queen
vector<vector<int>> evQueenB = {
        {-20,-10,-10, -5, -5,-10,-10,-20},
        {-10,  0,  5,  0,  0,  0,  0,-10},
        {-10,  5,  5,  5,  5,  5,  0,-10},
        {-5,   0,  5,  5,  5,  5,  0, -5},
        {-5,  0,  5,  5,  5,  5,  0, -5},
        {-10,  0,  5,  5,  5,  5,  0,-10},
        {-10,  0,  0,  0,  0,  0,  0,-10},
        {-20,-10,-10, -5, -5,-10,-10,-20}
};

// Evaluation grid for a king middle game
vector<vector<int>> evKingBMG = {
        {20,  30, 10,  0,  0, 10, 30, 20},
        {20,  20,  0,  0,  0,  0, 20, 20},
        {-10,-20,-20,-20,-20,-20,-20,-10},
        {-20,-30,-30,-40,-40,-30,-30,-20},
        {-30,-40,-40,-50,-50,-40,-40,-30},
        {-30,-40,-40,-50,-50,-40,-40,-30},
        {-30,-40,-40,-50,-50,-40,-40,-30},
        {-30,-40,-40,-50,-50,-40,-40,-30}
};

// Evaluation grid for a king end game
vector<vector<int>> evKingBEG = {
        {-50,-30,-30,-30,-30,-30,-30,-50},
        {-30,-30,  0,  0,  0,  0,-30,-30},
        {-30,-10, 20, 30, 30, 20,-10,-30},
        {-30,-10, 30, 40, 40, 30,-10,-30},
        {-30,-10, 30, 40, 40, 30,-10,-30},
        {-30,-10, 20, 30, 30, 20,-10,-30},
        {-30,-20,-10,  0,  0,-10,-20,-30},
        {-50,-40,-30,-20,-20,-30,-40,-50}
};


// Evaluation of the chessboard
int ChessBoard::evBoard() {
    this->BoardScore = 0;
    BoardScore = 0;
    int gamestate;
    for (Piece* bp : this->VECTORBlackPieces) {
        switch (bp->type) {
            case Piece::Type::Rook:
                this->BoardScore -= 500;
                this->BoardScore -= evRookB[bp->x][bp->y];
                break;
            case Piece::Type::Pawn:
                this->BoardScore -= 100;
                this->BoardScore -= evPawnB[bp->x][bp->y];
                break;
            case Piece::Type::Queen:
                this->BoardScore -= 900;
                this->BoardScore -= evQueenB[bp->x][bp->y]; // bp->y == 8 ????
                break;
            case Piece::Type::King:
                gamestate = this->GameState(bp);
                // if checkmate
                if (gamestate == 1) {
                    this->BoardScore = 50000;
                    gamestate = this->GameState(bp);
                    return 50000;
                }
                else {
                    this->BoardScore -= 20000;
                    this->BoardScore -= evKingBMG[bp->x][bp->y];
                }
                break;
            case Piece::Type::Bishop:
                this->BoardScore -= 330;
                this->BoardScore -= evBishopB[bp->x][bp->y];
                break;
            case Piece::Type::Knight:
                this->BoardScore -= 320;
                this->BoardScore -= evKnightB[bp->x][bp->y];
                break;
        }
    }
    for (Piece* wp : this->VECTORWhitePieces) {
        switch (wp->type) {
            case Piece::Type::Rook:
                this->BoardScore += 500;
                this->BoardScore += evRookW[wp->x][wp->y];
                break;
            case Piece::Type::Pawn:
                this->BoardScore += 100;
                this->BoardScore += evPawnW[wp->x][wp->y];
                break;
            case Piece::Type::Queen:
                this->BoardScore += 900;
                this->BoardScore += evQueenW[wp->x][wp->y];
                break;
            case Piece::Type::King:
                // if checkmate
                gamestate = this->GameState(wp);
                if (gamestate == -1) {
                    this->BoardScore = -50000;
                    return -50000;
                }
                else {
                    this->BoardScore += 20000;
                    this->BoardScore += evKingWMG[wp->x][wp->y];
                }
                break;
            case Piece::Type::Bishop:
                this->BoardScore += 330;
                this->BoardScore += evBishopW[wp->x][wp->y];
                break;
            case Piece::Type::Knight:
                this->BoardScore += 320;
                this->BoardScore += evKnightW[wp->x][wp->y];
                break;
        }
    }
    return this->BoardScore;
}

// Inverses the evaluations grids
vector<vector<int>> evGridInversed(vector<vector<int>> evGrid) {
    vector<int> TEMPLine;
    for (int i = 0; i<5; i++) {
        TEMPLine = evGrid[i];
        evGrid[i] = evGrid[7-i];
        evGrid[7-i] = TEMPLine;
    }
    return evGrid;
}