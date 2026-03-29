#pragma once

/**
 * termcolor.hpp — ANSI terminal color & style library for C++
 * Part of the REX package registry.
 *
 * Usage:
 *   #include "termcolor.hpp"
 *   using namespace termcolor;
 *
 *   std::cout << fg::red << "Error!" << reset << std::endl;
 *   std::cout << bg::blue << fg::white << bold << "Hello!" << reset << std::endl;
 *   std::cout << color("Hello!", fg::green) << std::endl;
 */

#include <ostream>
#include <string>

namespace termcolor {

// ─── ANSI escape helpers ────────────────────────────────────────────────────

namespace detail {
    inline std::ostream& ansi(std::ostream& os, const char* code) {
        return os << "\033[" << code << "m";
    }
}

// ─── Reset ──────────────────────────────────────────────────────────────────

inline std::ostream& reset(std::ostream& os)     { return detail::ansi(os, "0");  }

// ─── Text styles ────────────────────────────────────────────────────────────

inline std::ostream& bold(std::ostream& os)      { return detail::ansi(os, "1");  }
inline std::ostream& dim(std::ostream& os)       { return detail::ansi(os, "2");  }
inline std::ostream& italic(std::ostream& os)    { return detail::ansi(os, "3");  }
inline std::ostream& underline(std::ostream& os) { return detail::ansi(os, "4");  }
inline std::ostream& blink(std::ostream& os)     { return detail::ansi(os, "5");  }
inline std::ostream& reverse(std::ostream& os)   { return detail::ansi(os, "7");  }
inline std::ostream& strikethrough(std::ostream& os) { return detail::ansi(os, "9"); }

// ─── Foreground colors ──────────────────────────────────────────────────────

namespace fg {
    inline std::ostream& black  (std::ostream& os) { return detail::ansi(os, "30"); }
    inline std::ostream& red    (std::ostream& os) { return detail::ansi(os, "31"); }
    inline std::ostream& green  (std::ostream& os) { return detail::ansi(os, "32"); }
    inline std::ostream& yellow (std::ostream& os) { return detail::ansi(os, "33"); }
    inline std::ostream& blue   (std::ostream& os) { return detail::ansi(os, "34"); }
    inline std::ostream& magenta(std::ostream& os) { return detail::ansi(os, "35"); }
    inline std::ostream& cyan   (std::ostream& os) { return detail::ansi(os, "36"); }
    inline std::ostream& white  (std::ostream& os) { return detail::ansi(os, "37"); }

    // Bright variants
    inline std::ostream& bright_black  (std::ostream& os) { return detail::ansi(os, "90"); }
    inline std::ostream& bright_red    (std::ostream& os) { return detail::ansi(os, "91"); }
    inline std::ostream& bright_green  (std::ostream& os) { return detail::ansi(os, "92"); }
    inline std::ostream& bright_yellow (std::ostream& os) { return detail::ansi(os, "93"); }
    inline std::ostream& bright_blue   (std::ostream& os) { return detail::ansi(os, "94"); }
    inline std::ostream& bright_magenta(std::ostream& os) { return detail::ansi(os, "95"); }
    inline std::ostream& bright_cyan   (std::ostream& os) { return detail::ansi(os, "96"); }
    inline std::ostream& bright_white  (std::ostream& os) { return detail::ansi(os, "97"); }

    // True-color (RGB) — requires terminal support
    struct rgb {
        int r, g, b;
        rgb(int r, int g, int b) : r(r), g(g), b(b) {}
        friend std::ostream& operator<<(std::ostream& os, const rgb& c) {
            return os << "\033[38;2;" << c.r << ";" << c.g << ";" << c.b << "m";
        }
    };

    // 256-color palette index
    struct color256 {
        int index;
        explicit color256(int index) : index(index) {}
        friend std::ostream& operator<<(std::ostream& os, const color256& c) {
            return os << "\033[38;5;" << c.index << "m";
        }
    };
}

// ─── Background colors ──────────────────────────────────────────────────────

namespace bg {
    inline std::ostream& black  (std::ostream& os) { return detail::ansi(os, "40"); }
    inline std::ostream& red    (std::ostream& os) { return detail::ansi(os, "41"); }
    inline std::ostream& green  (std::ostream& os) { return detail::ansi(os, "42"); }
    inline std::ostream& yellow (std::ostream& os) { return detail::ansi(os, "43"); }
    inline std::ostream& blue   (std::ostream& os) { return detail::ansi(os, "44"); }
    inline std::ostream& magenta(std::ostream& os) { return detail::ansi(os, "45"); }
    inline std::ostream& cyan   (std::ostream& os) { return detail::ansi(os, "46"); }
    inline std::ostream& white  (std::ostream& os) { return detail::ansi(os, "47"); }

    // Bright variants
    inline std::ostream& bright_black  (std::ostream& os) { return detail::ansi(os, "100"); }
    inline std::ostream& bright_red    (std::ostream& os) { return detail::ansi(os, "101"); }
    inline std::ostream& bright_green  (std::ostream& os) { return detail::ansi(os, "102"); }
    inline std::ostream& bright_yellow (std::ostream& os) { return detail::ansi(os, "103"); }
    inline std::ostream& bright_blue   (std::ostream& os) { return detail::ansi(os, "104"); }
    inline std::ostream& bright_magenta(std::ostream& os) { return detail::ansi(os, "105"); }
    inline std::ostream& bright_cyan   (std::ostream& os) { return detail::ansi(os, "106"); }
    inline std::ostream& bright_white  (std::ostream& os) { return detail::ansi(os, "107"); }

    // True-color (RGB) background
    struct rgb {
        int r, g, b;
        rgb(int r, int g, int b) : r(r), g(g), b(b) {}
        friend std::ostream& operator<<(std::ostream& os, const rgb& c) {
            return os << "\033[48;2;" << c.r << ";" << c.g << ";" << c.b << "m";
        }
    };

    // 256-color palette background
    struct color256 {
        int index;
        explicit color256(int index) : index(index) {}
        friend std::ostream& operator<<(std::ostream& os, const color256& c) {
            return os << "\033[48;5;" << c.index << "m";
        }
    };
}

// ─── Utility: wrap a string with a color and auto-reset ─────────────────────

using ColorFn = std::ostream& (*)(std::ostream&);

/**
 * Wraps text with a foreground color and resets after.
 *
 * Example:
 *   std::cout << termcolor::colored("Error!", termcolor::fg::red) << "\n";
 */
inline std::string colored(const std::string& text, ColorFn color_fn);

/**
 * Wraps text with fg + bg color and resets after.
 */
inline std::string colored(const std::string& text, ColorFn fg_fn, ColorFn bg_fn);

/**
 * Wraps text with a color + style and resets after.
 */
inline std::string styled(const std::string& text, ColorFn color_fn, ColorFn style_fn);

// ─── Predefined convenience printers ────────────────────────────────────────

/**
 * Print helpers — print text in a named color and reset.
 * All functions append a newline by default.
 *
 * Example:
 *   termcolor::print_error("Something went wrong.");
 *   termcolor::print_success("Operation complete.");
 */
void print_error  (const std::string& msg, bool newline = true);
void print_success(const std::string& msg, bool newline = true);
void print_warning(const std::string& msg, bool newline = true);
void print_info   (const std::string& msg, bool newline = true);

} // namespace termcolor

// ─── Include inline implementation ──────────────────────────────────────────
#include "../src/termcolor.cpp"
