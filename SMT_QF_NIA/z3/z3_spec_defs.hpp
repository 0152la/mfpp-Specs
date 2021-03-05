#ifndef _Z3_SPEC_DEFS_HPP
#define _Z3_SPEC_DEFS_HPP

#include "z3++.h"
#include "z3_fuzz_type_defs.hpp"

namespace fuzz
{
    static z3::context ctx;
    static fuzz::int_term output_var(ctx);
} // namespace fuzz

#include "meta_spec_z3.hpp"
#include "spec.hpp"

namespace fuzz {
namespace lib_helper_funcs {

/*******************************************************************************
 * CONSTRUCTORS
 ******************************************************************************/

fuzz::int_term
ctor_expr(int n, fuzz::fuzz_context& ctx)
{
    return ctx.ctx.int_val(n);
}

fuzz::int_term
ctor_yield_free_var(fuzz::fuzz_context& ctx)
{
    return ctx.fvs.vars.at(fuzz::fuzz_rand<int, int>(0, FV_COUNT - 1));
}

/*******************************************************************************
 * LIBRARY OPERATIONS WRAPPERS
 ******************************************************************************/

fuzz::int_term
div_wrapper(fuzz::int_term const& e1, fuzz::int_term const& e2)
{
    return z3::ite(e2 != 0, e1 / e2, e1);
}

fuzz::int_term
mod_wrapper(fuzz::int_term const& e1, fuzz::int_term const& e2)
{
    return z3::ite(e2 != 0, z3::mod(e1, e2), e1);
}

fuzz::int_term
rem_wrapper(fuzz::int_term const& e1, fuzz::int_term const& e2)
{
    return z3::ite(e2 != 0, z3::rem(e1, e2), e1);
}

fuzz::int_term
pw_wrapper(fuzz::int_term const& e1, fuzz::int_term const& e2)
{
    return z3::ite(e1 != 0 && e2 != 0, e1.ctx().int_val(z3::pw(e1, e2)), e1);
}

/*******************************************************************************
 * int_term API WRAPPERS
 ******************************************************************************/

/*******************************************************************************
 * bool_term API WRAPPERS
 ******************************************************************************/

fuzz::bool_term
make_bool_const(fuzz::fuzz_context& ctx)
{
    return ctx.ctx.bool_val(fuzz::fuzz_rand<int, int>(1, 2) % 2);
}

} // namespace lib_helper_funcs
} // namespace fuzz

typedef fuzz::int_term OUT_VAR_TYPE;

#endif // _Z3_SPEC_DEFS_HPP
