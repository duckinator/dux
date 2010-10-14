#include <metodo/core/node.h>
#include <metodo/metodo.h>

/* NodeCreate(): Create a new node.
*  Parameters: None.
*/
Node *NodeCreate(void)
{
    Node *n;

    /* Allocate it. */
    n = kmalloc(sizeof(Node));

    /* Initialize. */
    n->next = n->prev = n->data = NULL;

    /* Return a pointer to the new node. */
    return n;
}

/* NodeFree(): Free a node.
*  Parameters:
*
*  n -- The node to free.
*/
void NodeFree(Node *n)
{
    /* Free it. */
    free(n);
}

/* NodeAdd(): Add a node to the end of a list.
*  Parameters:
*
*  data -- The data to add to the node.
*  n    -- The node to add.
*  l    -- The list that will hold the node (n).
*/
void NodeAdd(void *data, Node *n, List *l)
{
    Node *tn;

    n->data = data;

    /* First node? */
    if (!l->head)
    {
        l->head = n;
        l->tail = NULL;

        ++l->count;
        return;
    }

    /* Find the last node. */
    LIST_FOREACH_NEXT(tn, l->head);

    /* Set the `prev' to the last node. */
    n->prev = tn;

    /* Set the last node's `next' to us. */
    n->prev->next = n;

    /* Set the list's `tail' to us. */
    l->tail = n;

    /* Up the count. */
    ++l->count;
}

/* NodeDelete(): Remove a node from a list.
*  Parameters:
*
*  n -- The node to remove.
*  l -- The list that contains `n'.
*/
void NodeDelete(Node *n, List *l)
{
    /* Are we the head? */
    if (!n->prev)
        l->head = n->next;
    else
        n->prev->next = n->next;

    /* Are we the tail? */
    if (!n->next)
        l->tail = n->prev;
    else
        n->next->prev = n->prev;

    /* Down the count. */
    --l->count;
}

/* NodeFind(): Find a node by `data'.
*  Parameters:
*
*  data -- The data to match against nodes.
*/
Node *NodeFind(const void *data, const List *l)
{
    Node *n;

    LIST_FOREACH(n, l->head)
        if (n->data == data)
            return n;

    return NULL;
}

/* NodeMove(): Move a node from one list to another.
*  Parameters:
*
*  n   -- The node to move.
*  old -- The list containing the node.
*  new -- The list to move the node.
*/
void NodeMove(Node *n, List *old, List *new)
{
    /* Assumption: If n->next == NULL, then list->tail == m
     *      and:   If n->prev == NULL, then list->head == m
    */
    if (n->next)
        n->next->prev = n->prev;
    else
        old->tail = n->prev;

    if (n->prev)
        n->prev->next = n->next;
    else
        old->head = n->next;

    n->prev = NULL;
    n->next = new->head;

    if (new->head != NULL)
        new->head->prev = n;
    else if (new->tail == NULL)
        new->tail = n;

    new->head = n;

    --old->count;
    ++new->count;
}
