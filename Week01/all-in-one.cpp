/*
* SDEV 345 Week 1
* C++ Warm-Up
* Displays the possible chess moves for Pawn/Knight/King at locations A1 and D4
* Ben Lovy
* January 19, 2020
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

class ChessPiece
{
protected:
    int options_len;
    BoardSquare location;
    virtual BoardSquare *possibleMoves() = 0;

public:
    ChessPiece();
    ChessPiece(BoardSquare);
    void displayPossibleMoves();
};

ChessPiece::ChessPiece()
{
    location = BoardSquare();
}

ChessPiece::ChessPiece(BoardSquare bs)
{
    location = bs;
    options_len = 0;
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

class Pawn : public ChessPiece
{
protected:
    virtual BoardSquare *possibleMoves()
    {
        // one up, one down, one left, one right
        // check bounds
        // there's only one way - up.  No enemy detection.
        static BoardSquare ret[1];
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
        options_len = current;
        return ret;
    }
public:
    Pawn(BoardSquare loc = BoardSquare()) : ChessPiece(loc) {}
};

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