#include <stdio.h>

#include "export.h"


static void write_json_string(
    FILE *file,
    const char *text
)
{
    fputc('"', file);

    if (text != NULL)
    {
        for (int i = 0; text[i] != '\0'; i++)
        {
            unsigned char c =
                (unsigned char)text[i];

            switch (c)
            {
                case '"':
                    fputs("\\\"", file);
                    break;

                case '\\':
                    fputs("\\\\", file);
                    break;

                case '\n':
                    fputs("\\n", file);
                    break;

                case '\r':
                    fputs("\\r", file);
                    break;

                case '\t':
                    fputs("\\t", file);
                    break;

                default:
                    if (c < 32)
                    {
                        fprintf(
                            file,
                            "\\u%04x",
                            c
                        );
                    }
                    else
                    {
                        fputc(c, file);
                    }
            }
        }
    }

    fputc('"', file);
}


static void write_csv_field(
    FILE *file,
    const char *text
)
{
    /*
     * Always quote string fields.
     * Double embedded quotation marks
     * according to CSV rules.
     */
    fputc('"', file);

    if (text != NULL)
    {
        for (int i = 0; text[i] != '\0'; i++)
        {
            if (text[i] == '"')
            {
                fputs("\"\"", file);
            }
            else
            {
                fputc(text[i], file);
            }
        }
    }

    fputc('"', file);
}


int export_transactions_csv(
    const char *filename,
    const Transaction transactions[],
    size_t count
)
{
    if (
        filename == NULL ||
        transactions == NULL ||
        count <= 0
    )
    {
        return 0;
    }


    FILE *file =
        fopen(
            filename,
            "w"
        );


    if (file == NULL)
    {
        return 0;
    }


    fprintf(
        file,
        "transaction_id,"
        "account_id,"
        "device_id,"
        "merchant_id,"
        "amount,"
        "type,"
        "timestamp,"
        "description,"
        "risk_score\n"
    );


    for (size_t i = 0; i < count; i++)
    {
        write_csv_field(
            file,
            transactions[i].transaction_id
        );

        fputc(',', file);

        write_csv_field(
            file,
            transactions[i].account_id
        );

        fputc(',', file);

        write_csv_field(
            file,
            transactions[i].device_id
        );

        fputc(',', file);

        write_csv_field(
            file,
            transactions[i].merchant_id
        );

        fprintf(
            file,
            ",%.2f,",
            transactions[i].amount
        );

        write_csv_field(
            file,
            transactions[i].transaction_type
        );

        fputc(',', file);

        write_csv_field(
            file,
            transactions[i].timestamp
        );

        fputc(',', file);

        write_csv_field(
            file,
            transactions[i].description
        );

        fprintf(
            file,
            ",%d\n",
            transactions[i].risk_score
        );
    }


    fclose(file);

    return 1;
}


int export_transactions_json(
    const char *filename,
    const Transaction transactions[],
    size_t count
)
{
    if (
        filename == NULL ||
        transactions == NULL ||
        count <= 0
    )
    {
        return 0;
    }


    FILE *file =
        fopen(
            filename,
            "w"
        );


    if (file == NULL)
    {
        return 0;
    }


    fprintf(
        file,
        "{\n"
        "  \"transaction_count\": %zu,\n"
        "  \"transactions\": [\n",
        count
    );


    for (size_t i = 0; i < count; i++)
    {
        fprintf(file, "    {\n");

        fprintf(
            file,
            "      \"transaction_id\": "
        );

        write_json_string(
            file,
            transactions[i].transaction_id
        );

        fprintf(
            file,
            ",\n      \"account_id\": "
        );

        write_json_string(
            file,
            transactions[i].account_id
        );

        fprintf(
            file,
            ",\n      \"device_id\": "
        );

        write_json_string(
            file,
            transactions[i].device_id
        );

        fprintf(
            file,
            ",\n      \"merchant_id\": "
        );

        write_json_string(
            file,
            transactions[i].merchant_id
        );

        fprintf(
            file,
            ",\n      \"amount\": %.2f",
            transactions[i].amount
        );

        fprintf(
            file,
            ",\n      \"type\": "
        );

        write_json_string(
            file,
            transactions[i].transaction_type
        );

        fprintf(
            file,
            ",\n      \"timestamp\": "
        );

        write_json_string(
            file,
            transactions[i].timestamp
        );

        fprintf(
            file,
            ",\n      \"description\": "
        );

        write_json_string(
            file,
            transactions[i].description
        );

        fprintf(
            file,
            ",\n      \"risk_score\": %d\n",
            transactions[i].risk_score
        );

        fprintf(
            file,
            "    }%s\n",
            i < count - 1 ?
            "," :
            ""
        );
    }


    fprintf(
        file,
        "  ]\n"
        "}\n"
    );


    fclose(file);

    return 1;
}int export_suspicious_csv(
    const char *filename,
    const Transaction transactions[],
    size_t count,
    int risk_threshold
)
{
    if (
        filename == NULL ||
        transactions == NULL
    )
    {
        return 0;
    }

    FILE *file =
        fopen(filename, "w");

    if (file == NULL)
    {
        return 0;
    }

    fprintf(
        file,
        "transaction_id,"
        "origin_account,"
        "destination_account,"
        "amount,"
        "type,"
        "risk_score,"
        "actual_fraud\n"
    );

    for (size_t i = 0; i < count; i++)
    {
        if (
            transactions[i].risk_score <
            risk_threshold
        )
        {
            continue;
        }

        fprintf(
            file,
            "\"%s\",\"%s\",\"%s\",%.2f,"
            "\"%s\",%d,%d\n",
            transactions[i].transaction_id,
            transactions[i].account_id,
            transactions[i].destination_id,
            transactions[i].amount,
            transactions[i].transaction_type,
            transactions[i].risk_score,
            transactions[i].actual_fraud
        );
    }

    fclose(file);

    return 1;
}


int export_actual_fraud_csv(
    const char *filename,
    const Transaction transactions[],
    size_t count
)
{
    if (
        filename == NULL ||
        transactions == NULL
    )
    {
        return 0;
    }

    FILE *file =
        fopen(filename, "w");

    if (file == NULL)
    {
        return 0;
    }

    fprintf(
        file,
        "transaction_id,"
        "origin_account,"
        "destination_account,"
        "amount,"
        "type,"
        "risk_score,"
        "actual_fraud\n"
    );

    for (size_t i = 0; i < count; i++)
    {
        if (!transactions[i].actual_fraud)
        {
            continue;
        }

        fprintf(
            file,
            "\"%s\",\"%s\",\"%s\",%.2f,"
            "\"%s\",%d,%d\n",
            transactions[i].transaction_id,
            transactions[i].account_id,
            transactions[i].destination_id,
            transactions[i].amount,
            transactions[i].transaction_type,
            transactions[i].risk_score,
            transactions[i].actual_fraud
        );
    }

    fclose(file);

    return 1;
}