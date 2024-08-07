#include <ranges>
#include <string>
#include <vector>
#include "aoc.hpp"
#include "doctest.h"

using namespace aoc;

TEST_CASE("file_lines_for_each") {
    std::vector<std::string> sut1;
    file_lines_for_each("test_input.txt", [&sut1](const auto& item) { sut1.push_back(item); });
    CHECK_EQ(sut1[0], "123");
    CHECK_EQ(sut1[1], "456");
    CHECK_EQ(sut1[2], "789");

    std::vector<int> sut2;
    file_lines_for_each("test_input.txt", [&sut2](const auto& item) { sut2.push_back(std::stoi(item)); });
    CHECK_EQ(sut2[0], 123);
    CHECK_EQ(sut2[1], 456);
    CHECK_EQ(sut2[2], 789);

    std::vector<std::string> sut3;
    file_lines_for_each("test_input.txt", [&sut3](const auto& item) { sut3.push_back(item); }, false);
    CHECK_EQ(sut3[0], "123");
    CHECK_EQ(sut3[1], "456");
    CHECK_EQ(sut3[2], "");
    CHECK_EQ(sut3[3], "789");
}

TEST_CASE("read_lines") {
    const auto sut1 = read_lines("test_input.txt");
    CHECK_EQ(sut1[0], "123");
    CHECK_EQ(sut1[1], "456");
    CHECK_EQ(sut1[2], "789");

    const auto sut2 = read_lines("test_input.txt", false);
    CHECK_EQ(sut2[0], "123");
    CHECK_EQ(sut2[1], "456");
    CHECK_EQ(sut2[2], "");
    CHECK_EQ(sut2[3], "789");
}

TEST_CASE("split_string") {
    const auto sut1 = split_string("abc,def", ",") | std::ranges::to<std::vector<std::string>>();
    CHECK_NE(std::ranges::find(sut1, "abc"), std::ranges::end(sut1));
    CHECK_NE(std::ranges::find(sut1, "def"), std::ranges::end(sut1));
    CHECK_EQ(std::ranges::find(sut1, "abc,def"), std::ranges::end(sut1));

    const auto sut2 = split_string("123:.:-456", [](const auto& item) {
        return std::stoi(item);
    }, ":.:") | std::ranges::to<std::vector<int>>();
    CHECK_NE(std::ranges::find(sut2, 123), std::ranges::end(sut2));
    CHECK_NE(std::ranges::find(sut2, -456), std::ranges::end(sut2));
}

TEST_CASE("parse_pos") {
    const auto sut1 = parse_pos<int>("123, -456", [](const auto& item) {
        return std::stoi(item);
    }, ", ");
    CHECK_EQ(sut1.x, 123);
    CHECK_EQ(sut1.y, -456);

    const auto sut2 = parse_pos<double>("1.2:-3.4", [](const auto& item) {
        return std::stod(item);
    }, ":");
    CHECK_EQ(sut2.x, 1.2);
    CHECK_EQ(sut2.y, -3.4);

    const auto sut3 = parse_pos<int>("", [](const auto& item) {
        return std::stoi(item);
    }, ",");
    CHECK_EQ(sut3.x, 0);
    CHECK_EQ(sut3.y, 0);

    const auto sut4 = parse_pos<int>("123", [](const auto& item) {
        return std::stoi(item);
    }, ",");
    CHECK_EQ(sut4.x, 0);
    CHECK_EQ(sut4.y, 0);
}

TEST_CASE("parse_pos_rgx") {
    const auto sut1 = parse_pos_rgx<int>("123,456", [](const auto& item) {
        return std::stoi(item);
    }, R"((-?\d+\.?\d*),(-?\d+\.?\d*))");
    CHECK_EQ(sut1.x, 123);
    CHECK_EQ(sut1.y, 456);

    const auto sut2 = parse_pos_rgx<double>("1.2,-3.4", [](const auto& item) {
        return std::stod(item);
    }, R"((-?\d+\.?\d*),(-?\d+\.?\d*))");
    CHECK_EQ(sut2.x, 1.2);
    CHECK_EQ(sut2.y, -3.4);
}
