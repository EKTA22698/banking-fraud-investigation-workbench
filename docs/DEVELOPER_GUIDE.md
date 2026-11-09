# Developer Guide

## Banking Transaction Fraud Investigation Workbench

## 1. Architecture

The project separates application control, domain/data management,
algorithms, CLI modules, benchmarking, and testing.

```text
main.c
  |
  +-- ApplicationState
  |
  +-- CLI modules
        |
        +-- dataset menu
        +-- transaction viewer
        +-- fraud menu
        +-- search/sort menu
        +-- pattern menu
        +-- graph menu
        +-- planning menu
        +-- algorithm laboratory
        +-- benchmark menu
        +-- test menu
        +-- export menu
                |
                v
          Algorithm Library
```

`main.c` should remain a thin controller. New substantial functionality
should normally be placed in an appropriate module instead of expanding
the main switch body.

---

## 2. Source Organization

```text
src/
+-- main.c
+-- algorithms/
+-- benchmark/
+-- cli/
+-- core/
+-- tests/
```

### algorithms/

Contains reusable algorithm implementations grouped by paradigm or
problem family.

### cli/

Contains menu/controller logic.

CLI modules should call reusable algorithms rather than reimplementing
them.

### core/

Contains core application and data-management functionality, including
central application state and dataset-loading support.

### benchmark/

Contains algorithm and scalability benchmark implementations.

### tests/

Contains deterministic correctness tests and cross-algorithm oracles.

---

## 3. Application State

The application uses `ApplicationState` to centralize dataset ownership
and active-dataset selection.

It tracks:

- fixed transaction storage
- fixed dataset count
- dynamically allocated PaySim storage
- whether the dynamic dataset is active
- active transaction pointer
- active transaction count

This prevents individual CLI modules from independently managing dataset
ownership.

---

## 4. Dataset Ownership

Synthetic datasets use fixed application transaction storage.

The full PaySim dataset uses dynamic allocation because it contains
millions of records.

When switching between dataset types, ownership must be handled
carefully so that:

- old dynamic memory is released;
- active pointers do not reference freed memory;
- application cleanup does not double-free storage.

Dataset cleanup should remain centralized.

---

## 5. Algorithm Modules

Public algorithm declarations are stored under `include/`.

Implementations are stored under `src/algorithms/`.

A new reusable algorithm should normally follow this workflow:

1. Define public structures and constants in the relevant header.
2. Declare the public function.
3. Implement it in the appropriate algorithm directory.
4. Register the `.c` source in `CMakeLists.txt`.
5. Add deterministic automated tests.
6. Optionally expose it through the Algorithm Laboratory.
7. Document its theoretical complexity.

---

## 6. CLI Module Pattern

CLI modules expose small public entry points such as:

```c
void run_planning_menu(void);
```

or functions receiving the currently active dataset.

The CLI layer is responsible for:

- prompting users;
- validating interactive input;
- formatting results;
- invoking reusable algorithms.

Algorithm implementations should not depend on the main menu.

---

## 7. Error Handling

Input validation should occur before algorithm execution.

Typical invalid cases include:

- null arrays
- zero or negative sizes
- invalid capacities
- invalid graph vertices
- unsupported thresholds
- malformed interactive input

Reusable algorithms should return safe empty or default results when
appropriate.

---

## 8. Testing Strategy

The automated test suite uses deterministic correctness oracles.

Examples include:

- known sorting order
- known Binary Search identifier
- known Maximum Subarray result
- known Fast Power result
- Classical vs Strassen equality
- Dijkstra vs Bellman-Ford agreement
- Prim vs Kruskal MST-cost agreement
- all four string matchers agreeing
- Dynamic Programming vs Backtracking 0/1 Knapsack agreement
- known CRT solution

Latest verified state:

```text
Tests Run    : 48
Tests Passed : 48
Tests Failed : 0

OVERALL RESULT: PASS
```

A feature should not be considered complete until the full regression
suite passes.

---

## 9. Benchmarking

Benchmark code is separated from algorithm implementations.

The benchmark layer measures practical behavior without changing the
algorithm's correctness logic.

Current benchmark groups include:

- sorting
- string matching
- matrix multiplication
- graph algorithms
- complete benchmark suite
- PaySim scalability and fraud quality

Raw PaySim scalability measurements are stored in:

```text
docs/benchmark_results.csv
```

Figures can be regenerated with:

```powershell
python scripts\generate_benchmark_graphs.py
```

Matplotlib is required only for documentation graph generation. It is
not required to build or run the C application.

---

## 10. Build System

The project uses CMake.

Windows/MSYS2 configuration:

```powershell
cmake --preset windows-ucrt64
cmake --build --preset windows-ucrt64
```

Generated `build/` artifacts are excluded from version control.

When adding a new `.c` file, ensure it is registered in
`CMakeLists.txt`.

---

## 11. Clean-Build Verification

Before a release, perform:

```powershell
Remove-Item -Recurse -Force build
cmake --preset windows-ucrt64
cmake --build --preset windows-ucrt64
```

Then run:

```powershell
.\build\fraud_workbench.exe
```

and execute the automated test suite.

This confirms that the repository can reproduce the executable without
stale build artifacts.

---

## 12. PaySim

The raw PaySim file is intentionally excluded from version control.

Expected local location:

```text
data/raw/PS_20174392719_1491204439457_log.csv
```

The dynamic loader:

- skips the CSV header;
- validates parsed records;
- expands storage as required;
- reports progress for large loads;
- shrinks storage to the successfully loaded record count where
  possible.

Ground-truth fraud labels are retained for evaluation.

They must not be used as direct inputs to heuristic fraud scoring.

---

## 13. Performance Considerations

Do not apply algorithms blindly to the full PaySim dataset.

Examples:

- bounded TSP is intentionally limited;
- investigation graphs are bounded;
- backtracking is demonstrated on small instances;
- Branch and Bound can remain exponential;
- full-dataset exports can be very large.

Algorithm selection should respect theoretical complexity and memory
requirements.

---

## 14. Documentation

Important documentation files include:

```text
README.md
docs/USER_GUIDE.md
docs/DEVELOPER_GUIDE.md
docs/DEMO_SCENARIOS.md
docs/COMPLEXITY_REPORT.md
docs/COMPLEXITY_CLASSES.md
docs/BENCHMARK_ENVIRONMENT.md
docs/benchmark_results.csv
```

When algorithms or benchmark methodology change, the corresponding
documentation should also be updated.

---

## 15. Release Checklist

Before creating a release:

1. Perform a clean CMake build.
2. Run all automated tests.
3. Confirm zero failed tests.
4. Run the three demonstration scenarios.
5. Verify PaySim loading if the local dataset is available.
6. Run `git diff --check`.
7. Ensure generated result and build files are not staged.
8. Review README and documentation.
9. Capture required evaluation screenshots.
10. Create the final release tag only after verification.

---

## 16. Current Verified Project State

The current verified implementation includes:

- full PaySim dynamic loading of 6,362,620 transactions;
- 48/48 automated tests passing;
- Fractional Knapsack using Greedy allocation;
- 0/1 Knapsack using Dynamic Programming;
- 0/1 Knapsack using Backtracking;
- Branch-and-Bound strategy comparison;
- graph, network-flow, string-matching, and number-theory modules;
- empirical benchmark and scalability evidence;
- theoretical complexity analysis;
- P/NP/NP-Complete/NP-Hard analysis;
- polynomial-time reduction documentation.

The implementation should remain frozen during final submission
preparation unless a verified defect or mandatory requirement is found.