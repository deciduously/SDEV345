/*
* SDEV 345 Week 1
* C++ Warm-Up
* Displays the possible chess moves for Pawn/Knight/King at locations A1 and D4
* Class representing a single chessboard square
* Ben Lovy
* January 16, 2020
*/

#ifndef __BOARDSQUARE_HPP
#define __BOARDSQUARE_HPP

#include <iostream>

typedef uint8_t board_dim;

const board_dim MAX_DIM = 7;

// A BoardSquare represents a single piece on a chess board
class BoardSquare
{
    // column and row are each 0 - 7
    board_dim column;
    board_dim row;
public:
    // Default constructor returns 0,0
    BoardSquare();
    // Pass as (col,row);
    BoardSquare(board_dim, board_dim);
    // Getters for Algebraic Chess Notation output
    char get_col_ACN_char() const;
    int get_ACN_row() const;
    // get one up
    BoardSquare up() const;
    // get one down
    BoardSquare down() const;
    // get one left
    BoardSquare left() const;
    // get one right
    BoardSquare right() const;
    // Will throw if attempt to create invalid square
    class OffBoardException {
        public:
        OffBoardException() {};
    };
};

std::ostream &operator<<(std::ostream &s, const BoardSquare bs);

#endif