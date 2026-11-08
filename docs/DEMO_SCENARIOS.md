# Banking Fraud Investigation Workbench
## Demonstration Scenarios

---

## Scenario 1: Normal Banking Operation

### Objective

Demonstrate routine fraud triage on a small, interpretable banking transaction dataset.

### Dataset

`data/small/transactions_small.csv`

### Workflow

1. Load the Small Dataset.
2. Review the dataset summary.
3. Run Fraud Investigation.
4. Inspect suspicious transactions.
5. Use transaction search and sorting.
6. Examine the fraud evidence network.
7. Generate an investigation plan.
8. Export investigation results.

### Demonstrated Capabilities

- CSV dataset loading and validation
- Transaction inspection
- Fraud-risk scoring
- Merge Sort and Quick Sort
- Binary Search
- Fraud network analysis
- Investigation prioritization
- CSV/JSON export

### Expected Outcome

The workbench identifies the intentionally suspicious high-value transfer cluster while ordinary transactions remain lower risk.

---

## Scenario 2: Capacity and Constraint Shock

### Objective

Demonstrate how the workbench responds when suspicious transaction volume increases while investigation resources remain limited.

### Dataset

`data/medium/transactions_shock.csv`

### Workflow

1. Load the Capacity Shock dataset.
2. Run Fraud Investigation.
3. Observe the increased suspicious workload.
4. Use Investigation Planning to prioritize cases under a limited time budget.
5. Demonstrate 0/1 Knapsack for case prioritization.
6. Demonstrate Ford-Fulkerson for investigation throughput.
7. Demonstrate Maximum Bipartite Matching for investigator-to-case assignment.

### Demonstrated Algorithms

- 0/1 Knapsack
- Activity Selection
- Interval Partitioning
- Branch and Bound
- Ford-Fulkerson Maximum Flow
- Maximum Bipartite Matching

### Expected Outcome

The system demonstrates that not every alert can be investigated simultaneously and uses optimization algorithms to allocate limited resources.

---

## Scenario 3: Large-Scale PaySim Fraud Investigation

### Objective

Evaluate fraud detection, scalability, and evidence-network analysis on a large public financial transaction dataset.

### Dataset

PaySim public financial fraud dataset.

Total records:

`6,362,620`

The raw PaySim dataset is not stored in the Git repository because of its size.

### Workflow

1. Load the full PaySim dataset.
2. Validate all transaction records.
3. Run fraud investigation with a selected risk threshold.
4. Compare workbench predictions against PaySim ground-truth fraud labels.
5. Review the confusion matrix.
6. Measure Precision, Recall, Accuracy, and F1 Score.
7. Construct a suspicious-account investigation graph.
8. Run graph algorithms on the evidence network.
9. Run the PaySim scalability benchmark.
10. Export predicted suspicious transactions and ground-truth fraud records.

### Fraud Evaluation

The workbench separates its prediction from the PaySim `isFraud` ground-truth field.

The ground-truth label is used only for evaluation and is not used when calculating the workbench risk score.

Evaluation includes:

- True Positives
- False Positives
- True Negatives
- False Negatives
- Accuracy
- Precision
- Recall
- F1 Score

### Graph Analysis

PaySim origin and destination accounts are converted into an investigation subgraph.

Supported algorithms include:

- Dijkstra
- Bellman-Ford
- Floyd-Warshall
- Prim
- Kruskal

### Scalability Evaluation

Fraud analysis is benchmarked at:

- 10,000 transactions
- 100,000 transactions
- 1,000,000 transactions
- Full PaySim dataset

Measurements include:

- Runtime
- Transactions processed per second
- Approximate dataset memory
- Precision
- Recall
- F1 Score

### Expected Outcome

The scenario demonstrates that the workbench can process millions of transactions while providing measurable fraud-detection quality and algorithmic scalability results.

---

## Dataset Roles

| Dataset | Purpose |
|---|---|
| Tiny/Small | Correctness and interpretable demonstrations |
| Medium | Moderate workload testing |
| Capacity Shock | Resource-constrained investigation scenario |
| Large Synthetic | Controlled scalability testing |
| Adversarial | Worst-case algorithm behavior |
| PaySim | Large-scale fraud evaluation and ground truth |

---

## Reproducibility

Synthetic datasets are generated deterministically using the scripts included with the project.

The PaySim raw dataset must be downloaded separately and placed in the expected `data/raw/` location before running the large-scale scenario.