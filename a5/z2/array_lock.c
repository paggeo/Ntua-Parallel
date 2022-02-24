#include "lock.h"
#include "../common/alloc.h"
#include <stdbool.h>
#include <pthread.h>

struct lock_struct {
	int size;
	bool *flag;
	int tail;
};

__thread int mySlotIndex;

lock_t *lock_init(int nthreads)
{
	lock_t *lock;

	XMALLOC(lock, 1);
	/* other initializations here. */
	lock->size = nthreads;
	XMALLOC(lock->flag,nthreads);
	int i;
	lock->flag[0] = true;
	for(i=1;i<nthreads;i++) lock->flag[i] = false;
	lock->tail = 0;
	
	return lock;
}

void lock_free(lock_t *lock)
{
	XFREE(lock);
}

void lock_acquire(lock_t *lock)
{	
	// take the tail value (%lock->size to be circular)
	// and increament the tail value atomically
	int slot = __sync_fetch_and_add(&(lock->tail),1) %lock->size;
	mySlotIndex = slot; // Save my slot to thread value;
	while (!lock->flag[slot]){};
	// First how would come will take mySlotIndex = 0 = tail , would do tail++
	// check if lock->flag[mySlotIndex] = true 
	// The second will take mySlotIndex=tail=1, would do tail++
	// check if lock->flag[mySlotIndex]=true
}

void lock_release(lock_t *lock)
{
	//Get my slot
	int slot = mySlotIndex;
	//Make my slot false
	lock->flag[slot] = false;
	// Make the next 
	lock->flag[(slot+1)%lock->size] = true;
}
