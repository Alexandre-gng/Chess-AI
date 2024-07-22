/* TO DO:
 *
 *  - Roque
 *  - En passant mdrrr
 *  - draw par répétition
 *
 *  - MCTS
 *
 *  - l56 FunctionsBoardMinMax.cpp => Non prise en charge des découvertes quand initialisaton des coups
 *
 *  - PGN to board
 *
 *  =========== FAIT ===========
 *  - Promotion d'un pion OK
 *  - Détection draw (si un des joueurs ne peut plus bouger ses pièces (Checker si
 *  toute ses pièces ont une liste de coups disponibles vide) OK
 *  - Changer le checkMove du roi pour ne pas qu'il s'approche d'un autre roi
 *      (à faire dans initPossibleMoves(), et à faire avec checkKingSafe) OK
 *  - Liste des coups possibles pour une pièce : OK
 *      - Cavalier OK
 *      - Reine OK
 *      - Roi OK
 *      - Tour OK
 *      - Fou OK
 *      - Pion OK
 *
 *  - Fonction d'évaluation (traditional hand-crafted evaluation): OK
 *      - (-20000) si roi en échec et mat OK
 *      - mobility OK
 *      - Tapered Eval OK
 *
 *  - MinMax (idéalement adapté à la classe de Node issue de MCTS)
 *
 *  - Ajouter les restrictions des moves possibles quand roi en échec
 *      (initMovesOnePlayer) OK
 *
 *  - Cycle de jeu OK
 *
 *  ============= BUGS ============
 *  El famoso avec mat rook + bishop:
 *      - Problème d'initialisation des moves de la rook OK?
 *      - Mauvaise détection du mat OK
 */

#include <iostream>
#include <vector>
#include "ClassBoard.h"
#include "ClassPlayer.h"

using namespace std;

// Classical chessboard
/*
std::vector<std::vector<char>> TESTGRID = {
        {'T', 'C', 'F', 'Q', 'R', 'F', 'C', 'T'},
        {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
        {'#', '#', '#', '#', '#', '#', '#', '#'},
        {'#', '#', '#', '#', '#', '#', '#', '#'},
        {'#', '#', '#', '#', '#', '#', '#', '#'},
        {'#', '#', '#', '#', '#', '#', '#', '#'},
        {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
        {'t', 'c', 'f', 'q', 'r', 'f', 'c', 't'}
};
*/
// QUEEN EATEN IN 2 MOVES (3)
/*
std::vector<std::vector<char>> TESTGRID = {
        {'#', '#', '#', '#', '#', '#', '#', '#'},
        {'#', '#', '#', '#', '#', '#', '#', '#'},
        {'#', '#', '#', '#', '#', '#', '#', '#'},
        {'#', '#', '#', '#', '#', '#', '#', '#'},
        {'#', '#', '#', '#', '#', '#', 'R', '#'},
        {'#', '#', '#', 'Q', '#', 'c', '#', '#'},
        {'#', '#', '#', '#', '#', '#', '#', '#'},
        {'#', '#', '#', '#', '#', '#', 'r', '#'}
};
*/

// CHECKMATE IN 2 MOVES (3)
/*
std::vector<std::vector<char>> TESTGRID = {
        {'#', 'C', '#', 'R', '#', '#', '#', '#'},
        {'#', 'P', 'P', '#', '#', 'P', 'P', 'P'},
        {'#', '#', '#', '#', '#', '#', '#', '#'},
        {'#', '#', '#', '#', 'Q', '#', '#', '#'},
        {'#', '#', '#', '#', '#', '#', '#', '#'},
        {'#', '#', '#', '#', '#', '#', '#', '#'},
        {'#', 'p', 'p', 'f', 'p', '#', '#', '#'},
        {'#', '#', 'r', 't', 'q', '#', '#', '#'}
};
*/
// CHECKMATE IN 2 MOVES (3)
/*
std::vector<std::vector<char>> TESTGRID = {
        {'#', 'P', '#', 'R', '#', '#', '#', '#'},
        {'#', 'P', 'P', '#', '#', 'P', 'P', 'P'},
        {'#', '#', '#', '#', '#', '#', '#', '#'},
        {'#', '#', '#', '#', 'Q', '#', '#', '#'},
        {'#', '#', '#', '#', '#', '#', '#', '#'},
        {'#', '#', '#', '#', '#', '#', '#', '#'},
        {'#', 'p', 'p', 'f', 'p', '#', '#', '#'},
        {'#', '#', 'r', 't', '#', '#', '#', '#'}
};
*/

