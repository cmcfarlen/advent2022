
#include "util.h"

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

int main(int argc, char** argv)
{
    day1();

    return 0;
}
