# Evaluation Evidence

## Banking Transaction Fraud Investigation Workbench

This document maps executable evidence to the major implementation,
correctness, scalability, and evaluation requirements of the project.

---

## 1. Main Application

![Main menu](evidence/01_main_menu.png)

The main menu demonstrates the integrated Banking Transaction Fraud
Investigation Workbench and its major functional modules:

- dataset loading
- transaction viewing
- fraud investigation
- search and sorting
- pattern matching
- fraud-network analysis
- investigation planning
- algorithm laboratory
- benchmarking
- automated testing
- result export

---

## 2. Automated Correctness Testing

The automated regression suite covers sorting, searching, divide and
conquer, greedy algorithms, dynamic programming, backtracking, Branch
and Bound, graph algorithms, network flow, bipartite matching, string
matching, number theory, and invalid-input cases.

![Automated tests - part 1](evidence/02.1_test_suite_pass.png)

![Automated tests - part 2](evidence/02.2_test_suite_pass.png)

![Automated tests - part 3](evidence/02.3_test_suite_pass.png)

![Automated tests - summary](evidence/02.4_test_suite_pass.png)

Latest verified regression result:

```text
Tests Run    : 48
Tests Passed : 48
Tests Failed : 0

OVERALL RESULT: PASS
```

The suite also contains cross-algorithm correctness checks, including
DP vs Backtracking Knapsack, Dijkstra vs Bellman-Ford, Prim vs Kruskal,
Classical vs Strassen, and agreement between the string-matching
algorithms.

---

## 3. Full PaySim Dataset Loading

![PaySim loading - part 1](evidence/03.1_paysim_full_load.png)

![PaySim loading - completion](evidence/03.2_paysim_full_load.png)

The dynamic loader processes the complete PaySim dataset.

Verified run:

```text
Valid records      : 6362620
Invalid records    : 0
Allocated capacity : 6362620 transactions
```

This demonstrates large-scale dynamic dataset handling beyond the
fixed synthetic transaction capacity.

---

## 4. Fraud Evaluation

![Fraud evaluation - part 1](evidence/04.1_fraud_evaluation.png)

![Fraud evaluation - metrics](evidence/04.2_fraud_evaluation.png)

The PaySim fraud-investigation workflow compares heuristic predictions
against the dataset ground truth and reports classification-quality
metrics.

The evaluation includes:

- true positives
- false positives
- true negatives
- false negatives
- precision
- recall
- F1 score

At risk threshold 50, the full-dataset benchmark demonstrates a
high-recall but low-precision heuristic, reinforcing that the system
is intended for investigation prioritization rather than autonomous
fraud blocking.

---

## 5. PaySim Scalability

![PaySim scalability - part 1](evidence/05.1_paysim_scalability.png)

![PaySim scalability - completion](evidence/05.2_paysim_scalability.png)

The scalability benchmark evaluates:

- 10,000 transactions
- 100,000 transactions
- 1,000,000 transactions
- 6,362,620 transactions

Measurements include:

- execution time
- throughput
- approximate memory
- precision
- recall
- F1 score

The benchmark demonstrates approximately linear transaction-processing
and dataset-memory growth for the fraud-evaluation workload.

Detailed results are available in:

- `docs/benchmark_results.csv`
- `docs/COMPLEXITY_REPORT.md`
- `docs/BENCHMARK_ENVIRONMENT.md`

---

## 6. Algorithm Comparison Evidence

The following screenshots demonstrate interactive algorithm
experiments and comparisons from the Algorithm Laboratory.

![Algorithm comparison - part 1](evidence/06.1_algorithm_comparison.png)

![Algorithm comparison - part 2](evidence/06.2_algorithm_comparison.png)

![Algorithm comparison - part 3](evidence/06.3_algorithm_comparison.png)

![Algorithm comparison - part 4](evidence/06.4_algorithm_comparison.png)

![Algorithm comparison - part 5](evidence/06.6_algorithm_comparison.png)

These demonstrations complement the automated test suite by showing
algorithm behavior and results interactively.

Implemented comparison areas include:

- Classical vs Strassen matrix multiplication
- Dynamic Programming vs Backtracking 0/1 Knapsack
- FIFO vs LIFO vs Least-Cost Branch and Bound
- shortest-path algorithms
- minimum-spanning-tree algorithms
- multiple string-matching strategies

---

## 7. Supporting Benchmark Figures

### Runtime Scalability

![Runtime scalability](figures/paysim_runtime.png)

### Memory Scalability

![Memory scalability](figures/paysim_memory.png)

### Fraud Detection Quality

![Fraud detection quality](figures/paysim_quality.png)

These figures were generated from the recorded benchmark data rather
than manually estimated values.

---

## 8. Supporting Documentation

The executable evidence is supported by:

- `README.md`
- `docs/USER_GUIDE.md`
- `docs/DEVELOPER_GUIDE.md`
- `docs/DEMO_SCENARIOS.md`
- `docs/COMPLEXITY_REPORT.md`
- `docs/COMPLEXITY_CLASSES.md`
- `docs/BENCHMARK_ENVIRONMENT.md`
- `docs/benchmark_results.csv`

Together these materials document implementation, correctness,
complexity, computational hardness, reproducibility, limitations, and
empirical evaluation.

---

## 9. Verification Summary

| Evidence Area | Status |
|---|---|
| Integrated CLI application | PASS |
| Automated regression suite | 48 / 48 PASS |
| Full PaySim loading | 6,362,620 records |
| Invalid PaySim records in reported run | 0 |
| Fraud-quality evaluation | Demonstrated |
| Large-scale scalability benchmark | Demonstrated |
| Algorithm comparisons | Demonstrated |
| Complexity analysis | Documented |
| P / NP / NP-Complete / NP-Hard analysis | Documented |
| Polynomial-time reduction | Documented |
| Reproducible CMake build | Verified |

---

## 10. Evaluation Position

The evidence demonstrates that the project is not only a collection of
standalone algorithm implementations.

The algorithms are integrated into a coherent banking-fraud
investigation application and are supported by:

- deterministic correctness testing;
- cross-algorithm comparisons;
- theoretical complexity analysis;
- empirical benchmarks;
- large-scale PaySim evaluation;
- documented limitations and responsible-use considerations.