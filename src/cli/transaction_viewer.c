#include <stdio.h>

#include "transaction_viewer.h"
#include "transaction.h"


void run_transaction_viewer(
    const Transaction transactions[],
    size_t transaction_count
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


    const size_t page_size = 25;

    size_t page = 0;

    char command = '\0';


    do
    {
        size_t start =
            page * page_size;


        /*
         * Safety check.
         */
        if (start >= transaction_count)
        {
            page = 0;
            start = 0;
        }


        size_t end =
            start + page_size;


        if (end > transaction_count)
        {
            end =
                transaction_count;
        }


        printf("\n");
        printf(
            "============================================================\n"
        );

        printf(
            "          TRANSACTIONS %zu - %zu OF %zu\n",
            start + 1,
            end,
            transaction_count
        );

        printf(
            "============================================================\n"
        );


        for (
            size_t i = start;
            i < end;
            i++
        )
        {
            printf(
                "\nTransaction #%zu\n",
                i + 1
            );

            printf(
                "------------------------------------------------------------\n"
            );

            print_transaction(
                &transactions[i]
            );
        }


        printf("\n");
        printf(
            "============================================================\n"
        );

        printf("[N] Next Page\n");
        printf("[P] Previous Page\n");
        printf("[J] Jump to Page\n");
        printf("[Q] Back to Main Menu\n");

        printf(
            "============================================================\n"
        );

        printf("Choice: ");


        if (
            scanf(
                " %c",
                &command
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


        /*
         * NEXT PAGE
         */
        if (
            command == 'N' ||
            command == 'n'
        )
        {
            if (
                (page + 1) *
                page_size <
                transaction_count
            )
            {
                page++;
            }
            else
            {
                printf(
                    "\nAlready at the last page.\n"
                );
            }
        }


        /*
         * PREVIOUS PAGE
         */
        else if (
            command == 'P' ||
            command == 'p'
        )
        {
            if (page > 0)
            {
                page--;
            }
            else
            {
                printf(
                    "\nAlready at the first page.\n"
                );
            }
        }


        /*
         * JUMP TO PAGE
         */
        else if (
            command == 'J' ||
            command == 'j'
        )
        {
            size_t total_pages =
                (
                    transaction_count +
                    page_size - 1
                ) /
                page_size;


            size_t requested_page;


            printf(
                "Enter page number (1-%zu): ",
                total_pages
            );


            if (
                scanf(
                    "%zu",
                    &requested_page
                ) != 1
            )
            {
                printf(
                    "Invalid page number.\n"
                );

                while (getchar() != '\n')
                {
                }

                continue;
            }


            if (
                requested_page == 0 ||
                requested_page >
                    total_pages
            )
            {
                printf(
                    "Page must be between "
                    "1 and %zu.\n",
                    total_pages
                );
            }
            else
            {
                page =
                    requested_page - 1;
            }
        }


        /*
         * QUIT
         */
        else if (
            command == 'Q' ||
            command == 'q'
        )
        {
            /* Return to main menu. */
        }


        else
        {
            printf(
                "\nInvalid command. "
                "Use N, P, J or Q.\n"
            );
        }


    } while (
        command != 'Q' &&
        command != 'q'
    );
}