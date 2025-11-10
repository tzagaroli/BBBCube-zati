#include "Exercices/Exercice1.hpp"

/**
 * \brief HelloMultithread "Main"
 */
int HelloMultithread()
{
    // Init two threads : thread1_id and thread2_id
	pthread_t thread1_id;
	pthread_t thread2_id;

    // Create thread1_id that should run thread1main
	int ret = pthread_create(&thread1_id, NULL, thread1main, NULL);
	if(ret < 0)
	{
		std::cerr << "pthread_create 1 failed!" << std::endl;
	}

    // Create thread2_id that should run thread2main
	ret = pthread_create(&thread2_id, NULL, thread2main, NULL);
	if(ret < 0)
	{
		std::cerr << "pthread_create 2 failed!" << std::endl;
	}

    // Wait for both threads to join (Never reached)
	pthread_join(thread1_id, NULL);
	pthread_join(thread2_id, NULL);

    return 0;
}

void* thread1main(void* arg)
{
	while(true)
	{
        // Print on console
		std::cout << "Hello World! Ich bin der erste Thread!" << std::endl;
        // Wait 1s
		sleep(1);
	}
}
void* thread2main(void* arg)
{
	while(true)
	{
        // Print on console
		std::cout << "Hello World! Ich bin der zweite Thread!" << std::endl;
        // Wait 1s
		sleep(1);
	}
}