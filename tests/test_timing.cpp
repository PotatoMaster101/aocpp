#include <chrono>
#include <thread>
#include "aoc.hpp"
#include "doctest.h"

using namespace aoc;

TEST_CASE("time_func") {
    const auto time = time_func([](){ std::this_thread::sleep_for(std::chrono::milliseconds(500)); });
    const auto duration = std::chrono::duration<double, std::milli>(time).count();
    CHECK_GE(duration, 500);
}
