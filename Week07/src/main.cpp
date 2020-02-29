/**
* SDEV 345 Week 7
* Circular Linked List
* Implement a circular linked list and menu-driven CLI
* Ben Lovy
* February 29, 2020
*/

#include <iostream>

/**Circular Linked List class*/
template <class T>
class DoublyLinkedList
{
    /**Node is instantialed with null pointers*/
    struct Node
    {
        T val;
        Node *next;
        Node *prev;
        explicit Node(T v) : val(v), next(nullptr), prev(nullptr) {}
    };
    /**Pointers for the fist and last node*/
    Node *first = nullptr;
    Node *last = nullptr;

public:
    /**Default constructor*/
    DoublyLinkedList() = default;

    /**Check if any nodes present*/
    bool empty() const
    {
        return first == nullptr;
    }

    /**Insert a value at the end of the list
     * \param Value to add*/
    void insert_back(T val)
    {
        // Create new node
        Node *ins = new Node(val);
        if (empty())
        {
            // traverse to end
            Node *trav = first;
            while (trav->next != nullptr)
            {
                trav = trav->next;
            }
            trav->next = ins;
        }
        else
            first = ins;
    }
    /**Insert a value at the front of the list
     * \param Value to add
     */
    void insert_front(T val)
    {
        // Create node
        Node *ins = new Node(val);

        // If it's the first node, just make it the last one
        // If not, link the current first node's previous ptr to this new node
        if (empty())
            last = ins;
        else
            first->prev = ins;

        // Hook new node to to the previous head
        ins->next = first;
        // replace old first with new node
        first = ins;
    }
    /**Remove the last node and return its contents*/
    T pop_back()
    {
        // store val
        Node *popped = first;
        // is it the only node?
        if (!first->next)
            last = nullptr;
        else
            first->next->prev = nullptr; // remove it from the links

        // Move old second to first
        first = first->next;

        // Extract value to return
        T ret = popped->val;

        // Cleanup and return
        delete popped;
        return ret;
    }
    /**Remove the first node and return its contents*/
    T pop_front()
    {
        // store val
        Node *popped = last;
        // is it the only node?
        if (!first->next)
            last = nullptr;
        else
            last->prev->next = nullptr; // remove it from the links

        // Move old second to last to last
        last = last->prev;

        // Extract value to return
        T ret = popped->val;

        // Cleanup and return
        delete popped;
        return ret;
    }

    /**Display forwards - just calls out to operator<<()*/
    void show() const
    {
        std::cout << *this << "\n";
    }
    /**Display backwards*/
    void showReverse() const
    {
        using std::cout;
        cout << "[ ";
        Node *trav = last;
        while (trav != nullptr)
        {
            cout << trav->val << " ";
            trav = trav->prev;
        }
        cout << "]";
    }

    /**Destructor*/
    ~DoublyLinkedList()
    {
        // Empty all nodes, start at beginning
        Node *trav = first;

        while (trav)
        {
            Node *del = trav;
            trav = trav->next;
            delete del;
        }
    }
    friend std::ostream &operator<<(std::ostream &s, const DoublyLinkedList &l)
    {
        s << "[ ";
        Node *trav = l.first;
        while (trav != nullptr)
        {
            s << trav->val << " ";
            trav = trav->next;
        }
        s << "]";
        return s;
    }
};

const size_t BUFFER_SIZE = 256;

/**CLI for queue*/
class DoublyLinkedListMenu
{
    DoublyLinkedList<int> list;

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
            cout << "1) Insert first node\n2) Insert last node\n3) Delete first node\n";
            cout << "4) Delete last node\n5) Display list forward\n6) Display list backwards\nChoice> ";
            cin >> user_choice;

            switch (*user_choice)
            {

            case '1':
            {
                char buffer[BUFFER_SIZE];
                cout << "Enter value to insert: ";
                cin >> buffer;
                list.insert_front(atoi(buffer));
                break;
            }
            case '2':
            {
                char buffer[BUFFER_SIZE];
                cout << "Enter value to insert: ";
                cin >> buffer;
                list.insert_back(atoi(buffer));
                break;
            }
            case '3':
            {
                cout << "Popped from front: " << list.pop_front() << "\n";
                break;
            }
            case '4':
            {
                cout << "Popped from front: " << list.pop_front() << "\n";
                break;
            }
            case '5':
            {
                list.show();
                break;
            }
            case '6':
            {
                list.showReverse();
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
    DoublyLinkedListMenu().cli();
    return 0;
}
