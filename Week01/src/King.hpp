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