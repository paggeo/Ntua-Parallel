#include <stdio.h>
#include <stdlib.h> /* rand() */
#include <limits.h>
#include <stdint.h>

#include "../common/alloc.h"
#include "ll.h"
#define TRUE 1
#define FALSE 0
#define OR_TRUE(p) ((ll_node_t *) ((uintptr_t) (p) | (uintptr_t) TRUE))	//pointer with last bit 1
#define OR_FALSE(p) ((ll_node_t *) ((uintptr_t) (p) | (uintptr_t) FALSE))	//pointer with last bit 0
#define AND_TRUE(p) ((ll_node_t *) ((uintptr_t) (p) & (uintptr_t) TRUE))	//return all with mark
#define AND_FALSE(p) ((ll_node_t *) ((uintptr_t) (p) & (uintptr_t) FALSE))	//return pointer with mark 0
#define LAST_ZERO(p) ((ll_node_t *) ((uintptr_t) (p) & (uintptr_t) ~TRUE))	//remove pointer bits return last bit

typedef struct ll_node {
	int key;
	struct ll_node *next;
	/* other fields here? */
} ll_node_t;

typedef struct window {
	ll_node_t *pred,*curr;
} window;


struct linked_list {
	ll_node_t *head;
	/* other fields here? */
};

/**
 * Create a new linked list node.
 **/
static ll_node_t *ll_node_new(int key)
{
	ll_node_t *ret;

	XMALLOC(ret, 1);
	ret->key = key;
	ret->next = NULL;
	/* Other initializations here? */

	return ret;
}

/**
 * Free a linked list node.
 **/
static void ll_node_free(ll_node_t *ll_node)
{
	XFREE(ll_node);
}

/**
 * Create a new empty linked list.
 **/
ll_t *ll_new()
{
	ll_t *ret;

	XMALLOC(ret, 1);
	ret->head = ll_node_new(-1);
	ret->head->next = ll_node_new(INT_MAX);
	ret->head->next->next = NULL;

	return ret;
}

/**
 * Free a linked list and all its contained nodes.
 **/
void ll_free(ll_t *ll)
{
	ll_node_t *next, *curr = ll->head;
	while (curr) {
		next = curr->next;
		ll_node_free(curr);
		curr = next;
	}
	XFREE(ll);
}

window* find (window* win,ll_node_t* head,int key)
{
	ll_node_t *pred,*curr,*succ;
	pred=NULL;
	curr=NULL;
	succ=NULL;
	int marked[]={0};	//marked = false
	int snip;
	retry: while (1) {
		pred = head;
		curr = LAST_ZERO(pred->next);
		while (1) {
			marked[0] = AND_TRUE(curr->next);				//atomic get
			succ = LAST_ZERO(curr->next);
			while (marked[0]) {	//fysikh diagrafh komvwn
				snip = __sync_bool_compare_and_swap(&(pred->next),LAST_ZERO(pred->next),LAST_ZERO(pred->next))
							&& __sync_bool_compare_and_swap(&(pred->next), curr, succ);
				if (!snip) goto retry;
				curr = succ;
				marked[0] = AND_TRUE(curr->next);
				succ = LAST_ZERO(curr->next);
				//ll_node_free(curr);
			}
			if (curr->key >= key) {
				win->pred = pred;
				win->curr = curr;
				return win;
			}
			pred = curr;
			curr = succ;
		}
	}
}

int ll_contains(ll_t *ll, int key)
{
	int marked[]={0};
	ll_node_t *curr;
	curr =  ll->head;
	while (curr->key <key){
		curr = LAST_ZERO(curr->next);
	}
	marked[0]=AND_TRUE(curr->next);
	return (curr->key == key && !marked[0]);
}

int ll_add(ll_t *ll, int key)
{
	int splice;
	window* win=(window*)malloc(sizeof(window));
	ll_node_t *pred,*curr,*new_node;
	while (1) {
	 	win = find(win,ll->head,key);
		pred = win->pred;
		curr = win->curr;
		if (curr->key == key) {
			return 0;
		}
		else {
			new_node=ll_node_new(key);
			new_node->next = curr;
			if (__sync_bool_compare_and_swap(&pred->next, LAST_ZERO(pred->next), LAST_ZERO(pred->next))
                && __sync_bool_compare_and_swap(&pred->next, curr, new_node)) return 1;
		}
	}
}

int ll_remove(ll_t *ll, int key)
{
	int snip;
	window *win=(window*)malloc(sizeof(window));
	while (1) {
		win = find(win,ll->head,key);
		ll_node_t *pred,*curr,*succ;
		pred = win->pred;
		curr = win->curr;
		if (curr->key != key) {
			//free(win);
			return 0;
		}
		else {
			succ = LAST_ZERO(curr->next);
			snip = __sync_bool_compare_and_swap(&(curr->next),LAST_ZERO(succ),OR_TRUE(succ));
			if (!snip) continue;
			__sync_bool_compare_and_swap(&pred->next, LAST_ZERO(pred->next), LAST_ZERO(pred->next))
                && __sync_bool_compare_and_swap(&pred->next, curr, succ);
			//ll_node_free(curr);
			//free(win);
			return 1;
		}
	}
}

/**
 * Print a linked list.
 **/
void ll_print(ll_t *ll)
{
	ll_node_t *curr = ll->head;
	printf("LIST [");
	while (curr) {
		if (curr->key == INT_MAX)
			printf(" -> MAX");
		else
			printf(" -> %d", curr->key);
		curr = curr->next;
	}
	printf(" ]\n");
	fflush(stdout);
}
