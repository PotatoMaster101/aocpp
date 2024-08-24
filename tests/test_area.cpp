#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <ranges>
#include <stdexcept>
#include "aoc.hpp"
#include "doctest.h"

using namespace aoc;

TEST_CASE("constructor") {
    area sut{10};
    CHECK_EQ(sut.max_x, 10);
    CHECK_EQ(sut.max_y, 10);
    CHECK_EQ(sut.min_x, 0);
    CHECK_EQ(sut.min_y, 0);

    sut = area{12, 13, -1, -2};
    CHECK_EQ(sut.max_x, 12);
    CHECK_EQ(sut.max_y, 13);
    CHECK_EQ(sut.min_x, -1);
    CHECK_EQ(sut.min_y, -2);

    CHECK_THROWS_AS(area{-1}, std::out_of_range);
    CHECK_THROWS_AS(area(-1, 10, 0, 0), std::out_of_range);
    CHECK_THROWS_AS(area(10, -1, 0, 0), std::out_of_range);
}

TEST_CASE("rows") {
    constexpr area sut{10, 15, 0, 0};
    CHECK_EQ(sut.rows(), sut.max_y - sut.min_y + 1);
}

TEST_CASE("cols") {
    constexpr area sut{10, 15, 0, 0};
    CHECK_EQ(sut.cols(), sut.max_x - sut.min_x + 1);
}

TEST_CASE("has") {
    constexpr area sut1{10, 15, -1, -2};
    CHECK(sut1.has(pos{sut1.min_x, sut1.min_y}));
    CHECK(sut1.has(pos{sut1.max_x, sut1.max_y}));
    CHECK(sut1.has(pos{1.2, 3.4}));
    CHECK_FALSE(sut1.has(pos{11, sut1.max_y}));
    CHECK_FALSE(sut1.has(pos{sut1.max_x, 16}));
    CHECK_FALSE(sut1.has(pos{sut1.min_x, -3}));
    CHECK_FALSE(sut1.has(pos{-2, sut1.min_y}));

    constexpr area sut2{10, 10, -10, -10};
    CHECK(sut2.has(area{10, 10, -10, -10}));
    CHECK(sut2.has(area{5, 5, 0, 0}));
    CHECK(sut2.has(area{0, 0, -5, -5}));
    CHECK_FALSE(sut2.has(area{11, 10, -10, -10}));
    CHECK_FALSE(sut2.has(area{10, 11, -10, -10}));
    CHECK_FALSE(sut2.has(area{10, 10, -11, -10}));
    CHECK_FALSE(sut2.has(area{10, 10, -10, -11}));

    constexpr area sut3{0, 0, 0, 0};
    CHECK(sut3.has(pos{0, 0}));
}

TEST_CASE("intersects") {
    constexpr area sut1{10, 10, -10, -10};
    CHECK(sut1.intersects(area{10, 10, -10, -10}));
    CHECK(sut1.intersects(area{5, 5, 0, 0}));
    CHECK(sut1.intersects(area{0, 0, -5, -5}));
    CHECK(sut1.intersects(area{11, 10, -10, -10}));
    CHECK(sut1.intersects(area{10, 10, -11, -10}));
    CHECK(sut1.intersects(area{10, 10, -10, -11}));
    CHECK(sut1.intersects(area{100, 100, -100, -100}));

    constexpr area sut2{10, 10, 0, 0};
    CHECK_FALSE(sut2.intersects(area{-1, -1, -10, -10}));
    CHECK_FALSE(sut2.intersects(area{-1, 10, -10, 0}));
    CHECK_FALSE(sut2.intersects(area{10, -1, 0, -10}));

    constexpr area sut3{0, 0, 0, 0};
    CHECK(sut3.intersects(area{0, 0, 0, 0}));
}

TEST_CASE("top_left") {
    constexpr area sut1{10, 15, -1, -2};
    CHECK_EQ(sut1.top_left(), pos{sut1.min_x, sut1.max_y});

    constexpr area sut2{0};
    CHECK_EQ(sut2.top_left(), pos{0});
}

TEST_CASE("top_right") {
    constexpr area sut1{10, 15, -1, -2};
    CHECK_EQ(sut1.top_right(), pos{sut1.max_x, sut1.max_y});

    constexpr area sut2{0};
    CHECK_EQ(sut2.top_right(), pos{0});
}

TEST_CASE("bottom_left") {
    constexpr area sut1{10, 15, -1, -2};
    CHECK_EQ(sut1.bottom_left(), pos{sut1.min_x, sut1.min_y});

    constexpr area sut2{0};
    CHECK_EQ(sut2.bottom_left(), pos{0});
}

TEST_CASE("bottom_right") {
    constexpr area sut1{10, 15, -1, -2};
    CHECK_EQ(sut1.bottom_right(), pos{sut1.max_x, sut1.min_y});

    constexpr area sut2{0};
    CHECK_EQ(sut2.bottom_right(), pos{0});
}

TEST_CASE("in_area") {
    constexpr area obj{10, 10, 0, 0};
    const auto sut1 = obj.in_area(pos{0, 0}.neighbours()) | std::ranges::to<std::vector<pos<int>>>();
    CHECK_EQ(sut1.size(), 2);
    CHECK_NE(std::ranges::find(sut1, pos{1, 0}), std::ranges::end(sut1));
    CHECK_NE(std::ranges::find(sut1, pos{0, 1}), std::ranges::end(sut1));
    CHECK_EQ(std::ranges::find(sut1, pos{-1, 0}), std::ranges::end(sut1));
    CHECK_EQ(std::ranges::find(sut1, pos{0, -1}), std::ranges::end(sut1));

    const auto sut2 = obj.in_area(pos{5, 5}.neighbours()) | std::ranges::to<std::vector<pos<int>>>();
    CHECK_EQ(sut2.size(), 4);
    CHECK_NE(std::ranges::find(sut2, pos{4, 5}), std::ranges::end(sut2));
    CHECK_NE(std::ranges::find(sut2, pos{6, 5}), std::ranges::end(sut2));
    CHECK_NE(std::ranges::find(sut2, pos{5, 4}), std::ranges::end(sut2));
    CHECK_NE(std::ranges::find(sut2, pos{5, 6}), std::ranges::end(sut2));

    const auto sut3 = obj.in_area(pos{5, 5}.neighbours(), [](const auto& p) {
        return p.x == 6 || p.y == 6;
    }) | std::ranges::to<std::vector<pos<int>>>();
    CHECK_EQ(sut3.size(), 2);
    CHECK_NE(std::ranges::find(sut3, pos{6, 5}), std::ranges::end(sut3));
    CHECK_NE(std::ranges::find(sut3, pos{5, 6}), std::ranges::end(sut3));
}
