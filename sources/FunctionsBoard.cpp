#include <iostream>
#include <string>
#include <algorithm>
#include "ClassBoard.h"
#include "ClassPieces.h"

using namespace std;


// ============================================== INITIALISATION GAME CYCLE FUNCTIONS ==============================================
/*
void gameCycle() {


    }

    while

    return;
}
*/

// ============================================== INITIALISATION COPY FUNCTIONS ==============================================
// Initialisation of a ChessBoard copy, used to create temporary ChessBoard
ChessBoard ChessBoard::initBoardCopy() {
    ChessBoard BoardCopy;
    ChessBoard* ptrBoardCopy = &BoardCopy;

    ptrBoardCopy->Grid = this->Grid;

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            ptrBoardCopy->Grid[i][j] = nullptr;
        }
    }

    Piece* bKing;
    Piece* wKing;
    for (auto bp: this->VECTORBlackPieces) {
        Piece* newbp = bp->clone();
        ptrBoardCopy->VECTORBlackPieces.push_back(newbp);
        ptrBoardCopy->Grid[bp->x][bp->y] = newbp;
        if (newbp->type == Piece::Type::King) {
            bKing = newbp;
        }
    }
    for (auto wp: this->VECTORWhitePieces) {
        Piece* newwp = wp->clone();
        ptrBoardCopy->VECTORWhitePieces.push_back(newwp);
        ptrBoardCopy->Grid[wp->x][wp->y] = newwp;
        if (newwp->type == Piece::Type::King) {
            wKing = newwp;
        }
    }
    Player* whitePlayer = new Player(Piece::Color::White);
    Player* blackPlayer = new Player(Piece::Color::Black);
    whitePlayer->VECTORPieces = ptrBoardCopy->VECTORWhitePieces;
    blackPlayer->VECTORPieces = ptrBoardCopy->VECTORBlackPieces;
    whitePlayer->ptrKing = wKing;
    blackPlayer->ptrKing = bKing;

    ptrBoardCopy->WhitePlayer = *whitePlayer;
    ptrBoardCopy->BlackPlayer = *blackPlayer;
    return BoardCopy;
}

// Gets a Piece* in the ChessBoard, using Player->VectorPieces and information of a specific Piece (ptrPiece)
Piece* ChessBoard::getPieceForCopy(Player originelPlayer, Piece* ptrPiece) {
    Piece* finalPiece;
    if (originelPlayer.color == Piece::Color::Black) {
        for (auto p : this->VECTORBlackPieces) {
            if (ptrPiece->x == p->x && ptrPiece->y == p->y && ptrPiece->type == p->type) {
                finalPiece = p;
                return finalPiece;
            }
        }
    } else {
        for (auto p : this->VECTORWhitePieces) {
            if (ptrPiece->x == p->x && ptrPiece->y == p->y && ptrPiece->type == p->type) {
                finalPiece = p;
                return finalPiece;
            }
        }
    }
}

