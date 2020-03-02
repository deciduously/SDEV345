Though it may not always be immediately obvious how, any algorithm that can be expressed imperatively can also be expressed recursively.  Recursive solutions can quite often be more concise to express, but if not written careful do have a tendency to consume more memory than their imperative counterparts as more stack frames are allocated.

One way to mitigate this in C++ is by writing tail-recursive implementations, wherein the recursion occurs in *tail position*.  This means the recursive self-call is final instruction in your function - you don't perform the recursion and then operate on that result before returning to the caller.

As with most concepts, it's best illustrated via example.  Here's a C++ implementation of Euler's algorithm for finding the greatest common divisor of two positive integers `m` and `n`:

```cpp
/**Calculate the greatest common divisor of positive integers m and n.
 * Returns -1 on error
 */
int gcd(int, int);

int main()
{
    int m = 119, n = 544;
    std::cout << gcd(m,n) << "\n"; // outputs 17
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
```

This implementation uses a `for` loop to adjust the inputs to this algorithm, checking on each iteration.  However, the whole point of a loop body is to run some section of code repeatedly on slightly different parameters until some condition is met.  We can use a function body much like we use a loop body, and instead of transforming local variables, simply adjust the parameters we pass into the sub-call:

```cpp
#include <iostream>

/**Calculate the greatest common divisor of positive integers m and n.
 * Returns -1 on error
 */
int rec_gcd(int, int);

int main()
{
    int m = 119, n = 544;
    std::cout << rec_gcd(m,n) << "\n";
    return 0;
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
```

This function produces the same result, but saves a little typing.  The recursive call in the the inner `if/else` branch occurs in tail position, because we don't do anything else with the value returned by the subcall before passing it back up.

Generally when you call a new function, a whole new stack frame is allocated and any relevant locals are copied onto the stack for the function body to access.  When we recur in tail position, the compiler is able top avoid this entirely.  We already have a stack frame allocated for this `rec_gcd()` function body, we're in it right now!  Nothing needs to change except the specific locals passed in.  In the call `rec_gcd(divisor, (dividend % divisor))`, we essentially perform the exact same variable-swapping logic that the previous implementation had spelled out more explicitly:  `int r= m % n; m = n; n = r;`.  THe compiler still does exactly that when performing this recursion, it just happens implicitly when swapping the locals in your stack frame.  This program will produce identical results with similar runtime characteristics to the imperative version.

Works cited:

“Tail Recursion.” GeeksforGeeks, 4 Sept. 2018, www.geeksforgeeks.org/tail-recursion/.
