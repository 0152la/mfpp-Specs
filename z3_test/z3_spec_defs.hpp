#ifndef _Z3_SPEC_DEFS_HPP
#define _Z3_SPEC_DEFS_HPP

#include "spec_fuzz.hpp"

namespace fuzz
{
    typedef z3::expr bool_expr;
    typedef z3::expr int_expr;

    class FreeVars {
      public:
        std::vector<int_expr> vars;
    };

    static z3::context ctx;
    static fuzz::int_expr output_var(ctx);

namespace lib_helper_funcs {

fuzz::int_expr
ctor_expr(int n, z3::context& ctx)
{
    return ctx.int_val(n);
}

fuzz::int_expr
ctor_yield_free_var(fuzz::FreeVars& fvs)
{
    return fvs.vars.at(fuzz::fuzz_rand<int, int>(0, FV_COUNT - 1));
}

/*******************************************************************************
 * LIBRARY OPERATIONS WRAPPERS
 ******************************************************************************/

fuzz::int_expr
div_wrapper(fuzz::int_expr const& e1, fuzz::int_expr const& e2)
{
    return z3::ite(e2 != 0, e1 / e2, e1);
}

fuzz::int_expr
mod_wrapper(fuzz::int_expr const& e1, fuzz::int_expr const& e2)
{
    return z3::ite(e2 != 0, z3::mod(e1, e2), e1);
}

fuzz::int_expr
rem_wrapper(fuzz::int_expr const& e1, fuzz::int_expr const& e2)
{
    return z3::ite(e2 != 0, z3::rem(e1, e2), e1);
}

fuzz::int_expr
pw_wrapper(fuzz::int_expr const& e1, fuzz::int_expr const& e2)
{
    return z3::ite(e1 != 0 && e2 != 0, e1.ctx().int_val(z3::pw(e1, e2)), e1);
}

/*******************************************************************************
 * int_term API WRAPPERS
 ******************************************************************************/

fuzz::int_expr
make_ite_int_expr(fuzz::bool_expr cond, fuzz::int_expr if_b, fuzz::int_expr then_b)
{
    return z3::ite(cond, if_b, then_b);
}

/*******************************************************************************
 * bool_term API WRAPPERS
 ******************************************************************************/

fuzz::bool_expr
make_bool_const(z3::context& ctx)
{
    return ctx.bool_val(fuzz::fuzz_rand<int, int>(1, 2) % 2);
}

fuzz::bool_expr
not_wrapper(fuzz::bool_expr e)
{
    return z3::operator!(e);
}

fuzz::bool_expr
and_wrapper(fuzz::bool_expr e1, fuzz::bool_expr e2)
{
    return z3::operator&&(e1, e2);
}

fuzz::bool_expr
nand_wrapper(fuzz::bool_expr e1, fuzz::bool_expr e2)
{
    return z3::nand(e1, e2);
}

fuzz::bool_expr
or_wrapper(fuzz::bool_expr e1, fuzz::bool_expr e2)
{
    return z3::operator||(e1, e2);
}

fuzz::bool_expr
nor_wrapper(fuzz::bool_expr e1, fuzz::bool_expr e2)
{
    return z3::nor(e1, e2);
}

fuzz::bool_expr
xor_wrapper(fuzz::bool_expr e1, fuzz::bool_expr e2)
{
    return z3::operator^(e1, e2);
}

fuzz::bool_expr
implies_wrapper(fuzz::bool_expr e1, fuzz::bool_expr e2)
{
    return z3::implies(e1, e2);
}

fuzz::bool_expr
lt_wrapper(fuzz::int_expr const& e1, fuzz::int_expr const& e2)
{
    return z3::operator<(e1, e2);
}

fuzz::bool_expr
gt_wrapper(fuzz::int_expr const& e1, fuzz::int_expr const& e2)
{
    return z3::operator>(e1, e2);
}

fuzz::bool_expr
lte_wrapper(fuzz::int_expr const& e1, fuzz::int_expr const& e2)
{
    return z3::operator<=(e1, e2);
}

fuzz::bool_expr
gte_wrapper(fuzz::int_expr const& e1, fuzz::int_expr const& e2)
{
    return z3::operator>=(e1, e2);
}

fuzz::bool_expr
eq_wrapper(fuzz::int_expr const& e1, fuzz::int_expr const& e2)
{
    return z3::operator==(e1, e2);
}

fuzz::bool_expr
neq_wrapper(fuzz::int_expr const& e1, fuzz::int_expr const& e2)
{
    return z3::operator!=(e1, e2);
}

fuzz::bool_expr
make_ite_bool_expr(fuzz::bool_expr cond, fuzz::bool_expr const& then_e,
    fuzz::bool_expr const& else_e)
{
    return z3::ite(cond, then_e, else_e);
}

} // namespace lib_helper_funcs
} // namespace fuzz

typedef fuzz::int_expr OUT_VAR_TYPE;

#include "set_meta_tests_z3.hpp"

#endif // _Z3_SPEC_DEFS_HPP
