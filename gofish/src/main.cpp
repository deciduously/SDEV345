#include <cstdlib>
#include <iostream>
#include <ctime>

// Cards are just ints
typedef int card;

class Card
{
    card c;
    static char rank[];
    static char suits[];

public:
    Card()
    {
        c = 0;
    }
    Card(card card)
    {
        c = card;
    }
    friend std::ostream &operator<<(std::ostream &s, const Card &c)
    {
        s << rank[c.c / 4];
        s << suits[c.c % 4];
        return s;
    }
};

char Card::rank[] = {'2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K', 'A'};
char Card::suits[] = {'C', 'D', 'H', 'S'};

class Player
{
    int handSize;
    Card hand[7] = {};

public:
    Player()
    {
        // Init to empty hand
        handSize = 0;
    }
    void addCard(Card c)
    {
        hand[handSize] = c;
        handSize++;
    }
    friend std::ostream &operator<<(std::ostream &s, const Player &p)
    {
        s << "Player hand: [ ";
        for (int i = 0; i < p.handSize; i++)
            s << p.hand[i] << " ";
        s << "]";
        return s;
    }
};

const int DECK_SIZE = 52;

// Stores a deck of cards as a queue
// TODO shuffle
class Deck
{
    Card deck[DECK_SIZE] = {};
    int currentSize;
public:
    Deck()
    {
        currentSize = DECK_SIZE;
        for (int i = 0; i < currentSize; i++)
            deck[i] = i;
    }

    // Pop top card off the deck
    Card deal()
    {
        // Grab top card
        Card ret = deck[currentSize - 1];
        // Reset size to no longer include element
        currentSize--;
        // Return card
        return ret;
    }
    // Creates an empty deck for the discard pile
    void empty()
    {
        for (int i = 0; i < currentSize; i++)
            deck[i] = {};
        currentSize = 0;
    }

    // Scramble the array
    void shuffle()
    {
        int shuffleSize = currentSize;
        while (shuffleSize > 1)
        {
            // pick random
            int idx = std::rand() % (currentSize - 1);
            shuffleSize--;
            // Shuffle
            Card tmp = deck[shuffleSize];
            deck[shuffleSize] = deck[idx];
            deck[idx] = tmp;
        }
    }
};

// This will have two deck and a discard

class Game
{
    Deck deck;
    Deck discard;
    Player players[2];
    int numPlayers;

public:
    Game()
    {
        // Init deck and discard
        deck = Deck();
        deck.shuffle();
        discard = Deck();
        discard.empty();
        // Init two players
        numPlayers = 2;
        for (int i = 0; i < numPlayers; i++)
            players[i] = Player();
        // Deal a 7 card hand to each
        for (int i = 0; i < numPlayers; i++)
        {
            for (int j = 0; j < 7; j++)
            {
                players[i].addCard(deck.deal());
            }
        }
    }
    friend std::ostream &operator<<(std::ostream &s, const Game &g)
    {
        s << "Game:\n";
        for (int i = 0; i < g.numPlayers; i++)
            s << g.players[i] << "\n";
        return s;
    }
};

int main()
{
    // seed PRNG
    std::srand(std::time(0));
    // Init game
    Game g = Game();
    // Output gamestate
    std::cout << g;
}
