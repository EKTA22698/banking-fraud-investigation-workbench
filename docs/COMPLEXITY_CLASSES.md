# Computational Complexity Classes and Polynomial-Time Reduction

## Banking Transaction Fraud Investigation Workbench

---

## 1. Purpose

This document discusses the computational complexity classes relevant
to the Banking Transaction Fraud Investigation Workbench.

The project contains both polynomial-time algorithms and
combinatorial optimization problems whose general forms are
computationally difficult.

The discussion covers:

- P
- NP
- NP-Complete
- NP-Hard
- decision versus optimization problems
- polynomial-time reduction
- Subset Sum to 0/1 Knapsack reduction
- implications for investigation planning

---

# 2. Class P

P is the class of decision problems that can be solved in polynomial
time by a deterministic algorithm.

Polynomial-time algorithms are generally considered computationally
tractable because their running time is bounded by:

O(n^k)

for some constant k.

Several algorithms used by the workbench solve problems that have
polynomial-time solutions.

Examples include:

- Binary Search
- Merge Sort
- Quick Sort in its expected case
- Dijkstra's shortest-path algorithm
- Bellman-Ford
- Floyd-Warshall
- Prim's minimum spanning tree algorithm
- Kruskal's minimum spanning tree algorithm
- Ford-Fulkerson for integral capacities under the O(EF) analysis
- Bipartite Matching
- KMP string matching
- Matrix Chain Multiplication using dynamic programming
- Longest Common Subsequence using dynamic programming

These algorithms can process increasingly large inputs without
requiring exhaustive enumeration of every possible solution.

---

# 3. Class NP

NP is the class of decision problems for which a proposed solution can
be verified in polynomial time.

NP does not mean "non-polynomial."

Instead, it means that if a candidate certificate or solution is
provided, its correctness can be checked efficiently.

For example, consider the decision version of Subset Sum:

"Does there exist a subset whose values sum exactly to target T?"

If somebody provides a subset, the workbench can add its elements and
verify the target in polynomial time.

Therefore Subset Sum belongs to NP.

Similarly, for the decision version of Travelling Salesperson:

"Does there exist a tour with total cost at most K?"

Given a proposed tour, the program can verify that every required
vertex is visited and calculate its total cost in polynomial time.

---

# 4. NP-Complete Problems

A problem is NP-Complete when:

1. it belongs to NP, and
2. every problem in NP can be polynomially reduced to it.

NP-Complete problems are therefore among the hardest decision
problems in NP.

If any NP-Complete problem were solved by a deterministic
polynomial-time algorithm, then every problem in NP would also have a
polynomial-time solution, implying:

P = NP

No such general polynomial-time algorithm is currently known.

Problems represented in the workbench whose standard decision
versions are NP-Complete include:

- Subset Sum
- 0/1 Knapsack decision problem
- Travelling Salesperson decision problem

---

# 5. NP-Hard Problems

A problem is NP-Hard if it is at least as hard as every problem in NP.

An NP-Hard problem does not necessarily need to be a decision problem
and does not necessarily need to belong to NP.

Optimization versions of several problems in the workbench are
NP-Hard.

Examples include:

- optimization Travelling Salesperson Problem
- optimization 0/1 Knapsack Problem

For example, the workbench's bounded TSP asks for the minimum-cost
investigation route rather than only asking whether a route below a
given threshold exists.

This optimization form is NP-Hard.

---

# 6. Decision vs Optimization Problems

The distinction between decision and optimization formulations is
important.

## 6.1 0/1 Knapsack

Decision version:

"Is there a subset of investigation cases whose total investigation
time is at most W and whose total risk value is at least V?"

This standard decision problem is NP-Complete.

Optimization version:

"What is the maximum risk value achievable with investigation time at
most W?"

This optimization problem is NP-Hard.

The workbench solves the optimization form using dynamic programming
for bounded integer capacity and also demonstrates an exponential
backtracking solution.

---

## 6.2 Travelling Salesperson Problem

Decision version:

"Does an investigation tour exist with total route cost at most K?"

The standard decision version is NP-Complete.

Optimization version:

"What is the minimum possible investigation-tour cost?"

The optimization version is NP-Hard.

