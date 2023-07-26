#include "util.h"
#include <set>

namespace day3 {

    int priority(char item)
    {
        if (item >= 'a' && item <= 'z') {
            // a-z is 1-26
            return (item - 'a') + 1;
        }
        if (item >= 'A' && item <= 'Z') {
            return (item - 'A') + 27;
        }
        fmt::print("strange item {}\n", item);
        return 0;
    }

    auto to_set = [](auto&& r) { return ranges::to<std::set>(r); };

    int search_rucksack(const std::string& contents)
    {
        auto v = contents |
                ranges::views::chunk(contents.size() / 2) |
                ranges::views::transform(to_set) |
                ranges::to_vector;

        auto& front = v[0];
        auto& back = v[1];
        auto both = ranges::views::set_intersection(front, back);

        //fmt::print("front: {} back: {} both: {}\n", ranges::to<std::string>(front), ranges::to<std::string>(back), ranges::to<std::string>(both));

        return ranges::accumulate(both | ranges::views::transform(priority), 0);
    }

    void run_part1()
    {
        auto l = lines("../input/day3.txt");
        int sum_of_priorities = ranges::accumulate(l | ranges::views::transform(search_rucksack), 0);

        fmt::print("sum of priorities: {}\n", sum_of_priorities);
    }

    void run_part2()
    {
        auto intersect_ranges = [](auto&& g) {
            std::set<char> u;
            for (const auto& e: g) {
                if (u.empty()) {
                    u.insert(e.begin(), e.end());
                } else {
                    std::set<char> tmp;
                    std::set_intersection(e.begin(), e.end(), u.begin(), u.end(), std::inserter(tmp, tmp.begin()));
                    u = std::move(tmp);
                }
                fmt::print(" {}\n", e);
            }
            fmt::print("  union {}\n", u);

            return ranges::front(u);
        };
        auto input = lines("../input/day3.txt");

        auto groups = input |
                ranges::views::transform(to_set) |
                ranges::views::chunk(3) |
                ranges::views::transform(intersect_ranges) |
                ranges::views::transform(priority);

        fmt::print("sum {}\n", ranges::accumulate(groups, 0));
    }
}

int main(int argc, char** argv)
{
    day3::run_part2();

    return 0;
}
