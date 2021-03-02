#ifndef _Z3_SPEC_DEFS_HPP
#define _Z3_SPEC_DEFS_HPP

#include "spec_fuzz.hpp"

namespace fuzz
{
    typedef z3::expr bool_term;
    typedef z3::expr int_term;

    class FreeVars {
      public:
        std::vector<int_term> vars;
    };

    static z3::context ctx;
    static fuzz::int_term output_var(ctx);
} // namespace fuzz

#include "meta_spec_z3.hpp"
#include "smt_spec.hpp"

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

fuzz::int_term
make_ite_int_term(fuzz::bool_term cond, fuzz::int_term if_b, fuzz::int_term then_b)
{
    return z3::ite(cond, if_b, then_b);
}

/*******************************************************************************
 * bool_term API WRAPPERS
 ******************************************************************************/

fuzz::bool_term
make_bool_const(fuzz::fuzz_context& ctx)
{
    return ctx.ctx.bool_val(fuzz::fuzz_rand<int, int>(1, 2) % 2);
}

fuzz::bool_term
not_wrapper(fuzz::bool_term e)
{
    return z3::operator!(e);
}

fuzz::bool_term
and_wrapper(fuzz::bool_term e1, fuzz::bool_term e2)
{
    return z3::operator&&(e1, e2);
}

fuzz::bool_term
nand_wrapper(fuzz::bool_term e1, fuzz::bool_term e2)
{
    return z3::nand(e1, e2);
}

fuzz::bool_term
or_wrapper(fuzz::bool_term e1, fuzz::bool_term e2)
{
    return z3::operator||(e1, e2);
}

fuzz::bool_term
nor_wrapper(fuzz::bool_term e1, fuzz::bool_term e2)
{
    return z3::nor(e1, e2);
}

fuzz::bool_term
xor_wrapper(fuzz::bool_term e1, fuzz::bool_term e2)
{
    return z3::operator^(e1, e2);
}

fuzz::bool_term
implies_wrapper(fuzz::bool_term e1, fuzz::bool_term e2)
{
    return z3::implies(e1, e2);
}

fuzz::bool_term
lt_wrapper(fuzz::int_term const& e1, fuzz::int_term const& e2)
{
    return z3::operator<(e1, e2);
}

fuzz::bool_term
gt_wrapper(fuzz::int_term const& e1, fuzz::int_term const& e2)
{
    return z3::operator>(e1, e2);
}

fuzz::bool_term
lte_wrapper(fuzz::int_term const& e1, fuzz::int_term const& e2)
{
    return z3::operator<=(e1, e2);
}

fuzz::bool_term
gte_wrapper(fuzz::int_term const& e1, fuzz::int_term const& e2)
{
    return z3::operator>=(e1, e2);
}

fuzz::bool_term
eq_wrapper(fuzz::int_term const& e1, fuzz::int_term const& e2)
{
    return z3::operator==(e1, e2);
}

fuzz::bool_term
neq_wrapper(fuzz::int_term const& e1, fuzz::int_term const& e2)
{
    return z3::operator!=(e1, e2);
}

fuzz::bool_term
make_ite_bool_term(fuzz::bool_term cond, fuzz::bool_term const& then_e,
    fuzz::bool_term const& else_e)
{
    return z3::ite(cond, then_e, else_e);
}

} // namespace lib_helper_funcs
} // namespace fuzz

typedef fuzz::int_term OUT_VAR_TYPE;

#endif // _Z3_SPEC_DEFS_HPP
