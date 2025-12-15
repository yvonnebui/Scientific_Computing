# exercise 1b)
The runtime measurements show two main patterns.
First, the initial run is the slowest (warm-up effect) because data must be loaded from RAM into the CPU caches.
The following runs are faster due to cache hits.

Second, all measurements have minor noise caused by operating system interference and context switches.

To obtain a single, trustworthy measurement,
we can select the value least affected by noise, by taking minimum runtime,
as this value represents the execution closest to ideal performance.


# exercise 1c)

## what do you recognize in the plots

The plots show the runtime of the AXPY operation as a function of the vector dimension $n$. While the overall trend is linear, confirming the $O(n)$ complexity, there are distinct non-linear jumps and changes in slope at specific values of $n$.

This non-linear behavior is directly caused by the computer's memory hierarchy.

1.  **Cache Hits (Steeper Slope, Fast):** For small $n$, the total data required for $x, y, z$ fits entirely within the fast CPU Cache (L1, L2, L3). Performance is high.
2.  **Capacity Misses (Jumps/Slope Change):** As $n$ increases, the total data size exceeds the capacity of one cache level. The processor is then forced to retrieve the data from the next, significantly slower memory level (e.g., L3 or RAM). This transition results in a increase in runtime.
3.  **RAM Dominance (Gentler Slope, Slower):** Once $n$ is very large, the data is primarily accessed from the slow Main Memory (RAM), and the slope stabilizes, reflecting the bandwidth limit of the RAM.

## Is it possible to determine any details of the memory hierarchy?
Yes,the specific values of $n$ where the sharp jumps or slope changes occur indicate the point where the total data size exceeds a cache level capacity


## Why does the runtime not increase linearly even though the vector length grows linearly?
because the time required to access the data is not constant. The runtime is dominated by the memory access time, which increases as the data size forces the system to rely on slower levels of the memory hierarchy.
