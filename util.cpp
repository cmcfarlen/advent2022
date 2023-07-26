#include "util.h"

std::ifstream open(const std::string& path)
{
    std::ifstream result(path);
    if (result.is_open()) {
        return result;
    }
    throw std::runtime_error(fmt::format("failed to open file: {}", path));
}

std::vector<std::string> lines(const std::string& path)
{
    auto f = open(path);
    if (f) {
        return ranges::getlines(f) | ranges::to_vector;
    }
    return {};
}

int to_int(const std::string& s)
{
    return std::stoi(s);
}
