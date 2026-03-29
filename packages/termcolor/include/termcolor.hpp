#pragma once

/**
 * termcolor.hpp — Biblioteca ANSI de cores e estilos para terminal C++
 * Versão single-header: basta copiar este arquivo para o seu projeto.
 *
 * Uso:
 *   #include "termcolor.hpp"
 *   using namespace termcolor;
 *
 *   std::cout << fg::red << "Erro!" << reset << "\n";
 *   std::cout << bg::blue << fg::white << bold << "Olá!" << reset << "\n";
 */

#include <iostream>
#include <sstream>
#include <string>

namespace termcolor {

// ─── Helper interno ──────────────────────────────────────────────────────────

namespace detail {
    inline std::ostream& ansi(std::ostream& os, const char* code) {
        return os << "\033[" << code << "m";
    }
}

// ─── Reset ───────────────────────────────────────────────────────────────────

inline std::ostream& reset        (std::ostream& os) { return detail::ansi(os, "0"); }

// ─── Estilos de texto ────────────────────────────────────────────────────────

inline std::ostream& bold         (std::ostream& os) { return detail::ansi(os, "1"); }
inline std::ostream& dim          (std::ostream& os) { return detail::ansi(os, "2"); }
inline std::ostream& italic       (std::ostream& os) { return detail::ansi(os, "3"); }
inline std::ostream& underline    (std::ostream& os) { return detail::ansi(os, "4"); }
inline std::ostream& blink        (std::ostream& os) { return detail::ansi(os, "5"); }
inline std::ostream& reverse      (std::ostream& os) { return detail::ansi(os, "7"); }
inline std::ostream& strikethrough(std::ostream& os) { return detail::ansi(os, "9"); }

// ─── Cores de texto (Foreground) ─────────────────────────────────────────────

namespace fg {
    inline std::ostream& black          (std::ostream& os) { return detail::ansi(os, "30");  }
    inline std::ostream& red            (std::ostream& os) { return detail::ansi(os, "31");  }
    inline std::ostream& green          (std::ostream& os) { return detail::ansi(os, "32");  }
    inline std::ostream& yellow         (std::ostream& os) { return detail::ansi(os, "33");  }
    inline std::ostream& blue           (std::ostream& os) { return detail::ansi(os, "34");  }
    inline std::ostream& magenta        (std::ostream& os) { return detail::ansi(os, "35");  }
    inline std::ostream& cyan           (std::ostream& os) { return detail::ansi(os, "36");  }
    inline std::ostream& white          (std::ostream& os) { return detail::ansi(os, "37");  }

    inline std::ostream& bright_black   (std::ostream& os) { return detail::ansi(os, "90");  }
    inline std::ostream& bright_red     (std::ostream& os) { return detail::ansi(os, "91");  }
    inline std::ostream& bright_green   (std::ostream& os) { return detail::ansi(os, "92");  }
    inline std::ostream& bright_yellow  (std::ostream& os) { return detail::ansi(os, "93");  }
    inline std::ostream& bright_blue    (std::ostream& os) { return detail::ansi(os, "94");  }
    inline std::ostream& bright_magenta (std::ostream& os) { return detail::ansi(os, "95");  }
    inline std::ostream& bright_cyan    (std::ostream& os) { return detail::ansi(os, "96");  }
    inline std::ostream& bright_white   (std::ostream& os) { return detail::ansi(os, "97");  }

    // True Color RGB
    struct rgb {
        int r, g, b;
        rgb(int r, int g, int b) : r(r), g(g), b(b) {}
        friend std::ostream& operator<<(std::ostream& os, const rgb& c) {
            return os << "\033[38;2;" << c.r << ";" << c.g << ";" << c.b << "m";
        }
    };

