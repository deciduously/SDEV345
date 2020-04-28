/*
 ** SDEV345 Final Project
 ** Simlation to add customers to the shortest queues
 ** Ben Lovy
 ** April 28 2020
 */

#include <chrono>

#include <iostream>

#include <random>

#include <string>

#include <thread>

#include <vector>

// Wrapper around RNG, produces random digits between 0 and 5 inclusive
class RateGenerator {
public:
  RateGenerator() = default;
  static unsigned int get_rate(int min, int max) {
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution dist(min, max);
    return dist(rng);
  }
};

/**Linked List class, used to store the data for each queue*/
template <class T> class LinkedList {
  struct Node {
    T val;
    Node *next;
    explicit Node(T v, Node *n = nullptr) : val(v), next(n) {}
  };
  Node *head = nullptr;

public:
  // Default constructor instantiates empty list
  LinkedList() = default;
  /**Check if list is empty*/
  bool empty() { return head == nullptr; }
  /**Get number of nodes in list*/
  size_t size() {
    Node *trav = head;
    size_t ret = 0;
    while (trav) {
      ++ret;
      trav = trav->next;
    }
    return ret;
  }
  /**Locate node in list, returns index or -1 if not found
   * \param value to search*/
  int find(T val) {
    Node *trav = head;
    int ret = 0;
    while (trav->val != val) {
      if (trav->next == nullptr)
        return -1;
      ret++;
      trav = trav->next;
    }
    return ret;
  }
  /**Insert a value at the end of the list
   * \param Value to add*/
  void insertEnd(T val) {
    // Create new node
    Node *ins = new Node(val);
    if (head != nullptr) {
      // traverse to end
      Node *trav = head;
      while (trav->next != nullptr) {
        trav = trav->next;
      }
      trav->next = ins;
    } else
      head = ins;
  }
  /**Remove the first node and return its contents*/
  T pop_front() {
    // Grab the value, then call remove()
    T ret = head->val;
    remove(ret);
    return ret;
  }
  /** Get a pointer to the first node - assumes non-emty list!*/
  T peek_front() { return head->val; }
  /**Remove a node.  Returns true on success, false if not found
   * \param node's value*/
  bool remove(T val) {
    if (head != nullptr) {
      Node *trav = head;
      Node *prev = head;
      while (trav->val != val) {
        if (trav->next == nullptr) {
          // No match
          return false;
        } else {
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
      delete trav;               // delete it
      return true;
    } else
      return false;
  }
  /**Destructor*/
  ~LinkedList() {
    // Empty all nodes
    Node *trav = head;

    while (trav) {
      Node *del = trav;
      trav = trav->next;
      delete del;
    }
  }
  friend std::ostream &operator<<(std::ostream &s, const LinkedList &l) {
    Node *trav = l.head;
    while (trav != nullptr) {
      s << "*";
      trav = trav->next;
    }
    return s;
  }
};

// A single customer
class Customer {
  unsigned int work_left;

public:
  Customer(unsigned int load) : work_left(load) {}
  // Each iteration, tick closer to zero.  Return true if done
  bool tick() {
    if (work_left > 0)
      --work_left;
    return work_left == 0;
  }
  friend std::ostream &operator<<(std::ostream &s, const Customer &c) {
    s << c.work_left;
    return s;
  }
};

/**Queue using a LinkedList for storage of Customer pointers*/
class CustomerQueue {
  LinkedList<Customer *> data;

public:
  /**Default constructor starts with an empty list*/
  CustomerQueue() = default;
  /**Check if queue is empty*/
  bool empty() { return data.empty(); }
  /**Remove and return the front element.  Assumes non-empty list*/
  Customer *pop_front() { return data.pop_front(); }
  /** Get a pointer to the front of the list but do not remove it.  Assumes
   * non-empty list.*/
  Customer *peek_front() { return data.peek_front(); }
  /**Add a new item to the back*/
  void push_back(Customer *val) { data.insertEnd(val); }
  /*Return the number of nodes in the underlying data structure*/
  size_t size() { return data.size(); }
  /**Tick first customer in the queue.  If that drops it to zero, pop it*/
  bool tick() {
    // If it's empty, do nothing
    if (data.empty())
      return false;
    if (data.peek_front()->tick()) {
      data.pop_front();
      return true;
    }
    return false;
  }
  friend std::ostream &operator<<(std::ostream &s, const CustomerQueue &lq) {
    s << lq.data;
    return s;
  }
};

// Container for all lines, seeding with customers
// // Each time one spawns, a new interval is selected
class Checkout {
  // Object used for getting random rates
  RateGenerator rg;
  // Stores seconds until next customer
  unsigned int countdown;
  // Rate of refresh
  std::chrono::milliseconds rate;
  // Total queues in the checkout
  unsigned int num_queues;
  // Pointers to the queues themselves
  std::vector<CustomerQueue *> queues;

public:
  Checkout(unsigned int n, unsigned int refresh) {
    if (n < 1) {
      std::cerr << "Must have at least one queue!";
      exit(1);
    }
    rg = RateGenerator();
    rate = std::chrono::milliseconds(refresh);

    num_queues = n;
    reset_countdown();

    // Init all queues
    queues.reserve(num_queues);
    for (unsigned int i = 0; i < num_queues; i++) {
      queues[i] = new CustomerQueue();
    }

    // Seed with a single customer
    add_customer();
  }

  // Add a single customer to the shortest queue
  void add_customer() {
    // Init new customer - will be quicker to finish than added over time
    Customer *ins = new Customer(rg.get_rate(4, 9));

    // Find shortest
    size_t shortest = find_shortest();

    // Push
    queues[shortest]->push_back(ins);
  }

  // Return the index of the shortest
  size_t find_shortest() {
    // First, assume it's the first one
    size_t shortest = queues[0]->size();
    size_t idx = 0;
    for (size_t i = 1; i < num_queues; ++i) {
      // The check all the rest
      size_t new_size = queues[i]->size();
      if (new_size < shortest) {
        shortest = new_size;
        idx = i;
      }
    }
    return idx;
  }

  // Pick a new random countdown
  void reset_countdown() { countdown = rg.get_rate(1, 5); }

  // Display all queues
  void show() {
    using std::cout;
    for (unsigned int i = 0; i < num_queues; ++i) {
      cout << i + 1 << ": ";
      cout << *queues[i] << "\n";
    }
  }

  // Fake a clear screen to avoid a Curses dependency - dump newlines to stdout
  void silly_clear() { std::cout << std::string(100, '\n'); }

  // Run simulation
  void run() {
    for (unsigned int i = 1;; ++i) {
      // Clear screen
      silly_clear();
      // Display current state
      std::cout << "Iteration " << i << "\n";
      show();
      // Tick state
      tick();
      // Chill out for a while
      std::this_thread::sleep_for(rate);
    }
  }

  // Remove any complete customers and add a new one if necessary
  void tick() {
    // If the countdown expires, add 'add' more and pick a new countdown
    if (countdown == 0) {
      int add = 5;
      for (int i = 0; i < add; i++)
        add_customer();
      reset_countdown();
    }

    // Tick all the queues
    for (size_t i = 0; i < num_queues; ++i) {
      if (queues[i]->tick()) {
      }
      // std::cout << "Customer finished in queue " << i << "\n";
    }

    // Decrement countdown
    --countdown;
  }
};

int main() {
  // Init checkout system with 9 lines, refreshing once per second
  Checkout system(9, 1000);
  // Run it
  system.run();
  return 0;
}
