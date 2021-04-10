/*
    CodeWeavers Programming Test -- Code Review

    The task:  review the enclosed code and find
        1)  Design flaws
        2)  Programming errors
        3)  Style problems

    Review the code for the above three criteria, marking the code
    up visibly (the markings don't have to compile).  

    For design and style flaws, you should breifly describe the flaw
    and suggest a solution (it is not necessary to code a full solution).
    If a design or style flaw is repeated, you do not need to discuss it
    again.

    Please suggest fixes for any bugs that would cause the code to fail
    from running as it is currently designed.
    
    Note:  This code was _intentionally_ written to be bad, you
    should expect many problems.
*/




/*  Linked list management subroutine library */

struct  n       
{

    // The user data needs to have a type as in string format 
    void        *user_data;
    int         f;
    struct n    *next;
};

/*  Finds:
    1. All struct declerations need to be present in header files and not in .c
    2. The user_data fields should be of type char * and not void (line 33)
    3. There is no need of f flag rather the correct implementation is in word_sort.c (line 34)
    4. There shouldn't be space in annotation and structure name.

    Eg:
    struct n
    {
    char        *user_data;
    struct n    *next;
    };
*/


/* Insert at end of list */
void insert(struct n *head, void *data, int data_size)
{
    struct n *new_node, *p;

    new_node = malloc(sizeof(new_node));

    new_node->next = NULL;

    new_node->user_data = malloc(data_size);
    memcpy(new_node->user_data, data, sizeof(data));

    /* If list is empty, just insert at the top */
    if (head == NULL)
        head = new_node;
    else
        /*  Else, insert at end of list */
        for (p = head; p; p = p->next)
            /* We're at the end if the next node is NULL, so insert */
            if (p->next == NULL)
                p->next = new_node;
}

/*  Finds:
    5. The *data type should be char *data and return type should be struct n*
    6. To allocate new_node use:
        new_node = (struct n *)malloc(sizeof(struct n));
    7. Use data_size in memcpy:
        memcpy(new_node->user_data, data, data_size); 
    8. Return head pointer as per requirement.


struct n *
insert(struct n *head, char *data, int data_size)
{
    struct n *new_node, *p;

    // Allocate memory for new node.
    new_node = (struct n *)malloc(sizeof(struct n));

    new_node->next = NULL;

    new_node->user_data = (char *)malloc(sizeof(char) * data_size);
    memcpy(new_node->user_data, data, data_size);

    if (head == NULL)
    {
        head = new_node;
    }
    else
    {
        for (p = head; p != NULL; p = p->next)
        {
            if (p->next == NULL)
            {
                p->next = new_node;
                return head;
            }
        }
    }

    return head;
}
*/


/* Traverse the list, invoking a passed in callback function, which
    can optionally tell us to free the node when we return  */
void traverse(struct n *head, bool free_flag)
{
  struct n *p;

  for (p = head; p; p = p->next)    {
    (*callback_func)(p->user_data, p->f);
    if (p->f)           // If they want to free the node, do that
        free(p);
  }
}

/*  Finds:
    9. The head should be pointer passed by reference to actually delete the nodes.
    10. assign *p to *head
    11. There is no requirement to add callback as the decision to delete the nodes
        Can be done through passing a free_flag variable.

void
traverse(struct n **head, bool free_flag)
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
*/



/* Free the list */
void freel(struct n *head)
{
    struct n *p;
    for (p = head; p; p = p->next)
        free(p);
}

/*  Finds:
    12. The head pointer should be passed by reference.

void
freel(struct n **head)
{
    struct n *p = *head;
    for (; p; p = p->next)
        free(p);
}
*/


/* Quickly sort the list */
void qsort(struct n *head, int compare(void *a, void *b))
{
    struct n *p, *q;

    for (p = head; p; p = p->next);
        for (q = p->next; q; q = q->next)
        {
            if (compare(q->user_data, p->user_data) < 0)
            {
                /* Swap 'em */
                p->user_data = q->user_data;
                q->user_data = p->user_data;
            }
        }
}

/*  Finds:
    13. The function should properly define the syntax of callback function compare as pointer.
    14. There requires a third variable to swap the two char pointers.

void
qsortx(struct n *head, unsigned int flags, int (*compare)(char *a, char *b, unsigned int flags))
{
    struct n *p, *q;

    for (p = head; p != NULL; p = p->next)
    {
        for (q = p->next; q != NULL; q = q->next)
        {
            if (compare(q->user_data, p->user_data, flags) < 0)
            {
                char *tmp;
                tmp = p->user_data;
                p->user_data = q->user_data;
                q->user_data = tmp;
            }
        }
    }
}
*/