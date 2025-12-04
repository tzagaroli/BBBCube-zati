#pragma once

#include <atomic>
#include <csignal>

extern std::atomic<bool> g_stop;   // Déclaration seulement

void sigintHandler(int);           // Déclaration seulement
