#ifndef _CVC4_SPEC_DEFS_HPP
#define _CVC4_SPEC_DEFS_HPP

#include "spec_fuzz.hpp"
#include "cvc4cpp.h"
#include <utility>

typedef std::pair<CVC4::api::Term, CVC4::api::Term> mr_pair;
typedef std::pair<CVC4::api::Term, CVC4::api::Term> check_pair;
typedef mr_pair OUT_VAR_TYPE;

namespace fuzz
{
    static CVC4::api::Solver slv;
    static mr_pair output_var;
    mr_pair output_var_get(size_t);
} // namespace fuzz

#include "set_meta_tests_cvc4.hpp"

#endif // _CVC4_SPEC_DEFS_HPP
