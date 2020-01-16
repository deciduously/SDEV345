/*
* SDEV 345 Week 1
* C++ Warm-Up
* Displays the possible chess moves for Pawn/Knight/King at locations A1 and D4
* Entry Point
* Ben Lovy
* January 16, 2020
*/

#include "MoveGenerator.hpp"

int main() {
    // Instantiate generator
    MoveGenerator mg = MoveGenerator();

    // Show default - A1
    mg.showAllMoves();

    // Set to D4
    mg.setLocation(3,3);

    // Display new moves
    std::cout << "----\n";
    mg.showAllMoves();
}