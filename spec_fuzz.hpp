#ifndef _SPEC_FUZZ_HPP
#define _SPEC_FUZZ_HPP

#include <cassert>
#include <string>

namespace fuzz
{
    void start() {}
    void end()   {}

    void mfr_fuzz_start(std::string s) {};
    void mfr_fuzz_end(std::string s) {};

    template <class T> T fuzz_new();
    template<typename T, typename U> T fuzz_rand(U min, U max);

    void meta_test() {}
}

#endif // _SPEC_FUZZ_HPP
