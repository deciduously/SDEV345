/**
* SDEV 345 Week 10
* Binary Tree
* Implement a binary tree and menu-driven CLI
* Ben Lovy
* March 25, 2020
*/

#include <iostream>

/**Binary Tree class*/
template <class T>
class BinaryTree
{
public:
    struct Node {
        T val;
        Node* left;
        Node* right;
        explicit Node(T v, Node* l = nullptr, Node* r = nullptr)
        : val(v),
          left(l),
          right(r)
        {}
    };
    // Default constructor instantiates empty list
    BinaryTree() = default;
    /**Locate node in list, returns index or -1 if not found
     * \param value to search*/
    Node* find(T val)
    {
        // if empty, nothing here
        if (!root)
            return nullptr;

        // Otherwise, search for it
        Node* trav = root;

        while (trav->val != val)
        {
            if (val < trav->val)
                trav = trav->left;
            else
                trav = trav->right;

            // Did we hit the end?
            if (!trav)
                return nullptr;
        }
        // If were here, we found it
        return trav;
    }
    /**Insert a value at the end of the list
     * \param Value to add*/
    void insert(T val)
    {
        // Construct new node
        Node* ins = new Node(val);

        // Is the tree empty?  If so, this is the new root
        if (!root)
            root = ins;
        else
        {
            // Otherwise, pop it in the right location
            Node* trav = root;
            // Store a parent to link to
            Node* parent;

            // Loop forever until it's located
            for (;;)
            {
                parent = trav;
                if (val < trav->val)
                {
                    // go left
                    trav = trav->left;
                    // are we here?
                    if (!trav)
                    {
                        // Link it up - we're done
                        parent->left = ins;
                        return;
                    }
                }
                else
                {
                    // go right
                    trav = trav->right;
                    if (!trav)
                    {
                        // Link it up - we're done
                        parent->right = ins;
                        return;
                    }
                }
            }
        }
    }
    /**Destructor*/
    static void destroySubTree(Node* &t)
    {
        if (t)
        {
            destroySubTree(t->left);
            destroySubTree(t->right);
            delete t;
        }
    }
    ~BinaryTree()
    {
        destroySubTree(root);
    }
private:
    Node* root = nullptr;
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
                    cout << "Value to insert: ";
                    cin >> new_val;
                    btree.insert(new_val);
                    break;
                }
                case '2':
                {
                    int new_val;
                    cout << "Value to find: ";
                    cin >> new_val;
                    BinaryTree<int>::Node* found_node = btree.find(new_val);
                    if (found_node)
                        cout << "Found " << found_node->val << "\n";
                    else
                        cout << "Not Found!\n";
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