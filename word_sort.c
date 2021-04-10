#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>

#include "word_sort.h"

/* Insert new string at the end of the list. */
struct n *
insert(struct n *head, const char *data, int data_size)
{
    struct n *new_node, *p;

    // Allocate memory for new node.
    new_node = (struct n *)malloc(sizeof(struct n));

    new_node->next = NULL;

    new_node->user_data = (char *)malloc(sizeof(char) * data_size);
    memcpy(new_node->user_data, data, data_size);

    /* If list is empty, just insert at the top */
    if (head == NULL)
    {
        head = new_node;
    }
    else
    {
        /*  Else, insert at end of list */
        for (p = head; p != NULL; p = p->next)
        {
            /* We're at the end if the next node is NULL, so insert */
            if (p->next == NULL)
            {
                p->next = new_node;
                return head;
            }
        }
    }

    return head;
}

/* Traverse the list and print the contents, based on flag either delete the nodes. */
void traverse(struct n **head, bool free_flag)
{
    struct n *p = *head;

    for (; p; p = p->next)
        puts(p->user_data);

    if (free_flag)
    {
        for (; p; p = p->next)
            free(p);
    }
}

/* Free the list */
void freel(struct n **head)
{
    struct n *p = *head;
    for (; p; p = p->next)
        free(p);
}

/* Quickly sort the list using Bubble sort */
void qsortx(struct n *head, unsigned int flags, int (*compare)(const char *a, const char *b, unsigned int flags))
{
    struct n *p, *q;

    for (p = head; p != NULL; p = p->next)
    {
        for (q = p->next; q != NULL; q = q->next)
        {
            if (compare(q->user_data, p->user_data, flags) < 0)
            {
                /* Swap them */
                char *tmp;
                tmp = p->user_data;
                p->user_data = q->user_data;
                q->user_data = tmp;
            }
        }
    }
}

/*  Callback which compares two strings a and b
    1. If in alphabetic order a > b then returned value is > 0
    2. If alphabetic order a=b then returns 0
    3. If alphabetic order a < b then returned value is < 0

    Flags:
    0x1 = sort words in reverse order hence a is replaced by b

    0x2 = sort case insensitive, so both strings are converted to upper class and compared.*/
int compare(const char *a, const char *b, unsigned int flags)
{
    if (flags == WORD_SORT_REVERSE)
        return strcmp(b, a);

    if (flags == WORD_SORT_IGNORE_CASE)
    {
        while (toupper(*a) == toupper(*b))
        {
            if (*a == 0)
                return 0;
            a++;
            b++;
        }
        return toupper(*(unsigned const char *)a) - toupper(*(unsigned const char *)(b));
    }
    return strcmp(a, b);
}

/*  This function sorts the given string in alphabetical order based on the flag.
    The string is first seperated from whitespaces then converted into a linkedlist.
    The linkedlist is then sorted using bubble sort and the result is concatenated
    with whitespaces to give a complete string.
    It returns the total characters in the processed string
    and 0 if no operation performed.*/
unsigned int
word_sort(const char *src, char **dst, unsigned int *dst_len, unsigned int flags)
{
    struct n *head = NULL;
    unsigned int total_chars = 0;

    char *cpy = strdup(src);

    // Tokenize the string by removing the whitespaces
    char *tok = strtok(cpy, " \t\n");
    while (tok != NULL)
    {
        head = insert(head, tok, strlen(tok));
        tok = strtok(NULL, " \t\n");
    }

    *dst = (char *)malloc(sizeof(char) * (strlen(src) + 1));

    // Call sort function with flags.
    qsortx(head, flags, compare);

    struct n *p = NULL;
    for (p = head; p; p = p->next)
    {
        if (p->next != NULL)
        {
            strcat(*dst, p->user_data);
            strcat(*dst, " ");
        }
        else
            strcat(*dst, p->user_data);

        total_chars += strlen(p->user_data) + 1;
    }

    *dst_len = total_chars;

    return total_chars;
}

/*  Driver program to run all test cases for sorting program. */
int main()
{
    char src[18] = "The   \t\n cat  sat";
    char src2[45] = "Hi \t \n hi \t\t\t\t there \n \t my name is Shivam \n";

    char *ptr = NULL;

    unsigned int ans = 0;
    unsigned int dst_len = 0;

    ans = word_sort(src2, &ptr, &dst_len, WORD_SORT_IGNORE_CASE);
    printf("Sorted string: %s \n", ptr);
    printf("Total chars= %d \n", dst_len);
    free(ptr);

    assert(word_sort(src, &ptr, &dst_len, 0) == 12 && "Testcase 1 failed");
    assert((strcmp(ptr, "The cat sat") == 0) && "Testcase 2 failed");

    assert(word_sort(src, &ptr, &dst_len, WORD_SORT_IGNORE_CASE) == 12 && "Testcase 3 failed");
    assert((strcmp(ptr, "cat sat The") == 0) && "Testcase 4 failed");

    assert(word_sort(src, &ptr, &dst_len, WORD_SORT_REVERSE) == 12 && "Testcase 5 failed");
    assert((strcmp(ptr, "sat cat The") == 0) && "Testcase 6 failed");

    assert(word_sort(src2, &ptr, &dst_len, 0) == 30 && "Testcase 7 failed");
    assert((strcmp(ptr, "Hi Shivam hi is my name there") == 0) && "Testcase 8 failed");

    assert(word_sort(src2, &ptr, &dst_len, WORD_SORT_IGNORE_CASE) == 30 && "Testcase 9 failed");
    assert((strcmp(ptr, "Hi hi is my name Shivam there") == 0) && "Testcase 10 failed");

    assert(word_sort(src2, &ptr, &dst_len, WORD_SORT_REVERSE) == 30 && "Testcase 11 failed");
    assert((strcmp(ptr, "there name my is hi Shivam Hi") == 0) && "Testcase 12 failed");

    printf("All 12 cases passed\n");

    return 0;
}