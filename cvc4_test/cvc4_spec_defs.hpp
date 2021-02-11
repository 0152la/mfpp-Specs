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
        int_term vars[FV_COUNT];
    };

    static CVC4::api::Solver slv;
    static int_term output_var;
} // namespace fuzz

typedef fuzz::int_term OUT_VAR_TYPE;

#endif // _CVC4_SPEC_DEFS_HPP
