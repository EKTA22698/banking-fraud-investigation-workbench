#include <stdio.h>

#include "fraud.h"
#include "transaction.h"


static int calculate_paysim_risk(
    const Transaction *transaction
)
{
    int risk = 0;

    /*
     * Large transactions.
     */
    if (transaction->amount >= 200000.0)
    {
        risk += 30;
    }
    else if (transaction->amount >= 100000.0)
    {
        risk += 20;
    }
    else if (transaction->amount >= 50000.0)
    {
        risk += 10;
    }


    /*
     * PaySim fraud is especially associated
     * with TRANSFER and CASH_OUT operations.
     */
    if (
        transaction->transaction_type[0] == 'T'
    )
    {
        risk += 20;
    }

    else if (
        transaction->transaction_type[0] == 'C' &&
        transaction->transaction_type[1] == 'A' &&
        transaction->transaction_type[2] == 'S' &&
        transaction->transaction_type[3] == 'H' &&
        transaction->transaction_type[4] == '_' &&
        transaction->transaction_type[5] == 'O'
    )
    {
        risk += 20;
    }


    /*
     * Origin account becomes empty after
     * moving a significant balance.
     */
    if (
        transaction->old_balance_origin > 0.0 &&
        transaction->new_balance_origin == 0.0 &&
        transaction->amount >=
            transaction->old_balance_origin * 0.90
    )
    {
        risk += 30;
    }


    /*
     * Large balance inconsistency.
     */
    double expected_origin =
        transaction->old_balance_origin -
        transaction->amount;

    double difference =
        expected_origin -
        transaction->new_balance_origin;

    if (difference < 0.0)
    {
        difference = -difference;
    }

    if (difference > 1000.0)
    {
        risk += 10;
    }


    if (risk > 100)
    {
        risk = 100;
    }

    return risk;
}


FraudEvaluation evaluate_paysim_fraud(
    Transaction transactions[],
    size_t count,
    int risk_threshold
)
{
    FraudEvaluation evaluation = {0};

    evaluation.total_transactions =
        count;


    for (size_t i = 0; i < count; i++)
    {
        Transaction *transaction =
            &transactions[i];

        transaction->risk_score =
            calculate_paysim_risk(
                transaction
            );


        int predicted =
            transaction->risk_score >=
            risk_threshold;

        int actual =
            transaction->actual_fraud != 0;


        if (actual)
        {
            evaluation.actual_fraud++;
        }
        else
        {
            evaluation.actual_normal++;
        }


        if (predicted)
        {
            evaluation.predicted_fraud++;
        }
        else
        {
            evaluation.predicted_normal++;
        }


        if (predicted && actual)
        {
            evaluation.true_positive++;
        }

        else if (predicted && !actual)
        {
            evaluation.false_positive++;
        }

        else if (!predicted && actual)
        {
            evaluation.false_negative++;
        }

        else
        {
            evaluation.true_negative++;
        }
    }


    /*
     * Accuracy
     */
    if (count > 0)
    {
        evaluation.accuracy =
            100.0 *
            (
                evaluation.true_positive +
                evaluation.true_negative
            ) /
            (double)count;
    }


    /*
     * Precision
     */
    size_t precision_denominator =
        evaluation.true_positive +
        evaluation.false_positive;

    if (precision_denominator > 0)
    {
        evaluation.precision =
            100.0 *
            evaluation.true_positive /
            (double)precision_denominator;
    }


    /*
     * Recall / Fraud Detection Rate
     */
    size_t recall_denominator =
        evaluation.true_positive +
        evaluation.false_negative;

    if (recall_denominator > 0)
    {
        evaluation.recall =
            100.0 *
            evaluation.true_positive /
            (double)recall_denominator;
    }


    /*
     * F1 score.
     *
     * precision and recall are percentages,
     * which is okay because the same scale
     * cancels correctly in the formula.
     */
    if (
        evaluation.precision +
        evaluation.recall >
        0.0
    )
    {
        evaluation.f1_score =
            2.0 *
            evaluation.precision *
            evaluation.recall /
            (
                evaluation.precision +
                evaluation.recall
            );
    }


    return evaluation;
}


void print_fraud_evaluation(
    const FraudEvaluation *evaluation,
    int risk_threshold
)
{
    if (evaluation == NULL)
    {
        return;
    }


    printf("\n");
    printf("============================================================\n");
    printf("              PAYSIM FRAUD EVALUATION\n");
    printf("============================================================\n");

    printf(
        "Risk Threshold        : %d\n",
        risk_threshold
    );

    printf(
        "Transactions Evaluated: %zu\n",
        evaluation->total_transactions
    );

    printf(
        "Actual Fraud          : %zu\n",
        evaluation->actual_fraud
    );

    printf(
        "Actual Normal         : %zu\n",
        evaluation->actual_normal
    );

    printf(
        "Predicted Fraud       : %zu\n",
        evaluation->predicted_fraud
    );

    printf(
        "Predicted Normal      : %zu\n",
        evaluation->predicted_normal
    );


    printf("\n");
    printf("CONFUSION MATRIX\n");
    printf("------------------------------------------------------------\n");

    printf(
        "True Positive  (TP) : %zu\n",
        evaluation->true_positive
    );

    printf(
        "False Positive (FP) : %zu\n",
        evaluation->false_positive
    );

    printf(
        "True Negative  (TN) : %zu\n",
        evaluation->true_negative
    );

    printf(
        "False Negative (FN) : %zu\n",
        evaluation->false_negative
    );


    printf("\n");
    printf("QUALITY METRICS\n");
    printf("------------------------------------------------------------\n");

    printf(
        "Accuracy  : %.4f%%\n",
        evaluation->accuracy
    );

    printf(
        "Precision : %.4f%%\n",
        evaluation->precision
    );

    printf(
        "Recall    : %.4f%%\n",
        evaluation->recall
    );

    printf(
        "F1 Score  : %.4f%%\n",
        evaluation->f1_score
    );

    printf(
        "============================================================\n"
    );
}