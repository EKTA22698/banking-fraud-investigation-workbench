# Complexity Analysis and Experimental Evaluation

## Banking Transaction Fraud Investigation Workbench

---

## 1. Purpose

This report analyzes the theoretical and empirical complexity of the
algorithms implemented in the Banking Transaction Fraud Investigation
Workbench.

The project combines classical Design and Analysis of Algorithms (DAA)
techniques with fraud-investigation use cases including transaction
search, suspicious-pattern detection, investigation prioritization,
evidence-network analysis, resource allocation, and large-scale fraud
evaluation.

The analysis considers:

- Big-O upper bounds
- Big-Omega lower bounds
- Big-Theta tight bounds
- best, average, and worst cases where meaningful
- auxiliary-space requirements
- recurrence relations
- algorithmic paradigm comparisons
- empirical benchmark measurements
- scalability on the PaySim dataset

---

## 2. Experimental Environment

Benchmarks were collected on the following system:

| Component | Configuration |
|---|---|
| Processor | Intel Core Ultra 5 125H |
| Physical Cores | 14 |
| Logical Processors | 18 |
| Physical Memory | approximately 16 GB |
| Compiler | GCC 16.2.0 (MSYS2 UCRT64) |
| Build System | CMake 4.4.4 |
| Operating System | Microsoft Windows NT 10.0.26300.0 |
| Language | C |
| Build Configuration | CMake windows-ucrt64 preset |

Measured execution times are machine-dependent and should therefore be
interpreted together with the theoretical complexity analysis.

Very small benchmark workloads occasionally report 0.000 ms because
their execution time is below the effective resolution of the current
timing method. Such values should not be interpreted as zero-cost
algorithms.

---

# 3. Asymptotic Notation

## 3.1 Big-O

Big-O describes an asymptotic upper bound.

If:

T(n) = O(f(n))

then beyond some sufficiently large input size, T(n) grows no faster
than a constant multiple of f(n).

Big-O is commonly used to describe worst-case scalability.

---

## 3.2 Big-Omega

Big-Omega describes an asymptotic lower bound.

If:

T(n) = Omega(f(n))

then T(n) requires at least a constant multiple of f(n) asymptotically.

---

## 3.3 Big-Theta

Big-Theta gives a tight asymptotic bound.

If:

T(n) = Theta(f(n))

then f(n) describes both an asymptotic upper and lower bound for T(n).

---

# 4. Master Complexity Table

