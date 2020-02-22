/**
* SDEV 345 Week 4
* Linked List
* Implement a linked list and menu-driven CLI
* Ben Lovy
* February 11, 2020
*/

#include <iostream>

/**Linked List class*/
template <class T>
class LinkedList
{
    struct Node {
        T val;
        Node* next;
        explicit Node(T v, Node* n = nullptr) : val(v), next(n) {}
    };
    Node *head = nullptr;
public:
    // Default constructor instantiates empty list
    LinkedList() = default;
    /**Locate node in list, returns index or -1 if not found
     * \param value to search*/
    int find(T val)
    {
        Node *trav = head;
        int ret = 0;
        while (trav->val != val)
        {
            if (trav->next == nullptr)
                return -1;
            ret++;
            trav = trav->next;
        }
        return ret;
    }
    /**Insert a value at the end of the list
     * \param Value to add*/
    void insertEnd(T val)
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
    /**Remove a node.  Returns true on success, false if not found
     * \param node's value*/
    bool remove(T val)
    {
        if (head != nullptr)
        {
            Node* trav = head;
            Node* prev = head;
            while(trav->val != val)
            {
                if (trav->next == nullptr)
                {
                    // No match
                    return false;
                }
                else
                {
                    // Advance
                    prev = trav;
                    trav = trav->next;
                }
            }
            // Successful match
            // If we're at the beginning, skip it
            if (trav == head)
                head = head->next;
            else
                prev->next = trav->next; // skip it
            delete trav; // delete it
            return true;
        }
        else return false;
    }
    /**Destructor*/
    ~LinkedList()
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
    friend std::ostream& operator<<(std::ostream& s, const LinkedList& l)
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

/**CLI for Linked List*/
template <class T>
class ListMenu
{
    LinkedList<T> list;
public:
    void cli()
    {
        for (;;)
        {
            char user_choice[2];
            std::cout << "Select numeral:\n\n";
            std::cout << "1) Insert\n2) Delete\n3) Display\n4) Locate\nChoice> ";
            std::cin >> user_choice;

            switch (*user_choice)
            {
                char buffer[BUFFER_SIZE];
                case '1':
                {
                    std::cout << "Enter int to insert: ";
                    std::cin >> buffer;
                    list.insertEnd(atof(buffer));
                    break;
                }
                case '2':
                {
                    std::cout << "Enter int to remove: ";
                    std::cin >> buffer;
                    bool res = list.remove(atof(buffer));
                    std::cout << (res ? "Removed" : "Not found") << "\n";
                    break;
                }
                case '3':
                {
                    std::cout << list << "\n";
                    break;
                }
                case '4':
                {
                    std::cout << "Enter int to search for: ";
                    std::cin >> buffer;
                    std::cout << "Find result: " << list.find(atof(buffer)) << "\n";
                    break;
                }
                default:
                    std::cerr << "Unknown!\n";
                    break;
            }
        }
    }
};

int main()
{
    ListMenu<int>().cli();
    return 0;
}