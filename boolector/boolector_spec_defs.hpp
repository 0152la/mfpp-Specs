#ifndef _BOOLECTOR_SPEC_DEFS_HPP
#define _BOOLECTOR_SPEC_DEFS_HPP

#include "spec_fuzz.hpp"
#include "boolector.h"

typedef BoolectorNode* OUT_VAR_TYPE;

namespace fuzz
{
    static BoolectorNode* output_var;
    BoolectorNode* output_var_get(size_t);
} // namespace fuzz

#include "set_meta_tests_boolector.hpp"

#endif // _BOOLECTOR_SPEC_DEFS_HPP