| Algorithm | Paradigm | Best | Average / Typical | Worst | Auxiliary Space |
|---|---|---|---|---|---|
| Merge Sort | Divide & Conquer | Theta(n log n) | Theta(n log n) | Theta(n log n) | Theta(n) |
| Quick Sort | Divide & Conquer | Theta(n log n) | Theta(n log n) | Theta(n^2) | O(log n) average, O(n) worst recursion |
| Iterative Binary Search | Divide & Conquer/Search | Omega(1) | O(log n) | O(log n) | Theta(1) |
| Recursive Binary Search | Divide & Conquer/Search | Omega(1) | O(log n) | O(log n) | O(log n) |
| Maximum Subarray | Divide & Conquer | implementation-dependent | Theta(n log n) | O(n log n) | O(log n) |
| Fast Power | Divide & Conquer | Theta(log e) | Theta(log e) | Theta(log e) | O(log e) recursion |
| Celebrity Problem | Elimination | Theta(n) | Theta(n) | Theta(n) | Theta(1) |
| Classical Matrix Multiplication | Iterative | Theta(n^3) | Theta(n^3) | Theta(n^3) | Theta(n^2) result storage |
| Strassen Matrix Multiplication | Divide & Conquer | Theta(n^log2(7)) | Theta(n^log2(7)) | Theta(n^log2(7)) | implementation-dependent temporary matrices |
| Activity Selection | Greedy | O(n log n) with sorting | O(n log n) | O(n log n) | O(n) output |
| Interval Partitioning | Greedy | implementation-dependent | polynomial | implementation-dependent | O(n) |
| Fractional Knapsack | Greedy | O(n^2) | O(n^2) | O(n^2) | O(n) |
| Huffman Coding | Greedy | implementation-dependent | O(n log n) with heap | O(n log n) | O(n) |
| Dijkstra | Greedy/Graph | - | O(V^2) for adjacency matrix | O(V^2) | O(V) |
| Prim | Greedy/Graph | - | O(V^2) for adjacency matrix | O(V^2) | O(V) |
| Kruskal | Greedy/Graph | - | O(E log E) | O(E log E) | O(V + E) |
| 0/1 Knapsack DP | Dynamic Programming | Theta(nW) | Theta(nW) | Theta(nW) | Theta(nW) |
| Matrix Chain Multiplication | Dynamic Programming | Theta(n^3) | Theta(n^3) | Theta(n^3) | Theta(n^2) |
| Longest Common Subsequence | Dynamic Programming | Theta(mn) | Theta(mn) | Theta(mn) | Theta(mn) |
| Optimal BST | Dynamic Programming | implementation-dependent | O(n^3) | O(n^3) | O(n^2) |
| Bellman-Ford | Dynamic Programming/Graph | - | Theta(VE) | Theta(VE) | O(V) |
| Floyd-Warshall | Dynamic Programming/Graph | Theta(V^3) | Theta(V^3) | Theta(V^3) | Theta(V^2) |
| Bounded TSP | Dynamic Programming | exponential | O(n^2 2^n) | O(n^2 2^n) | O(n 2^n) |
| N-Queens | Backtracking | input-dependent | exponential | O(n!) search-space scale | O(n) recursion/state |
| Subset Sum | Backtracking | Omega(1) | exponential | O(2^n) | O(n) |
| 0/1 Knapsack Backtracking | Backtracking | Omega(1) | exponential | O(2^n) | O(n) |
| FIFO Branch & Bound | Branch & Bound | input-dependent | exponential | O(2^n) | exponential frontier possible |
| LIFO Branch & Bound | Branch & Bound | input-dependent | exponential | O(2^n) | O(n) path plus search state |
| Least-Cost Branch & Bound | Branch & Bound | input-dependent | exponential | O(2^n) | exponential frontier possible |
| Ford-Fulkerson | Network Flow | input-dependent | O(EF) for integral capacities | O(EF) | O(V + E) |
| Maximum Bipartite Matching | Matching | input-dependent | O(VE) using augmenting paths | O(VE) | O(V) |
| Naive Pattern Matching | String Matching | Omega(n) | input-dependent | O(nm) | Theta(1) |
| Rabin-Karp | String Matching | O(n+m) expected | O(n+m) expected | O(nm) | O(1) excluding output |
| Finite Automaton Matching | String Matching | Theta(n) search after preprocessing | Theta(n) search | Theta(n) search | preprocessing table |
| KMP | String Matching | Theta(n+m) | Theta(n+m) | Theta(n+m) | O(m) |
| Chinese Remainder Theorem | Number Theory | polynomial | polynomial | polynomial | implementation-dependent |

Here, n generally denotes input size, V vertices, E edges, W knapsack
capacity, F maximum flow value, and m pattern or second-sequence length
depending on the algorithm.

---

# 5. Recurrence Analysis

## 5.1 Merge Sort - Master Theorem

Merge Sort divides the input into two equal subproblems and performs
linear merging work:

T(n) = 2T(n/2) + Theta(n)

Using the Master Theorem:

a = 2  
b = 2  
f(n) = Theta(n)

n^(log_b(a)) = n

Therefore this is the balanced case:

T(n) = Theta(n log n)

This explains why Merge Sort retains the same asymptotic order in its
best, average, and worst cases.

---

## 5.2 Binary Search - Iteration Method

Binary Search repeatedly halves the remaining search interval:

T(n) = T(n/2) + Theta(1)

After k expansions:

T(n) = T(n/2^k) + k Theta(1)

The recursion stops when:

n / 2^k = 1

Therefore:

k = log2(n)

and:

T(n) = Theta(log n)

The iterative implementation uses constant auxiliary space, whereas
the recursive version requires a logarithmic call stack.

---

## 5.3 Fast Power - Substitution

Exponentiation by squaring reduces the exponent approximately by half
at each recursive step:

T(e) = T(e/2) + Theta(1)

Assume:

T(e/2) <= c log(e/2) + d

Then:

T(e) <= c(log e - 1) + d + Theta(1)

With an appropriate constant c:

T(e) = O(log e)

The recursion must also perform one step for every halving of the
exponent, giving:

T(e) = Theta(log e)

---

## 5.4 Strassen - Recursion Tree / Master Theorem

Strassen replaces eight recursive matrix products with seven:

T(n) = 7T(n/2) + Theta(n^2)

Using the Master Theorem:

a = 7  
b = 2

n^(log2 7) is approximately n^2.807.

Since the non-recursive work Theta(n^2) grows more slowly:

