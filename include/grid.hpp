#ifndef CHAR_GRID_HPP
#define CHAR_GRID_HPP
#include <cstddef>
#include <stdexcept>
#include "pos.hpp"

namespace aoc {
    /// Represents a grid.
    template <std::ranges::random_access_range Cont>
    struct grid {
        Cont data;

        explicit grid(const Cont& data) : data(data) {
            if (std::size(data) == 0 || std::size(data[0]) == 0)
                throw std::out_of_range("data");
        }

        [[nodiscard]] bound<> boundary() const {
            return bound<>{std::size(data[0]) - 1, std::size(data) - 1};
        }

        const auto& operator[](std::size_t i) const {
            return data[i];
        }

        template <std::integral T = std::size_t>
        const auto& operator[](const pos<T>& p) const {
            return data[p.y][p.x];
        }

        template <std::integral T = std::size_t>
        auto& operator[](const pos<T>& p) {
            return data[p.y][p.x];
        }
    };
}    // namespace aoc

#endif  // CHAR_GRID_HPP
