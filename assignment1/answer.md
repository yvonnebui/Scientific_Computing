# Exercise 2
## b)
### Test for x = 1
```
poly:   -5987.000000000000000
horner: -5987.000000000000000
```
### Test for x = 999
```
poly:   0.000000000000000
horner: 1.000000000000000
```
### observation
The solutions for x = 1 are correct with both functions,
but for x = 999 only Horner's scheme method produces the correct solution, which is P(999) = 1. 

## c)
### polynomial 
**Multiplications:**
- For computing powers $x^i$: $1 + 2 + ... + n = \frac{n(n+1)}{2}$
- For multiplying coefficients $a_i$ with $x^i$: $n$
- **Total:** $\frac{n(n+1)}{2} + n = \frac{n(n+3)}{2}$ = **O(n²)**

**Additions:** n = **O(n)**

### horner's scheme
**Multiplications:** n = **O(n)**

**Additions:** n = **O(n)**

### conclusion
Horner's scheme is more efficient

## d)
### d1)
$$
\begin{align}
D_n &= \frac{1}{d_0} + \frac{1}{d_0 d_1} + \frac{1}{d_0 d_1 d_2} + \ldots + \frac{1}{d_0 d_1 \cdots d_n} \\
&= \frac{1}{d_0} \left(1 + \frac{1}{d_1} + \frac{1}{d_1 d_2} + \ldots + \frac{1}{d_1 d_2 \cdots d_n}\right) \\
&= \frac{1}{d_0} \left(1 + \frac{1}{d_1} \left(1 + \frac{1}{d_2} + \ldots + \frac{1}{d_2 d_3 \cdots d_n}\right)\right) \\
&= \frac{1}{d_0} \left(1 + \frac{1}{d_1} \left(1 + \frac{1}{d_2} \left(1 + \ldots \right)\right)\right)
\end{align}
$$

### d3) sequence of values: 17