T(n) = Theta(n^log2 7)

approximately:

Theta(n^2.807)

This improves asymptotically over classical Theta(n^3) matrix
multiplication.

For very small matrices, however, Strassen's additional recursive and
temporary-storage overhead can dominate its theoretical advantage.

---

## 5.5 Maximum Subarray

The divide-and-conquer formulation recursively solves left and right
halves and evaluates a crossing solution:

T(n) = 2T(n/2) + Theta(n)

Therefore:

T(n) = Theta(n log n)

This is another direct Master-Theorem case.

---

## 5.6 Recurrences Where the Standard Master Theorem Is Not the Best Tool

Not every algorithm in the workbench has a recurrence of the form:

T(n) = aT(n/b) + f(n)

Backtracking algorithms such as Subset Sum and 0/1 Knapsack generate
an include/exclude search tree:

T(n) = 2T(n-1) + Theta(1)

The subproblem size decreases by one rather than being divided by a
constant factor b.

Therefore the standard Master Theorem is not directly applicable.

Expanding the recurrence gives:

T(n)
= 2[2T(n-2) + Theta(1)] + Theta(1)
= 4T(n-2) + Theta(2)
= ...
= 2^n T(0) + Theta(2^n)

Therefore:

T(n) = Theta(2^n)

in the unpruned worst case.

---

# 6. Greedy vs Dynamic Programming vs Backtracking

## 6.1 Fractional Knapsack

The Fractional Knapsack implementation allows partial allocation of an
investigation case.

Cases are ranked by:

risk value / investigation time

and processed greedily in decreasing ratio order.

The current teaching implementation uses insertion sorting, producing
O(n^2) ranking time and O(n) greedy selection time.

For the five-hour demonstration, the workbench obtained:

Maximum Risk Coverage = 143.33

because the final selected investigation could be partially allocated.

---

## 6.2 0/1 Knapsack using Dynamic Programming

For 0/1 Knapsack, each investigation case must either be selected
completely or rejected completely.

The DP formulation considers:

DP[i][w]

representing the best risk value obtainable from the first i cases
under capacity w.

Its complexity is:

Time: Theta(nW)  
Space: Theta(nW)

For the automated oracle with capacity 8:

Optimal Risk = 205

---

## 6.3 0/1 Knapsack using Backtracking

The backtracking implementation recursively explores two decisions for
each case:

1. include the case
2. exclude the case

Branches exceeding the available investigation time are pruned.

Worst-case complexity remains:

Time: O(2^n)  
Recursion Space: O(n)

The automated test produced:

Backtracking Optimal Risk = 205

and explicitly verified:

DP and Backtracking Knapsack agree: PASS

This demonstrates that two different paradigms reach the same optimum
while having substantially different scalability characteristics.

---

# 7. Graph Algorithm Comparisons

## 7.1 Dijkstra vs Bellman-Ford

Dijkstra is efficient when edge weights are non-negative.

The workbench adjacency-matrix implementation has approximately:

O(V^2)

time complexity.

Bellman-Ford repeatedly relaxes edges and supports negative weights:

Theta(VE)

The automated suite verifies that both algorithms return the same
shortest-path result on the positive-weight evidence graph.

Bellman-Ford is therefore more general, while Dijkstra is preferable
under the workbench's non-negative evidence-cost assumption.

---

## 7.2 Prim vs Kruskal

Both algorithms construct a minimum spanning tree.

Prim grows one connected tree by repeatedly selecting a minimum-cost
edge connecting the current tree to a new vertex.

Kruskal processes edges globally in increasing weight order while
avoiding cycles.

The test suite verifies:

Prim MST cost = Kruskal MST cost

for the demonstration evidence network.

---

## 7.3 Floyd-Warshall

Floyd-Warshall computes all-pairs shortest paths using dynamic
programming.

Time:

Theta(V^3)

Space:

Theta(V^2)

It is suitable for the small bounded investigation graphs used for
interactive evidence analysis, but not for millions of PaySim
accounts directly.

---

# 8. String-Matching Comparison

The workbench implements four pattern-search algorithms.

## Naive

Worst-case:

O(nm)

because the pattern may be compared character-by-character at many
text positions.

## Rabin-Karp

Expected:

O(n+m)

under effective hashing.

Worst-case:

O(nm)

when many hash collisions require verification.

## Finite Automaton

After preprocessing, text scanning is linear:

Theta(n)

The preprocessing table requires additional space.

## KMP

KMP constructs a prefix-function table and avoids rechecking
characters unnecessarily.

