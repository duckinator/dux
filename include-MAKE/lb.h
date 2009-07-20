#ifndef LB_H
#define LB_H

struct lb {
	unsigned char first;
	struct lb *next;
	unsigned int size;
	unsigned char *buf;
};

typedef struct lb lb_t;

lb_t *lb_init();
lb_t *lb_add(lb_t *first, unsigned int size, unsigned char *buf);
void lb_del(lb_t *first, lb_t *todel);

#endif
