#include "SignalHandler.hpp"
#include <iostream>

std::atomic<bool> g_stop{false};   // Définition unique

void sigintHandler(int)
{
    std::cout << "SIGINT received" << std::endl;
    g_stop.store(true);
}
