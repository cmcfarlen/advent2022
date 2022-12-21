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

    int search_rucksack(const std::string& contents)
    {
        auto v = contents |
                ranges::views::chunk(contents.size() / 2) |
                ranges::views::transform([](auto&&r) { return ranges::to<std::set>(r); }) |
                ranges::to_vector;

        auto& front = v[0];
        auto& back = v[1];
        auto both = ranges::views::set_intersection(front, back);

        //fmt::print("front: {} back: {} both: {}\n", ranges::to<std::string>(front), ranges::to<std::string>(back), ranges::to<std::string>(both));

        return ranges::accumulate(both | ranges::views::transform(priority), 0);
    }

    void run()
    {
        auto f = std::ifstream("../input/day3.txt");
        if (f.bad()) {
            throw std::runtime_error("Failed to open");
        }

        int sum_of_priorities = ranges::accumulate(ranges::getlines(f) | ranges::views::transform(search_rucksack), 0);

        fmt::print("sum of priorities: {}\n", sum_of_priorities);

        f.seekg(0);

        sum_of_priorities = ranges::accumulate(ranges::getlines(f) | ranges::views::transform(search_rucksack), 0);

        fmt::print("sum of priorities: {}\n", sum_of_priorities);
    }
}

int main(int argc, char** argv)
{
    day3::run();

    return 0;
}
