#ifndef _CAIRO_SPEC_AST_HPP
#define _CAIRO_SPEC_AST_HPP

#include "cairomm/cairomm.h"

namespace fuzz
{
    static Cairo::RefPtr<Cairo::Context> output_var;

    void start() {};
    void end()   {};

    template <class T> T fuzz_new();
    template <class T> T fuzz_rand(T min, T max);

    void meta_test() {};
    template<typename T> T fuzz_rand(T min, T max);
}

#endif // _CAIRO_SPEC_AST_HPP
