/*
* SDEV 345 Week 1
* C++ Warm-Up
* Displays the possible chessboard moves various pieces at two locations
* Ben Lovy
* January 15, 2020
*/

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
    // Copy constructor
    BoardSquare(const BoardSquare&);
    // Get the char to display for the column
    const char col_ACN_char() const;
    int get_ACN_row() const;
    // get one up
    BoardSquare up() const;
    //// get one down
    //BoardSquare &down() const;
    //// get one left
    //BoardSquare &left() const;
    //// get one right
    //BoardSquare &right() const;
    // Will throw if attempt to create invalid square
    class OffBoardException {
        public:
        OffBoardException() {};
    };
};

BoardSquare::BoardSquare()
{
    column = 0;
    row = 0;
}

BoardSquare::BoardSquare(board_dim c, board_dim r)
{
    if (c < MAX_DIM || r < MAX_DIM)
    {
        throw OffBoardException();
    }
    column = c;
    row = r;
}

BoardSquare::BoardSquare(const BoardSquare &orig)
{
    column = orig.column;
    row = orig.row;
}

const char BoardSquare::col_ACN_char() const
{
    return static_cast<char>(row + 'A');
}

int BoardSquare::get_ACN_row() const
{
    return row + 1;
}

BoardSquare BoardSquare::up() const
{
    if (row >= MAX_DIM)
        throw OffBoardException();
    else
        return BoardSquare(column, row + 1);
}

//BoardSquare BoardSquare::down() const
//{
//    if (row >= MAX_DIM)
//        throw OffBoardException();
//    else
//        return BoardSquare(column, row + 1);
//}
//
//BoardSquare BoardSquare::left() const
//{
//    if (row >= MAX_DIM)
//        throw OffBoardException();
//    else
//        return BoardSquare(column, row + 1);
//}
//
//BoardSquare BoardSquare:right() const
//{
//    if (row >= MAX_DIM)
//        throw OffBoardException();
//    else
//        return BoardSquare(column, row + 1);
//}

std::ostream &operator<<(std::ostream &s, const BoardSquare bs)
{
    s << bs.col_ACN_char() << bs.get_ACN_row();
    return s;
}

// All the different types implemented
enum class PieceVariant
{
    Pawn,
    Knight
};

// Abstract ChessPiece

class ChessPiece
{
protected:
    PieceVariant variant;
    BoardSquare location;

public:
    ChessPiece();
    ChessPiece(BoardSquare);
    virtual BoardSquare *possibleMoves() const = 0;
};

ChessPiece::ChessPiece()
{
    location = BoardSquare();
}

ChessPiece::ChessPiece(BoardSquare bs)
{
    location = bs;
}

// Pawn

class Pawn : public ChessPiece
{
public:
    Pawn(BoardSquare loc = BoardSquare()) : ChessPiece(loc)
    {
        variant = PieceVariant::Pawn;
    };
    virtual BoardSquare *possibleMoves() const
    {
        // one up, one down, one left, one right
        // check bounds
        // there are at most 4 possibilities
        static BoardSquare ret[4];
        int current = 0;

        // try/catch each - if it throws, do nothing
        // up

        // down

        // left

        // right
    }
}

// Knight

// IF TIME:

// Bishop

// Rook

// Queen

// King

int main() {
    using std::cout;

    BoardSquare origin;
    BoardSquare other;

    try
    {
        origin = BoardSquare();
        other = BoardSquare(7,3);
    }
    catch (BoardSquare::OffBoardException e)
    {
        std::cerr << "Tried to instantiate invalid BoardSquare";
    }

    cout << "Chess Pieces\n";
    cout << BoardSquare() << " " << BoardSquare(7,3) << "\n";
}