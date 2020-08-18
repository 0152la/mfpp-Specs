#ifndef _SPEC_FUZZ_HPP
#define _SPEC_FUZZ_HPP

#include "z3++.h"

#include <cassert>
#include <vector>
//#include "testing/isl-point-gen-helpers.h"

namespace fuzz
{
    namespace input
    {
        static int dims = 5;
        static int cons = 20;
    }

    static z3::context ctx;
    static z3::expr output_var(ctx);

    void start() {}
    void end()   {}

    template <class T> T fuzz_new();
    template<typename T, typename U> T fuzz_rand(U min, U max);

    void meta_test() {}
}

#ifndef EXECUTE
#include "set_meta_tests_z3_obf.hpp"
#endif

#endif // _SPEC_FUZZ_HPP
