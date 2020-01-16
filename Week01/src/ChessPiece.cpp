/*
* SDEV 345 Week 1
* C++ Warm-Up
* Displays the possible chess moves for Pawn/Knight/King at locations A1 and D4
* ChessPiece implementation
* Ben Lovy
* January 16, 2020
*/

#include <iostream>
#include "ChessPiece.hpp"

ChessPiece::ChessPiece()
{
    location = BoardSquare();
}

ChessPiece::ChessPiece(BoardSquare bs)
{
    location = bs;
}

void ChessPiece::displayPossibleMoves()
{

    using std::cout;
    BoardSquare * options = possibleMoves();
    for (int i = 0; i < options_len; i++)
    {
        cout << *(options + i) << " ";
    }
    cout << "\n";
}