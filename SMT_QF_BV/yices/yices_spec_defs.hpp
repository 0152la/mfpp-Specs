#ifndef _YICES_SPEC_DEFS_HPP
#define _YICES_SPEC_DEFS_HPP

#include "spec_fuzz.hpp"
#include "yices.h"

typedef term_t OUT_VAR_TYPE;

namespace fuzz
{
    class FreeVars {
        public:
            int_term vars[FV_COUNT];
    };

    static term_t output_var;
    term_t output_var_get(size_t);

namespace lib_helper_funcs {

/*******************************************************************************
 * CONSTRUCTORS
 ******************************************************************************/

bv_term
ctor_yield_free_var(fuzz::FreeVars& fvs)
{
    return fvs.vars[fuzz::fuzz_rand<int, int>(0, 99)];
}

bv_term
ctor_expr(int n)
{
    return yices_bvconst_uint32(BV_SIZE, n);
}

bool_term
ctor_bool()
{
    size_t rand_bool = fuzz::fuzz_rand<int>(1, 2);
    return rand_bool % 2 ? yices_true() : yices_false();
}

/*******************************************************************************
 * LIBRARY OPERATIONS WRAPPERS
 ******************************************************************************/

bv_term
rotate_left_wrapper(bv_term t, unsigned int n)
{
    return yices_rotate_left(t, n % (BV_SIZE + 1));
}

bv_term
rotate_right_wrapper(bv_term t, unsigned int n)
{
    return yices_rotate_right(t, n % (BV_SIZE + 1));
}

/*******************************************************************************
 * bv_term API WRAPPERS
 ******************************************************************************/

bv_term
ite_lt_wrapper(bv_term cond1, bv_term cond2, bv_term then_e, bv_term else_e)
{
    return yices_ite(yices_bvlt_atom(cond1, cond2), then_e, else_e);
}

bv_term
ite_gte_wrapper(bv_term cond1, bv_term cond2, bv_term then_e, bv_term else_e)
{
    return yices_ite(yices_bvge_atom(cond1, cond2), then_e, else_e);
}


} // namespace lib_helper_funcs
} // namespace fuzz

#include "meta_spec_yices.hpp"
#include "smt_spec.hpp"

#endif // _YICES_SPEC_DEFS_HPP

