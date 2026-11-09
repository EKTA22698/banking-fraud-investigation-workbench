# User Guide

## Banking Transaction Fraud Investigation Workbench

## 1. Purpose

The Banking Transaction Fraud Investigation Workbench is a menu-driven
C application for demonstrating Design and Analysis of Algorithms in a
banking-fraud investigation context.

The workbench supports transaction analysis, fraud triage, pattern
searching, investigation-network analysis, optimization, algorithm
demonstrations, benchmarking, testing, and result export.

---

## 2. Build and Run

From the project root:

```powershell
cmake --preset windows-ucrt64
cmake --build --preset windows-ucrt64
.\build\fraud_workbench.exe

### Very small benchmark reports 0.000 ms

A reported value of `0.000 ms` means that the workload completed below
the effective resolution of the current benchmark timer.

It does not mean that the algorithm requires zero execution time.

### Build fails after adding a source file

Confirm that the new `.c` file has been added to `CMakeLists.txt`.

Then reconfigure and rebuild:

```powershell
cmake --preset windows-ucrt64
cmake --build --preset windows-ucrt64
```