Time:

Theta(n+m)

Space:

O(m)

The automated suite verifies that all four algorithms return identical
match positions, including overlapping matches.

---

# 9. Branch-and-Bound Comparison

The project implements:

- FIFO Branch and Bound
- LIFO Branch and Bound
- Least-Cost / Best-Bound Branch and Bound

All three solve the same investigation-case selection problem.

The automated oracle reports:

FIFO optimum       = 115  
LIFO optimum       = 115  
Least-Cost optimum = 115

and:

All strategies agree: PASS

The strategies differ primarily in node-expansion order rather than
the mathematical optimum.

Their worst-case search remains exponential because ineffective bounds
may still require exploring a large portion of the combinatorial
search space.

---

# 10. Network Algorithms

## 10.1 Ford-Fulkerson

Ford-Fulkerson models investigation throughput as a capacity network.

For integral capacities, a common bound is:

O(EF)

where F is the maximum-flow value.

The automated oracle verifies:

Maximum Flow = 17

---

## 10.2 Maximum Bipartite Matching

The workbench maps fraud cases to compatible investigators.

Using augmenting-path matching, the implemented approach has
polynomial complexity commonly represented as:

O(VE)

for the simple DFS-based formulation.

The automated oracle verifies a maximum matching size of 4.

---

# 11. Chinese Remainder Theorem

CRT is used in the workbench as a distributed transaction-identifier
reconstruction demonstration.

Independent banking nodes provide modular residues:

x = 2 (mod 3)  
x = 3 (mod 5)  
x = 2 (mod 7)

The workbench reconstructs:

x = 23 (mod 105)

The automated test verifies the smallest non-negative solution 23.

The moduli must be pairwise coprime for the implemented formulation.

---

# 12. Empirical Benchmark Results

## 12.1 Complete Algorithm Benchmark

### Sorting - 10,000 Transactions

| Algorithm | Measured Time |
|---|---:|
| Merge Sort | 21.000 ms |
| Quick Sort | 2.000 ms |

Correctness comparison: PASS

Benchmark transaction memory:

10.76 MB

On this particular deterministic workload and machine, Quick Sort was
substantially faster than Merge Sort.

This measurement does not imply that Quick Sort has a better
worst-case asymptotic bound. Quick Sort can degrade to O(n^2), while
Merge Sort remains Theta(n log n).

---

## 12.2 String Matching - 100,000 Characters

| Algorithm | Measured Time |
|---|---:|
| Naive | 0.000 ms |
| Rabin-Karp | 0.000 ms |
| Finite Automaton | 1.000 ms |
| KMP | 0.000 ms |

Correctness comparison: PASS

Several values fall below the effective resolution of the benchmark
timer. They should therefore be interpreted as "below measurable
resolution for this workload", not literally zero execution cost.

---

## 12.3 Matrix Multiplication - 8 x 8

| Algorithm | Measured Time |
|---|---:|
| Classical | below timer resolution |
| Strassen | below timer resolution |

Correctness comparison: PASS

At this small matrix size, the experiment is primarily a correctness
demonstration rather than a meaningful performance comparison.

Larger matrices or repeated executions would be required to measure
the asymptotic crossover reliably.

---

## 12.4 Graph Algorithms - Six Vertices

Dijkstra, Bellman-Ford, Prim, and Kruskal all completed below the
effective timer resolution for the six-vertex demonstration graph.

Correctness checks:

Shortest-path comparison: PASS  
MST comparison: PASS

These experiments validate algorithm agreement, while theoretical
complexity remains the more meaningful scalability measure at this
small graph size.

---

# 13. PaySim Scalability Evaluation

The full PaySim dataset contains:

6,362,620 transactions

The dynamic loader successfully processed all records with zero
invalid records during the reported run.

## Results

| Records | Time (ms) | Transactions/sec | Approx. Memory (MB) | Precision (%) | Recall (%) | F1 (%) |
|---:|---:|---:|---:|---:|---:|---:|
| 10,000 | 1 | 10,000,000 | 3.59 | 4.04 | 100.00 | 7.76 |
| 100,000 | 5 | 20,000,000 | 35.86 | 0.39 | 100.00 | 0.77 |
| 1,000,000 | 40 | 25,000,000 | 358.58 | 0.16 | 99.25 | 0.31 |
| 6,362,620 | 205 | 31,037,171 | 2,281.52 | 0.38 | 99.73 | 0.76 |

Risk threshold:

50

---

