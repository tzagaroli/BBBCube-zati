#include <iostream>

#define EXERCICE_NB 1

#include "Exercices/Exercice1.hpp"

int main()
{
#if EXERCICE_NB == 1
	HelloMultithread();
#elif EXERCICE_NB == 2

#else
	std::cout << "Nothing to do" << std::endl;
#endif
}
