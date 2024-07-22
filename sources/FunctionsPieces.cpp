#include <iostream>
#include <vector>
#include "ClassBoard.h"
#include "ClassPieces.h"

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

// Add all of the possible moves to a bishop's VECTORPossibleMoves
void Piece::BishopPossibleMoves(ChessBoard C) {
    Piece::Color pColor = this->color;
    // Bottom corner right
    for (int i = 1; i < 8; i++) {
        if (y + i > 7 || x + i > 7) {
            break;
        }
        if (x+i <= 7 && y+i <= 7 && C.Grid[x+i][y+i] != nullptr) {
            if (C.Grid[x + i][y + i]->color == pColor || C.Grid[x + i][y + i]->type == Piece::Type::King) {
                break;
            } else {
                VECTORPossibleMoves.push_back({this->x+i, this->y+i});
                break;
            }
        }
        else {
            VECTORPossibleMoves.push_back({this->x+i, this->y+i});
            continue;
        }
    }
    // Bottom corner left
    for (int i = 1; i < 8; i++) {
        if (y-i < 0 || x+i > 7) {
            break;
        }
        if (C.Grid[x+i][y-i] != nullptr) {
            if (C.Grid[x + i][y - i]->color == pColor || C.Grid[x + i][y - i]->type == Piece::Type::King) {
                break;
            } else {
                VECTORPossibleMoves.push_back({this->x+i, this->y-i});
                break;
            }
        }
        else {
            VECTORPossibleMoves.push_back({this->x + i, this->y - i});
            continue;
        }
    }
    // Top corner right
    for (int i = 1; i < 8; i++) {
        if (y + i > 7 || x - i < 0) {
            break;
        }
        if (C.Grid[x - i][y + i] != nullptr) {
            if (C.Grid[x - i][y + i]->color == pColor || C.Grid[x - i][y + i]->type == Piece::Type::King) {
                break;
            } else {
                VECTORPossibleMoves.push_back({this->x - i, this->y + i});
                break;
            }
        }
        else {
            VECTORPossibleMoves.push_back({this->x - i, this->y + i});
            continue;
        }
    }
    // Top corner left
    for (int i = 1; i < 8; i++) {
        if (y - i < 0 || x - i < 0) {
            break;
        }
        if (C.Grid[x - i][y - i] != nullptr) {
            if (C.Grid[x - i][y - i]->color == pColor || C.Grid[x - i][y - i]->type == Piece::Type::King) {
                break;
            } else {
                VECTORPossibleMoves.push_back({this->x - i, this->y - i});
                break;
            }
        }
        else {
            VECTORPossibleMoves.push_back({this->x - i, this->y - i});
            continue;
        }
    }
    return;
}

// Add all of the possible moves to a rook's VECTORPossibleMoves
void Piece::RookPossibleMoves(ChessBoard C) {
    Piece::Color pColor = this->color;
    // Checks in the 4 differents directions of the rook
    for (int j = 0; j != 4; j++) {
        for (int i = 1; i < 8; i++) {
            // Top line of the rook
            if (j == 0 ) {
                if (x - i < 0) {
                    break;
                }
                if (C.Grid[x-i][y] != nullptr) {
                    if (C.Grid[x - i][y]->color == pColor || C.Grid[x - i][y]->type == Piece::Type::King) {
                        break;
                    }
                    else {
                        VECTORPossibleMoves.push_back({this->x-i, this->y});
                        break;
                    }
                }
                else {
                    VECTORPossibleMoves.push_back({this->x-i, this->y});
                    continue;
                }
            }
            // Bottom line of the rook
            if (j == 1) {
                if (x + i > 7) {
                    break;
                }
                if (C.Grid[x+i][y] != nullptr) {
                    if (C.Grid[x + i][y]->color == pColor || C.Grid[x + i][y]->type == Piece::Type::King) {
                        break;
                    }
                    else {
                        VECTORPossibleMoves.push_back({this->x+i, this->y});
                        break;
                    }
                }
                else {
                    VECTORPossibleMoves.push_back({this->x+i, this->y});
                    continue;
                }
            }
            // Right line of the rook
            if (j == 2) {
                if (y + i > 7) {
                    break;
                }
                if (C.Grid[x][y+i] != nullptr) {
                    if (C.Grid[x][y+i]->color == pColor || C.Grid[x][y+i]->type == Piece::Type::King) {
                        break;
                    }
                    else {
                        VECTORPossibleMoves.push_back({this->x, this->y+i});
                        break;
                    }
                }
                else {
                    VECTORPossibleMoves.push_back({this->x, this->y+i});
                    continue;
                }
            }
            // Left line of the rook
            if (j == 3) {
                if (y - i < 0) {
                    break;
                }
                if (C.Grid[x][y-i] != nullptr) {
                    if (C.Grid[x][y-i]->color == pColor || C.Grid[x][y-i]->type == Piece::Type::King) {
                        break;
                    }
                    else {
                        VECTORPossibleMoves.push_back({this->x, this->y-i});
                        break;
                    }
                }
                else {
                    VECTORPossibleMoves.push_back({this->x, this->y-i});
                    continue;
                }
            }
        }
    }
    return;
}

