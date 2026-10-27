#include <stdio.h>
#include <string.h>

#include "fraud.h"

/*
 * Checks whether the same device is being used
 * by multiple different accounts.
 */
static int count_accounts_using_device(
    const Transaction transactions[],
    int transaction_count,
    int current_index
)
{
    int count = 1;
    int i;

    for (i = 0; i < transaction_count; i++)
    {
        if (i == current_index)
        {
            continue;
        }

        if (strcmp(
                transactions[i].device_id,
                transactions[current_index].device_id
            ) == 0 &&
            strcmp(
                transactions[i].account_id,
                transactions[current_index].account_id
            ) != 0)
        {
            count++;
        }
    }

    return count;
}


static int has_suspicious_description(
    const Transaction *transaction
)
{
    if (strstr(transaction->description, "CRYPTO") != NULL)
    {
        return 1;
    }

    if (strstr(transaction->description, "INTERNATIONAL") != NULL)
    {
        return 1;
    }

    return 0;
}


int calculate_risk_score(
    Transaction transactions[],
    int transaction_count,
    int index
)
{
    int score = 0;

    Transaction *transaction = &transactions[index];

    /*
     * Rule 1:
     * Very high transaction amount.
     */
    if (transaction->amount >= 50000.0)
    {
        score += 35;
    }
    else if (transaction->amount >= 20000.0)
    {
        score += 20;
    }

    /*
     * Rule 2:
     * Same device used by multiple accounts.
     */
    if (count_accounts_using_device(
            transactions,
            transaction_count,
            index
        ) >= 3)
    {
        score += 30;
    }

    /*
     * Rule 3:
     * Suspicious transaction description.
     *
     * Later this simple search will be replaced/
     * complemented by Naive, Rabin-Karp,
     * Finite Automaton and KMP.
     */
    if (has_suspicious_description(transaction))
    {
        score += 20;
    }

    /*
     * Rule 4:
     * Transaction during unusual hours.
     * Timestamp format:
     * YYYY-MM-DDTHH:MM
     */
    if (strlen(transaction->timestamp) >= 13)
    {
        int hour =
            (transaction->timestamp[11] - '0') * 10 +
            (transaction->timestamp[12] - '0');

        if (hour >= 0 && hour < 5)
        {
            score += 15;
        }
    }

    if (score > 100)
    {
        score = 100;
    }

    return score;
}


const char *get_risk_level(int risk_score)
{
    if (risk_score >= 70)
    {
        return "HIGH";
    }

    if (risk_score >= 40)
    {
        return "MEDIUM";
    }

    return "LOW";
}


void analyze_fraud(
    Transaction transactions[],
    int transaction_count
)
{
    int i;
    int suspicious_count = 0;

    if (transaction_count <= 0)
    {
        printf("\nNo dataset is currently loaded.\n");
        printf("Please load a dataset first.\n");
        return;
    }

    printf("\n");
    printf("==========================================================================\n");
    printf("                         FRAUD TRIAGE RESULTS\n");
    printf("==========================================================================\n");

    printf(
        "%-8s %-10s %-10s %-12s %-8s\n",
        "TXN ID",
        "ACCOUNT",
        "AMOUNT",
        "RISK SCORE",
        "LEVEL"
    );

    printf("--------------------------------------------------------------------------\n");

    for (i = 0; i < transaction_count; i++)
    {
        transactions[i].risk_score =
            calculate_risk_score(
                transactions,
                transaction_count,
                i
            );

        /*
         * For the triage screen, show MEDIUM
         * and HIGH risk transactions.
         */
        if (transactions[i].risk_score >= 40)
        {
            suspicious_count++;

            printf(
                "%-8s %-10s %10.2f %-12d %-8s\n",
                transactions[i].transaction_id,
                transactions[i].account_id,
                transactions[i].amount,
                transactions[i].risk_score,
                get_risk_level(
                    transactions[i].risk_score
                )
            );
        }
    }

    printf("==========================================================================\n");

    printf(
        "Suspicious transactions found: %d\n",
        suspicious_count
    );
}