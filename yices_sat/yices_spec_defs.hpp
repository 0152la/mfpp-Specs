#ifndef _YICES_SPEC_DEFS_HPP
#define _YICES_SPEC_DEFS_HPP

#include "spec_fuzz.hpp"
#include "yices.h"

typedef std::pair<term_t, term_t> mr_pair;
typedef mr_pair OUT_VAR_TYPE;

namespace fuzz
{
    static mr_pair output_var;
    mr_pair output_var_get(size_t);
} // namespace fuzz

#include "set_meta_tests_yices.hpp"

#endif // _YICES_SPEC_DEFS_HPP

