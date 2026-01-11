#pragma once

#include <atomic>
#include <csignal>

extern std::atomic<bool> g_stop;

void sigintHandler(int);
