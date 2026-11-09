# Benchmark Environment

## Hardware

- Processor: Intel(R) Core(TM) Ultra 5 125H
- Physical CPU cores: 14
- Logical processors: 18
- Physical memory: approximately 16 GB

## Software

- Operating system: Microsoft Windows NT 10.0.26300.0
- Compiler: GCC 16.2.0
- Compiler distribution: MSYS2 UCRT64
- Build system: CMake 4.4.4
- Build preset: windows-ucrt64
- Programming language: C

## Large-Scale Dataset

PaySim Public Fraud Dataset

- Records loaded: 6,362,620
- Invalid records during reported run: 0
- Dynamic allocation used for full dataset loading

## Fraud Benchmark Configuration

- Risk threshold: 50
- Evaluation sizes:
  - 10,000 transactions
  - 100,000 transactions
  - 1,000,000 transactions
  - 6,362,620 transactions

## Timing Note

Very small algorithm workloads may complete below the effective
resolution of the current clock-based timer.

A reported value of 0.000 ms therefore means that the workload
completed below measurable timer resolution for that run; it does not
mean that the algorithm has zero execution cost.

Large-scale PaySim measurements provide more meaningful scalability
evidence because the workload extends to more than six million
transactions.