// Add all of the possible moves to a knight's VECTORPossibleMoves
void Piece::KnightPossibleMoves(ChessBoard C) {
    Piece::Color pColor = this->color;
    vector<vector<int>> *ptrVECTORPossibleMoves = &VECTORPossibleMoves;
    // Bottom right corner (top)
    if (this->x + 1 <= 7 && this->y + 2 <= 7) {
        if (C.Grid[this->x + 1][this->y + 2] == nullptr || (C.Grid[this->x + 1][this->y + 2]->color != pColor &&
                                                            C.Grid[this->x + 1][this->y + 2]->type !=
                                                            Piece::Type::King)) {
            ptrVECTORPossibleMoves->push_back({this->x + 1, this->y + 2});
        }
    }
    // Bottom right corner (bottom)
    if (this->x + 2 <= 7 && this->y + 1 <= 7) {
        if (C.Grid[this->x + 2][this->y + 1] == nullptr || (C.Grid[this->x + 2][this->y + 1]->color != pColor &&
                                                            C.Grid[this->x + 2][this->y + 1]->type !=
                                                            Piece::Type::King)) {
            ptrVECTORPossibleMoves->push_back({this->x + 2, this->y + 1});
        }
    }
    // Bottom left corner (bottom)
    if (this->x + 2 <= 7 && this->y - 1 >= 0) {
        if (C.Grid[this->x + 2][this->y - 1] == nullptr || (C.Grid[this->x + 2][this->y - 1]->color != pColor &&
                                                            C.Grid[this->x + 2][this->y - 1]->type !=
                                                            Piece::Type::King)) {
            ptrVECTORPossibleMoves->push_back({this->x + 2, this->y - 1});
        }
    }
    // Bottom left corner (top)
    if (this->x + 1 <= 7 && this->y - 2 >= 0) {
        if (C.Grid[this->x + 1][this->y - 2] == nullptr || (C.Grid[this->x + 1][this->y - 2]->color != pColor &&
                                                            C.Grid[this->x + 1][this->y - 2]->type !=
                                                            Piece::Type::King)) {
            ptrVECTORPossibleMoves->push_back({this->x + 1, this->y - 2});
        }
    }
    // Top left corner (bottom)
    if (this->x - 1 >= 0 && this->y - 2 >= 0) {
        if (C.Grid[this->x - 1][this->y - 2] == nullptr || (C.Grid[this->x - 1][this->y - 2]->color != pColor &&
                                                            C.Grid[this->x - 1][this->y - 2]->type !=
                                                            Piece::Type::King)) {
            ptrVECTORPossibleMoves->push_back({this->x - 1, this->y - 2});
        }
    }
    // Top left corner (top)
    if (this->x - 2 >= 0 && this->y - 1 >= 0) {
        if (C.Grid[this->x - 2][this->y - 1] == nullptr || (C.Grid[this->x - 2][this->y - 1]->color != pColor &&
                                                            C.Grid[this->x - 2][this->y - 1]->type !=
                                                            Piece::Type::King)) {
            ptrVECTORPossibleMoves->push_back({this->x - 2, this->y - 1});
        }
    }
    // Top right corner (top)
    if (this->x - 2 >= 0 && this->y + 1 <= 7) {
        if (C.Grid[this->x - 2][this->y + 1] == nullptr || (C.Grid[this->x - 2][this->y + 1]->color != pColor &&
                                                            C.Grid[this->x - 2][this->y + 1]->type !=
                                                            Piece::Type::King)) {
            ptrVECTORPossibleMoves->push_back({this->x - 2, this->y + 1});
        }
    }
    // Top right corner (bottom)
    if (this->x - 1 >= 0 && this->y + 2 <= 7) {
        if (C.Grid[this->x - 1][this->y + 2] == nullptr || (C.Grid[this->x - 1][this->y + 2]->color != pColor &&
                                                            C.Grid[this->x - 1][this->y + 2]->type !=
                                                            Piece::Type::King)) {
            ptrVECTORPossibleMoves->push_back({this->x - 1, this->y + 2});
        }
    }
    return;
}

