/**
* SDEV 345 Week 11
* Tree Traversal
* Demonstrate Pre-Order, In-Order, and Post-Order Traversal
* Ben Lovy
* April 05, 2020
*/

#include <iostream>
#include <random>
#include <string>

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

            // Loop forever until it's located
            for (;;)
            {
                // Store a parent to link to
                Node* parent = trav;
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

    // Traversals

    template <class F>
    void show_traversal(const std::string& name, F func)
    {
        using std::cout;

        cout << name << " traversal:\n[ ";
        func(root);
        cout << "]\n";
    }

    void show_all_traversals()
    {
        show_traversal("Pre-Order", pre_order);
        show_traversal("In-Order", in_order);
        show_traversal("Post-Order", post_order);
    }

    static void in_order(Node* local)
    {
        if (local)
        {
            in_order(local->left);
            std::cout << local->val << " ";
            in_order(local->right);
        }
    }

    static void post_order(Node* local)
    {
        if (local)
        {
            post_order(local->left);
            post_order(local->right);
            std::cout << local->val << " ";
        }
    }

    static void pre_order(Node* local)
    {
        if (local)
        {
            std::cout << local->val << " ";
            pre_order(local->left);
            pre_order(local->right);
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

int main()
{
    using std::cout;

    // Init tree
    BinaryTree<int> tree;

    // Init RNG
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution dist(1, 999);

    // Add one random element
    tree.insert(dist(rng));

    // Show off
    cout << "One element:\n";
    tree.show_all_traversals();

    // Add two more random elements
    tree.insert(dist(rng));
    tree.insert(dist(rng));

    // Show off
    cout << "Three elements:\n";
    tree.show_all_traversals();

    // Add eighteen more random elements
    for (int i = 0; i < 18; ++i) tree.insert(dist(rng));

    // Show off
    cout << "Twenty elements:\n";
    tree.show_all_traversals();

    return 0;
}