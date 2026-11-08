#include <stdio.h>

#include "fraud_menu.h"
#include "fraud.h"


void run_fraud_menu(
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

        printf(
            "Please load a dataset first.\n"
        );

        return;
    }


    /*
     * PaySim large-scale fraud evaluation.
     */
    if (is_paysim)
    {
        int threshold;

        printf("\n");
        printf("============================================================\n");
        printf("             PAYSIM FRAUD INVESTIGATION\n");
        printf("============================================================\n");

        printf(
            "Transactions: %zu\n",
            transaction_count
        );

        printf(
            "Enter risk threshold (0-100) "
            "[recommended: 50]: "
        );


        if (
            scanf(
                "%d",
                &threshold
            ) != 1
        )
        {
            printf(
                "Invalid threshold.\n"
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


        printf(
            "\nAnalyzing %zu transactions...\n",
            transaction_count
        );


        FraudEvaluation evaluation =
            evaluate_paysim_fraud(
                transactions,
                transaction_count,
                threshold
            );


        print_fraud_evaluation(
            &evaluation,
            threshold
        );


        return;
    }


    /*
     * Original/synthetic datasets.
     */
    analyze_fraud(
        transactions,
        (int)transaction_count
    );
}