// ============================================== INITIALISATION FUNCTIONS ==============================================
// Initialisation of the chessboard with the classical beggining positions
vector<vector<Piece*>> ChessBoard::initBoardClassical()
{
    vector<vector<Piece*>> g(8, vector<Piece*>(8, nullptr));

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            // black pawns
            if (i == 1) {
                Piece *p = new Piece(Piece::Type::Pawn, Piece::Color::Black, i, j);
                g[i][j] = p;
                VECTORBlackPieces.push_back(p);
                continue;
            }
            // Black rook
            if ((i == 0 && j == 7) || (i == 0 && j == 0)) {
                Piece *p = new Piece(Piece::Type::Rook, Piece::Color::Black, i, j);
                g[i][j] = p;
                VECTORBlackPieces.push_back(p);
                continue;
            }
            // Black bishop
            if ((i == 0 && j == 5) || (i == 0 && j == 2)) {
                Piece *p = new Piece(Piece::Type::Bishop, Piece::Color::Black, i, j);
                g[i][j] = p;
                VECTORBlackPieces.push_back(p);
                continue;
            }
            // Black knight
            if ((i == 0 && j == 6) || (i == 0 && j == 1)) {
                Piece *p = new Piece(Piece::Type::Knight, Piece::Color::Black, i, j);
                g[i][j] = p;
                VECTORBlackPieces.push_back(p);
                continue;
            }
            // Black Queen
            if ((i == 0 && j == 3)) {
                Piece *p = new Piece(Piece::Type::Queen, Piece::Color::Black, i, j);
                g[i][j] = p;
                VECTORBlackPieces.push_back(p);
                continue;
            }
            // Black King
            if ((i == 0 && j == 4)) {
                Piece *p = new Piece(Piece::Type::King, Piece::Color::Black, i, j);
                g[i][j] = p;
                VECTORBlackPieces.push_back(p);
                continue;
            }
            // white pawns
            if (i == 6) {
                Piece *p = new Piece(Piece::Type::Pawn, Piece::Color::White, i, j);
                g[i][j] = p;
                VECTORWhitePieces.push_back(p);
                continue;
            }
            // White rook
            if ((i == 7 && j == 7) || (i == 7 && j == 0)) {
                Piece *p = new Piece(Piece::Type::Rook, Piece::Color::White, i, j);
                g[i][j] = p;
                VECTORWhitePieces.push_back(p);
                continue;
            }
            // White bishop
            if ((i == 7 && j == 5) || (i == 7 && j == 2)) {
                Piece *p = new Piece(Piece::Type::Bishop, Piece::Color::White, i, j);
                g[i][j] = p;
                VECTORWhitePieces.push_back(p);
                continue;
            }
            // White knight
            if ((i == 7 && j == 6) || (i == 7 && j == 1)) {
                Piece *p = new Piece(Piece::Type::Knight, Piece::Color::White, i, j);
                g[i][j] = p;
                VECTORWhitePieces.push_back(p);
                continue;
            }
            // White Queen
            if ((i == 7 && j == 3)) {
                Piece *p = new Piece(Piece::Type::Queen, Piece::Color::White, i, j);
                g[i][j] = p;
                VECTORWhitePieces.push_back(p);
                continue;
            }
            // White King
            if ((i == 7 && j == 4)) {
                Piece *p = new Piece(Piece::Type::King, Piece::Color::White, i, j);
                g[i][j] = p;
                VECTORWhitePieces.push_back(p);
                continue;
            }
        }
    }
    return g;
}

