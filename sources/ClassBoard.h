#ifndef CHESSBOARD_CLASSBOARD_H
#define CHESSBOARD_CLASSBOARD_H

#include "ClassPieces.h"
#include "ClassPlayer.h"

using namespace std;


// ============= TEMP PRE DECLARATION ================
int MinMax(ChessBoard, int, bool, int, int, Player);
ChessBoard playMoveMinMax(ChessBoard Board, int depth, const Player& player);
void initMovesOnePlayer(ChessBoard* Board, Player *player);

class ChessBoard
{
public:
    vector<vector<Piece*>> Grid;
    vector<Piece*> VECTORWhitePieces;
    vector<Piece*> VECTORBlackPieces;
    // Score of a board position
    int BoardScore;
    // Boolean to check who is playing
    bool isWhitePlaying;
    // ID to debug
    string id;

    Player WhitePlayer;
    Player BlackPlayer;
    ChessBoard()
    {
        vector<vector<Piece*>> g(8, vector<Piece*>(8, nullptr));
    }

    // hashage or anything it should be
    string hashage();

    // ==================== COPY THINGS ====================
    // Initialisation of a ChessBoard copy
    ChessBoard initBoardCopy();
    // Gets the similar piece for a copy from the originel board
    Piece* getPieceForCopy(Player, Piece*);

    // ==================== INITIALISATION THINGS ====================
    // Initialisation of the board, set pieces
    vector<vector<Piece*>> initBoardClassical();
    // Initialisation of the board but from a vector<vector<char>> to test things
    vector<vector<Piece*>> initBoardFromVECTOR(vector<vector<char>>);
    // Textual print of the chessboard
    void printBoard();

    // ================== EVALUATION FUNCTIONS ==================
    // Evaluates a position with the grid
    int evBoard();

    // =================== MOVE FUNCTIONS ===================
    // It litteraly does the move
    void doMove(Piece*, int, int);
    // Checks in the entire board if the king is checked
    bool isKingChecked(Piece*);
    // Checks if a move will checked a king (TO DO)
    bool CheckKingSafe(Piece*, int, int);

    // =================== Checking if a king is checked ===================
    // Tells the state of the chessboard (draw, checkmate, or nothing)
    int GameState(Piece*);

    // Checks if a player can castle
    bool canPlayerCastle(Player player);
    // Checks if a rook is checking a king
    bool isRookChecking(Piece*, Piece*);
    // Checks if a bishop is checking a king
    bool isBishopChecking(Piece*, Piece*);
    // Checks if a knight is checking a king
    bool isKnightChecking(Piece*, Piece*);
    // Checks if a Pawn is checking a king
    bool isPawnChecking(Piece*, Piece*);
};


#endif //CHESSBOARD_CLASSBOARD_H