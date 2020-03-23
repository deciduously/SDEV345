/**
* SDEV 345 Week 10
* Binary Tree
* Implement a binary tree and menu-driven CLI
* Ben Lovy
* February 22, 2020
*/

#include <iostream>

/**Binary Tree class*/
template <class T>
class BinaryTree
{
    struct Node {
        T val;
        Node* left;
        Node* right;
        //explicit Node(T v, Node* n = nullptr) : val(v), next(n) {}
    };
    Node *head = nullptr;
public:
    // Default constructor instantiates empty list
    BinaryTree() = default;
    /**Locate node in list, returns index or -1 if not found
     * \param value to search*/
    int find(T val)
    {
        // TODO
    }
    /**Insert a value at the end of the list
     * \param Value to add*/
    void insert(T val)
    {
        //TODO
    }
    /**Destructor*/
    ~BinaryTree()
    {
        // TODO
    }
};

const size_t BUFFER_SIZE = 256;

/**CLI for tree*/
class BinaryTreeMenu
{
    BinaryTree<int> btree;
public:
    void cli()
    {
        using std::cerr;
        using std::cin;
        using std::cout;
        for (;;)
        {
            char user_choice[2];
            cout << "Select numeral:\n\n";
            cout << "1) Insert\n2) Find\nChoice> ";
            cin >> user_choice;

            switch (*user_choice)
            {

                case '1':
                {
                    int new_val;
                    cout << "Value to Insert: ";
                    cin >> new_val;
                    btree.insert(new_val);
                    break;
                }
                case '2':
                {
                    int new_val;
                    cout << "Value to Insert: ";
                    cin >> new_val;
                    cout << btree.find(new_val) << "\n";
                    break;
                }
                default:
                    cerr << "Unknown!\n";
                    break;
            }
        }
    }
};

int main()
{
    BinaryTreeMenu().cli();
    return 0;
}