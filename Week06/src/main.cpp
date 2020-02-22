/**
* SDEV 345 Week 6
* Linked List
* Implement a queued linked list and menu-driven CLI
* Ben Lovy
* February 22, 2020
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
    /**Check if list is empty*/
    bool empty()
    {
        return head == nullptr;
    }
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
    /**Remove the first node and return its contents*/
    T pop_front()
    {
        // Grab the value, then call remove()
        T ret = head->val;
        remove(ret);
        return ret;
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

/**Queue using a LinkedList for storage*/
template <class T>
class LLQueue
{
    LinkedList<T> data;
public:
    /**Default constructor starts with an empty list*/
    LLQueue() = default;
    /**Check if queue is empty*/
    bool empty()
    {
        return data.empty();
    }
    /**Remove and return the front element.  Assumes non-empty list*/
    T pop_front()
    {
        return data.pop_front();
    }
    /**Add a new item to the back*/
    void push_back(T val)
    {
        data.insertEnd(val);
    }
    friend std::ostream& operator<<(std::ostream& s, const LLQueue& lq)
    {
        s << lq.data;
        return s;
    }
};

const size_t BUFFER_SIZE = 256;

/**CLI for queue*/
class QueueMenu
{
    LLQueue<int> queue;
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
            cout << "1) Is queue empty?\n2) Pop front\n3) Push back\n4) Display\nChoice> ";
            cin >> user_choice;

            switch (*user_choice)
            {

                case '1':
                {
                    cout << "Queue is empty: ";
                    cout << (queue.empty() ? "true" : "false") << "\n";
                    break;
                }
                case '2':
                {
                    cout << "Popped from front: " << queue.pop_front() << "\n";
                    break;
                }
                case '3':
                {
                    char buffer[BUFFER_SIZE];
                    cout << "Enter value to insert: ";
                    cin >> buffer;
                    queue.push_back(atoi(buffer));
                    break;
                }
                case '4':
                {
                    cout << queue << "\n";
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
    QueueMenu().cli();
    return 0;
}