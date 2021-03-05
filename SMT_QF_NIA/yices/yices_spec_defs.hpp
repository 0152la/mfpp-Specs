#ifndef _YICES_SPEC_DEFS_HPP
#define _YICES_SPEC_DEFS_HPP

#include "spec_fuzz.hpp"
#include "yices.h"

typedef term_t OUT_VAR_TYPE;

namespace fuzz
{
    class FreeVars {
        public:
            fuzz::int_term vars[FV_COUNT];
    };
    static term_t output_var;
    term_t output_var_get(size_t);
}

#include "meta_spec_yices.hpp"
#include "smt_spec.hpp"

namespace fuzz {

namespace lib_helper_funcs {

/*******************************************************************************
 * CONSTRUCTORS
 ******************************************************************************/

fuzz::int_term
ctor_yield_free_var(fuzz::fuzz_context& fctx)
{
    return fctx.fvs.vars[fuzz::fuzz_rand<int, int>(0, 99)];
}

fuzz::int_term
ctor_expr(int n)
{
    return yices_int32(n);
}

fuzz::bool_term
ctor_bool()
{
    size_t rand_bool = fuzz::fuzz_rand<int>(1, 2);
    return rand_bool % 2 ? yices_true() : yices_false();
}

/*******************************************************************************
 * LIBRARY OPERATIONS WRAPPERS
 ******************************************************************************/

fuzz::int_term
yices_power_wrapper(fuzz::int_term t, unsigned int i)
{
    return yices_power(t, i % 32);
}

} // namespace lib_helper_funcs
} // namespace fuzz


#endif // _YICES_SPEC_DEFS_HPP

