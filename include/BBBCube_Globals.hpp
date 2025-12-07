#pragma once

#include <chrono>

static constexpr auto cycleTime = std::chrono::milliseconds(20);

static constexpr bool verbose = false;

static constexpr float regulationLimit = 0.174533f;
