#include "SignalHandler.hpp"
#include <iostream>

std::atomic<bool> g_stop{false};   // Définition unique


// Signal handler called when SIGINT (Ctrl+C) is received
void sigintHandler(int)
{
    std::cout << "SIGINT received" << std::endl;
    g_stop.store(true);
}
