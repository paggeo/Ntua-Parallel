#include <stdio.h>
#include <stdlib.h> /* rand() */
#include <limits.h>
#include <pthread.h> /* for pthread_spinlock_t */
#include <stdbool.h>

#include "../common/alloc.h"
#include "ll.h"

typedef struct ll_node {
	int key;
	struct ll_node *next;
	/* other fields here? */
	pthread_spinlock_t spin;
	bool marked;
} ll_node_t;

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
	ret->marked = false;
	int pshared = 0 ;
	if(pthread_spin_init(&ret->spin,pshared)!=0){
		printf("Couldn't init the spinlock\n");
	}
	return ret;
}

/**
 * Free a linked list node.
 **/
static void ll_node_free(ll_node_t *ll_node)
{
	if(pthread_spin_destroy(&(ll_node->spin))!=0){
		printf("Couldn't init the spinlock\n");
	}
	
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

bool validate(ll_node_t *pred,ll_node_t *curr){
	return !pred->marked && !curr->marked && pred->next == curr;
}
int ll_contains(ll_t *ll, int key)
{
	ll_node_t *curr;

	curr = ll->head;
	while (curr->key < key){
		curr = curr->next;
	}
	return curr->key == key && !curr->marked;
}

int ll_add(ll_t *ll, int key)
{
	int ret = 0;
	ll_node_t *curr;
	ll_node_t *next;
	ll_node_t *new_node;

	while(true){
		curr = ll->head;
		next = curr->next;
		while (next->key < key){
			curr = next;
			next = curr->next;
		}
		
		pthread_spin_lock(&curr->spin);
		pthread_spin_lock(&next->spin);

		if(validate(curr,next)){
			if(key != next->key){
				ret = 1;
				new_node = ll_node_new(key);
				new_node->next = next;
				curr->next = new_node;
				pthread_spin_unlock(&curr->spin);
				pthread_spin_unlock(&next->spin);
				return ret;
				
			}
			pthread_spin_unlock(&curr->spin);
			pthread_spin_unlock(&next->spin);
			return ret;
		}
		pthread_spin_unlock(&curr->spin);
		pthread_spin_unlock(&next->spin);
	}
	
	return 0;
}

int ll_remove(ll_t *ll, int key)
{
	int ret = 0;
	ll_node_t *curr;
	ll_node_t *next;

	while(true){
		curr = ll->head;
		next = curr->next;
		while (next->key < key){
			curr = next;
			next = curr->next;
		}
		
		pthread_spin_lock(&curr->spin);
		pthread_spin_lock(&next->spin);

		if(validate(curr,next)){
			if(key == next->key){
				ret = 1;
				next->marked = true;
				curr->next = next->next;
				pthread_spin_unlock(&next->spin);
				pthread_spin_unlock(&curr->spin);
				return ret;
				
			}
			else {
				pthread_spin_unlock(&curr->spin);
				pthread_spin_unlock(&next->spin);
				return ret;
			}
		}
		pthread_spin_unlock(&curr->spin);
		pthread_spin_unlock(&next->spin);
	}
	
	return 0;
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
}
