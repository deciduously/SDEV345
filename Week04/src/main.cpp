/**
* SDEV 345 Week 4
* Stacks
* Prompt user for string input and reverse it using a stack
* Ben Lovy
* February 4, 2020
*/

#include <iostream>

const size_t BUFFER_SIZE = 32;

template <class T>
class SimpleStack
{
    T stack[BUFFER_SIZE] = {};
    size_t size;
public:
    SimpleStack()
    {
        size = 0;
    };

    void push(T val)
    {
        if (size < BUFFER_SIZE - 1)
        {
            stack[size] = val;
            size++;
        } else
        {
            std::cerr << "Stack already at max capacity!" << "\n";
            std::exit(1);
        }
    }

    T pop()
    {
        // Grab top card
        if (size > 0)
        {
            T ret = stack[size - 1];
            stack[size - 1] = {};
            size--;
            return ret;
        } else
        {
            std::cerr << "Cannot pop from empty stack!" << "\n";
            std::exit(1);
        }
    }

    size_t get_size()
    {
        return size;
    }
};

class StringReverser
{
    SimpleStack<char> chars;
public:
    StringReverser()
    {
        using std::cin;
        using std::cout;
        char tmpInput[BUFFER_SIZE];
        // Prompt for input
        cout << "Enter string to reverse: ";
        cin.getline(tmpInput, BUFFER_SIZE);

        // Push each character to stack
        for (int i = 0; tmpInput[i] != '\0'; i++)
        {
            chars.push(tmpInput[i]);
        }


        // Pop each off the stack
        cout << "\nBackwards:\n";
        while (chars.get_size() > 0)
        {
            cout << chars.pop();
        }
        cout << "\n";
    }
};

int main()
{
    // Run program
    StringReverser sr;
    return 0;
}