// Initialisation of the possible moves of a Pawn
void Piece::PawnPossibleMoves(ChessBoard C) {
    // Black pawn
    if (this->color == Piece::Color::Black) {
        if (this->x == 1) {
            if (C.Grid[this->x+1][y] == nullptr && C.Grid[this->x+2][y] == nullptr) {
                this->VECTORPossibleMoves.push_back({x+2, y});
            }
        }
        if (x+1 <= 7) {
            if (C.Grid[this->x + 1][y] == nullptr) {
                this->VECTORPossibleMoves.push_back({x + 1, y});
            }
        }
        // Eating a piece
        if (x+1 <= 7 && y+1 <= 7) {
            if (C.Grid[x + 1][y + 1] != nullptr && C.Grid[x + 1][y + 1]->type != Piece::Type::King &&
                C.Grid[x + 1][y + 1]->color == Piece::Color::White) {
                this->VECTORPossibleMoves.push_back({x + 1, y + 1});
            }
        }
        if (y-1 >= 0 && x+1 <= 7) {
            if (C.Grid[x + 1][y - 1] != nullptr && C.Grid[x + 1][y - 1]->type != Piece::Type::King &&
                C.Grid[x + 1][y - 1]->color == Piece::Color::White) {
                this->VECTORPossibleMoves.push_back({x + 1, y - 1});
            }
        }
    }
        // White pawn
    else {
        if (this->x == 6) {
            if (C.Grid[this->x-1][y] == nullptr && C.Grid[this->x-2][y] == nullptr) {
                this->VECTORPossibleMoves.push_back({x-2, y});
            }
        }
        if (x-1 >= 0) {
            if (C.Grid[this->x - 1][y] == nullptr) {
                this->VECTORPossibleMoves.push_back({x - 1, y});
            }
        }
        // Eating a piece
        if (x-1 >= 0 && y-1 >= 0) {
            if (C.Grid[x - 1][y - 1] != nullptr && C.Grid[x - 1][y - 1]->type != Piece::Type::King &&
                C.Grid[x - 1][y - 1]->color == Piece::Color::Black) {
                this->VECTORPossibleMoves.push_back({x - 1, y - 1});
            }
        }
        if (x-1 >= 0 && y+1 <= 7) {
            if (C.Grid[x - 1][y + 1] != nullptr && C.Grid[x - 1][y + 1]->type != Piece::Type::King &&
                C.Grid[x - 1][y + 1]->color == Piece::Color::Black) {
                this->VECTORPossibleMoves.push_back({x - 1, y + 1});
            }
        }
    }
    return;
}