The workbench deliberately bounds the number of vertices so that an
exact dynamic-programming solution remains practical for educational
demonstrations.

---

# 7. Polynomial-Time Reduction

A polynomial-time reduction transforms an instance of one problem A
into an instance of another problem B in polynomial time.

It is written:

A <=p B

A reduction demonstrates that if B could be solved efficiently, then
A could also be solved efficiently after performing the transformation.

Polynomial reductions are therefore a central technique for
establishing computational hardness.

---

# 8. Reduction: Subset Sum to 0/1 Knapsack

The workbench implements both Subset Sum and 0/1 Knapsack, making this
reduction directly relevant to the project.

We show:

Subset Sum <=p 0/1 Knapsack Decision

Suppose a Subset Sum instance contains positive integers:

a1, a2, ..., an

and target:

T

The question is:

"Does some subset sum exactly to T?"

---

## 8.1 Constructing the Knapsack Instance

For every Subset Sum value ai, create one Knapsack item.

Set:

weight_i = ai

and:

value_i = ai

Set the Knapsack capacity to:

W = T

and the required value to:

V = T

The resulting Knapsack decision question becomes:

"Is there a subset of items whose total weight is at most T and whose
total value is at least T?"

---

## 8.2 Forward Direction

Assume the Subset Sum instance has a subset whose sum is exactly T.

Because each Knapsack item's weight and value both equal ai, selecting
the corresponding items gives:

total weight = T

and:

total value = T

Therefore:

total weight <= W

and:

total value >= V

so the constructed Knapsack instance is YES.

---

## 8.3 Reverse Direction

Assume the constructed Knapsack instance is YES.

Then some selected items satisfy:

total weight <= T

and:

total value >= T

But each item's weight equals its value.

Therefore total weight and total value are numerically identical.

The two inequalities can simultaneously hold only when:

total weight = total value = T

Thus the corresponding original values form a subset whose sum is
exactly T.

Therefore the original Subset Sum instance is also YES.

---

## 8.4 Transformation Cost

Creating the Knapsack instance requires processing each of the n input
values once.

Therefore the transformation requires:

O(n)

time and O(n) output storage.

This is polynomial.

Hence:

Subset Sum <=p 0/1 Knapsack Decision

This reduction helps explain why the decision version of 0/1 Knapsack
is computationally difficult.

---

# 9. Why Dynamic Programming Does Not Make Knapsack Polynomial in Input Length

The workbench's dynamic-programming 0/1 Knapsack implementation has
complexity:

O(nW)

where:

n = number of items  
W = numerical capacity

At first this may appear polynomial.

However, W is represented in binary using approximately:

log W

bits.

Therefore O(nW) is not polynomial in the bit-length of the general
input.

The algorithm is described as pseudo-polynomial.

This is consistent with the NP-Complete classification of the
decision version of 0/1 Knapsack.

---

# 10. Backtracking and Computational Hardness

The workbench also solves 0/1 Knapsack using backtracking.

For every investigation case, two decisions are possible:

- include
- exclude

This produces an unpruned binary search tree containing up to:

2^n

candidate subsets.

Therefore the worst-case running time is exponential:

O(2^n)

The automated test suite confirms that the DP and backtracking
implementations return the same optimum on the same investigation
instance.

This demonstrates an important distinction:

correctness does not imply equal scalability.

---

# 11. Subset Sum

The workbench's Subset Sum implementation uses backtracking.

For n values, each value can potentially be either included or
excluded.

The worst-case search therefore contains exponentially many subsets:

O(2^n)

The standard decision version of Subset Sum is NP-Complete.

A candidate subset, however, can be verified in polynomial time by
adding its values and comparing the result with the target.

---

# 12. Bounded TSP in the Workbench

The project intentionally places a strict bound on the number of
vertices accepted by the exact TSP demonstration.

This is an engineering decision motivated by computational
complexity.

The implemented dynamic-programming formulation requires approximately:

O(n^2 * 2^n)

time and:

O(n * 2^n)

space.

The exponential term means that doubling the input size can increase
the amount of required work dramatically.

Therefore the exact solver is appropriate for small investigation
routing scenarios but not for large transaction networks.

