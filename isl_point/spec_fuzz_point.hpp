#ifndef _SPEC_FUZZ_HPP
#define _SPEC_FUZZ_HPP

#ifndef TEST
#include "isl-noexceptions-point.h"
#include "set_meta_tests_isl.hpp"
#else
#include "isl-noexceptions.h"
#endif

#include <cassert>
#include <vector>

namespace fuzz
{
    namespace input
    {
        static int dims = 5;
        static int cons = 20;
    }

    static isl::set output_var;

    void start() {}
    void end()   {}

    template <class T> T fuzz_new();
    //isl::set fuzz_new(std::string type_name);
    template<typename T> T fuzz_rand(T min, T max);

    void meta_test() {}
}

#endif // _SPEC_FUZZ_HPP
