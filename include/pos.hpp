#ifndef POS_HPP
#define POS_HPP
#include <array>
#include <cmath>
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

        [[nodiscard]] constexpr pos up(T val = 1) const {
            return pos{x, y + val};
        }

        [[nodiscard]] constexpr pos down(T val = 1) const {
            return pos{x, y - val};
        }

        [[nodiscard]] constexpr pos left(T val = 1) const {
            return pos{x - val, y};
        }

        [[nodiscard]] constexpr pos right(T val = 1) const {
            return pos{x + val, y};
        }

        [[nodiscard]] constexpr std::array<pos, 4> neighbours(T dist = 1) const {
            return { pos{x + dist, y}, pos{x - dist, y}, pos{x, y + dist}, pos{x, y - dist} };
        }

        [[nodiscard]] constexpr pos swap() const {
            return pos{y, x};
        }

        template <typename U> requires std::is_arithmetic_v<U>
        [[nodiscard]] T mdist(const pos<U>& another) const {
            return std::abs(x - another.x) + std::abs(y - another.y);
        }

        template <typename U> requires std::is_arithmetic_v<U>
        constexpr pos& operator+=(const pos<U>& rhs) {
            x += rhs.x;
            y += rhs.y;
            return *this;
        }

        template <typename U> requires std::is_arithmetic_v<U>
        constexpr pos& operator-=(const pos<U>& rhs) {
            x -= rhs.x;
            y -= rhs.y;
            return *this;
        }

        template <typename U> requires std::is_arithmetic_v<U>
        constexpr pos& operator*=(U rhs) {
            x *= rhs;
            y *= rhs;
            return *this;
        }

        constexpr auto operator<=>(const pos&) const = default;
    };

    template <typename T, typename U> requires std::is_arithmetic_v<T> && std::is_arithmetic_v<U>
    [[nodiscard]] constexpr pos<T> operator+(const pos<T>& lhs, const pos<U>& rhs) {
        return pos<T>{lhs.x + rhs.x, lhs.y + rhs.y};
    }

    template <typename T, typename U> requires std::is_arithmetic_v<T> && std::is_arithmetic_v<U>
    [[nodiscard]] constexpr pos<T> operator-(const pos<T>& lhs, const pos<U>& rhs) {
        return pos<T>{lhs.x - rhs.x, lhs.y - rhs.y};
    }

    template <typename T, typename U> requires std::is_arithmetic_v<T> && std::is_arithmetic_v<U>
    [[nodiscard]] constexpr pos<T> operator*(const pos<T>& lhs, U rhs) {
        return pos<T>{lhs.x * rhs, lhs.y * rhs};
    }

    template <typename T, typename U> requires std::is_arithmetic_v<T> && std::is_arithmetic_v<U>
    [[nodiscard]] constexpr pos<T> operator*(U lhs, const pos<T>& rhs) {
        return pos<T>{lhs * rhs.x, lhs * rhs.y};
    }

    template <typename T> requires std::is_arithmetic_v<T>
    [[nodiscard]] constexpr pos<T> operator-(const pos<T>& lhs) {
        return pos<T>{-lhs.x, -lhs.y};
    }

    template <typename T> requires std::is_arithmetic_v<T>
    std::ostream& operator<<(std::ostream& os, const pos<T>& pos) {
        return os << '(' << pos.x << ',' << pos.y << ')';
    }
}   // namespace aoc

#endif  // POS_HPP
