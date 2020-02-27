/**
* SDEV 345 Week 7
* Circular Linked List
* Implement a circular linked list and menu-driven CLI
* Ben Lovy
* February 26, 2020
*/

#include <iostream>

/**Circular Linked List class*/
template <class T>
class DoublyLinkedList
{
    struct Node {
        T val;
        Node* next;
        explicit Node(T v, Node* n = nullptr) : val(v), next(n) {}
    };
    Node *head = nullptr;
public:
    // Default constructor instantiates empty list
    DoublyLinkedList() = default;

    /**Insert a value at the end of the list
     * \param Value to add*/
    void insert_back(T val)
    {
        // Create new node
        Node* ins = new Node(val);
        if (head != nullptr)
        {
            // traverse to end
            Node* trav = head;
            while (trav->next != nullptr)
            {
                trav = trav->next;
            }
            trav->next = ins;
        } else
            head = ins;
    }
    /**Insert a value at the front of the list
     * \param Value to add
     */
    void insert_front(T val)
    {
        // TODO
    }
    /**Remove the last node and return its contents*/
    T pop_back()
    {
        // TODO
    }
    /**Remove the first node and return its contents*/
    T pop_front()
    {
        // Grab the value, then call remove()
        T ret = head->val;
        remove(ret);
        return ret;
    }

    /**Destructor*/
    ~DoublyLinkedList()
    {
        // Empty all nodes
        Node* trav = head;

        while(trav)
        {
            Node* del = trav;
            trav = trav->next;
            delete del;
        }
    }
    friend std::ostream& operator<<(std::ostream& s, const DoublyLinkedList& l)
    {
        s << "[ ";
        Node* trav = l.head;
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
                    cout << list << "\n";
                    break;
                }
                case '6':
                {
                    // TODO
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