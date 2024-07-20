#ifndef CHESSBOARD_CLASSPLAYER_H
#define CHESSBOARD_CLASSPLAYER_H

#include "ClassPieces.h"

class Player {
public:
    // ptr to VECTORWhitePieces, or VECTORBlackPieces
    vector<Piece*> VECTORPieces;
    Piece::Color color;
    Piece* ptrKing;
    // number of possible moves
    int mobility;
    // Tells if a player is an AI or not
    bool isAI;
    bool canBigCastle;
    bool canLitleCastle;

    Player() {
    }
    Player(Piece::Color c) {
        color = c;
    }

    // Counts the number of possible moves (helps for evaluation)
    void initMobility() {
        this->mobility = 0;
        vector<Piece*> TEMPVECTORPieces = this->VECTORPieces;
        for (Piece* p: TEMPVECTORPieces) {
            this->mobility += p->VECTORPossibleMoves.size();
        }
        return;
    }

    string printColorPlayer() {
        if (this->color == Piece::Color::Black) {
            return "black";
        }
        else {
            return "white";
        }
        return "none";
    }
};


#endif //CHESSBOARD_CLASSPLAYER_H
