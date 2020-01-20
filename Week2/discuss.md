One common method for finding prime numbers is known as a prime sieve.  Using thes method, you start with a complete range of integers and sequential remove composite members from the set.  The most basic of these is the Sieve of Eratosthenes.  I'll demonstrate on the integers 2 through 10:

```txt
2 3 4 5 6 7 8 9 10
```

First, start with 2 and remove every second number, which gets rid of the multiples of 2

```txt
2 3 -4- 5 -6- 7 -8- 9 -10-
```

Then find the next number that hasn't ben removed.  On our case, it's 3.  Now we remove all the multiples of 3 that weren't already removed in the 2s step:

```txt
2 3 -4- 5 -6- 7 -8- -9- -10-
```

The next number up from 3 is 4, but it's already been removed, so we skip right to 5:

```txt
2 3 -4- 5 -6- 7 -8- -9- -10-
```

The number five up from there is 10, which was already removed, we we're done.  Similar with 6, and then we get to 7.  There isn't a number in our set that's seven greater than seven, so there's nothing to do.  All the other numbers have been removed.  Taking the removed ones out:

```txt
2 3 5 7
```

We've located the primes.  This is a simple algorithm, but not necessarily the most efficient.  The biggest problem is the space this requires - imagine trying to find all the primes between two and one billion.  We also knock out half the numbers on the very first go - one way to reduce the operations required is to start with only sets of odd numbers, because no even numbers will ever be prime (except 2).

To avoid these problems, more complex sieves have been formulated that use known properties of numbers to avoid some work.  For instance, the sieve of Atkin observes that if any number modoulo 60 is is divisible by two, three, or five is itself divisible by that prime, and therefore not a prime itself.  It completely skips these numbers.  It is also seeded with 2, 3, and 5 as prior knowledge.

There also exist tools like Hadoop which are capable of splitting a workload across multiple hardware nodes, which can allow from larger sets if your input data is too big to fit in one computer's RAM.

Works cited:

"Sieve of Atkin." GeeksforGeeks, 13 Jan. 2020, www.geeksforgeeks.org/sieve-of-atkin/.
“Sieve of Eratosthenes.” GeeksforGeeks, 15 Jan. 2020, www.geeksforgeeks.org/sieve-of-eratosthenes/.