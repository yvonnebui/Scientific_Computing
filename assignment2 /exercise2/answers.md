# exercise 2a)

## The Central Difference Method
works well at first. As the step size (h) gets smaller, the error goes down quickly, which is good.
However, when h becomes very tiny (smaller than 10^-7 ),
the error starts to shoot up very fast.
This happens because the computer has to subtract two numbers that are almost identical, 
which creates a large rounding error that ruins the result.

## The Complex Step Method
This method is much better. Its error stays low and keeps decreasing until it stabilizes around 10^-15.
This method avoids the subtraction, which is why the problem above doesn't occur.

# exercise 2b)

## The Central Difference Method
This method is unaffected by the pollution because it only uses the real part of the function.
Its error remains dominated by subtractive cancellation at small h.

## The Complex Step Method
The Complex Step Method is sensitive to the pollution.
The error is slightly greater with 2.220446e-15, whereas it previously reached 1.776357e-15.

# exercise 2c)

## The Central Difference Method

**Truncation Error**
$$E_{\text{trunc}, 1}(h) \leq C_1 h^2$$

**Rounding Error**
$$E_{\text{round}, 1}(h) \leq \frac{K_1 u}{h}$$

**Total Error**
$$|\bar{D}_1(h) - f'(x)| \leq C_1 h^2 + \frac{K_1 u}{h}$$

**Optimal $h$**
$$\frac{d}{dh} \left(C_1 h^2 + \frac{K_1 u}{h}\right) = 0 \implies h_{\text{opt}} = u^{1/3}$$

**Does $h$ roughly match your numerical observations from part a)?**
Yes. Since $u \approx 10^{-16}$ (for double precision), the analysis predicts $h_{\text{opt}} = (10^{-16})^{1/3} \approx 10^{-5.33}$.
This prediction closely matches the observed minimum error floor in the numerical results from part a) which occurred around $h = 10^{-6.0}$ to $10^{-7.0}$.

## The Complex Step Method

**Truncation Error**
$$E_{\text{trunc}, 2}(h) \leq C_2 h^2$$

**Rounding Error**
$$E_{\text{round}, 2}(h) \leq K_2 u$$

**Total Error**
$$|\bar{D}_2(h) - f'(x)| \leq C_2 h^2 + K_2 u$$

($C_i, K_i$ are constants; $u$ is the Unit Roundoff.)

**Does your analysis explain the different behaviors of the two methods observed in part a)?**
Yes.

* **$D_1(h)$:** The total error is dominated by the **$\frac{K_1 u}{h}$ term** for small $h$, causing the error to increase exponentially (the U-shaped curve) due to the large factor $1/h$.
* **$D_2(h)$:** The rounding error term ($K_2 u$) is constant and on the order of machine precision. The error is dominated by the **$C_2 h^2$ term**, allowing the error to decrease steadily until it hits the machine precision floor, thus demonstrating its superior robustness and accuracy for small $h$.