// Initialisation of the VECTOR that tells every possible move of a piece
void Piece::initPossibleMoves(ChessBoard C) {
    this->VECTORPossibleMoves.clear();
    switch (this->type) {
        case Piece::Type::Pawn:
            this->PawnPossibleMoves(C);
            break;
        case Piece::Type::Rook:
            this->RookPossibleMoves(C);
            break;
        case Piece::Type::Bishop:
            this->BishopPossibleMoves(C);
            break;
        case Piece::Type::Queen:
            this->BishopPossibleMoves(C);
            this->RookPossibleMoves(C);
            break;
        case Piece::Type::Knight:
            this->KnightPossibleMoves(C);
            break;
        case Piece::Type::King:
            ChessBoard copyC = C.initBoardCopy();
            Player player;

            if (this->color == Piece::Color::White) {
                player = copyC.WhitePlayer;
            } else {
                player = copyC.BlackPlayer;
            }

            Piece* ptrPieceCopy = copyC.getPieceForCopy(player, this);
            // Is used to stop an operation if the opposng king is close
            bool STOP;
            for (int i = -1; i <= 1; i++) {
                for (int j = -1; j <= 1; j++) {
                    STOP = false;
                    int xi = x + i;
                    int yi = y + j;

                    // Continue if the move is out of bounds or is the current position of the king
                    if (xi < 0 || xi >= 8 || yi < 0 || yi >= 8 || (i == 0 && j == 0)) {
                        continue;
                    }

                    copyC = C.initBoardCopy();
                    ptrPieceCopy = copyC.getPieceForCopy(player, this);

                    // If the destination cell is empty or contains an opponent's piece
                    if (copyC.Grid[xi][yi] == nullptr || copyC.Grid[xi][yi]->color != ptrPieceCopy->color) {
                        copyC.doMove(ptrPieceCopy, xi, yi);

                        for (int m = -1; i <= 1; i++) {
                            for (int n = -1; j <= 1; j++) {
                                int mi = xi + m;
                                int ni = yi + n;
                                if (mi < 0 || mi >= 8 || ni < 0 || ni >= 8) {
                                    continue;
                                }
                                if ((m == 0 && n == 0) || copyC.Grid[mi][ni] == nullptr) {
                                    continue;
                                }
                                if (copyC.Grid[mi][ni]->type == Piece::Type::King) {
                                    STOP = true;
                                }
                            }
                        }
                        if (STOP) {
                            continue;
                        }
                        // Check if the king is not in check after the move
                        if (!copyC.isKingChecked(ptrPieceCopy)) {
                            this->VECTORPossibleMoves.push_back({xi, yi});
                        }
                    }
                }
            }
            break;
    }
}

