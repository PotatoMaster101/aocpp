#include <cmath>
#include <ranges>
#include "aoc.hpp"
#include "doctest.h"

using namespace aoc;

TEST_CASE("constructor") {
    pos sut{10, 15};
    CHECK_EQ(sut.x, 10);
    CHECK_EQ(sut.y, 15);

    sut = pos{20};
    CHECK_EQ(sut.x, 20);
    CHECK_EQ(sut.y, 20);
}

TEST_CASE("operator+=") {
    pos sut{10, 15};
    sut += pos{20, 25};
    CHECK_EQ(sut.x, 10 + 20);
    CHECK_EQ(sut.y, 15 + 25);
}

TEST_CASE("operator+") {
    constexpr pos p{10, 15};
    constexpr pos sut = p + pos{20, 25};
    CHECK_EQ(sut.x, p.x + 20);
    CHECK_EQ(sut.y, p.y + 25);
}

TEST_CASE("operator-=") {
    pos sut{10, 15};
    sut -= pos{20, 25};
    CHECK_EQ(sut.x, 10 - 20);
    CHECK_EQ(sut.y, 15 - 25);
}

TEST_CASE("operator-") {
    constexpr pos p{10, 15};
    constexpr auto sut = p - pos{20, 25};
    CHECK_EQ(sut.x, p.x - 20);
    CHECK_EQ(sut.y, p.y - 25);
}

TEST_CASE("operator*=") {
    pos sut{10, 15};
    sut *= 5;
    CHECK_EQ(sut.x, 10 * 5);
    CHECK_EQ(sut.y, 15 * 5);
}

TEST_CASE("operator*") {
    constexpr pos p{10, 15};
    auto sut = p * 5;
    CHECK_EQ(sut.x, p.x * 5);
    CHECK_EQ(sut.y, p.y * 5);

    sut = 5 * p;
    CHECK_EQ(sut.x, p.x * 5);
    CHECK_EQ(sut.y, p.y * 5);
}

TEST_CASE("up") {
    constexpr pos p{10, 15};
    constexpr auto sut = p.up();
    CHECK_EQ(sut.x, p.x);
    CHECK_EQ(sut.y, p.y + 1);
}

TEST_CASE("down") {
    constexpr pos p{10, 15};
    constexpr auto sut = p.down();
    CHECK_EQ(sut.x, p.x);
    CHECK_EQ(sut.y, p.y - 1);
}

TEST_CASE("left") {
    constexpr pos p{10, 15};
    constexpr auto sut = p.left();
    CHECK_EQ(sut.x, p.x - 1);
    CHECK_EQ(sut.y, p.y);
}

TEST_CASE("right") {
    constexpr pos p{10, 15};
    constexpr auto sut = p.right();
    CHECK_EQ(sut.x, p.x + 1);
    CHECK_EQ(sut.y, p.y);
}

TEST_CASE("neighbours") {
    constexpr pos p{10, 15};
    auto sut = p.neighbours();
    CHECK_NE(std::ranges::find(sut, pos{p.x, p.y + 1}), std::ranges::end(sut));
    CHECK_NE(std::ranges::find(sut, pos{p.x, p.y - 1}), std::ranges::end(sut));
    CHECK_NE(std::ranges::find(sut, pos{p.x + 1, p.y}), std::ranges::end(sut));
    CHECK_NE(std::ranges::find(sut, pos{p.x - 1, p.y}), std::ranges::end(sut));

    sut = p.neighbours(3);
    CHECK_NE(std::ranges::find(sut, pos{p.x, p.y + 3}), std::ranges::end(sut));
    CHECK_NE(std::ranges::find(sut, pos{p.x, p.y - 3}), std::ranges::end(sut));
    CHECK_NE(std::ranges::find(sut, pos{p.x + 3, p.y}), std::ranges::end(sut));
    CHECK_NE(std::ranges::find(sut, pos{p.x - 3, p.y}), std::ranges::end(sut));
}

TEST_CASE("neighbours_diag") {
    constexpr pos p{10, 15};
    auto sut = p.neighbours_diag();
    CHECK_NE(std::ranges::find(sut, pos{p.x + 1, p.y + 1}), std::ranges::end(sut));
    CHECK_NE(std::ranges::find(sut, pos{p.x - 1, p.y + 1}), std::ranges::end(sut));
    CHECK_NE(std::ranges::find(sut, pos{p.x + 1, p.y - 1}), std::ranges::end(sut));
    CHECK_NE(std::ranges::find(sut, pos{p.x - 1, p.y - 1}), std::ranges::end(sut));

    sut = p.neighbours_diag(3);
    CHECK_NE(std::ranges::find(sut, pos{p.x + 3, p.y + 3}), std::ranges::end(sut));
    CHECK_NE(std::ranges::find(sut, pos{p.x - 3, p.y + 3}), std::ranges::end(sut));
    CHECK_NE(std::ranges::find(sut, pos{p.x + 3, p.y - 3}), std::ranges::end(sut));
    CHECK_NE(std::ranges::find(sut, pos{p.x - 3, p.y - 3}), std::ranges::end(sut));
}

TEST_CASE("swap") {
    constexpr pos p{10, 15};
    constexpr auto sut = p.swap();
    CHECK_EQ(sut.x, p.y);
    CHECK_EQ(sut.y, p.x);
}

TEST_CASE("manhattan") {
    constexpr pos p{10, 15};
    constexpr auto another = pos{20, 54};
    const auto sut = p.manhattan(another);
    CHECK_EQ(sut, std::abs(p.x - another.x) + std::abs(p.y - another.y));
}

TEST_CASE("at") {
    const std::vector<std::string> sut1{"abc", "def"};
    CHECK_EQ(at(sut1, pos<>{0}), 'a');
    CHECK_EQ(at(sut1, pos<>{1, 1}), 'e');

    std::vector<std::string> sut2{"abc", "def"};
    at(sut2, pos<>{0}) = 'z';
    CHECK_EQ(at(sut2, pos<>{0}), 'z');
}

TEST_CASE("origin") {
    constexpr auto sut = origin();
    CHECK_EQ(sut.x, 0);
    CHECK_EQ(sut.y, 0);
}

TEST_CASE("unit_x") {
    constexpr auto sut = unit_x();
    CHECK_EQ(sut.x, 1);
    CHECK_EQ(sut.y, 0);
}

TEST_CASE("unit_y") {
    constexpr auto sut = unit_y();
    CHECK_EQ(sut.x, 0);
    CHECK_EQ(sut.y, 1);
}