// Initialises the board with a vector<vector<Piece*>>, useful for tests or to import a chess problem
vector<vector<Piece*>> ChessBoard::initBoardFromVECTOR(vector<vector<char>> c)
{
    vector<vector<Piece*>> g(8, vector<Piece*>(8, nullptr));

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (c[i][j] == '#')
            {
                g[i][j] = nullptr;
                continue;
            }
            if (c[i][j] == 'p') {
                Piece *p = new Piece(Piece::Type::Pawn, Piece::Color::White, i, j);
                g[i][j] = p;
                VECTORWhitePieces.push_back(p);
                continue;
            }
            if (c[i][j] == 'P') {
                Piece *p = new Piece(Piece::Type::Pawn, Piece::Color::Black, i, j);
                g[i][j] = p;
                VECTORBlackPieces.push_back(p);
                continue;
            }
            if (c[i][j] == 'q') {
                Piece *p = new Piece(Piece::Type::Queen, Piece::Color::White, i, j);
                g[i][j] = p;
                VECTORWhitePieces.push_back(p);
                continue;
            }
            if (c[i][j] == 'Q') {
                Piece *p = new Piece(Piece::Type::Queen, Piece::Color::Black, i, j);
                g[i][j] = p;
                VECTORBlackPieces.push_back(p);
                continue;
            }
            if (c[i][j] == 't') {
                Piece *p = new Piece(Piece::Type::Rook, Piece::Color::White, i, j);
                g[i][j] = p;
                VECTORWhitePieces.push_back(p);
                continue;
            }
            if (c[i][j] == 'T') {
                Piece *p = new Piece(Piece::Type::Rook, Piece::Color::Black, i, j);
                g[i][j] = p;
                VECTORBlackPieces.push_back(p);
                continue;
            }
            if (c[i][j] == 'r') {
                Piece *p = new Piece(Piece::Type::King, Piece::Color::White, i, j);
                g[i][j] = p;
                VECTORWhitePieces.push_back(p);
                continue;
            }
            if (c[i][j] == 'R') {
                Piece *p = new Piece(Piece::Type::King, Piece::Color::Black, i, j);
                g[i][j] = p;
                VECTORBlackPieces.push_back(p);
                continue;
            }
            if (c[i][j] == 'c') {
                Piece *p = new Piece(Piece::Type::Knight, Piece::Color::White, i, j);
                g[i][j] = p;
                VECTORWhitePieces.push_back(p);
                continue;
            }
            if (c[i][j] == 'C') {
                Piece *p = new Piece(Piece::Type::Knight, Piece::Color::Black, i, j);
                g[i][j] = p;
                VECTORBlackPieces.push_back(p);
                continue;
            }
            if (c[i][j] == 'f') {
                Piece *p = new Piece(Piece::Type::Bishop, Piece::Color::White, i, j);
                g[i][j] = p;
                VECTORWhitePieces.push_back(p);
                continue;
            }
            if (c[i][j] == 'F') {
                Piece *p = new Piece(Piece::Type::Bishop, Piece::Color::Black, i, j);
                g[i][j] = p;
                VECTORBlackPieces.push_back(p);
                continue;
            }
        }
    }
    return g;
}

// Textual print of the chessboard
void ChessBoard::printBoard() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (Grid[i][j] != nullptr && Grid[i][j]->type == Piece::Type::Rook) {
                if (Grid[i][j]->color == Piece::Color::Black) {
                    cout << "T";
                }
                else {
                    cout << "t";
                }
                continue;
            }
            if (Grid[i][j] != nullptr && Grid[i][j]->type == Piece::Type::Pawn) {
                if (Grid[i][j]->color == Piece::Color::Black) {
                    cout << "P";
                }
                else {
                    cout << "p";
                }
                continue;
            }
            if (Grid[i][j] != nullptr && Grid[i][j]->type == Piece::Type::King) {
                if (Grid[i][j]->color == Piece::Color::Black) {
                    cout << "R";
                }
                else {
                    cout << "r";
                }
                continue;
            }
            if (Grid[i][j] != nullptr && Grid[i][j]->type == Piece::Type::Knight) {
                if (Grid[i][j]->color == Piece::Color::Black) {
                    cout << "C";
                }
                else {
                    cout << "c";
                }
                continue;
            }
            if (Grid[i][j] != nullptr && Grid[i][j]->type == Piece::Type::Bishop) {
                if (Grid[i][j]->color == Piece::Color::Black) {
                    cout << "F";
                }
                else {
                    cout << "f";
                }
                continue;
            }
            if (Grid[i][j] != nullptr && Grid[i][j]->type == Piece::Type::Queen) {
                if (Grid[i][j]->color == Piece::Color::Black) {
                    cout << "Q";
                }
                else {
                    cout << "q";
                }
                continue;
            }
            if (Grid[i][j] == nullptr) {
                cout << "#";
                continue;
            }
        }
        cout << "\n";
    }
}

