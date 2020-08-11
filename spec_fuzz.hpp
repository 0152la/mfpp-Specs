#ifndef _SPEC_FUZZ_HPP
#define _SPEC_FUZZ_HPP

#include <cassert>
#include <vector>

namespace fuzz
{
    //static OUT_VAR_TYPE output_var;

    void start() {}
    void end()   {}

    template <class T> T fuzz_new();
    template<typename T, typename U> T fuzz_rand(U min, U max);

    void meta_test() {}
}

#endif // _SPEC_FUZZ_HPP
