#include "ClassBoard.h"
#include "ClassPlayer.h"
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

// Erases a possible move from a Piece->possibleMove
void eraseOneMove(vector<vector<int>>& v, vector<int>& element) {
    auto it = std::remove(v.begin(), v.end(), element);
    v.erase(it, v.end());
}


// Inits all of the possible moves for every piece of a specific player
void initMovesOnePlayer(ChessBoard* Board, Player *player) {
    vector<Piece*> TEMPVECTOR;
    ChessBoard TEMPBoard = *Board;
    if (player->color == Piece::Color::White) {
        TEMPVECTOR = Board->VECTORWhitePieces;
    }
    else {
        TEMPVECTOR = Board->VECTORBlackPieces;
    }
    // If the player's king is checked
    bool KingChecked = Board->isKingChecked(player->ptrKing);
    if (KingChecked) {
        for (Piece* p: TEMPVECTOR) {
            Piece TEMPPiece = *p;

            p->initPossibleMoves(*Board);
            vector<vector<int>> TEMPpossibleMoves = p->VECTORPossibleMoves;
            if (p->type != Piece::Type::King) {
                for (auto move: TEMPpossibleMoves) {
                    TEMPBoard.Grid = Board->Grid;
                    // Simulate the move
                    TEMPBoard.Grid[p->x][p->y] = nullptr;
                    TEMPPiece.x = move[0];
                    TEMPPiece.y = move[1];
                    TEMPBoard.Grid[move[0]][move[1]] = p;
                    // Delete the moves that are making the king checked
                    if (TEMPBoard.isKingChecked(player->ptrKing)) {
                        for (auto moveToDelete: p->VECTORPossibleMoves) {
                            if (moveToDelete[0] == move[0] && moveToDelete[1] == move[1]) {
                                eraseOneMove(p->VECTORPossibleMoves, moveToDelete);
                                break;
                            }
                        }
                    }
                }
            }
            else {
                player->ptrKing = p;
            }
        }
    }
    // If the player's king is not checked
    else {
        for (Piece* p: TEMPVECTOR) {
            p->initPossibleMoves(*Board);
            if (p->type == Piece::Type::King) {
                player->ptrKing = p;
            }
        }
    }
    return;
}

// Classic MinMax algorithm with alpha beta enhancement
int MinMax(ChessBoard B, int depth, bool MAXIMISING, int alpha, int beta, Player player) {
    // Creates a copy of the actual Board
    ChessBoard TEMPnewBoard = B.initBoardCopy();
    ChessBoard* ptrTEMPnewBoard = &TEMPnewBoard;

    Player* copyPlayer;
    Player* nextPlayer;
    if (player.color == Piece::Color::White) {
        copyPlayer = &ptrTEMPnewBoard->WhitePlayer;
        nextPlayer = &ptrTEMPnewBoard->BlackPlayer;
    } else {
        copyPlayer = &ptrTEMPnewBoard->BlackPlayer;
        nextPlayer = &ptrTEMPnewBoard->WhitePlayer;
    }

    initMovesOnePlayer(ptrTEMPnewBoard, copyPlayer);
    initMovesOnePlayer(ptrTEMPnewBoard, nextPlayer);

    int state = B.GameState(player.ptrKing);
    int eval = B.evBoard();

    // Terminal state checks
    if (state == 1) {
        return 50000 + (depth + 1) * 2;
    }
    if (state == -1) {
        return -50000 - (depth + 1) * 2;
    }
    if (state == 0 || depth == 0) {
        return eval;
    }

    if (MAXIMISING) {
        int maxEval = -50000;
        for (const auto& p : copyPlayer->VECTORPieces) {
            for (const auto& l : p->VECTORPossibleMoves) {
                int x = l[0];
                int y = l[1];

                ChessBoard newBoard = B.initBoardCopy();
                Piece* TEMPPiece = newBoard.getPieceForCopy(player, p);
                newBoard.doMove(TEMPPiece, x, y);

                eval = MinMax(newBoard, depth - 1, false, alpha, beta, *nextPlayer);
                maxEval = max(eval, maxEval);
                alpha = max(alpha, eval);

                // Beta pruning
                if (beta <= alpha) {
                    break;
                }
            }
        }
        return maxEval;
    } else {
        int minEval = 50000;
        for (const auto& p : copyPlayer->VECTORPieces) {
            for (const auto& l : p->VECTORPossibleMoves) {
                int x = l[0];
                int y = l[1];

                ChessBoard newBoard = B.initBoardCopy();
                Piece* TEMPPiece = newBoard.getPieceForCopy(player, p);
                newBoard.doMove(TEMPPiece, x, y);

                eval = MinMax(newBoard, depth - 1, true, alpha, beta, *nextPlayer);
                minEval = min(eval, minEval);
                beta = min(beta, eval);

                // Alpha pruning
                if (beta <= alpha) {
                    break;
                }
            }
        }
        return minEval;
    }
}



ChessBoard playMoveMinMax(ChessBoard Board, int depth, const Player& player) {
    Player enemyPlayer;
    bool MAXIMISING;
    if (player.color == Piece::Color::White) {
        enemyPlayer = Board.BlackPlayer;
        MAXIMISING = false;
    } else {
        enemyPlayer = Board.WhitePlayer;
        MAXIMISING = true;
    }

    int alpha = -50000;
    int beta = 50000;
    int MAXeval = -50000;
    int TEMPscore;
    ChessBoard bestBoard = Board;
    initMovesOnePlayer(&Board, &Board.BlackPlayer);
    initMovesOnePlayer(&Board, &Board.WhitePlayer);
    // BUG = MAUVAISE MISE A JOUR DES COORDONNEES DES PIECES
    for (Piece* piece : player.VECTORPieces) {
        vector<vector<int>> TEMP = piece->VECTORPossibleMoves;
        Piece* TEMPPiece;
        for (auto move : TEMP) {
            ChessBoard newBoard = Board.initBoardCopy();
            ChessBoard* ptrnewBoard = &newBoard;

            TEMPPiece = newBoard.getPieceForCopy(player, piece);

            newBoard.doMove(TEMPPiece, move[0], move[1]);
            // Update of the new enemy player with the newBoard
            if (newBoard.BlackPlayer.color == player.color) {
                enemyPlayer = newBoard.WhitePlayer;
            } else {
                enemyPlayer = newBoard.BlackPlayer;
            }
            int gameState = newBoard.GameState(enemyPlayer.ptrKing);
            if ((gameState == 1 && player.color == Piece::Color::White) ||
                (gameState == -1 && player.color == Piece::Color::Black)) {
                return newBoard;
            }
            TEMPscore = MinMax(newBoard, depth - 1, MAXIMISING, alpha, beta, enemyPlayer);
            (&newBoard)->BoardScore = TEMPscore;
            if (TEMPscore > MAXeval) {
                MAXeval = TEMPscore;
                bestBoard = newBoard;
            }
        }
    }
    return bestBoard;
}
