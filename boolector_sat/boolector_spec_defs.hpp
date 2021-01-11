#ifndef _BOOLECTOR_SPEC_DEFS_HPP
#define _BOOLECTOR_SPEC_DEFS_HPP

#include "spec_fuzz.hpp"
#include "boolector.h"

typedef std::pair<BoolectorNode*, BoolectorNode*> mr_pair;
typedef mr_pair OUT_VAR_TYPE;
typedef int32_t sat_stat;

namespace fuzz
{
    static mr_pair output_var;
    mr_pair output_var_get(size_t);
} // namespace fuzz

#include "set_meta_tests_boolector.hpp"

#endif // _BOOLECTOR_SPEC_DEFS_HPP


