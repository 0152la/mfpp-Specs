#ifndef _SPEC_FUZZ_HPP
#define _SPEC_FUZZ_HPP

#include "cvc4cpp.h"

#include <cassert>
#include <vector>

namespace fuzz
{
    namespace input
    {
        static int dims = 5;
        static int cons = 20;
    }

    static CVC4::api::Solver slv;
    static CVC4::api::Term output_var;

    void start() {}
    void end()   {}

    template <class T> T fuzz_new();
    template<typename T> T fuzz_rand(T min, T max);

    void meta_test() {}
}

#ifndef EXECUTE
#include "set_meta_tests_cvc4.hpp"
#endif

#endif // _SPEC_FUZZ_HPP