// ============================================== CHECKING MOVES FUNCTIONS ==============================================
// Checks if a move will checked a king
bool ChessBoard::CheckKingSafe(Piece* ptr, int x, int y) {
    Piece::Color TEMPKingColor = ptr->color;
    ChessBoard TEMPB = *this;
    Piece ptrCopy = *ptr;
    Piece* p = &ptrCopy;
    TEMPB.Grid = this->Grid;
    TEMPB.Grid[p->x][p->y] = nullptr;
    p->x = x;
    p->y = y;
    TEMPB.Grid[x][y] = p;
    if (ptr->type == Piece::Type::King) {
        if (this->Grid[x][y] != nullptr) {
            if (this->Grid[x][y]->color == TEMPKingColor) {
                return false;
            }
        }
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (x - 1 + i >= 0 && x - 1 + i < 8 && y - 1 + j >= 0 && y - 1 + j < 8 && !(i == 1 && j == 1)) {
                    int xi = x - 1 + i;
                    int yi = y - 1 + j;
                    if (TEMPB.Grid[x - 1 + i][y - 1 + j] != nullptr) {
                        if (TEMPB.Grid[x - 1 + i][y - 1 + j]->type == Piece::Type::King) {
                            return false;
                        }
                    }
                }
            }
        }
    }
    return !TEMPB.isKingChecked(p);
}


// ============================================== CHECKING CHECK FUNCTIONS ==============================================


// Checks the state of the chessboard (draw ? checkmate ? nothing ?)
// -1 = Black wins  | 0 = Draw | 1 = White victory | 100 = nothing
int ChessBoard::GameState(Piece* ptrKing) {
    int x = ptrKing->x;
    int y = ptrKing->y;
    ChessBoard boardCopy = this->initBoardCopy();
    Player playerCopy;
    Piece* COPYptrKing;

    vector<Piece*> *ptrVECTORPieces;
    vector<Piece*> *COPYptrVECTORPieces;
    if (ptrKing->color == Piece::Color::Black) {
        playerCopy = boardCopy.BlackPlayer;
        ptrVECTORPieces = &boardCopy.VECTORBlackPieces;
        COPYptrVECTORPieces = &boardCopy.VECTORBlackPieces;
    }
    else {
        playerCopy = boardCopy.WhitePlayer;
        ptrVECTORPieces = &boardCopy.VECTORWhitePieces;
        COPYptrVECTORPieces = &boardCopy.VECTORWhitePieces;
    }
    // Gets the ptrKing of boardCopy
    for (auto p: *ptrVECTORPieces) {
        if (p->type == Piece::Type::King) {
            COPYptrKing = p;
            break;
        }
    }
    // Checkmate detection
    initMovesOnePlayer(&boardCopy, &boardCopy.BlackPlayer);
    initMovesOnePlayer(&boardCopy, &boardCopy.WhitePlayer);
    if (isKingChecked(ptrKing)) {
        if (ptrKing->color == Piece::Color::Black) {
            vector<Piece*> TEMPVECTOR = *ptrVECTORPieces;
            for (const auto p: TEMPVECTOR) {
                vector<vector<int>> TEMPMOVES = p->VECTORPossibleMoves;
                for (const auto move: TEMPMOVES) {
                    boardCopy = this->initBoardCopy();
                    initMovesOnePlayer(&boardCopy, &boardCopy.BlackPlayer);
                    initMovesOnePlayer(&boardCopy, &boardCopy.WhitePlayer);
                    boardCopy.doMove(p, move[0], move[1]);
                    if (!isKingChecked(COPYptrKing)) {
                        return 100;
                    }
                }
            }
            return 1;
        }
        else {
            vector<Piece*> TEMPVECTOR = *ptrVECTORPieces;
            for (const auto p: TEMPVECTOR) {
                vector<vector<int>> TEMPMOVES = p->VECTORPossibleMoves;
                for (const auto move: TEMPMOVES) {
                    boardCopy = this->initBoardCopy();
                    boardCopy.doMove(p, move[0], move[1]);
                    if (!isKingChecked(COPYptrKing)) {
                        return 100;
                    }
                }
            }
            return -1;
        }
    }
        // Draw detection
    else {
        bool isDraw = true;
        for (auto p : *ptrVECTORPieces){
            if (!p->VECTORPossibleMoves.empty()) {
                isDraw = false;
                break;
            }
        }
        if (isDraw) {
            return 0;
        }
        else {
            return 100;
        }
    }
}

