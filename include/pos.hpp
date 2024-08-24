#ifndef POS_HPP
#define POS_HPP
#include <array>
#include <cmath>
#include <concepts>
#include <cstddef>
#include <ostream>

namespace aoc {
    /// Represents a position in a 2D space.
    template <typename T = std::size_t> requires std::is_arithmetic_v<T>
    struct pos {
        T x;
        T y;

        constexpr explicit pos(T xy = 0) : x{xy}, y{xy} {}
        constexpr explicit pos(T x, T y) : x{x}, y{y} {}
        constexpr auto operator<=>(const pos&) const = default;

        [[nodiscard]] constexpr pos up(T distance = 1) const noexcept {
            return pos{x, y + distance};
        }

        [[nodiscard]] constexpr pos down(T distance = 1) const noexcept {
            return pos{x, y - distance};
        }

        [[nodiscard]] constexpr pos left(T distance = 1) const noexcept {
            return pos{x - distance, y};
        }

        [[nodiscard]] constexpr pos right(T distance = 1) const noexcept {
            return pos{x + distance, y};
        }

        [[nodiscard]] constexpr std::array<pos, 4> neighbours(T distance = 1) const noexcept {
            return { pos{x + distance, y}, pos{x - distance, y}, pos{x, y + distance}, pos{x, y - distance} };
        }

        [[nodiscard]] constexpr std::array<pos, 4> neighbours_diag(T distance = 1) const noexcept {
            return { pos{x + distance, y + distance}, pos{x + distance, y - distance}, pos{x - distance, y + distance}, pos{x - distance, y - distance} };
        }

        [[nodiscard]] constexpr pos swap() const noexcept {
            return pos{y, x};
        }

        template <typename U> requires std::is_arithmetic_v<U>
        [[nodiscard]] T manhattan(const pos<U>& another) const {
            return std::abs(x - another.x) + std::abs(y - another.y);
        }

        template <typename U> requires std::is_arithmetic_v<U>
        constexpr pos& operator+=(const pos<U>& rhs) noexcept {
            x += rhs.x;
            y += rhs.y;
            return *this;
        }

        template <typename U> requires std::is_arithmetic_v<U>
        constexpr pos& operator-=(const pos<U>& rhs) noexcept {
            x -= rhs.x;
            y -= rhs.y;
            return *this;
        }

        template <typename U> requires std::is_arithmetic_v<U>
        constexpr pos& operator*=(U rhs) noexcept {
            x *= rhs;
            y *= rhs;
            return *this;
        }
    };

    template <typename T = std::size_t> requires std::is_arithmetic_v<T>
    [[nodiscard]] constexpr pos<T> origin() noexcept {
        return pos<T>{0, 0};
    }

    template <typename T = std::size_t> requires std::is_arithmetic_v<T>
    [[nodiscard]] constexpr pos<T> unit_x() noexcept {
        return pos<T>{1, 0};
    }

    template <typename T = std::size_t> requires std::is_arithmetic_v<T>
    [[nodiscard]] constexpr pos<T> unit_y() noexcept {
        return pos<T>{0, 1};
    }

    template <std::ranges::random_access_range Rng, std::integral T = std::size_t>
    auto& at(Rng& rng, const pos<T>& pos) {
        return rng[pos.y][pos.x];
    }

    template <std::ranges::random_access_range Rng, std::integral T = std::size_t>
    [[nodiscard]] const auto& at(const Rng& rng, const pos<T>& pos) {
        return rng[pos.y][pos.x];
    }

    template <typename T, typename U> requires std::is_arithmetic_v<T> && std::is_arithmetic_v<U>
    [[nodiscard]] constexpr pos<T> operator+(const pos<T>& lhs, const pos<U>& rhs) noexcept {
        return pos<T>{lhs.x + rhs.x, lhs.y + rhs.y};
    }

    template <typename T, typename U> requires std::is_arithmetic_v<T> && std::is_arithmetic_v<U>
    [[nodiscard]] constexpr pos<T> operator-(const pos<T>& lhs, const pos<U>& rhs) noexcept {
        return pos<T>{lhs.x - rhs.x, lhs.y - rhs.y};
    }

    template <typename T, typename U> requires std::is_arithmetic_v<T> && std::is_arithmetic_v<U>
    [[nodiscard]] constexpr pos<T> operator*(const pos<T>& lhs, U rhs) noexcept {
        return pos<T>{lhs.x * rhs, lhs.y * rhs};
    }

    template <typename T, typename U> requires std::is_arithmetic_v<T> && std::is_arithmetic_v<U>
    [[nodiscard]] constexpr pos<T> operator*(U lhs, const pos<T>& rhs) noexcept {
        return pos<T>{lhs * rhs.x, lhs * rhs.y};
    }

    template <typename T> requires std::is_arithmetic_v<T>
    [[nodiscard]] constexpr pos<T> operator-(const pos<T>& lhs) noexcept {
        return pos<T>{-lhs.x, -lhs.y};
    }

    template <typename T> requires std::is_arithmetic_v<T>
    std::ostream& operator<<(std::ostream& os, const pos<T>& pos) {
        return os << '(' << pos.x << ',' << pos.y << ')';
    }
}   // namespace aoc

#endif  // POS_HPP