Large fraud networks should instead use other graph-analysis methods
or approximation/heuristic approaches depending on the required
problem.

---

# 13. Fractional Knapsack Is Different

Fractional Knapsack must not be confused with 0/1 Knapsack.

In Fractional Knapsack, an item can be partially selected.

This property permits a greedy optimal strategy:

1. compute value-to-weight ratio
2. sort items by decreasing ratio
3. take the highest-ratio items first
4. take a fraction of the final item when required

The workbench maps this to divisible investigation effort.

Because fractional selection changes the mathematical problem,
Fractional Knapsack has a polynomial-time greedy solution.

In contrast, general 0/1 Knapsack optimization is NP-Hard.

---

# 14. N-Queens Classification Note

The workbench demonstrates N-Queens using backtracking.

An exponential implementation does not by itself prove that a problem
is NP-Complete or NP-Hard.

Complexity classes describe problems, not merely the running time of a
particular implementation.

Therefore this report does not classify N-Queens as NP-Complete simply
because the demonstration uses exponential backtracking.

This distinction prevents a common complexity-analysis error.

---

# 15. Branch and Bound

Branch and Bound does not change the worst-case computational hardness
of an NP-Hard optimization problem.

Instead, it attempts to avoid exploring parts of the search space that
cannot improve the current best solution.

The workbench demonstrates:

- FIFO Branch and Bound
- LIFO Branch and Bound
- Least-Cost / Best-Bound Branch and Bound

The three strategies differ in node-expansion order.

The automated test suite verifies that all three produce the same
optimal result for the demonstration instance.

In favorable cases, bounding can reduce practical search substantially.

In the worst case, however, exponentially many states may still need
to be explored.

---

# 16. Complexity Classification Summary

| Problem / Algorithm | Classification / Characteristic |
|---|---|
| Binary Search | Polynomial-time |
| Merge Sort | Polynomial-time |
| Quick Sort | Polynomial expected time; quadratic worst case |
| KMP | Polynomial-time |
| Dijkstra | Polynomial-time |
| Bellman-Ford | Polynomial-time |
| Floyd-Warshall | Polynomial-time |
| Prim | Polynomial-time |
| Kruskal | Polynomial-time |
| Ford-Fulkerson with integral capacities | Polynomial in E and numeric flow value under O(EF); this bound is pseudo-polynomial with respect to capacity bit-length |
| Bipartite Matching | Polynomial-time |
| Fractional Knapsack | Polynomial-time |
| 0/1 Knapsack Decision | NP-Complete |
| 0/1 Knapsack Optimization | NP-Hard |
| Subset Sum Decision | NP-Complete |
| TSP Decision | NP-Complete |
| TSP Optimization | NP-Hard |
| Bounded exact TSP implementation | Exponential-time exact algorithm |

---

# 17. Implications for Fraud Investigation

The complexity classifications influence the architecture of the
workbench.

Polynomial algorithms are suitable for frequent operations such as:

- searching transactions
- sorting records
- pattern matching
- shortest-path analysis
- spanning-tree analysis
- matching investigators to cases
- evaluating transaction streams

Computationally difficult exact algorithms are instead used on bounded
investigation subproblems such as:

- selecting discrete investigation cases
- solving small routing problems
- demonstrating exhaustive/backtracking search
- comparing Branch-and-Bound strategies

This separation allows the workbench to process millions of PaySim
transactions while still demonstrating computationally difficult DAA
problems on appropriately bounded instances.

---

# 18. Conclusion

The Banking Transaction Fraud Investigation Workbench contains both
tractable polynomial-time algorithms and bounded demonstrations of
computationally difficult combinatorial problems.

The distinction between P, NP, NP-Complete, and NP-Hard explains why
some operations can be applied directly to large transaction datasets
while other exact algorithms must operate on small investigation
subproblems.

The polynomial-time reduction:

Subset Sum <=p 0/1 Knapsack Decision

connects two algorithms implemented by the project and demonstrates
how computational hardness can be transferred through a polynomial
mapping.

The project therefore demonstrates not only algorithm implementation,
but also the relationship between theoretical complexity,
algorithmic paradigm, exact optimization, and practical system design.