#include "MoveGenerator.hpp"

#include "King.hpp"
#include "Knight.hpp"
#include "Pawn.hpp"

MoveGenerator::MoveGenerator()
{
    location = BoardSquare();
}

MoveGenerator::MoveGenerator(board_dim col, board_dim row)
{
    location = BoardSquare(col, row);
}

void MoveGenerator::showAllMoves() const
{
    using std::cout;
    // Init pieces
    King king = King(location);
    Knight knight = Knight(location);
    Pawn pawn = Pawn(location);

    cout << "Chess Piece Possible Moves From: " << location << "\n" << "King\n";
    king.displayPossibleMoves();
    cout << "\n" << "Knight\n";
    knight.displayPossibleMoves();
    cout << "\n" << "Pawn\n";
    pawn.displayPossibleMoves();
}

void MoveGenerator::setLocation(board_dim row, board_dim col)
{
    location = BoardSquare(row, col);
}