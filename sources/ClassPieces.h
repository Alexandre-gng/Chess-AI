#ifndef CHESSBOARD_CLASSPIECES_H
#define CHESSBOARD_CLASSPIECES_H

#include <vector>
#include <string>
#include "ClassBoard.h"


// Déclaration anticipée de la classe ChessBoard
class ChessBoard;

using namespace std;


// Class of a chess pieces
class Piece
{
public:
    enum class Type {
        Rook,
        Pawn,
        Queen,
        King,
        Bishop,
        Knight
    };
    enum class Color {
        White,
        Black
    };
    // Number of Pieces x 2
    vector<vector<int>> VECTORPossibleMoves;
    Type type;
    Color color;
    // position
    int x, y;
    // forever, i just see you again can i get a kiss

    // Constructor
    Piece(Type t, Color c, int xPos, int yPos) : type(t), color(c), x(xPos), y(yPos) {}

    // Permits to clone a Piece* in order to create a new virtual ChessBoard
    Piece* clone() const {
        Piece* newPiece = new Piece(*this);
        newPiece->VECTORPossibleMoves = this->VECTORPossibleMoves;
        newPiece->color = this->color;
        newPiece->type = this->type;
        newPiece->x = this->x;
        newPiece->y = this->y;
        return newPiece;
    }


    // Initialisation of the possible moves of a Piece generally
    void initPossibleMoves(ChessBoard);

    // Initialisation of the possible moves of a Bishop
    void BishopPossibleMoves(ChessBoard);
    // Initialisation of the possible moves of a Rook
    void RookPossibleMoves(ChessBoard);
    // Initialisation of the possible moves of a Pawn
    void PawnPossibleMoves(ChessBoard);
    // Initialisation of the possible moves of a Knight
    void KnightPossibleMoves(ChessBoard);


    // Pawn promotion detection
    void PromotePawn(ChessBoard*);

    // toString for tests
    string toString() {
        if (color == Piece::Color::Black) {
            switch (type) {
                case Piece::Type::Rook:
                    return "Rook et Black";
                    break;
                case Piece::Type::Pawn:
                    return "Pawn et Black";
                    break;
                case Piece::Type::Queen:
                    return "Queen et Black";
                    break;
                case Piece::Type::King:
                    return "King et Black";
                    break;
                case Piece::Type::Bishop:
                    return "Bishop et Black";
                    break;
                case Piece::Type::Knight:
                    return "Knight et Black";
                    break;
            }
        } else {
            switch (type) {
                case Piece::Type::Rook:
                    return "Rook et white";
                    break;
                case Piece::Type::Pawn:
                    return "Pawn et white";
                    break;
                case Piece::Type::Queen:
                    return "Queen et white";
                    break;
                case Piece::Type::King:
                    return "King et white";
                    break;
                case Piece::Type::Bishop:
                    return "Bishop et white";
                    break;
                case Piece::Type::Knight:
                    return "Knight et white";
                    break;
            }
        }
    }
};


#endif