## 13.1 Runtime Scalability

Measured runtime increased from:

1 ms at 10,000 transactions

to:

205 ms at 6,362,620 transactions.

The fraud-evaluation pass processes each transaction a bounded number
of times, so approximately linear growth with transaction count is
consistent with the expected O(n) analysis.

The throughput values should not be interpreted as perfectly stable
hardware limits because short measurements are strongly affected by
timer granularity, caching, CPU frequency scaling, and operating-system
scheduling.

---

## 13.2 Memory Scalability

Approximate dataset memory increased from:

3.59 MB at 10,000 records

to:

2,281.52 MB at 6,362,620 records.

Each transaction occupies fixed-size struct storage, so dataset memory
grows linearly:

Theta(n)

The full dataset therefore requires approximately 2.28 GB for the
transaction array under the current structure representation.

---

## 13.3 Fraud-Detection Quality

At threshold 50, full PaySim evaluation produced:

Precision = 0.38%  
Recall = 99.73%  
F1 = 0.76%

This indicates a strongly recall-oriented heuristic.

The detector identifies almost all ground-truth fraudulent
transactions but also flags many legitimate transactions, producing
low precision.

This is an important limitation rather than a result that should be
hidden.

The workbench should therefore be interpreted as an educational
fraud-triage and investigation-prioritization system rather than an
autonomous production fraud-blocking system.

A human investigator would still need to review generated alerts.

---

# 14. Theoretical vs Empirical Results

The experiments illustrate an important DAA principle:

empirical speed and asymptotic complexity answer different questions.

For example, Quick Sort was much faster than Merge Sort for the
10,000-transaction benchmark even though both have expected
Theta(n log n) behavior and Quick Sort has an O(n^2) worst case.

Similarly, matrix and graph workloads were too small for reliable
timing differentiation, although their theoretical complexities differ
substantially.

PaySim provides a more useful scalability experiment because the
workload spans four orders of magnitude and reaches more than six
million records.

---

# 15. Practical Algorithm Selection

The workbench uses different algorithms because no single algorithmic
paradigm is optimal for every investigation task.

- Merge Sort provides predictable sorting complexity.
- Quick Sort provides strong practical performance on suitable data.
- Binary Search provides logarithmic lookup after ordering.
- KMP provides deterministic linear pattern matching.
- Fractional Knapsack supports divisible investigation allocation.
- 0/1 Knapsack DP provides exact optimization under discrete capacity.
- Backtracking demonstrates exhaustive combinatorial search.
- Branch and Bound attempts to reduce exhaustive exploration using bounds.
- Dijkstra is suitable for non-negative evidence paths.
- Bellman-Ford provides a more general shortest-path formulation.
- Prim and Kruskal provide independent MST strategies.
- Ford-Fulkerson models investigation throughput constraints.
- Bipartite Matching assigns investigators to compatible fraud cases.
- CRT demonstrates modular reconstruction across distributed nodes.

Algorithm choice therefore depends on input constraints, correctness
requirements, graph properties, divisibility assumptions, and expected
data scale.

---

# 16. Limitations of the Experimental Evaluation

The benchmark results have several limitations.

1. Timing uses the project's current clock-based measurement approach.
   Very small workloads can fall below timer resolution.

2. Measurements represent one hardware/software environment and are
   not universal constants.

3. Operating-system scheduling, caching, compiler optimization and CPU
   frequency changes can affect timings.

4. Small graph and matrix demonstrations emphasize correctness rather
   than performance crossover.

5. The PaySim risk scorer is heuristic and intentionally independent
   of the ground-truth fraud label. Its high recall and low precision
   show that additional feature engineering or statistical/ML methods
   would be necessary for production-quality fraud classification.

6. PaySim is a synthetic financial dataset and cannot represent every
   property of real banking traffic.

---

# 17. Conclusion

The Banking Transaction Fraud Investigation Workbench demonstrates
multiple Design and Analysis of Algorithms paradigms within a unified
financial-investigation application.

The theoretical analysis explains expected scalability, while the
automated correctness suite and empirical benchmarks verify practical
behavior.

The most significant scalability experiment processes the complete
6,362,620-record PaySim dataset.

The results show approximately linear transaction-processing and
memory growth for the fraud-evaluation workload, while also exposing
the limitations of the current high-recall heuristic detector.

The combined theoretical and empirical evaluation demonstrates why
algorithm selection must consider not only execution time, but also
space requirements, input assumptions, optimality requirements,
correctness guarantees, and practical workload characteristics.