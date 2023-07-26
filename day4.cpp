#include "util.h"

int main(int argc, char** argv)
{
    auto input = lines("../input/day4-example.txt");
    /*
    auto to_pair = [](auto&& p) {
        auto it = p.begin();
        //return std::make_pair(*it++, *it);
        return std::make_pair("a", "b");
    };
    auto parse_pair = [to_pair](const std::string& p) {
        //return to_pair(p | ranges::views::split('-') | ranges::views::transform(to_int));
        //return p | ranges::views::split('-') | ranges::views::transform([](auto& r) {
        //    return true;
        //});
        return true;
    };
            */

    auto answer = input | ranges::views::split(',');
    /*
            ranges::views::transform([](const auto&& line) {
                fmt::print("parsing: {}\n", line);
                //return to_pair(line | ranges::views::split(','));
                return std::make_pair("a", "b");
            });
            */

    for (const auto& o: answer){
        fmt::print("{}\n", o);
    }

    return 0;
}
