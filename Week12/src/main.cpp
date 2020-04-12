/**
* SDEV 345 Week 12
* Red-Black Tree
* Insert (30,28,21,11,17,4) into an empty red-black tree and display a diagram.
* Ben Lovy
* April 12, 2020
*/

#include <iostream>
#include <string>

/**Red Black Tree class.*/
template <class T>
class RedBlackTree
{
public:
    struct Node {
        T val;
        Node* parent;
        Node* left;
        Node* right;
        bool red;
        explicit Node(
            T v,
            Node* p = nullptr,
            Node* l = nullptr,
            Node* r = nullptr,
            bool is_red = true) // nodes start Red by default
        : val(v),
          parent(p),
          left(l),
          right(r),
          red(is_red)
        {}
    };
    // Default constructor instantiates empty list
    RedBlackTree() {
        null_tree = new Node(0, nullptr, nullptr, nullptr, false);
        root = null_tree;
    }

    /**Insert a value in the tree
     * \param Value to add*/
    void insert(T val)
    {
        // Construct new node
        Node* ins = new Node(val, nullptr, null_tree, null_tree, true);

        // Find the proper location
        Node* p = nullptr;
        Node* trav = root;

        while (trav != null_tree)
        {
            p = trav;
            if (ins->val < trav->val)
            {
                trav = trav->left;
            }
            else
            {
                trav = trav->right;
            }
        }

        // Hook it up

        ins->parent = p;
        if (!p)
        {
            root = ins;
        }
        else if (ins->val < p->val)
        {
            p->left = ins;
        }
        else
        {
            p->right = ins;
        }

        // If we just inserted the root node, we're done - toggle and return.
        if (!ins->parent)
        {
            ins->red = false;
            return;
        }

        // If the grandparent is null, we're okay don't toggle, but still just return.
        if (!ins->parent->parent)
        {
            return;
        }

        // Otherwise, apply any needed balance fixes
        repair_insert(ins);
    }

    void show_diagram()
    {
        if (root)
        {
            show_tree(root, "", true);
        }
    }

    /**Destructor*/

    ~RedBlackTree()
    {
        destroySubTree(root);
        delete null_tree;
    }
private:
    Node* root;
    Node* null_tree;

    // Rotations

    /* Perform a right rotation from given node */
    void rotate_right(Node* node)
    {
        Node* orig_left = node->left;
        node->left = orig_left->right;

        if (orig_left->right != null_tree)
        {
            orig_left->right->parent = node;
        }

        orig_left->parent = node->parent;

        if (!node->parent)
        {
            root = orig_left;
        }
        else if (node == node->parent->right)
        {
            node->parent->right = orig_left;
        }
        else
        {
            node->parent->left = orig_left;
        }
        orig_left->right = node;
        node->parent = orig_left;
    }

    /* Perform a left rotation from a given node */
    void rotate_left(Node* node)
    {
        Node* orig_right = node->right;
        node->right = orig_right->left;

        if (orig_right->left != null_tree)
        {
            orig_right->left->parent = node;
        }

        orig_right->parent = node->parent;

        if(!node->parent)
        {
            root = orig_right;
        }
        else if (node == node->parent->left)
        {
            node->parent->left = orig_right;
        }
        else
        {
            node->parent->right = orig_right;
        }

        orig_right->left = node;
        node->parent = orig_right;
    }

    /* Verify properties and repair tree post-insert */
    void repair_insert(Node* node)
    {
        // Will be either the left or right depending if we're red or black
        Node* uncle;

        // Run fixes until tree is wholly repaired
        while (node->parent->red)
        {
            if (node->parent == node->parent->parent->right)
            {
                uncle = node->parent->parent->left;
                if (uncle->red)
                {
                    // Parent and Uncle are both red
                    uncle->red = false;
                    node->parent->red = false;
                    node->parent->parent->red = true;
                    node = node->parent->parent;
                }
                else
                {
                    if (node == node->parent->left)
                    {
                        // Parent is right of grandparent, new node is left of parent
                        node = node->parent;
                        rotate_right(node);
                    }

                    // Parent is right of grandparent, new node is right of parent
                    node->parent->red = false;
                    node->parent->parent->red = true;
                    rotate_left(node->parent->parent);
                }
            }
            else
            {
                uncle = node->parent->parent->right;

                if (uncle->red)
                {
                    // mirror of Parent and Uncle both red
                    uncle->red = false;
                    node->parent->red = false;
                    node->parent->parent->red = true;
                    node = node->parent->parent;
                }
                else
                {
                    if (node == node->parent->right)
                    {
                        // mirror of Parent right of grandparent, new node left of parent
                        node = node->parent;
                        rotate_left(node);
                    }

                    // mirror of parent right of grandparent, new node right of parent
                    node->parent->red = false;
                    node->parent->parent->red = true;
                    rotate_right(node->parent->parent);
                }
            }
            // all done?
            if (node == root) break;
        }
        root->red = false;
    }

    void destroySubTree(Node* &t)
    {
        if (t != null_tree)
        {
            destroySubTree(t->left);
            destroySubTree(t->right);
            delete t;
        }
    }

    void show_tree(Node* node, std::string pad, bool last)
    {
        using std::cout;

        if (node != null_tree)
        {
            cout << pad;
            if (last)
            {
                cout << "right ";
                pad += "      ";
            }
            else
            {
                cout << "left ";
                pad += "|     ";
            }

            std::string color = node->red ? "red" : "black";
            cout << node->val << "-" << color << "\n";
            show_tree(node->left, pad, false);
            show_tree(node->right, pad, true);
        }
    }
};

int main()
{
    RedBlackTree<int> rbt;

    rbt.insert(30);
    rbt.insert(28);
    rbt.insert(21);
    rbt.insert(11);
    rbt.insert(17);
    rbt.insert(4);

    rbt.show_diagram();

    return 0;
}