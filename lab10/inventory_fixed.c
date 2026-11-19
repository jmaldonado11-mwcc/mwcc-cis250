#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <semaphore.h>
 
#define ORDER_QUANTITY 30

int main(void)
{
    // Allocate shared memory for inventory
    int *inventory = mmap(
        NULL,
        sizeof(int),
        PROT_READ | PROT_WRITE,
        MAP_SHARED | MAP_ANONYMOUS,
        -1,
        0
    );
 
    if (inventory == MAP_FAILED) {
        perror("mmap");
        return 1;
    }

    sem_t *semaphore = mmap(
        NULL,
        sizeof(sem_t),
        PROT_READ | PROT_WRITE,
        MAP_SHARED | MAP_ANONYMOUS,
        -1,
        0
    );

    if (semaphore == MAP_FAILED) {
        perror("semaphore mmap");
	munmap(inventory, sizeof(int));
        return 1;
    }

    if (sem_init(semaphore, 1, 1) < 0) {
        perror("sem_init");
        munmap(inventory, sizeof(int));
	munmap(semaphore, sizeof(sem_t));
        return 1;
    }

    *inventory = 100;
 
    printf("Starting inventory: %d\n", *inventory);
    fflush(stdout);
 
    // Create first order-processing process
    pid_t pid1 = fork();
 
    if (pid1 < 0) {
        perror("fork");
	sem_destroy(semaphore);
        munmap(inventory, sizeof(int));
        munmap(semaphore, sizeof(int));
        return 1;
    }
 
    if (pid1 == 0) {
        // Process customer order 1
	sem_wait(semaphore);

        int available = *inventory;
 
        if (available >= ORDER_QUANTITY) {
            available -= ORDER_QUANTITY;
            *inventory = available;
 
            printf("Order 1 fulfilled: %d units\n",
                   ORDER_QUANTITY);
        }
	sem_post(semaphore); 
        _exit(0);
    }
 
    // Create second order-processing process
    pid_t pid2 = fork();
 
    if (pid2 < 0) {
        perror("fork");
	sem_destroy(semaphore);
        waitpid(pid1, NULL, 0);
        munmap(inventory, sizeof(int));
        munmap(semaphore, sizeof(int));
        return 1;
    }
 
    if (pid2 == 0) {
        // Process customer order 2
	sem_wait(semaphore);

        int available = *inventory;
 
        if (available >= ORDER_QUANTITY) {
            available -= ORDER_QUANTITY;
            *inventory = available;
 
            printf("Order 2 fulfilled: %d units\n",
                   ORDER_QUANTITY);
        }

	sem_post(semaphore); 
        _exit(0);
    }
 
    // Wait for both order-processing processes
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
 
    printf("\nExpected inventory: 40\n");
    printf("Actual inventory:   %d\n", *inventory);
 
    // Release shared memory
    sem_destroy(semaphore);
    munmap(inventory, sizeof(int));
    munmap(semaphore, sizeof(int));
 
    return 0;
}