// Checks if a king p* is checked
bool ChessBoard::isKingChecked(Piece* ptrKing) {
    int x = ptrKing->x;
    int y = ptrKing->y;
    vector<Piece*> VECTORPieces;
    if (ptrKing->color == Piece::Color::White) {
        VECTORPieces = VECTORBlackPieces;
    }
    else {
        VECTORPieces = VECTORWhitePieces;
    }
    bool RES;
    for (Piece* K: VECTORPieces) {
        switch (K->type) {
            case Piece::Type::Pawn:
                RES = this->isPawnChecking(ptrKing, K);
                if (RES) {
                }
                break;
            case Piece::Type::Rook:
                RES = this->isRookChecking(ptrKing, K);
                if (RES) {
                    return true;
                }
                break;
            case Piece::Type::Queen:
                RES = this->isRookChecking(ptrKing, K);
                if (RES) {
                    return true;
                }
                else {
                    RES = this->isBishopChecking(ptrKing, K);
                    if (RES) {
                        return true;
                    }
                }
                break;
            case Piece::Type::King:
                break;
            case Piece::Type::Bishop:
                RES = this->isBishopChecking(ptrKing, K);
                if (RES) {
                    return true;
                }
                break;
            case Piece::Type::Knight:
                RES = this->isKnightChecking(ptrKing, K);
                if (RES) {
                    return true;
                }
                break;
        }
    }
    return false;
}

bool ChessBoard::isPawnChecking(Piece* ptrKing, Piece* K) {
    int x = ptrKing->x;
    int y = ptrKing->y;
    if (ptrKing->color == Piece::Color::Black) {
        if (x+1 < 7 && y+1 <= 7) {
            if (Grid[x + 1][y + 1] != nullptr) {
                if (Grid[x + 1][y + 1]->type == Piece::Type::Pawn && Grid[x + 1][y + 1]->color == Piece::Color::White) {
                    return true;
                }
            }
        }
        if (x+1 < 7 && y-1 >= 0) {
            if (Grid[x + 1][y - 1] != nullptr) {
                if (Grid[x + 1][y - 1]->type == Piece::Type::Pawn && Grid[x + 1][y - 1]->color == Piece::Color::White) {
                    return true;
                }
            }
        }
    }
    else {
        if (x-1 > 0 && y+1 <= 7) {
            if (Grid[x - 1][y + 1] != nullptr) {
                if (Grid[x - 1][y + 1]->type == Piece::Type::Pawn && Grid[x - 1][y + 1]->color == Piece::Color::Black) {
                    return true;
                }
            }
        }
        if (x-1 > 0 && y-1 >= 0) {
            if (Grid[x - 1][y - 1] != nullptr) {
                if (Grid[x - 1][y - 1]->type == Piece::Type::Pawn && Grid[x - 1][y - 1]->color == Piece::Color::Black) {
                    return true;
                }
            }
        }
    }
    return false;
}


