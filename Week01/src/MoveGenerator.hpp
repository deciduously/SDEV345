/*
* SDEV 345 Week 1
* C++ Warm-Up
* Displays the possible chess moves for Pawn/Knight/King at locations A1 and D4
* Demonstration driver for all the implemented pieces at a location
* Ben Lovy
* January 16, 2020
*/

#ifndef __MOVEGENERATOR_HPP
#define __MOVEGENERATOR_HPP

#include "BoardSquare.hpp"

class MoveGenerator {
    BoardSquare location;
public:
    // Default Constructor will use origin
    MoveGenerator();
    // Pass location as (col, row)
    MoveGenerator(board_dim,board_dim);
    // Demonstrate all chess pieces
    void showAllMoves() const;
    // Set a new location
    void setLocation(board_dim row, board_dim col);
};

#endif