    // Paleta de 256 cores
    struct color256 {
        int index;
        explicit color256(int i) : index(i) {}
        friend std::ostream& operator<<(std::ostream& os, const color256& c) {
            return os << "\033[38;5;" << c.index << "m";
        }
    };
}

// ─── Cores de fundo (Background) ─────────────────────────────────────────────

namespace bg {
    inline std::ostream& black          (std::ostream& os) { return detail::ansi(os, "40");  }
    inline std::ostream& red            (std::ostream& os) { return detail::ansi(os, "41");  }
    inline std::ostream& green          (std::ostream& os) { return detail::ansi(os, "42");  }
    inline std::ostream& yellow         (std::ostream& os) { return detail::ansi(os, "43");  }
    inline std::ostream& blue           (std::ostream& os) { return detail::ansi(os, "44");  }
    inline std::ostream& magenta        (std::ostream& os) { return detail::ansi(os, "45");  }
    inline std::ostream& cyan           (std::ostream& os) { return detail::ansi(os, "46");  }
    inline std::ostream& white          (std::ostream& os) { return detail::ansi(os, "47");  }

    inline std::ostream& bright_black   (std::ostream& os) { return detail::ansi(os, "100"); }
    inline std::ostream& bright_red     (std::ostream& os) { return detail::ansi(os, "101"); }
    inline std::ostream& bright_green   (std::ostream& os) { return detail::ansi(os, "102"); }
    inline std::ostream& bright_yellow  (std::ostream& os) { return detail::ansi(os, "103"); }
    inline std::ostream& bright_blue    (std::ostream& os) { return detail::ansi(os, "104"); }
    inline std::ostream& bright_magenta (std::ostream& os) { return detail::ansi(os, "105"); }
    inline std::ostream& bright_cyan    (std::ostream& os) { return detail::ansi(os, "106"); }
    inline std::ostream& bright_white   (std::ostream& os) { return detail::ansi(os, "107"); }

    // True Color RGB
    struct rgb {
        int r, g, b;
        rgb(int r, int g, int b) : r(r), g(g), b(b) {}
        friend std::ostream& operator<<(std::ostream& os, const rgb& c) {
            return os << "\033[48;2;" << c.r << ";" << c.g << ";" << c.b << "m";
        }
    };

    // Paleta de 256 cores
    struct color256 {
        int index;
        explicit color256(int i) : index(i) {}
        friend std::ostream& operator<<(std::ostream& os, const color256& c) {
            return os << "\033[48;5;" << c.index << "m";
        }
    };
}

// ─── Utilitários ─────────────────────────────────────────────────────────────

using ColorFn = std::ostream& (*)(std::ostream&);

// Retorna string colorida com reset automático
inline std::string colored(const std::string& text, ColorFn color_fn) {
    std::ostringstream oss;
    color_fn(oss);
    oss << text;
    reset(oss);
    return oss.str();
}

// Retorna string com fg + bg e reset automático
inline std::string colored(const std::string& text, ColorFn fg_fn, ColorFn bg_fn) {
    std::ostringstream oss;
    fg_fn(oss);
    bg_fn(oss);
    oss << text;
    reset(oss);
    return oss.str();
}

// Retorna string com cor + estilo e reset automático
inline std::string styled(const std::string& text, ColorFn color_fn, ColorFn style_fn) {
    std::ostringstream oss;
    color_fn(oss);
    style_fn(oss);
    oss << text;
    reset(oss);
    return oss.str();
}

// ─── Helpers de print prontos ─────────────────────────────────────────────────

inline void print_error  (const std::string& msg, bool newline = true) {
    std::cout << fg::bright_red << bold << "[ERRO] " << reset
              << fg::red        << msg  << reset;
    if (newline) std::cout << "\n";
}

inline void print_success(const std::string& msg, bool newline = true) {
    std::cout << fg::bright_green << bold << "[OK] " << reset
              << fg::green        << msg  << reset;
    if (newline) std::cout << "\n";
}

inline void print_warning(const std::string& msg, bool newline = true) {
    std::cout << fg::bright_yellow << bold << "[AVISO] " << reset
              << fg::yellow        << msg  << reset;
    if (newline) std::cout << "\n";
}

inline void print_info   (const std::string& msg, bool newline = true) {
    std::cout << fg::bright_cyan << bold << "[INFO] " << reset
              << fg::cyan        << msg  << reset;
    if (newline) std::cout << "\n";
}

} // namespace termcolor