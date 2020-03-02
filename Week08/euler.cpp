#include <iostream>

/**Calculate the greatest common divisor of positive integers m and n.
 * Returns -1 on error
 */
int gcd(int, int);

int rec_gcd(int, int);

int main()
{
    int m = 119, n = 544;
    std::cout << rec_gcd(m,n) << "\n";
    return 0;
}

int gcd(int dividend, int divisor)
{
    int m = dividend, n = divisor;
    // Out of bounds
    if (n <= 0 || m <= 0)
        return -1;
    for (;;)
    {
        // 1. Let `r` be the remainder of diving `m / n`.
        int r = m % n;
        // 2. If `r == 0`, complete.  Return `n`.
        if (r == 0)
            return n;
        // 3. `m <- n`, `n <- r`, goto 1.
        m = n;
        n = r;
    }
}

int rec_gcd(int dividend, int divisor)
{
    if (dividend >= 0 && divisor >= 0)
    {
        if (divisor == 0)
            return dividend;
        else
            return rec_gcd(divisor, (dividend % divisor));
    }
    else
        return -1;
}