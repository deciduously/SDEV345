/**
* SDEV 345 Week 8
* Recursion
* Recursively output the hexadecimal representation of an integer
* Ben Lovy
* March 2, 2020
*/

#include <iostream>

/**IntFormatter provides print_as_hex() method to display stored value as hex to stdout*/
class IntFormatter
{
    int val;
    // Hex base for extracting least significant digit
    static int hex_base;
    /**Pretty-print number to stdout
     * \param Base-10 integer to output
    */
    static void rec_print_as_hex(int v)
    {
        using std::cout;
        // Is there any value left? If not, done
        if (v == 0)
            return;

        // Snag digit
        int digit = v % hex_base;

        // Display number in order

        // First, the unprocessed part
        rec_print_as_hex(v / hex_base);

        // Then, our newly calculated digit
        switch (digit)
        {
            case 15: cout << 'F'; break;
            case 14: cout << 'E'; break;
            case 13: cout << 'D'; break;
            case 12: cout << 'C'; break;
            case 11: cout << 'B'; break;
            case 10: cout << 'A'; break;
            default: cout << digit; break;
        }
    }
public:
    explicit IntFormatter(int v) : val(v) {}
    /*Print the hexadecimal representation of base-10 integer to stdout*/
    void print_as_hex()
    {
        std::cout << "0x";
        rec_print_as_hex(val);
        std::cout << "\n";
    }
};

int IntFormatter::hex_base = 16;

int main()
{
    using std::cin;
    using std::cout;
    // Infinitely prompt for input - CTRL-C to exit
    for (;;)
    {
        char buffer[256];
        cout << "Enter base-10 integer to format as hex: ";
        cin >> buffer;
        IntFormatter(atoi(buffer)).print_as_hex();
    }
    return 0;
}
