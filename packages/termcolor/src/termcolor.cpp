/**
 * termcolor.cpp — Implementation of termcolor utilities.
 * Included directly by termcolor.hpp (header-only pattern).
 */

// Guard against direct inclusion outside of the header
#ifndef TERMCOLOR_IMPL
#define TERMCOLOR_IMPL

#include <iostream>
#include <sstream>

namespace termcolor {

// ─── colored() — wrap string with one color ─────────────────────────────────

inline std::string colored(const std::string& text, ColorFn color_fn) {
    std::ostringstream oss;
    color_fn(oss);
    oss << text;
    reset(oss);
    return oss.str();
}

// ─── colored() — wrap string with fg + bg color ─────────────────────────────

inline std::string colored(const std::string& text, ColorFn fg_fn, ColorFn bg_fn) {
    std::ostringstream oss;
    fg_fn(oss);
    bg_fn(oss);
    oss << text;
    reset(oss);
    return oss.str();
}

// ─── styled() — wrap string with color + text style ─────────────────────────

inline std::string styled(const std::string& text, ColorFn color_fn, ColorFn style_fn) {
    std::ostringstream oss;
    color_fn(oss);
    style_fn(oss);
    oss << text;
    reset(oss);
    return oss.str();
}

// ─── Convenience print helpers ───────────────────────────────────────────────

inline void print_error(const std::string& msg, bool newline) {
    std::cout << fg::bright_red << bold << "[ERROR] " << reset
              << fg::red << msg << reset;
    if (newline) std::cout << "\n";
}

inline void print_success(const std::string& msg, bool newline) {
    std::cout << fg::bright_green << bold << "[OK] " << reset
              << fg::green << msg << reset;
    if (newline) std::cout << "\n";
}

inline void print_warning(const std::string& msg, bool newline) {
    std::cout << fg::bright_yellow << bold << "[WARN] " << reset
              << fg::yellow << msg << reset;
    if (newline) std::cout << "\n";
}

inline void print_info(const std::string& msg, bool newline) {
    std::cout << fg::bright_cyan << bold << "[INFO] " << reset
              << fg::cyan << msg << reset;
    if (newline) std::cout << "\n";
}

} // namespace termcolor

#endif // TERMCOLOR_IMPL
