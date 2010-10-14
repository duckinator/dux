#ifndef CORE_NODE_H
#define CORE_NODE_H

typedef struct node_
{
  struct node_ *next, *prev;
  void *data;
} Node;

typedef struct list_
{
  struct node_ *head, *tail;
  int count;
} List;

#define LIST_FOREACH(n, head) for (n = (head); n; n = n->next)
#define LIST_FOREACH_NEXT(n, head) for (n = (head); n->next; n = n->next)
#define LIST_LENGTH(list) (list)->count
#define LIST_FOREACH_SAFE(n, tn, head) for (n = (head), tn = n ? n->next : NULL; n != NULL; n = tn, tn = n ? n->next : NULL)

#endif
