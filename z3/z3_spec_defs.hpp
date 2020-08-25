#ifndef _Z3_SPEC_DEFS_HPP
#define _Z3_SPEC_DEFS_HPP

#include "spec_fuzz.hpp"
#include "z3++.h"

typedef z3::expr OUT_VAR_TYPE;

namespace fuzz
{
    static z3::context ctx;
    static z3::expr output_var(ctx);
} // namespace fuzz

#include "set_meta_tests_z3.hpp"

#endif // _Z3_SPEC_DEFS_HPP
