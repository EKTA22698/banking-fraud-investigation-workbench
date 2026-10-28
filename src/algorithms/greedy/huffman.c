#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "greedy.h"


typedef struct HuffmanNode
{
    unsigned char character;
    int frequency;

    struct HuffmanNode *left;
    struct HuffmanNode *right;

} HuffmanNode;


static HuffmanNode *create_node(
    unsigned char character,
    int frequency
)
{
    HuffmanNode *node =
        malloc(sizeof(HuffmanNode));

    if (node == NULL)
    {
        return NULL;
    }

    node->character = character;
    node->frequency = frequency;
    node->left = NULL;
    node->right = NULL;

    return node;
}


static void free_tree(
    HuffmanNode *root
)
{
    if (root == NULL)
    {
        return;
    }

    free_tree(root->left);
    free_tree(root->right);

    free(root);
}


static void print_codes(
    HuffmanNode *root,
    int code[],
    int depth
)
{
    int i;

    if (root == NULL)
    {
        return;
    }

    /*
     * Leaf node.
     */
    if (
        root->left == NULL &&
        root->right == NULL
    )
    {
        if (root->character == ' ')
        {
            printf(
                "'SPACE' : "
            );
        }
        else
        {
            printf(
                "'%c'     : ",
                root->character
            );
        }

        /*
         * A one-symbol input still needs
         * a valid code.
         */
        if (depth == 0)
        {
            printf("0");
        }
        else
        {
            for (i = 0; i < depth; i++)
            {
                printf("%d", code[i]);
            }
        }

        printf(
            " (frequency %d)\n",
            root->frequency
        );

        return;
    }

    code[depth] = 0;

    print_codes(
        root->left,
        code,
        depth + 1
    );

    code[depth] = 1;

    print_codes(
        root->right,
        code,
        depth + 1
    );
}


void run_huffman_demo(
    const char *text
)
{
    int frequency[MAX_HUFFMAN_CHARS] = {0};

    HuffmanNode *nodes[
        MAX_HUFFMAN_CHARS
    ];

    int node_count = 0;

    int i;
    int j;

    if (
        text == NULL ||
        text[0] == '\0'
    )
    {
        printf(
            "\nCannot build Huffman tree "
            "from empty text.\n"
        );

        return;
    }

    /*
     * Calculate character frequencies.
     */
    for (i = 0; text[i] != '\0'; i++)
    {
        unsigned char character =
            (unsigned char)text[i];

        frequency[character]++;
    }


    /*
     * Create one node for each
     * character that appears.
     */
    for (i = 0; i < MAX_HUFFMAN_CHARS; i++)
    {
        if (frequency[i] > 0)
        {
            nodes[node_count] =
                create_node(
                    (unsigned char)i,
                    frequency[i]
                );

            if (nodes[node_count] == NULL)
            {
                printf(
                    "ERROR: Huffman memory "
                    "allocation failed.\n"
                );

                for (j = 0; j < node_count; j++)
                {
                    free_tree(nodes[j]);
                }

                return;
            }

            node_count++;
        }
    }


    /*
     * Repeatedly combine the two
     * minimum-frequency nodes.
     *
     * This uses a simple array search.
     * Later benchmark discussion can
     * compare this with a min-heap.
     */
    while (node_count > 1)
    {
        int min1 = -1;
        int min2 = -1;

        for (i = 0; i < node_count; i++)
        {
            if (
                min1 == -1 ||
                nodes[i]->frequency <
                nodes[min1]->frequency
            )
            {
                min2 = min1;
                min1 = i;
            }
            else if (
                min2 == -1 ||
                nodes[i]->frequency <
                nodes[min2]->frequency
            )
            {
                min2 = i;
            }
        }

        HuffmanNode *left =
            nodes[min1];

        HuffmanNode *right =
            nodes[min2];

        HuffmanNode *parent =
            create_node(
                0,
                left->frequency +
                right->frequency
            );

        if (parent == NULL)
        {
            printf(
                "ERROR: Huffman memory "
                "allocation failed.\n"
            );

            return;
        }

        parent->left = left;
        parent->right = right;

        /*
         * Remove higher index first.
         */
        if (min1 > min2)
        {
            int temp = min1;
            min1 = min2;
            min2 = temp;
        }

        for (
            i = min2;
            i < node_count - 1;
            i++
        )
        {
            nodes[i] =
                nodes[i + 1];
        }

        node_count--;

        for (
            i = min1;
            i < node_count - 1;
            i++
        )
        {
            nodes[i] =
                nodes[i + 1];
        }

        node_count--;

        nodes[node_count] = parent;
        node_count++;
    }


    printf("\n============================================\n");
    printf("             HUFFMAN CODES\n");
    printf("============================================\n");

    int code[MAX_HUFFMAN_CHARS];

    print_codes(
        nodes[0],
        code,
        0
    );

    printf("============================================\n");

    free_tree(nodes[0]);
}