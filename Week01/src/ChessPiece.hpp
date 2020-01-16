/*
* SDEV 345 Week 1
* C++ Warm-Up
* Displays the possible chess moves for Pawn/Knight/King at locations A1 and D4
* ChessPiece abstract class
* Ben Lovy
* January 16, 2020
*/

#ifndef __CHESSPIECE_HPP
#define __CHESSPIECE_HPP

#include "BoardSquare.hpp"

class ChessPiece
{
protected:
    int options_len;
    BoardSquare location;
    virtual BoardSquare *possibleMoves() = 0;

public:
    ChessPiece();
    ChessPiece(BoardSquare);
    void displayPossibleMoves();
};

#endif