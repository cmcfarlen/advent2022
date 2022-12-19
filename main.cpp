#include <fstream>
#include <optional>
#include <string>
#include <algorithm>

#include "fmt/core.h"
#include "range/v3/all.hpp"

std::optional<std::ifstream> open(const std::string& path)
{
    std::ifstream result(path);
    if (result.is_open()) {
        return result;
    }
    return std::nullopt;
}

int to_int(const std::string& s)
{
    return std::stoi(s);
}

void day1()
{
    struct Elf {
        int id;
        int sum;

        int operator<=>(const Elf& other) const {
            return other.sum - sum;
        }
    };
    auto f = std::ifstream("../day1.txt");
    if (f.bad()) {
        throw std::runtime_error("Failed to open");
    }

    auto comp = ranges::views::split("") |
                ranges::views::transform([id = 0](auto group) mutable {
                    return Elf{id++, ranges::accumulate(group | ranges::views::transform(to_int), 0) };
                });

    std::vector<Elf> data = ranges::getlines(f) | comp | ranges::to_vector;

    std::sort(data.begin(), data.end());

    for (auto elf: data) {
        fmt::print("new elf {}: {} \n", elf.id, elf.sum);
    }

    Elf elf = data.front();
    fmt::print("best elf {}:{}\n", elf.id, elf.sum);

    int sum = ranges::accumulate(data | ranges::views::take(3) | ranges::views::transform([](auto& e) { return e.sum; }), 0);
    fmt::print("first three sum: {}\n", sum);
}

void day2()
{
    auto f = std::ifstream("../day2.txt");
    if (f.bad()) {
        throw std::runtime_error("Failed to open");
    }

    enum class Move {
        Rock,
        Paper,
        Scissor
    };

    template<> struct fmt::formatter<Move> {
        constexpr auto parse(format_parse_context& ctx) -> decltype(ctx.begin()) {
        }

        template <typename FormatContext>
        auto format(const Move& m, FormatContext& ctx) const -> declttype(ctx.out()) {

        }
    };



    auto move = [](const std::string& m) -> Move {
        switch (m[0])
        {
            case 'A':
            case 'X':
                return Move::Rock;
            case 'B':
            case 'Y':
                return Move::Paper;
            case 'C':
            case 'Z':
                return Move::Scissor;
        }
        return Move::Scissor;
    };

    std::vector<std::vector<Move>> data = ranges::getlines(f) | ranges::views::transform([=](const std::string& line) {
        return line | ranges::views::split(' ') | ranges::views::transform([](auto &&rng) { return std::string(&*rng.begin(), ranges::distance(rng)); }) | ranges::views::transform(move)  | ranges::to_vector;
    }) | ranges::to_vector;

    for (auto& x: data) {
        fmt::print("data: {} {}\n", x[0], x[1]);
    }

}

int main() {

    fmt::print("Hello, World!\n");
    //auto v = slurp_lines("../test.txt");
    day2();
    return 0;
}
