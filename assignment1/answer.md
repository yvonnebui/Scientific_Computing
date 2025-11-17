Exercise 2
b)
Test for x = 1
poly:   -5987.000000000000000
horner: -5987.000000000000000
Test for x = 999
poly:   0.000000000000000
horner: 1.000000000000000

The solutions for x = 1 are correct with both functions,
but for x = 999 only Horner's scheme method produces the correct solution, which is P(999) = 1. 

c)
-----polynomial----- 
multiplications for the powers x^i: 1 + 2 + ... + n = n(n+1)/2
multiplications between a_i and x^i: n
additions: n
 
total
muliplications: n(n+1)/2 + n = n(n+3)/2 = O(n^3)
additions: n = O(n)

-----horner's scheme-----
multiplications: n = O(n)
additions: n = O(n)

d1)
D_n = 1/d_0 + 1/(d_0d_1) + 1/(d_0d_1d_2) + ... + 1/(d_0d_1...d_n)
   = 1/d_0 * (1 + 1/d_1 + 1/(d_1d_2) + ... + 1/(d_1d_2...d_n))
   = 1/d_0 * (1 + 1/d_1 * (1 + 1/d_2 + ... + 1/(d_2d_3...d_n)))
   = 1/d_0 * (1 + 1/d_1 * (1 + 1/d_2 * (1 + ... )))

d3) sequence of values: 17
