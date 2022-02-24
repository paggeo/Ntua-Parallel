#include "../common/alloc.h"
#include "lock.h"
#include <stdbool.h>

typedef enum {
	UNLOCKED = 0,
	LOCKED
} lock_state_t;

struct lock_struct {
	lock_state_t state;
};

lock_t *lock_init(int nthreads)
{
	lock_t *lock;

	XMALLOC(lock, 1);
	lock->state = UNLOCKED;
	return lock;
}

void lock_free(lock_t *lock)
{
	XFREE(lock);
}

void lock_acquire(lock_t *lock)
{
	lock_t *l = lock;
	bool sit = true;
	while(sit){
		// Check constantly if the l->state become UNLOCKED
	
		while(l->state==LOCKED){};
	
		// This change the value of l->state to LOCKED and return the previous value
		// if l->state was UNLOCKED then the process can have the lock 
		// if not the process couldn't make it in time because another process
		// reached first so this one must wait again 
	
		if (__sync_lock_test_and_set(&l->state,LOCKED)==UNLOCKED) sit = false;
	}

}

void lock_release(lock_t *lock)
{
	lock_t *l = lock;
	__sync_lock_release(&l->state);

}
