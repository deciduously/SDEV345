/*
* SDEV 345 Week 1
* C++ Warm-Up
* Displays the possible chess moves for Pawn/Knight/King at locations A1 and D4
* Knight implementation of ChessPiece
* Ben Lovy
* January 16, 2020
*/


#ifndef __KING_HPP
#define __KING_HPP

#include "ChessPiece.hpp"

class King : public ChessPiece
{
protected:
    virtual BoardSquare *possibleMoves()
    {
        // one up, one down, one left, one right
        // check bounds
        // there are at most 4 possibilities for a pawn
        static BoardSquare ret[4];
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

        // down
        try
        {
            ret[current] = location.down();
            current++;
        }
        catch (BoardSquare::OffBoardException e)
        {
            // do nothing
        }

        // left
        try
        {
            ret[current] = location.left();
            current++;
        }
        catch (BoardSquare::OffBoardException e)
        {
            // do nothing
        }

        // right
        try
        {
            ret[current] = location.right();
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
    King(BoardSquare loc = BoardSquare()) : ChessPiece(loc) {}
};

#endif