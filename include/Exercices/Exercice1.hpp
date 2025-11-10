#pragma once

#include <iostream>
#include <pthread.h>
#include <cstdlib>
#include <unistd.h>

int HelloMultithread();

void* thread1main(void* arg);
void* thread2main(void* arg);
