/*
* SDEV 345 Week 1
* C++ Warm-Up
* Displays the possible chess moves for Pawn/Knight/King at locations A1 and D4
* Knight implementation of ChessPiece
* Ben Lovy
* January 16, 2020
*/

#include "ChessPiece.hpp"

#ifndef __KNIGHT_HPP
#define __KNIGHT_HPP

class Knight : public ChessPiece
{
protected:
    virtual BoardSquare *possibleMoves()
    {
        // one up, one down, one left, one right
        // check bounds
        // there are at most 8 possibilities for a Knight
        static BoardSquare ret[8];
        int current = 0;

        // try/catch each - if it throws, do nothing
        // up->up->left
        try
        {
            ret[current] = location.up().up().left();
            current++;
        }
        catch (BoardSquare::OffBoardException e)
        {
            // do nothing
        }

        // up->up->right
        try
        {
            ret[current] = location.up().up().right();
            current++;
        }
        catch (BoardSquare::OffBoardException e)
        {
            // do nothing
        }

        // up->right->right
        try
        {
            ret[current] = location.up().right().right();
            current++;
        }
        catch (BoardSquare::OffBoardException e)
        {
            // do nothing
        }

        // up->left->left
        try
        {
            ret[current] = location.up().left().left();
            current++;
        }
        catch (BoardSquare::OffBoardException e)
        {
            // do nothing
        }

        // down->down->right
        try
        {
            ret[current] = location.down().down().right();
            current++;
        }
        catch (BoardSquare::OffBoardException e)
        {
            // do nothing
        }

        // down->down->left
        try
        {
            ret[current] = location.down().down().left();
            current++;
        }
        catch (BoardSquare::OffBoardException e)
        {
            // do nothing
        }

        // down->left->left
        try
        {
            ret[current] = location.down().left().left();
            current++;
        }
        catch (BoardSquare::OffBoardException e)
        {
            // do nothing
        }

        // down->right->right
        try
        {
            ret[current] = location.down().right().right();
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
    Knight(BoardSquare loc = BoardSquare()) : ChessPiece(loc) {}
};

#endif