/*
* SDEV 345 Week 1
* C++ Warm-Up
* Displays the possible chess moves for Pawn/Knight/King at locations A1 and D4
* BoardSquare implementation
* Ben Lovy
* January 16, 2020
*/

#include "BoardSquare.hpp"

BoardSquare::BoardSquare()
{
    column = 0;
    row = 0;
}

BoardSquare::BoardSquare(board_dim c, board_dim r)
{
    if (c >= MAX_DIM || r >= MAX_DIM)
    {
        throw OffBoardException();
    }
    column = c;
    row = r;
}

char BoardSquare::get_col_ACN_char() const
{
    return static_cast<char>(column + 'A');
}

int BoardSquare::get_ACN_row() const
{
    return row + 1;
}

BoardSquare BoardSquare::up() const
{
    if (row >= MAX_DIM - 1)
        throw OffBoardException();
    else
        return BoardSquare(column, row + 1);
}

BoardSquare BoardSquare::down() const
{
    if (row == 0)
        throw OffBoardException();
    else
        return BoardSquare(column, row - 1);
}

BoardSquare BoardSquare::left() const
{
    if (column == 0)
        throw OffBoardException();
    else
        return BoardSquare(column - 1, row);
}

BoardSquare BoardSquare::right() const
{
    if (column >= MAX_DIM - 1)
        throw OffBoardException();
    else
        return BoardSquare(column + 1, row);
}

std::ostream &operator<<(std::ostream &s, const BoardSquare bs)
{
    s << bs.get_col_ACN_char() << bs.get_ACN_row();
    return s;
}