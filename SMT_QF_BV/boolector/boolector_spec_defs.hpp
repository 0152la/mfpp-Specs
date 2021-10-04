#ifndef _BOOLECTOR_SPEC_DEFS_HPP
#define _BOOLECTOR_SPEC_DEFS_HPP

#include "boolector_mfpp.h"

typedef BoolectorNode* OUT_VAR_TYPE;

#include "meta_spec_boolector.hpp"
#include "set_meta_tests_boolector.hpp"

namespace fuzz
{
    static BoolectorNode* output_var;
    BoolectorNode* output_var_get(size_t);
} // namespace fuzz

namespace lib_helper_funcs {

} // namespace lib_helper_funcs

#endif // _BOOLECTOR_SPEC_DEFS_HPP


