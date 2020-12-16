#ifndef _YICES_SPEC_DEFS_HPP
#define _YICES_SPEC_DEFS_HPP

#include "spec_fuzz.hpp"
#include "yices.h"

typedef term_t OUT_VAR_TYPE;

namespace fuzz
{
    static term_t output_var;
    term_t output_var_get(size_t);
} // namespace fuzz

#include "set_meta_tests_yices.hpp"

#endif // _YICES_SPEC_DEFS_HPP

