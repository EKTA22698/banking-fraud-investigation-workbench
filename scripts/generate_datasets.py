import csv
import os


HEADER = [
    "transaction_id",
    "account_id",
    "device_id",
    "merchant_id",
    "amount",
    "type",
    "timestamp",
    "description",
]


def make_transaction(index, scenario):
    transaction_id = f"T{index:06d}"

    account_id = f"A{1000 + (index % 500):04d}"
    device_id = f"D{1 + (index % 150):03d}"
    merchant_id = f"M{1 + (index % 100):03d}"

    amount = float(
        ((index * 7919) % 50000) + 100
    )

    transaction_type = (
        "UPI"
        if index % 3 == 0
        else "CARD"
        if index % 3 == 1
        else "TRANSFER"
    )

    hour = index % 24
    minute = (index * 7) % 60

    timestamp = (
        f"2026-10-28T{hour:02d}:{minute:02d}"
    )

    description = "NORMAL PAYMENT"

    # Inject realistic suspicious clusters.
    if index % 97 == 0:
        amount = 85000.0
        transaction_type = "TRANSFER"
        device_id = "D099"
        merchant_id = "M080"
        description = "CRYPTO TRANSFER"

    if index % 193 == 0:
        amount = 95000.0
        transaction_type = "TRANSFER"
        device_id = "D099"
        merchant_id = "M081"
        description = "INTERNATIONAL TRANSFER"

    # Capacity-shock scenario:
    # much larger concentration of suspicious cases.
    if scenario == "shock" and index % 10 == 0:
        amount = 99000.0
        transaction_type = "TRANSFER"
        device_id = "D099"
        merchant_id = "M080"
        description = "CRYPTO TRANSFER"

    # Adversarial data for sorting/pattern behavior.
    if scenario == "adversarial":
        amount = float(index)
        transaction_type = "TRANSFER"
        description = "AAAAAAAAAAAAAAAAAAAA"

    return [
        transaction_id,
        account_id,
        device_id,
        merchant_id,
        f"{amount:.2f}",
        transaction_type,
        timestamp,
        description,
    ]


def generate_file(path, count, scenario):
    os.makedirs(
        os.path.dirname(path),
        exist_ok=True
    )

    with open(
        path,
        "w",
        newline="",
        encoding="utf-8"
    ) as file:
        writer = csv.writer(file)
        writer.writerow(HEADER)

        for index in range(1, count + 1):
            writer.writerow(
                make_transaction(
                    index,
                    scenario
                )
            )

    print(
        f"Generated {path}: "
        f"{count} transactions"
    )


def main():
    generate_file(
        "data/medium/transactions_medium.csv",
        1000,
        "normal"
    )

    generate_file(
        "data/large/transactions_large.csv",
        10000,
        "normal"
    )

    generate_file(
        "data/adversarial/transactions_adversarial.csv",
        10000,
        "adversarial"
    )

    generate_file(
        "data/medium/transactions_shock.csv",
        1000,
        "shock"
    )


if __name__ == "__main__":
    main()