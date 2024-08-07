#ifndef BOUND_HPP
#define BOUND_HPP
#include <concepts>
#include <cstddef>
#include <ranges>
#include <stdexcept>
#include "pos.hpp"

namespace aoc {
    /// Represents an area bound.
    template <std::integral T = std::size_t>
    struct bound {
        T max_x;
        T max_y;
        T min_x = 0;
        T min_y = 0;

        constexpr explicit bound(T max) : max_x{max}, max_y{max} {
            if (max < min_x || max < min_y)
                throw std::out_of_range{"max"};
        }

        constexpr explicit bound(T maxX, T maxY, T minX = 0, T minY = 0) : max_x{maxX}, max_y{maxY}, min_x{minX}, min_y{minY} {
            if (maxX < minX)
                throw std::out_of_range{"maxX"};
            if (maxY < minY)
                throw std::out_of_range{"maxY"};
        }

        [[nodiscard]] constexpr T rows() const {
            return max_y - min_y + 1;
        }

        [[nodiscard]] constexpr T cols() const {
            return max_x - min_x + 1;
        }

        template <typename U> requires std::is_arithmetic_v<U>
        [[nodiscard]] constexpr bool has(const pos<U>& p) const {
            return p.x >= min_x && p.x <= max_x && p.y >= min_y && p.y <= max_y;
        }

        [[nodiscard]] constexpr pos<T> top_left() const {
            return pos<T>{min_x, max_y};
        }

        [[nodiscard]] constexpr pos<T> top_right() const {
            return pos<T>{max_x, max_y};
        }

        [[nodiscard]] constexpr pos<T> bottom_left() const {
            return pos<T>{min_x, min_y};
        }

        [[nodiscard]] constexpr pos<T> bottom_right() const {
            return pos<T>{max_x, min_y};
        }

        template <typename U> requires std::is_arithmetic_v<U>
        [[nodiscard]] constexpr auto neighbours(const pos<U>& p, U dist = 1) const {
            return std::views::filter(p.neighbours(dist), [self = this](const auto& item) {
                return self->has(item);
            });
        }

        template <typename U, std::predicate<pos<U>> Pred> requires std::is_arithmetic_v<U>
        [[nodiscard]] constexpr auto neighbours(const pos<U>& p, Pred pred, U dist = 1) const {
            return std::views::filter(p.neighbours(dist), [self = this, pred](const auto& item) {
                return self->has(item) && pred(item);
            });
        }
    };

    template <typename T, typename U> requires std::is_arithmetic_v<T> && std::is_arithmetic_v<U>
    [[nodiscard]] constexpr bool operator==(const bound<T>& lhs, const bound<U>& rhs) {
        return lhs.max_x == rhs.max_x && lhs.max_y == rhs.max_y && lhs.min_x == rhs.min_x && lhs.min_y == rhs.min_y;
    }

    template <typename T, typename U> requires std::is_arithmetic_v<T> && std::is_arithmetic_v<U>
    [[nodiscard]] constexpr bool operator!=(const bound<T>& lhs, const bound<U>& rhs) {
        return !(lhs == rhs);
    }
}   // namespace aoc

#endif  // BOUND_HPP
