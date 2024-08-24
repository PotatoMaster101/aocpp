#ifndef INPUT_HPP
#define INPUT_HPP
#include <concepts>
#include <cstddef>
#include <fstream>
#include <regex>
#include <string>
#include <vector>
#include "pos.hpp"

namespace aoc {
    template <std::invocable<std::string> Func>
    void file_lines_for_each(const std::string& path, Func forEach, const bool skipEmpty = true) {
        std::ifstream file{path};
        std::string line;
        while (std::getline(file, line))
            if (!line.empty() || !skipEmpty)
                forEach(line);
    }

    [[nodiscard]] inline std::vector<std::string> read_lines(const std::string& path, const bool skipEmpty = true) {
        std::vector<std::string> result;
        file_lines_for_each(path, [&result](const auto& line) { result.push_back(line); }, skipEmpty);
        return result;
    }

    [[nodiscard]] inline auto split_string(const std::string& str, const std::string& delim = ",") {
        return std::views::split(str, delim) | std::views::transform([](const auto& splitRng) {
            return std::string(std::ranges::cbegin(splitRng), std::ranges::cend(splitRng));
        });
    }

    template <std::invocable<std::string> Func>
    [[nodiscard]] auto split_string(const std::string& str, Func parse, const std::string& delim = ",") {
        return std::views::split(str, delim) | std::views::transform([parse](const auto& splitRng) {
            return parse(std::string(std::ranges::cbegin(splitRng), std::ranges::cend(splitRng)));
        });
    }

    template <typename T = std::size_t, std::invocable<std::string> Func> requires std::is_arithmetic_v<T>
    [[nodiscard]] pos<T> parse_pos(const std::string& str, Func parse, const std::string& delim = ",") {
        const auto splits = split_string(str, parse, delim) | std::views::take(2) | std::ranges::to<std::vector<T>>();
        return splits.size() == 2 ? pos<T>{splits[0], splits[1]} : pos<T>{};
    }

    template <typename T = std::size_t, std::invocable<std::string> Func> requires std::is_arithmetic_v<T>
    [[nodiscard]] pos<T> parse_pos_rgx(const std::string& str, Func parseFunc, const std::string& rgx = R"((-?\d+\.?\d*),(-?\d+\.?\d*))") {
        const std::regex r{rgx};
        std::smatch m;
        return std::regex_match(str, m, r) && m.size() == 3 ? pos<T>{parseFunc(m[1]), parseFunc(m[2])} : pos<T>{};
    }
}   // namespace aoc

#endif  // INPUT_HPP
