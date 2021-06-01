#ifndef _CVC4_SPEC_DEFS_HPP
#define _CVC4_SPEC_DEFS_HPP

#include "cvc4cpp.h"
#include "cvc4_fuzz_type_defs.hpp"

typedef fuzz::int_term OUT_VAR_TYPE;

#include "meta_spec_cvc4_nl.hpp"
#include "spec.hpp"

namespace fuzz {

static fuzz::int_term output_var;

namespace lib_helper_funcs {

fuzz::FreeVars
ctor_get_free_vars(fuzz::fuzz_context ctx)
{
    return ctx.fvs;
}

fuzz::int_term
ctor_yield_free_var(fuzz::FreeVars& fvs)
{
    return fvs.vars[fuzz::fuzz_rand<int, int>(0, 99)];
}

fuzz::int_term
ctor_expr(int n, fuzz::fuzz_context& ctx)
{
    return ctx.slv.mkInteger(n);
}

fuzz::int_term
make_abs_expr(fuzz::fuzz_context& ctx, fuzz::int_term lhs)
{
    return ctx.slv.mkTerm(CVC4::api::Kind::ABS, lhs);
}

fuzz::int_term
make_uminus_expr(fuzz::fuzz_context& ctx, fuzz::int_term lhs)
{
    return ctx.slv.mkTerm(CVC4::api::Kind::UMINUS, lhs);
}

fuzz::int_term
make_add_expr(fuzz::fuzz_context& ctx, fuzz::int_term lhs, fuzz::int_term rhs)
{
    return ctx.slv.mkTerm(CVC4::api::Kind::PLUS, lhs, rhs);
}

fuzz::int_term
make_sub_expr(fuzz::fuzz_context& ctx, fuzz::int_term lhs, fuzz::int_term rhs)
{
    return ctx.slv.mkTerm(CVC4::api::Kind::MINUS, lhs, rhs);
}

fuzz::int_term
make_mul_lhs_expr(fuzz::fuzz_context& ctx, fuzz::int_term lhs, int rhs)
{
    return ctx.slv.mkTerm(CVC4::api::Kind::MULT, lhs, ctx.slv.mkInteger(rhs));
}

fuzz::int_term
make_mul_rhs_expr(fuzz::fuzz_context& ctx, int lhs, fuzz::int_term rhs)
{
    return ctx.slv.mkTerm(CVC4::api::Kind::MULT, ctx.slv.mkInteger(lhs), rhs);
}

fuzz::int_term
make_int_div_expr(fuzz::fuzz_context& ctx, fuzz::int_term lhs, int rhs_int)
{
    fuzz::int_term rhs = ctx.slv.mkInteger(rhs_int);
    return ctx.slv.mkTerm(CVC4::api::Kind::ITE,
        ctx.slv.mkTerm(CVC4::api::Kind::EQUAL, ctx.slv.mkInteger(0), rhs),
        lhs, ctx.slv.mkTerm(CVC4::api::Kind::INTS_DIVISION, lhs, rhs));
}

fuzz::int_term
make_int_mod_expr(fuzz::fuzz_context& ctx, fuzz::int_term lhs, int rhs_int)
{
    fuzz::int_term rhs = ctx.slv.mkInteger(rhs_int);
    return ctx.slv.mkTerm(CVC4::api::Kind::ITE,
        ctx.slv.mkTerm(CVC4::api::Kind::EQUAL, ctx.slv.mkInteger(0), rhs),
        lhs, ctx.slv.mkTerm(CVC4::api::Kind::INTS_MODULUS, lhs, rhs));
}

fuzz::bool_term
make_lt_expr(fuzz::fuzz_context& ctx, fuzz::int_term lhs, fuzz::int_term rhs)
{
    return ctx.slv.mkTerm(CVC4::api::Kind::LT, lhs, rhs);
}

fuzz::bool_term
make_gt_expr(fuzz::fuzz_context& ctx, fuzz::int_term lhs, fuzz::int_term rhs)
{
    return ctx.slv.mkTerm(CVC4::api::Kind::GT, lhs, rhs);
}

fuzz::bool_term
make_leq_expr(fuzz::fuzz_context& ctx, fuzz::int_term lhs, fuzz::int_term rhs)
{
    return ctx.slv.mkTerm(CVC4::api::Kind::LEQ, lhs, rhs);
}

fuzz::bool_term
make_geq_expr(fuzz::fuzz_context& ctx, fuzz::int_term lhs, fuzz::int_term rhs)
{
    return ctx.slv.mkTerm(CVC4::api::Kind::GEQ, lhs, rhs);
}

fuzz::bool_term
make_eq_bool_expr(fuzz::fuzz_context& ctx, fuzz::bool_term lhs, fuzz::bool_term rhs)
{
    return ctx.slv.mkTerm(CVC4::api::Kind::EQUAL, lhs, rhs);
}

fuzz::bool_term
make_neq_bool_expr(fuzz::fuzz_context& ctx, fuzz::bool_term lhs, fuzz::bool_term rhs)
{
    return ctx.slv.mkTerm(CVC4::api::Kind::DISTINCT, lhs, rhs);
}

fuzz::bool_term
make_eq_int_expr(fuzz::fuzz_context& ctx, fuzz::int_term lhs, fuzz::int_term rhs)
{
    return ctx.slv.mkTerm(CVC4::api::Kind::EQUAL, lhs, rhs);
}

fuzz::bool_term
make_neq_int_expr(fuzz::fuzz_context& ctx, fuzz::int_term lhs, fuzz::int_term rhs)
{
    return ctx.slv.mkTerm(CVC4::api::Kind::DISTINCT, lhs, rhs);
}

fuzz::int_term
make_ite_int_expr(fuzz::fuzz_context& ctx, fuzz::bool_term cond, fuzz::int_term lhs, fuzz::int_term rhs)
{
    return ctx.slv.mkTerm(CVC4::api::Kind::ITE, cond, lhs, rhs);
}

fuzz::bool_term
make_ite_bool_expr(fuzz::fuzz_context& ctx, fuzz::bool_term cond, fuzz::bool_term lhs, fuzz::bool_term rhs)
{
    return ctx.slv.mkTerm(CVC4::api::Kind::ITE, cond, lhs, rhs);
}

fuzz::bool_term
make_const_bool(fuzz::fuzz_context& ctx)
{
    return ctx.slv.mkBoolean(fuzz::fuzz_rand<int, int>(1, 2) % 2);
}

fuzz::bool_term
make_not_expr(fuzz::fuzz_context& ctx, fuzz::bool_term lhs)
{
    return ctx.slv.mkTerm(CVC4::api::Kind::NOT, lhs);
}

fuzz::bool_term
make_and_expr(fuzz::fuzz_context& ctx, fuzz::bool_term lhs, fuzz::bool_term rhs)
{
    return ctx.slv.mkTerm(CVC4::api::Kind::AND, lhs, rhs);
}

fuzz::bool_term
make_implies_expr(fuzz::fuzz_context& ctx, fuzz::bool_term lhs, fuzz::bool_term rhs)
{
    return ctx.slv.mkTerm(CVC4::api::Kind::IMPLIES, lhs, rhs);
}

fuzz::bool_term
make_or_expr(fuzz::fuzz_context& ctx, fuzz::bool_term lhs, fuzz::bool_term rhs)
{
    return ctx.slv.mkTerm(CVC4::api::Kind::OR, lhs, rhs);
}

fuzz::bool_term
make_xor_expr(fuzz::fuzz_context& ctx, fuzz::bool_term lhs, fuzz::bool_term rhs)
{
    return ctx.slv.mkTerm(CVC4::api::Kind::XOR, lhs, rhs);
}

} // namespace lib_helper_funcs
} // namespace fuzz

#endif // _CVC4_SPEC_DEFS_HPP
