#include <stdio.h>

#include "export_menu.h"
#include "export.h"


void run_export_menu(
    Transaction transactions[],
    size_t transaction_count,
    int is_paysim
)
{
    if (
        transactions == NULL ||
        transaction_count == 0
    )
    {
        printf(
            "No dataset is currently loaded.\n"
        );

        return;
    }


    int export_choice;


    printf("\n");
    printf("============================================================\n");
    printf("                     EXPORT RESULTS\n");
    printf("============================================================\n");

    printf("1. Export Sample (first 1,000) as CSV\n");
    printf("2. Export Sample (first 1,000) as JSON\n");
    printf("3. Export Suspicious Transactions as CSV\n");

    if (is_paysim)
    {
        printf(
            "4. Export Actual PaySim Fraud as CSV\n"
        );
    }

    printf("5. Export Full Dataset as CSV\n");
    printf("0. Back\n");

    printf("============================================================\n");
    printf("Select export: ");


    if (
        scanf(
            "%d",
            &export_choice
        ) != 1
    )
    {
        printf(
            "Invalid input.\n"
        );

        while (getchar() != '\n')
        {
        }

        return;
    }


    size_t sample_count =
        transaction_count < 1000
            ? transaction_count
            : 1000;


    /*
     * SAMPLE CSV
     */
    if (export_choice == 1)
    {
        if (
            export_transactions_csv(
                "results/transactions_sample.csv",
                transactions,
                sample_count
            )
        )
        {
            printf(
                "\nExported %zu transactions to:\n"
                "results/transactions_sample.csv\n",
                sample_count
            );
        }
        else
        {
            printf(
                "\nERROR: CSV export failed.\n"
            );
        }
    }


    /*
     * SAMPLE JSON
     */
    else if (export_choice == 2)
    {
        if (
            export_transactions_json(
                "results/transactions_sample.json",
                transactions,
                sample_count
            )
        )
        {
            printf(
                "\nExported %zu transactions to:\n"
                "results/transactions_sample.json\n",
                sample_count
            );
        }
        else
        {
            printf(
                "\nERROR: JSON export failed.\n"
            );
        }
    }


    /*
     * PREDICTED SUSPICIOUS TRANSACTIONS
     */
    else if (export_choice == 3)
    {
        int threshold;

        printf(
            "Enter risk threshold: "
        );

        if (
            scanf(
                "%d",
                &threshold
            ) != 1
        )
        {
            printf(
                "Invalid risk threshold.\n"
            );

            while (getchar() != '\n')
            {
            }

            return;
        }


        if (
            threshold < 0 ||
            threshold > 100
        )
        {
            printf(
                "Risk threshold must be "
                "between 0 and 100.\n"
            );

            return;
        }


        if (
            export_suspicious_csv(
                "results/suspicious_transactions.csv",
                transactions,
                transaction_count,
                threshold
            )
        )
        {
            printf(
                "\nSuspicious transactions exported to:\n"
                "results/suspicious_transactions.csv\n"
            );
        }
        else
        {
            printf(
                "\nERROR: Export failed.\n"
            );
        }
    }


    /*
     * PAYSIM GROUND TRUTH
     */
    else if (
        export_choice == 4 &&
        is_paysim
    )
    {
        if (
            export_actual_fraud_csv(
                "results/paysim_actual_fraud.csv",
                transactions,
                transaction_count
            )
        )
        {
            printf(
                "\nPaySim ground-truth fraud exported to:\n"
                "results/paysim_actual_fraud.csv\n"
            );
        }
        else
        {
            printf(
                "\nERROR: Export failed.\n"
            );
        }
    }


    /*
     * FULL DATASET
     */
    else if (export_choice == 5)
    {
        printf(
            "\nWARNING: Full export contains "
            "%zu transactions.\n",
            transaction_count
        );

        printf(
            "This may create a very large file.\n"
        );

        printf(
            "Continue? (Y/N): "
        );


        char confirm;

        if (
            scanf(
                " %c",
                &confirm
            ) != 1
        )
        {
            printf(
                "Invalid input.\n"
            );

            return;
        }


        if (
            confirm != 'Y' &&
            confirm != 'y'
        )
        {
            printf(
                "Full export cancelled.\n"
            );

            return;
        }


        if (
            export_transactions_csv(
                "results/transactions_full.csv",
                transactions,
                transaction_count
            )
        )
        {
            printf(
                "\nFull dataset exported successfully.\n"
            );
        }
        else
        {
            printf(
                "\nERROR: Full export failed.\n"
            );
        }
    }


    else if (export_choice != 0)
    {
        printf(
            "Invalid export choice.\n"
        );
    }
}