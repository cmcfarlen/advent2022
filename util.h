#pragma once

#include <fstream>
#include <string>
#include <algorithm>
#include <optional>

#include "fmt/core.h"
#include "range/v3/all.hpp"

std::optional<std::ifstream> open(const std::string& path);
int to_int(const std::string& s);
