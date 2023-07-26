#pragma once

#include <fstream>
#include <string>
#include <algorithm>
#include <optional>
#include <set>
#include <vector>

#include "fmt/core.h"
#include "range/v3/all.hpp"

std::ifstream open(const std::string& path);
std::vector<std::string> lines(const std::string& path);
int to_int(const std::string& s);

template<typename T> struct fmt::formatter<std::set<T>> {
    static constexpr auto parse(format_parse_context& ctx) -> decltype(ctx.begin()) {
        return ctx.begin();
    }

    template <typename FormatContext>
    auto format(const std::set<T>& m, FormatContext& ctx) const -> decltype(ctx.out()) {
        auto it = ctx.out();
        it = fmt::format_to(it, "[");
        for (const auto& v: m) {
            it =  fmt::format_to(it, "{} ", v);
        }
        it = fmt::format_to(it, "]");
        return it;
    }
};

template<typename A, typename B> struct fmt::formatter<std::pair<A,B>> {
    static constexpr auto parse(format_parse_context& ctx) -> decltype(ctx.begin()) {
        return ctx.begin();
    }

    template <typename FormatContext>
    auto format(const std::pair<A,B>& m, FormatContext& ctx) const -> decltype(ctx.out()) {
        return fmt::format_to(ctx.out(), "[{},{}]", m.first, m.second);
    }
};
