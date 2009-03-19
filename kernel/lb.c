#include <system.h>
#include <lb.h>

lb_t *lb_init()
{
	lb_t *buf = malloc(sizeof(lb_t));
	buf->first = 1;
	buf->next = NULL;
	buf->size = 0;
	buf->buf = NULL;
	return buf;
}

lb_t *lb_add(lb_t *first, unsigned int size, unsigned char *buf)
{
	lb_t *cur = first;
	lb_t *new = malloc(sizeof(lb_t));

	while (cur->next != NULL)
		cur = first->next;

	cur->next = new;
	new->first = 0;
	new->next = NULL;
	new->size = size;
	new->buf = buf;
	return new;
}

void lb_del(lb_t *first, lb_t *todel)
{
	lb_t *cur = first;

	while (cur->next != todel)
		cur = first->next;

	cur->next = todel->next;

	free(todel);
}
