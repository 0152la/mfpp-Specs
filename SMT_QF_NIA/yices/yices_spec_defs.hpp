#ifndef _YICES_SPEC_DEFS_HPP
#define _YICES_SPEC_DEFS_HPP

#include "yices_mfpp.h"

typedef term_t OUT_VAR_TYPE;

#include "yices_fuzz_type_defs.hpp"
#include "meta_spec_yices.hpp"
#include "spec.hpp"

namespace fuzz {

static term_t output_var;
term_t output_var_get(size_t);

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

//fuzz::int_term
//yices_division_wrapper(fuzz::int_term t1, fuzz::int_term t2)
//{
    //return yices_ite(yices_eq(t2, yices_zero()), t1, yices_division(t1, t2));
//}

fuzz::int_term
yices_idiv_wrapper(fuzz::int_term t1, fuzz::int_term t2)
{
    return yices_ite(yices_eq(t2, yices_zero()), t1, yices_idiv(t1, t2));
}

fuzz::int_term
yices_imod_wrapper(fuzz::int_term t1, fuzz::int_term t2)
{
    return yices_ite(yices_eq(t2, yices_zero()), t1, yices_imod(t1, t2));
}

} // namespace lib_helper_funcs
} // namespace fuzz


#endif // _YICES_SPEC_DEFS_HPP