// FORK IN 1 (3)
/*
std::vector<std::vector<char>> TESTGRID = {
        {'#', '#', '#', '#', '#', '#', '#', 'r'},
        {'#', '#', '#', '#', '#', '#', '#', '#'},
        {'#', '#', '#', '#', 'Q', '#', '#', '#'},
        {'#', '#', '#', '#', '#', '#', '#', 'c'},
        {'#', '#', '#', '#', '#', '#', '#', '#'},
        {'#', '#', '#', 'R', '#', '#', '#', '#'},
        {'#', '#', '#', '#', '#', '#', '#', '#'},
        {'#', '#', '#', '#', '#', '#', '#', '#'},
};
*/

//CHECKMATE IN 2 MOVES (3)
/*
std::vector<std::vector<char>> TESTGRID = {
        {'#', 'P', '#', 'R', '#', 'q', '#', '#'},
        {'#', 'P', 'P', '#', '#', '#', '#', '#'},
        {'#', '#', 'F', '#', 'c', '#', '#', '#'},
        {'#', '#', '#', 'P', 'T', 'P', '#', '#'},
        {'#', '#', '#', '#', '#', '#', '#', '#'},
        {'#', 'p', 'c', '#', '#', '#', '#', '#'},
        {'p', 'r', 'p', '#', '#', '#', '#', '#'},
        {'#', '#', '#', '#', '#', '#', '#', '#'}
};
*/
int main()
{
    cout << "PROGAM LAUCNHED " << endl;

    bool HumanPlaying;

    // Creation of the board
    ChessBoard* ptrBoard = new ChessBoard();
    vector<vector<Piece*>> Grid = ptrBoard->initBoardClassical();
    ptrBoard->Grid = Grid;

    char color;
    Piece::Color AIcolor, HUMANcolor;
    do {
        cout << "AI is playing white (w) or black (b): ";
        cin >> color;
    } while (color != 'w' && color != 'b');

    if (color == 'w') {
        AIcolor = Piece::Color::White;
        HUMANcolor = Piece::Color::Black;
    } else {
        AIcolor = Piece::Color::Black;
        HUMANcolor = Piece::Color::White;
    }

    int depth;
    do {
        cout << "What is level of search for the MinMax function: ";
        cin >> depth;
    } while (depth <= 0);

    vector<Piece*> *ptrVECTORWhitePieces, *ptrVECTORBlackPieces;
    ptrVECTORWhitePieces = &ptrBoard->VECTORWhitePieces;
    ptrVECTORBlackPieces = &ptrBoard->VECTORBlackPieces;

    // Initialisation of the two players
    Player* ptrHuman = new Player(HUMANcolor);
    Player* ptrAI = new Player(AIcolor);
    Player Human = *ptrHuman;
    Player AI = *ptrAI;


    if (HUMANcolor == Piece::Color::White) {
        for (Piece* pw: ptrBoard->VECTORWhitePieces) {
            if (pw->type == Piece::Type::King) {
                ptrHuman->ptrKing = pw;
                continue;
            }
            pw->initPossibleMoves(*ptrBoard);
        }
        for (Piece* pb: ptrBoard->VECTORBlackPieces) {
            if (pb->type == Piece::Type::King) {
                ptrAI->ptrKing = pb;
                continue;
            }
            pb->initPossibleMoves(*ptrBoard);
        }
        ptrHuman->VECTORPieces = ptrBoard->VECTORWhitePieces;
        ptrAI->VECTORPieces = ptrBoard->VECTORBlackPieces;

        ptrBoard->WhitePlayer = *ptrHuman;
        ptrBoard->BlackPlayer = *ptrAI;
        HumanPlaying = true;

    }
    else {
        for (Piece* pw: ptrBoard->VECTORBlackPieces) {
            if (pw->type == Piece::Type::King) {
                ptrHuman->ptrKing = pw;
                continue;
            }
            pw->initPossibleMoves(*ptrBoard);
        }
        for (Piece* pb: ptrBoard->VECTORWhitePieces) {
            if (pb->type == Piece::Type::King) {
                ptrAI->ptrKing = pb;
                continue;
            }
            pb->initPossibleMoves(*ptrBoard);
        }
        ptrHuman->VECTORPieces = ptrBoard->VECTORBlackPieces;
        ptrAI->VECTORPieces = ptrBoard->VECTORWhitePieces;

        ptrBoard->WhitePlayer = *ptrAI;
        ptrBoard->BlackPlayer = *ptrHuman;
        HumanPlaying = false;
    }
    ptrHuman->initMobility();
    ptrAI->initMobility();

    int loosing = 0;
    cout << "INITIAL CHESSBOARD" << endl;
    ptrBoard->printBoard();

    ChessBoard Board = *ptrBoard;
    AI = *ptrAI;
    Human = *ptrHuman;

    while (loosing == 0) {
        ptrBoard->evBoard();
        cout << "EVAL = " << ptrBoard->BoardScore << endl;
        Board = *ptrBoard;
        int x, y;
        int resGamestate;
        bool possibleMove = false;
        if (HumanPlaying) {
            do {
                cout << "HUMAN PLAYING" << endl;
                cout << "Which piece do you want to move (x): " << endl;
                cin >> x;
                cout << "Which piece do you want to move (y): " << endl;
                cin >> y;
                if (x >= 0 && x <= 7 && y >= 0 && y <= 7) {
                    if (ptrBoard->Grid[x][y] != nullptr) {
                        if (ptrBoard->Grid[x][y]->color == ptrHuman->color) {
                            Piece *ptrPieceMoving = ptrBoard->Grid[x][y];
                            cout << "Where do you want to move it (x): " << endl;
                            cin >> x;
                            cout << "Where do you want to move it (y): " << endl;
                            cin >> y;
                            // Searching if the move is possible
                            for (auto move: ptrPieceMoving->VECTORPossibleMoves) {
                                if (move[0] == x && move[1] == y) {
                                    ptrBoard->doMove(ptrPieceMoving, x, y);
                                    ptrBoard->printBoard();
                                    possibleMove = true;
                                    break;
                                }
                            }
                        }
                        else {
                            possibleMove = false;
                        }
                    }
                    else {
                        possibleMove = false;
                    }
                }
                else {
                    possibleMove = false;
                }
                HumanPlaying = false;
            } while (!possibleMove);
            if (HUMANcolor == Piece::Color::Black) {
                ptrHuman = &ptrBoard->BlackPlayer;
            }
            else {
                ptrHuman = &ptrBoard->WhitePlayer;
            }
            resGamestate = ptrBoard->GameState(ptrHuman->ptrKing);
            if ((ptrBoard->GameState(ptrHuman->ptrKing) == 1 && ptrHuman->color == Piece::Color::White) || (ptrBoard->GameState(ptrHuman->ptrKing) == -1 && ptrHuman->color == Piece::Color::Black)) {
                loosing = resGamestate;
                cout << "HUMAN WON " << endl;
            }
        }
        // BUG: MAUVAISE MISE A JOUR DE LA BOARD ENTRE CHAQUE COUP
        // BUG2: "Board = playMoveMinMax(Board, depth, *ptrAI);" => le *ptrAI ne transmet pas correctement les données (passer par une copie ?)
        else {
            cout << "AI PLAYING . . ." << endl;
            *ptrBoard = playMoveMinMax(Board, depth, *ptrAI);
            ptrBoard->printBoard();
            HumanPlaying = true;
            resGamestate = Board.GameState(ptrHuman->ptrKing);
            if ((ptrBoard->GameState(ptrAI->ptrKing) == 1 && ptrAI->color == Piece::Color::White) || (ptrBoard->GameState(ptrAI->ptrKing) == -1 && ptrAI->color == Piece::Color::Black)) {
                loosing = resGamestate;
                cout << "AI WON " << endl;
            }
            if (AIcolor == Piece::Color::Black) {
                ptrAI->ptrKing = ptrBoard->BlackPlayer.ptrKing;
                ptrAI->VECTORPieces = ptrBoard->BlackPlayer.VECTORPieces;
            }
            else {
                ptrAI->ptrKing = ptrBoard->WhitePlayer.ptrKing;
                ptrAI->VECTORPieces = ptrBoard->WhitePlayer.VECTORPieces;
            }
        }
    }
    cout << "FINALE CHESSBOARD" << endl;
    ptrBoard->printBoard();

    return 0;
}