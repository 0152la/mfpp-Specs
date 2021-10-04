#ifndef _YICES_SPEC_DEFS_HPP
#define _YICES_SPEC_DEFS_HPP

#include "yices_mfpp.h"

typedef term_t OUT_VAR_TYPE;

#include "yices_fuzz_type_defs.hpp"
#include "meta_spec_yices.hpp"
#include "spec.hpp"

namespace fuzz
{
static term_t output_var;
term_t output_var_get(size_t);

namespace lib_helper_funcs {

/*******************************************************************************
 * CONSTRUCTORS
 ******************************************************************************/

fuzz::bv_term
ctor_yield_free_var(fuzz::fuzz_context& fctx)
{
    return fctx.fvs.vars[fuzz::fuzz_rand<int, int>(0, 99)];
}

fuzz::bv_term
ctor_expr(int n)
{
    return yices_bvconst_uint32(BV_SIZE, n);
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

fuzz::bv_term
rotate_left_wrapper(bv_term t, unsigned int n)
{
    return yices_rotate_left(t, n % (BV_SIZE + 1));
}

fuzz::bv_term
rotate_right_wrapper(bv_term t, unsigned int n)
{
    return yices_rotate_right(t, n % (BV_SIZE + 1));
}

/*******************************************************************************
 * bv_term API WRAPPERS
 ******************************************************************************/

fuzz::bv_term
ite_lt_wrapper(bv_term cond1, bv_term cond2, bv_term then_e, bv_term else_e)
{
    return yices_ite(yices_bvlt_atom(cond1, cond2), then_e, else_e);
}

fuzz::bv_term
ite_gte_wrapper(bv_term cond1, bv_term cond2, bv_term then_e, bv_term else_e)
{
    return yices_ite(yices_bvge_atom(cond1, cond2), then_e, else_e);
}


} // namespace lib_helper_funcs
} // namespace fuzz

#endif // _YICES_SPEC_DEFS_HPP
