#define WORD_SORT_REVERSE 0x1
#define WORD_SORT_IGNORE_CASE 0x2

/* Node structure of string type linkedlist. */
struct n
{
    char        *user_data;
    struct n    *next;
};

unsigned int word_sort(const char *src, char **dst, unsigned int *dst_len, unsigned int flags);

struct n *insert(struct n *head, const char *data, int data_size);

void traverse(struct n **head, bool free_flag);

void freel(struct n **head);

void qsortx(struct n *head, unsigned int flags, int (*compare)(const char *a, const char *b, unsigned int flags));

unsigned int word_sort(const char *src, char **dst, unsigned int *dst_len, unsigned int flags);
