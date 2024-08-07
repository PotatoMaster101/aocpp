#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <ranges>
#include <stdexcept>
#include "aoc.hpp"
#include "doctest.h"

using namespace aoc;

TEST_CASE("constructor") {
    bound sut{10};
    CHECK_EQ(sut.max_x, 10);
    CHECK_EQ(sut.max_y, 10);
    CHECK_EQ(sut.min_x, 0);
    CHECK_EQ(sut.min_y, 0);

    sut = bound{12, 13, -1, -2};
    CHECK_EQ(sut.max_x, 12);
    CHECK_EQ(sut.max_y, 13);
    CHECK_EQ(sut.min_x, -1);
    CHECK_EQ(sut.min_y, -2);

    CHECK_THROWS_AS(bound{-1}, std::out_of_range);
    CHECK_THROWS_AS(bound(-1, 10, 0, 0), std::out_of_range);
    CHECK_THROWS_AS(bound(10, -1, 0, 0), std::out_of_range);
}

TEST_CASE("operator==") {
    constexpr bound sut{10};
    CHECK_EQ(sut, bound{sut.max_x});
    CHECK_NE(sut, bound{sut.max_x + 1});
}

TEST_CASE("rows") {
    constexpr bound sut{10, 15, 0, 0};
    CHECK_EQ(sut.rows(), sut.max_y - sut.min_y + 1);
}

TEST_CASE("cols") {
    constexpr bound sut{10, 15, 0, 0};
    CHECK_EQ(sut.cols(), sut.max_x - sut.min_x + 1);
}

TEST_CASE("has") {
    constexpr bound sut{10, 15, -1, -2};
    CHECK(sut.has(pos{sut.min_x, sut.min_y}));
    CHECK(sut.has(pos{sut.max_x, sut.max_y}));
    CHECK(sut.has(pos{1.2, 3.4}));
    CHECK_FALSE(sut.has(pos{11, sut.max_y}));
    CHECK_FALSE(sut.has(pos{sut.max_x, 16}));
    CHECK_FALSE(sut.has(pos{sut.min_x, -3}));
    CHECK_FALSE(sut.has(pos{-2, sut.min_y}));
}

TEST_CASE("top_left") {
    constexpr bound sut{10, 15, -1, -2};
    CHECK_EQ(sut.top_left(), pos{sut.min_x, sut.max_y});
}

TEST_CASE("top_right") {
    constexpr bound sut{10, 15, -1, -2};
    CHECK_EQ(sut.top_right(), pos{sut.max_x, sut.max_y});
}

TEST_CASE("bottom_left") {
    constexpr bound sut{10, 15, -1, -2};
    CHECK_EQ(sut.bottom_left(), pos{sut.min_x, sut.min_y});
}

TEST_CASE("bottom_right") {
    constexpr bound sut{10, 15, -1, -2};
    CHECK_EQ(sut.bottom_right(), pos{sut.max_x, sut.min_y});
}

TEST_CASE("neighbours") {
    constexpr bound b{10};
    auto sut = b.neighbours(pos{0});
    CHECK_NE(std::ranges::find(sut, pos{1, 0}), std::ranges::end(sut));
    CHECK_NE(std::ranges::find(sut, pos{0, 1}), std::ranges::end(sut));
    CHECK_EQ(std::ranges::find(sut, pos{0, -1}), std::ranges::end(sut));
    CHECK_EQ(std::ranges::find(sut, pos{-1, 0}), std::ranges::end(sut));

    sut = b.neighbours(pos{5});
    CHECK_NE(std::ranges::find(sut, pos{6, 5}), std::ranges::end(sut));
    CHECK_NE(std::ranges::find(sut, pos{5, 6}), std::ranges::end(sut));
    CHECK_NE(std::ranges::find(sut, pos{4, 5}), std::ranges::end(sut));
    CHECK_NE(std::ranges::find(sut, pos{5, 4}), std::ranges::end(sut));

    sut = b.neighbours(pos{11});
    CHECK(sut.empty());

    sut = b.neighbours(pos{5}, 2);
    CHECK_NE(std::ranges::find(sut, pos{7, 5}), std::ranges::end(sut));
    CHECK_NE(std::ranges::find(sut, pos{5, 7}), std::ranges::end(sut));
    CHECK_NE(std::ranges::find(sut, pos{3, 5}), std::ranges::end(sut));
    CHECK_NE(std::ranges::find(sut, pos{5, 3}), std::ranges::end(sut));

    auto sutPred = b.neighbours(pos{5}, [](const auto& p) { return p.x == 6 || p.y == 6; });
    CHECK_NE(std::ranges::find(sutPred, pos{6, 5}), std::ranges::end(sutPred));
    CHECK_NE(std::ranges::find(sutPred, pos{5, 6}), std::ranges::end(sutPred));
    CHECK_EQ(std::ranges::find(sutPred, pos{4, 5}), std::ranges::end(sutPred));
    CHECK_EQ(std::ranges::find(sutPred, pos{5, 4}), std::ranges::end(sutPred));
}
