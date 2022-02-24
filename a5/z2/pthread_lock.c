#include "lock.h"
#include "../common/alloc.h"
#include <pthread.h>

struct lock_struct {
	pthread_spinlock_t spin;
};

lock_t *lock_init(int nthreads)
{
	lock_t *lock;

	XMALLOC(lock, 1);
	int pshared=0;
	/* other initializations here. */
	if(pthread_spin_init(&lock->spin,pshared)!=0){
		printf("Couldn't init the spinlock\n");
	}
	return lock;
}

void lock_free(lock_t *lock)
{
	if(pthread_spin_destroy(&lock->spin)!=0){
		printf("Couldn't destroy the spinlock\n");
	}
	XFREE(lock);
}

void lock_acquire(lock_t *lock)
{
	if(pthread_spin_lock(&lock->spin)!=0){
		printf("Couldn't take the lock\n");
	}
}

void lock_release(lock_t *lock)
{
	if(pthread_spin_unlock(&lock->spin)!=0){
		printf("Couldn't unlock the lock");
	}
}
