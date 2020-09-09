#ifndef _Z3_SPEC_DEFS_HPP
#define _Z3_SPEC_DEFS_HPP

#include "spec_fuzz.hpp"
#include "z3++.h"
#include <utility>

typedef std::pair<z3::expr, z3::expr> mr_pair;
typedef mr_pair OUT_VAR_TYPE;

namespace fuzz
{
    static z3::context ctx;
    static mr_pair output_var(ctx, ctx);
    mr_pair output_var_get(size_t);
} // namespace fuzz

#include "set_meta_tests_z3.hpp"

#endif // _Z3_SPEC_DEFS_HPP
