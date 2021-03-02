#ifndef _CVC4_SPEC_DEFS_HPP
#define _CVC4_SPEC_DEFS_HPP

#include "spec_fuzz.hpp"
#include "cvc4cpp.h"

//typedef struct FreeVars { CVC4::api::Term* vars[FV_COUNT]; } FreeVars;

namespace fuzz
{
    typedef CVC4::api::Term bool_term;
    typedef CVC4::api::Term int_term;
    class FreeVars {
      public:
        fuzz::int_term vars[FV_COUNT];
    };

    static CVC4::api::Solver slv;
    static int_term output_var;
} // namespace fuzz

typedef fuzz::int_term OUT_VAR_TYPE;

#include "meta_spec_cvc4_nl.hpp"
#include "smt_spec.hpp"
//#include "set_meta_tests_cvc4.hpp"

#endif // _CVC4_SPEC_DEFS_HPP
