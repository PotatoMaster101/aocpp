#ifndef AREA_HPP
#define AREA_HPP
#include <concepts>
#include <cstddef>
#include <ranges>
#include <stdexcept>
#include "pos.hpp"

namespace aoc {
    /// Represents a 2D area.
    template <std::integral T = std::size_t>
    struct area {
        T max_x;
        T max_y;
        T min_x = 0;
        T min_y = 0;

        constexpr explicit area(T max) : max_x{max}, max_y{max} {
            if (max < min_x || max < min_y)
                throw std::out_of_range{"max"};
        }

        constexpr explicit area(T maxX, T maxY, T minX = 0, T minY = 0) : max_x{maxX}, max_y{maxY}, min_x{minX}, min_y{minY} {
            if (maxX < minX)
                throw std::out_of_range{"maxX"};
            if (maxY < minY)
                throw std::out_of_range{"maxY"};
        }

        constexpr auto operator<=>(const area&) const = default;

        [[nodiscard]] constexpr pos<T> top_left() const noexcept {
            return pos<T>{min_x, max_y};
        }

        [[nodiscard]] constexpr pos<T> top_right() const noexcept {
            return pos<T>{max_x, max_y};
        }

        [[nodiscard]] constexpr pos<T> bottom_left() const noexcept {
            return pos<T>{min_x, min_y};
        }

        [[nodiscard]] constexpr pos<T> bottom_right() const noexcept {
            return pos<T>{max_x, min_y};
        }

        [[nodiscard]] constexpr T rows() const noexcept {
            return max_y - min_y + 1;
        }

        [[nodiscard]] constexpr T cols() const noexcept {
            return max_x - min_x + 1;
        }

        template <typename U> requires std::is_arithmetic_v<U>
        [[nodiscard]] constexpr bool has(const pos<U>& p) const noexcept {
            return p.x >= min_x && p.x <= max_x && p.y >= min_y && p.y <= max_y;
        }

        template <typename U> requires std::is_arithmetic_v<U>
        [[nodiscard]] constexpr bool has(const area<U>& b) const noexcept {
            return max_x >= b.max_x && min_x <= b.min_x && max_y >= b.max_y && min_y <= b.min_y;
        }

        template <typename U> requires std::is_arithmetic_v<U>
        [[nodiscard]] constexpr bool intersects(const area<U>& b) const noexcept {
            return min_x <= b.max_x && max_x >= b.min_x && min_y <= b.max_y && max_y >= b.min_y;
        }

        template <std::ranges::range Rng>
        [[nodiscard]] auto in_area(Rng posRng) const {
            return std::views::filter(posRng, [self = this](const auto& p) {
                return self->has(p);
            });
        }

        template <std::ranges::range Rng, std::predicate<pos<T>> Pred>
        [[nodiscard]] auto in_area(Rng posRng, Pred pred) const {
            return std::views::filter(posRng, [self = this, pred](const auto& p) {
                return self->has(p) && pred(p);
            });
        }
    };
}   // namespace aoc

#endif  // AREA_HPP
