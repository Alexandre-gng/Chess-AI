#include <fstream>
#include <iostream>
#include <string>
#include <ctype.h>
#include "ClassBoard.h"

using namespace std;



/*
 * - Si pièce enemie obstrue le roque
 * - Si Tour a bougé
 * - Si Roi a bougé
 *
 * - Inscription dans le VECTORPossibleMoves (uniquement du Roi):
 *       - [-1;0] pour BigCastle
 *       - [0;-1] pour LitleCastle
 *
 * A MODIFIER:
 *      - InitMoveOnePlayer (InitPossibleMoves ?)
 *      - getCopyBoard (transfèrer les variables canBigCastle et canLitleCastle)
 *      - Vérifier que le GameState se fasse bien après la mise en place du move (pour que les échecs restent détectés)
 *      - doMove() => Ajouter le Roque si coordonnées sont [0;-1] ou [-1;0]
 *      - doMove() => Si le mouvement concerne une tour ou le roi => FINITO PIPO
 *
 *
 *
 */
// Checks if a player can castle
bool ChessBoard::canPlayerCastle(Player player) {
    if(isKingChecked(player.ptrKing) || (!player.canBigCastle && !player.canLitleCastle)) {
        return false;
    }

    if (player.color == Piece::Color::Black) {

    }
    else {

    }

}




/*

void ChessBoard::doMove(Piece* p, int x, int y) {
    if (Grid[x][y] != nullptr) {
        vector<Piece*> *ptrTEMPvectPieces;
        Piece *pieceToDelete = Grid[x][y];
        if (p->color == Piece::Color::Black) {
             ptrTEMPvectPieces = &this->VECTORBlackPieces;
        }
        else {
            ptrTEMPvectPieces =  &this->VECTORWhitePieces;
        }

        for (auto whitePiece: *ptrTEMPvectPieces) {
            if (whitePiece->x == x && whitePiece->y == y && whitePiece->type == Grid[x][y]->type) {
                pieceToDelete = whitePiece;
                auto it = std::remove(ptrTEMPvectPieces->begin(), ptrTEMPvectPieces->end(), whitePiece);
                ptrTEMPvectPieces->erase(it);
                break;
            }
        }

        ptrTEMPvectPieces = &this->WhitePlayer.VECTORPieces;
        for (auto whitePiece: *ptrTEMPvectPieces) {
            if (whitePiece == pieceToDelete) {
                auto it = std::remove(ptrTEMPvectPieces->begin(), ptrTEMPvectPieces->end(), whitePiece);
                ptrTEMPvectPieces->erase(it);
                break;
            }
        }
    }
    Grid[p->x][p->y] = nullptr;
    p->x = x;
    p->y = y;
    Grid[x][y] = p;
    return;
}

 */


/*
ChessBoard PGNtoBoard(string pathfile) {
    ChessBoard Board;
    ChessBoard* ptrBoard = &Board;

    ifstream file(pathfile);
    string line;

    if(file) {
        char TEMPFirstChar;
        // Gets all of the basic tags
        do {
            int i = 1;
            string tag;
            while (isalpha(line[i])) {
                tag+= line[i];
                i++;
            }
            if (tag == "Event") {
            }
            TEMPFirstChar = line[0];
            file >> line;
        } while (TEMPFirstChar == *"[");

        // Gets all of the moves
        if (isdigit(line[0])) {
            do {

            } while ()
        }
    }
}
*/