// pawn promotion
void Piece::PromotePawn(ChessBoard* C) {
    string PieceChoice;
    if (this->color == Piece::Color::Black) {
        if (this->x == 7) {
            cout << "Which chess piece do you want to exchange your pawn with: " << endl;
            cout << " - Queen (Q)\n - Rook (R)\n - Bishop (B)\n - Knight (K)\n";
            cin >> PieceChoice;
            if (PieceChoice == "Q") {
                Piece* newPiece = new Piece(Type::Queen, Color::Black, 7, this->y);
                C->Grid[this->x][this->y] = newPiece;
                for (int i = 0; i < C->VECTORBlackPieces.size()-1; i++) {
                    if (C->VECTORBlackPieces[i]->x == this->x && C->VECTORBlackPieces[i]->y == this->y) {
                        C->VECTORBlackPieces.erase(C->VECTORBlackPieces.begin() + i);
                    }
                }
                C->VECTORBlackPieces.push_back(newPiece);
            }
            if (PieceChoice == "R") {
                Piece* newPiece = new Piece(Type::Rook, Color::Black, 7, this->y);
                C->Grid[this->x][this->y] = newPiece;
                for (int i = 0; i < C->VECTORBlackPieces.size()-1; i++) {
                    if (C->VECTORBlackPieces[i]->x == this->x && C->VECTORBlackPieces[i]->y == this->y) {
                        C->VECTORBlackPieces.erase(C->VECTORBlackPieces.begin() + i);
                    }
                }
                C->VECTORBlackPieces.push_back(newPiece);
            }
            if (PieceChoice == "B") {
                Piece* newPiece = new Piece(Type::Bishop, Color::Black, 7, this->y);
                C->Grid[this->x][this->y] = newPiece;
                for (int i = 0; i < C->VECTORBlackPieces.size()-1; i++) {
                    if (C->VECTORBlackPieces[i]->x == this->x && C->VECTORBlackPieces[i]->y == this->y) {
                        C->VECTORBlackPieces.erase(C->VECTORBlackPieces.begin() + i);
                    }
                }
                C->VECTORBlackPieces.push_back(newPiece);
            }
            if (PieceChoice == "K") {
                Piece* newPiece = new Piece(Type::Knight, Color::Black, 7, this->y);
                C->Grid[this->x][this->y] = newPiece;
                for (int i = 0; i < C->VECTORBlackPieces.size()-1; i++) {
                    if (C->VECTORBlackPieces[i]->x == this->x && C->VECTORBlackPieces[i]->y == this->y) {
                        C->VECTORBlackPieces.erase(C->VECTORBlackPieces.begin() + i);
                    }
                }
                C->VECTORBlackPieces.push_back(newPiece);
            }
        }
    }
    else {
        if (this->x == 0) {
            cout << "Which chess piece do you want to exchange your pawn with: " << endl;
            cout << " - Queen (Q)\n - Rook (R)\n - Bishop (B)\n - Knight (K)\n";
            cin >> PieceChoice;
            if (PieceChoice == "Q") {
                Piece* newPiece = new Piece(Type::Queen, Color::White, 0, this->y);
                C->Grid[this->x][this->y] = newPiece;
                for (int i = 0; i < C->VECTORWhitePieces.size()-1; i++) {
                    if (C->VECTORWhitePieces[i]->x == this->x && C->VECTORWhitePieces[i]->y == this->y) {
                        C->VECTORWhitePieces.erase(C->VECTORWhitePieces.begin() + i);
                    }
                }
                C->VECTORWhitePieces.push_back(newPiece);
            }
            if (PieceChoice == "R") {
                Piece* newPiece = new Piece(Type::Rook, Color::White, 0, this->y);
                C->Grid[this->x][this->y] = newPiece;
                for (int i = 0; i < C->VECTORWhitePieces.size()-1; i++) {
                    if (C->VECTORWhitePieces[i]->x == this->x && C->VECTORWhitePieces[i]->y == this->y) {
                        C->VECTORWhitePieces.erase(C->VECTORWhitePieces.begin() + i);
                    }
                }
                C->VECTORWhitePieces.push_back(newPiece);
            }
            if (PieceChoice == "B") {
                Piece* newPiece = new Piece(Type::Bishop, Color::White, 0, this->y);
                C->Grid[this->x][this->y] = newPiece;
                for (int i = 0; i < C->VECTORWhitePieces.size()-1; i++) {
                    if (C->VECTORWhitePieces[i]->x == this->x && C->VECTORWhitePieces[i]->y == this->y) {
                        C->VECTORWhitePieces.erase(C->VECTORWhitePieces.begin() + i);
                    }
                }
                C->VECTORWhitePieces.push_back(newPiece);
            }
            if (PieceChoice == "K") {
                Piece* newPiece = new Piece(Type::Knight, Color::White, 0, this->y);
                C->Grid[this->x][this->y] = newPiece;
                for (int i = 0; i < C->VECTORWhitePieces.size()-1; i++) {
                    if (C->VECTORWhitePieces[i]->x == this->x && C->VECTORWhitePieces[i]->y == this->y) {
                        C->VECTORWhitePieces.erase(C->VECTORWhitePieces.begin() + i);
                    }
                }
                C->VECTORWhitePieces.push_back(newPiece);
            }
        }
    }
    return;
}
