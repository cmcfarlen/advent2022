#include "util.h"

namespace day2 {
    enum class Move {
        Rock = 1,
        Paper,
        Scissor
    };

    enum class Outcome {
        Lose = 0,
        Draw = 3,
        Win = 6
    };

    int move_points(Move m) {
        return int(m);
    }

    Move lookup_move(char letter)
    {
        switch (letter)
        {
            case 'A':
            case 'X':
                return Move::Rock;
            case 'B':
            case 'Y':
                return Move::Paper;
            case 'C':
            case 'Z':
            default:
                return Move::Scissor;
        }
    }

    Outcome lookup_outcome(char letter)
    {
        switch (letter)
        {
            case 'X':
                return Outcome::Lose;
            case 'Y':
                return Outcome::Draw;
            case 'Z':
            default:
                return Outcome::Win;
        }
    }

    int outcome_points(Outcome o) {
        return int(o);
    }

    Move make_outcome(Move their_move, Outcome outcome)
    {
        switch (outcome) {
            case Outcome::Draw:
                return their_move;
            case Outcome::Win:
                switch (their_move) {
                    case Move::Rock:
                        return Move::Paper;
                    case Move::Paper:
                        return Move::Scissor;
                    case Move::Scissor:
                        return Move::Rock;
                }
                break;
            case Outcome::Lose:
                switch (their_move) {
                    case Move::Rock:
                        return Move::Scissor;
                    case Move::Paper:
                        return Move::Rock;
                    case Move::Scissor:
                        return Move::Paper;
                }
                break;
        }
    }

    Outcome outcome(Move my_move, Move their_move)
    {
        bool won = my_move == Move::Rock && their_move == Move::Scissor ||
                   my_move == Move::Paper && their_move == Move::Rock ||
                   my_move == Move::Scissor && their_move == Move::Paper;
        if (won) {
            return Outcome::Win;
        }

        bool draw = my_move == their_move;
        if (draw) {
            return Outcome::Draw;
        }
        return Outcome::Lose;
    }

    int round_score(Move their_move, Move my_move) {
        return move_points(my_move) + outcome_points(outcome(my_move, their_move));
    }

    int round_score(Move their_move, Outcome outcome) {
        Move my_move = make_outcome(their_move, outcome);

        return round_score(their_move, my_move);
    }
}

template<> struct fmt::formatter<day2::Move> {
    static constexpr auto parse(format_parse_context& ctx) -> decltype(ctx.begin()) {
        return ctx.begin();
    }

    template <typename FormatContext>
    auto format(const day2::Move& m, FormatContext& ctx) const -> decltype(ctx.out()) {
        switch (m) {
            case day2::Move::Rock:
                return fmt::format_to(ctx.out(), "{}", "ROCK");
            case day2::Move::Paper:
                return fmt::format_to(ctx.out(), "{}", "PAPER");
            case day2::Move::Scissor:
                return fmt::format_to(ctx.out(), "{}", "SCISSOR");
        }
        return fmt::format_to(ctx.out(), "{}", "WOW");
    }
};

template<> struct fmt::formatter<day2::Outcome> {
    static constexpr auto parse(format_parse_context& ctx) -> decltype(ctx.begin()) {
        return ctx.begin();
    }

    template <typename FormatContext>
    auto format(const day2::Outcome& m, FormatContext& ctx) const -> decltype(ctx.out()) {
        switch (m) {
            case day2::Outcome::Lose:
                return fmt::format_to(ctx.out(), "{}", "Lose");
            case day2::Outcome::Draw:
                return fmt::format_to(ctx.out(), "{}", "Draw");
            case day2::Outcome::Win:
                return fmt::format_to(ctx.out(), "{}", "Win");
        }
        return fmt::format_to(ctx.out(), "{}", "WOW");
    }
};



namespace day2 {

    /*
    std::tuple<Move,Move> to_move_tuple(ranges::random_access_range auto r)
    {
        return {lookup_move(r[0]), lookup_move(r[1])};
    }
     */

    std::tuple<Move,Outcome> to_move_tuple(auto r)
    {
        auto it = r.begin();

        return {lookup_move(*it++), lookup_outcome(*it++)};
    }

    void run()
    {
        auto f = std::ifstream("../input/day2.txt");
        if (f.bad()) {
            throw std::runtime_error("Failed to open");
        }

        auto data = ranges::getlines(f) | ranges::views::transform([=](const std::string& line) {
            return to_move_tuple(line
                                 | ranges::views::split(' ')
                                 | ranges::views::transform([](auto &&rng) { return *rng.begin(); }));
        }) | ranges::to_vector;

        int total_score = 0;
        for (auto& [a, b]: data) {
            fmt::print("data: {} {}\n", a, b);
            total_score += round_score(a, b);

        }

        fmt::print("Total score: {}\n", total_score);
    }
}


int main() {

    //auto v = slurp_lines("../test.txt");
    day2::run();
    return 0;
}
