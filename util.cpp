#include "util.h"

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