// Checks if a knight is checking a king
bool ChessBoard::isKnightChecking(Piece* ptrKing, Piece* K) {
    int x = ptrKing->x;
    int y = ptrKing->y;
    bool TEMPchecked = true;
    // Checks if a Knight is checking a king
    if (K->type == Piece::Type::Knight) {
        if (x == K->x + 1 || x == K->x - 1 || x == K->x + 2 || x == K->x - 2) {
            if (y == K->y + 1 || y == K->y - 1 || y == K->y + 2 || y == K->y - 2) {
                if (!((y == K->y + 2 || y == K->y - 2) && (x == K->x + 2 || x == K->x - 2)) && !((y == K->y + 1 || y == K->y - 1) && (x == K->x + 1 || x == K->x - 1))) {
                    //if (!(y == K->y + 2 && x == K->x + 2) && (y == K->y + 2 && x == K->x + 2))
                    if (ptrKing->color != K->color) {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

// Checks if a bishop is checking a king
bool ChessBoard::isBishopChecking(Piece* ptrKing, Piece* K) {
    int x = ptrKing->x;
    int y = ptrKing->y;
    bool TEMPchecked = true;
    if (x < K->x) {
        if (y < K->y) {
            // Pièce dans le coin inférieur droit
            if (K->x - x == K->y - y) {
                for (int i = 0; i < 8; i++) {
                    if (y + i < 0 || x + i > 7) {
                        break;
                    }
                    if (Grid[x + i][y + i] == nullptr) {
                        continue;
                    }
                    if (K->x == x + i && K->y == y + i) {
                        break;
                    }
                    if (Grid[x + i][y + i] != ptrKing) {
                        TEMPchecked = false;
                        break;
                    }
                }
                if (TEMPchecked) {
                    return true;
                }
            }
            // Pièce dans le coin inférieur gauche
        } else {
            if (K->x - x == y - K->y) {
                for (int i = 0; i < 8; i++) {
                    if (y - i < 0 || x + i > 7) {
                        break;
                    }
                    if (Grid[x + i][y - i] == nullptr) {
                        continue;
                    }
                    if (K->x == x + i && K->y == y - i) {
                        break;
                    }
                    if (Grid[x + i][y - i] != ptrKing) {
                        TEMPchecked = false;
                        break;
                    }
                }
                if (TEMPchecked) {
                    return true;
                }
            }
        }
    } else {
        if (y < K->y) {
            // Pièce dans le coin supérieur droit
            if (x - K->x == K->y - y) {
                for (int i = 0; i < 8; i++) {
                    if (y - i < 0 || x + i > 7) {
                        break;
                    }
                    if (Grid[x - i][y + i] == nullptr) {
                        continue;
                    }
                    if (K->x == x - i && K->y == y + i) {
                        break;
                    }
                    if (Grid[x - i][y + i] != ptrKing) {
                        TEMPchecked = false;
                        break;
                    }
                }
                if (TEMPchecked) {
                    return true;
                }
            }
            // Pièce dans le coin supérieur gauche
        } else {
            if (K->x - x == K->y - y) {
                for (int i = 0; i < 8; i++) {
                    if (y - i < 0 || x - i < 0) {
                        break;
                    }
                    if (Grid[x - i][y - i] == nullptr) {
                        continue;
                    }
                    if (Grid[x - i][y - i] != ptrKing) {
                        TEMPchecked = false;
                        break;
                    }
                }
                if (TEMPchecked) {
                    return true;
                }
            }
        }
    }
    return false;
}

// Checks if a rook is checking a king
bool ChessBoard::isRookChecking(Piece* ptrKing, Piece* K) {
    int x = ptrKing->x;
    int y = ptrKing->y;
    bool TEMPchecked = true;
    if (K->x > x) {
        // Rook under the king
        if (K->y == y) {
            for (int i = 0; i < 7; i++) {
                if (x+i > 7) {
                    break;
                }
                if (Grid[x+i][y] == nullptr) {
                    continue;
                }
                if (x + i == K->x) {
                    return true;
                }
                if (Grid[x + i][y] != ptrKing) {
                    TEMPchecked = false;
                    break;
                }
            }
            if (TEMPchecked) {
                return true;
            }
        }
    }
    if (K->x < x) {
        if (K->y == y) {
            for (int i = 0; i < 7; i++) {
                if (x-i < 0) {
                    break;
                }
                if (Grid[x-i][y] == nullptr) {
                    continue;
                }
                if (x - i == K->x) {
                    return true;
                }
                if (Grid[x - i][y] != ptrKing) {
                    TEMPchecked = false;
                    break;
                }
            }
            if (TEMPchecked) {
                return true;
            }
        }
    }
    if (K->x == x) {
        if (K->y > y) {
            for (int i = 0; i < 7; i++) {
                if (y + i > 7) {
                    break;
                }
                if (Grid[x][y + i] == nullptr) {
                    continue;
                }
                if (y + i == K->y) {
                    return true;
                }
                if (Grid[x][y + i] != ptrKing) {
                    TEMPchecked = false;
                    break;
                }
            }
            if (TEMPchecked) {
                return true;
            }
        }
    }
    if (K->x == x) {
        if (K->y < y) {
            for (int i = 0; i < 7; i++) {
                if (y - i < 0) {
                    break;
                }
                if (Grid[x][y - i] == nullptr) {
                    continue;
                }
                if (y - i == K->y) {
                    return true;
                }
                if (Grid[x][y - i] != ptrKing) {
                    TEMPchecked = false;
                    break;
                }
            }
            if (TEMPchecked) {
                return true;
            }
        }
    }
    return false;
}

// It litteraly does the move
void ChessBoard::doMove(Piece* p, int x, int y) {
    if (Grid[x][y] != nullptr) {
        Piece *pieceToDelete = Grid[x][y];
        // a Piece eating another one
        if (p->color == Piece::Color::Black) {
            for (auto whitePiece: this->VECTORWhitePieces) {
                if (whitePiece->x == x && whitePiece->y == y && whitePiece->type == Grid[x][y]->type) {
                    pieceToDelete = whitePiece;
                    auto it = std::remove(this->VECTORWhitePieces.begin(), this->VECTORWhitePieces.end(), whitePiece);
                    this->VECTORWhitePieces.erase(it);
                    break;
                }
            }

            vector<Piece *> *ptrTEMPvectPieces = &this->WhitePlayer.VECTORPieces;
            for (auto whitePiece: *ptrTEMPvectPieces) {
                if (whitePiece == pieceToDelete) {
                    auto it = std::remove(ptrTEMPvectPieces->begin(), ptrTEMPvectPieces->end(), whitePiece);
                    ptrTEMPvectPieces->erase(it);
                    break;
                }
            }
        }
        if (p->color == Piece::Color::White) {
            for (auto whitePiece: this->VECTORBlackPieces) {
                if (whitePiece->x == x && whitePiece->y == y && whitePiece->type == Grid[x][y]->type) {
                    pieceToDelete = whitePiece;
                    auto it = std::remove(this->VECTORBlackPieces.begin(), this->VECTORBlackPieces.end(), whitePiece);
                    this->VECTORBlackPieces.erase(it);
                    break;
                }
            }

            vector<Piece *> *ptrTEMPvectPieces = &this->BlackPlayer.VECTORPieces;
            for (auto whitePiece: *ptrTEMPvectPieces) {
                if (whitePiece == pieceToDelete) {
                    auto it = std::remove(ptrTEMPvectPieces->begin(), ptrTEMPvectPieces->end(), whitePiece);
                    ptrTEMPvectPieces->erase(it);
                    break;
                }
            }
        }
    }
    Grid[p->x][p->y] = nullptr;
    p->x = x;
    p->y = y;
    Grid[x][y] = p;
    return;
}

// Create a hash of a chessBoard
string ChessBoard::hashage() {
    ChessBoard B = *this;
    string hash;
    int numLigne = 0;
    int numCol = 0;
    for (auto ligne: B.Grid) {
        numLigne++;
        numCol = 0;
        for (auto piece: ligne) {
            numCol++;
            if (piece == nullptr) {
                hash += to_string(numLigne % 3);
                hash += "y";
                continue;
            }
            switch (piece->type) {
                case Piece::Type::King:
                    hash += to_string(1*numLigne);
                    hash += to_string(numCol*numLigne);
                    hash += "a";
                    break;
                case Piece::Type::Rook:
                    hash += to_string(2*numLigne);
                    hash += to_string(numCol*numLigne);
                    hash += "b";
                    break;
                case Piece::Type::Pawn:
                    hash += to_string(3*numLigne);
                    hash += to_string(numCol*numLigne);
                    hash += "c";
                    break;
                case Piece::Type::Queen:
                    hash += to_string(4*numLigne);
                    hash += to_string(numCol*numLigne);
                    hash += "d";
                    break;
                case Piece::Type::Bishop:
                    hash += to_string(5*numLigne);
                    hash += to_string(numCol*numLigne);
                    hash += "e";
                    break;
                case Piece::Type::Knight:
                    hash += to_string(6*numLigne);
                    hash += to_string(numCol*numLigne);
                    hash += "f";
                    break;
            }
        }
    }
    this->id = hash;
    return hash;
}

