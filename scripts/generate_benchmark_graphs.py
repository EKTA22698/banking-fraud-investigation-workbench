import csv
from pathlib import Path

import matplotlib.pyplot as plt


ROOT = Path(__file__).resolve().parent.parent
CSV_FILE = ROOT / "docs" / "benchmark_results.csv"
OUTPUT_DIR = ROOT / "docs" / "figures"

OUTPUT_DIR.mkdir(parents=True, exist_ok=True)


records = []
time_ms = []
memory_mb = []
precision = []
recall = []
f1 = []


with CSV_FILE.open("r", newline="", encoding="utf-8") as file:
    reader = csv.DictReader(file)

    for row in reader:
        records.append(int(row["records"]))
        time_ms.append(float(row["time_ms"]))
        memory_mb.append(float(row["memory_mb"]))
        precision.append(float(row["precision_percent"]))
        recall.append(float(row["recall_percent"]))
        f1.append(float(row["f1_percent"]))


# ---------------------------------------------------------
# Runtime scalability
# ---------------------------------------------------------

plt.figure(figsize=(8, 5))

plt.plot(
    records,
    time_ms,
    marker="o"
)

plt.title(
    "PaySim Fraud Analysis Runtime Scalability"
)

plt.xlabel(
    "Transactions"
)

plt.ylabel(
    "Execution Time (ms)"
)

plt.grid(
    True,
    alpha=0.3
)

plt.tight_layout()

plt.savefig(
    OUTPUT_DIR / "paysim_runtime.png",
    dpi=200
)

plt.close()


# ---------------------------------------------------------
# Memory scalability
# ---------------------------------------------------------

plt.figure(figsize=(8, 5))

plt.plot(
    records,
    memory_mb,
    marker="o"
)

plt.title(
    "PaySim Dataset Memory Scalability"
)

plt.xlabel(
    "Transactions"
)

plt.ylabel(
    "Approximate Memory (MB)"
)

plt.grid(
    True,
    alpha=0.3
)

plt.tight_layout()

plt.savefig(
    OUTPUT_DIR / "paysim_memory.png",
    dpi=200
)

plt.close()


# ---------------------------------------------------------
# Fraud-detection quality
# ---------------------------------------------------------

plt.figure(figsize=(8, 5))

plt.plot(
    records,
    precision,
    marker="o",
    label="Precision"
)

plt.plot(
    records,
    recall,
    marker="o",
    label="Recall"
)

plt.plot(
    records,
    f1,
    marker="o",
    label="F1"
)

plt.title(
    "PaySim Fraud Detection Quality"
)

plt.xlabel(
    "Transactions"
)

plt.ylabel(
    "Metric (%)"
)

plt.ylim(
    0,
    105
)

plt.grid(
    True,
    alpha=0.3
)

plt.legend()

plt.tight_layout()

plt.savefig(
    OUTPUT_DIR / "paysim_quality.png",
    dpi=200
)

plt.close()


print("Benchmark graphs generated successfully:")
print("  docs/figures/paysim_runtime.png")
print("  docs/figures/paysim_memory.png")
print("  docs/figures/paysim_quality.png")