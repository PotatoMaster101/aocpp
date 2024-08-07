#include <stdexcept>
#include <string>
#include <vector>
#include "aoc.hpp"
#include "doctest.h"

using namespace aoc;

TEST_CASE("constructor") {
    CHECK_THROWS_AS(grid{std::vector<std::string>()}, std::out_of_range);
    CHECK_THROWS_AS(grid{std::vector<std::string>(1)}, std::out_of_range);
}

TEST_CASE("boundary") {
    const auto sut = grid{std::vector<std::string>{"abc", "def"}};
    const auto boundary = sut.boundary();
    CHECK_EQ(boundary.max_x, 2);
    CHECK_EQ(boundary.max_y, 1);
    CHECK_EQ(boundary.min_x, 0);
    CHECK_EQ(boundary.min_y, 0);
}

TEST_CASE("operator[]") {
    auto sut = grid{std::vector<std::string>{"abc", "def"}};
    CHECK_EQ(sut[0], "abc");
    CHECK_EQ(sut[1], "def");

    CHECK_EQ(sut[pos{0, 0}], 'a');
    CHECK_EQ(sut[pos{0, 1}], 'd');

    sut[pos{0, 0}] = 'z';
    CHECK_EQ(sut[0], "zbc");
    CHECK_EQ(sut[pos{0, 0}], 'z');
}
