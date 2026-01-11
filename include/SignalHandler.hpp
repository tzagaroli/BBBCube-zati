#pragma once

#include <atomic>
#include <csignal>

// Global atomic flag indicating whether the application should stop
extern std::atomic<bool> g_stop;

// Signal handler for SIGINT (e.g., triggered by Ctrl+C)
void sigintHandler(int);
