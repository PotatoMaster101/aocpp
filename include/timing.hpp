#ifndef TIMING_HPP
#define TIMING_HPP

#include <chrono>

namespace aoc {
    template <std::invocable Func>
    auto time_func(Func func) {
        const auto start = std::chrono::steady_clock::now();
        func();
        return std::chrono::steady_clock::now() - start;
    }
}   // namespace aoc

#endif  // TIMING_HPP
