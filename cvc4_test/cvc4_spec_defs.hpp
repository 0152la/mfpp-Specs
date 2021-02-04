#ifndef _CVC4_SPEC_DEFS_HPP
#define _CVC4_SPEC_DEFS_HPP

#include "spec_fuzz.hpp"
#include "cvc4cpp.h"

//typedef struct FreeVars { CVC4::api::Term* vars[FV_COUNT]; } FreeVars;
typedef CVC4::api::Term OUT_VAR_TYPE;

namespace fuzz
{
    class FreeVars {
      public:
        CVC4::api::Term* vars[FV_COUNT];
    };

    static CVC4::api::Solver slv;
    static CVC4::api::Term output_var;
} // namespace fuzz

#include "set_meta_tests_cvc4.hpp"

#endif // _CVC4_SPEC_DEFS_HPP
