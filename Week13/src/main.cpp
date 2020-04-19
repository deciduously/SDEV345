/**
* SDEV 345 Week 13
* Hash table
* A hash table with a menu-dirven CLI offering Insert, Locate, Delete, and Display All
* Ben Lovy
* April 19, 2020
*/

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

struct DataMember
{
    std::string data;
    DataMember() : data("") {}
    DataMember(const std::string& d) : data(d) {}
};

class HashTable
{
    std::vector<DataMember*> data;
    size_t length;
    DataMember* nullMember;

    // Hash a key
    int get_hash(const std::string& key)
    {
        int some_prime = 37, prime_two = 54059, prime_three = 76963;

        int ret = some_prime;
        for (size_t i = 0; i < key.size(); ++i)
        {
            ret = (ret * prime_two) ^ (key[0] * prime_three);
        }
        return ret % length;
    }

    // Check if the table is full
    bool isFull()
    {
        return std::all_of(data.begin(), data.end(), [](auto member) {
            return member != nullptr;
        });
    }
public:
    HashTable(int size) : length(size)
    {
        data.resize(length);
        // Init all members to null
        std::fill(data.begin(), data.end(), nullptr);
        nullMember = new DataMember();
    }

    // Show off full table
    void display()
    {
        using std::cout;
        cout << "[ ";
        for (auto member : data)
        {
            if (member)
                cout << member->data << " ";
            else
                cout << "__ ";
        }
        cout << "]\n";
    }

    // Insert a key
    void insert(DataMember* item_ptr)
    {
        if (isFull())
        {
            std::cerr << "Cannot insert - table full!\n";
            return;
        }

        // Hash the data
        std::string s = item_ptr->data;
        int hash = get_hash(s);

        // Tell user if there was a collision
        if (data[hash])
            std::cout << "Note: hash collision!\n";

        // Adjust hash via linear probing until free
        while (data[hash] && data[hash]->data != "")
        {
            ++hash;
            hash %= length;
        }

        // Insert
        data[hash] = item_ptr;
    }

    // Locate a key
    DataMember* locate(const std::string& key)
    {
        // Get the hash
        int hash = get_hash(key);

        // Look for it
        while (data[hash])
        {
            if (data[hash]->data == key)
            {
                return data[hash];
            }
            ++hash;
            hash %= length;
        }
        // Not found
        return nullptr;
    }

    DataMember* remove(const std::string& key)
    {
        // Get the hash
        int hash = get_hash(key);

        // Look for it
        while (data[hash])
        {
            if (data[hash]->data == key)
            {
                // Delete and return it
                DataMember* del = data[hash];
                data[hash] = nullMember;
                return del;
            }
            ++hash;
            hash %= length;
        }

        // Not found
        return nullptr;
    }
};

int main()
{
    using std::cin;
    using std::cout;
    using std::string;

    DataMember* item_ptr;
    int selection, table_size;
    string key;

    // Init table
    cout << "Enter table size: ";
    cin >> table_size;
    HashTable table(table_size);

    // Menu
    for (;;)
    {
        cout << "1) Insert Key\n2) Delete Key\n3) Display hash table\n4) Find key\nSelection> ";
        cin >> selection;

        switch (selection)
        {
            case 1:
                cout << "Enter string to insert> ";
                cin >> key;
                // Init member
                item_ptr = new DataMember(key);
                // Add to table
                table.insert(item_ptr);
                break;
            case 2:
                cout << "Enter string to delete> ";
                cin >> key;
                table.remove(key);
                break;
            case 3:
                table.display();
                break;
            case 4:
                cout << "Enter string to locate> ";
                cin >> key;
                item_ptr = table.locate(key);
                if (item_ptr)
                    cout << "Successfully located ";
                else
                    cout << "Unable to locate ";
                cout << key << "\n";
                break;
            default:
                std::cerr << "Unknown option!  Try again\n";
        }
    }

    return 0;
}