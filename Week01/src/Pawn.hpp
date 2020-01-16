/*
* SDEV 345 Week 1
* C++ Warm-Up
* Displays the possible chess moves for Pawn/Knight/King at locations A1 and D4
* Pawn implementation of ChessPiece
* Ben Lovy
* January 16, 2020
*/


#ifndef __PAWN_HPP
#define __PAWN_HPP

#include "ChessPiece.hpp"

class Pawn : public ChessPiece
{
protected:
    virtual BoardSquare *possibleMoves()
    {
        // one up, one down, one left, one right
        // check bounds
        // there's only one way - up.  No enemy detection.
        static BoardSquare ret[1];
        int current = 0;

        // try/catch each - if it throws, do nothing
        // up
        try
        {
            ret[current] = location.up();
            current++;
        }
        catch (BoardSquare::OffBoardException e)
        {
            // do nothing
        }
        options_len = current;
        return ret;
    }
public:
    Pawn(BoardSquare loc = BoardSquare()) : ChessPiece(loc) {}
};

#endif