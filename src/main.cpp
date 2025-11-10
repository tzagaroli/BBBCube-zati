#include <iostream>

#define EXERCICE_NB 3

#include "Exercices/Exercice1.hpp"
#include "Exercices/Exercice3.hpp"

int main()
{
#if EXERCICE_NB == 1
	HelloMultithread();
#elif EXERCICE_NB == 2

#elif EXERCICE_NB == 3
	main_ex3();
#else
	std::cout << "Nothing to do" << std::endl;
#endif
}
