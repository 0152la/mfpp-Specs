#define BV_SIZE 32

#ifdef EXECUTE
#include "z3++.h"
#include <cassert>
typedef std::pair<z3::expr, z3::expr> mr_pair;
#else
#include "z3_bv_spec_defs.hpp"
#endif

namespace fuzz {
namespace lib_helper_funcs {

z3::expr
ctor_expr(int n, z3::context& ctx)
{
    return ctx.bv_val(n, BV_SIZE);
}

z3::expr
ite_lt_wrapper(z3::expr cond1, z3::expr cond2, z3::expr if_b, z3::expr then_b)
{
    return z3::ite(cond1 < cond2, if_b, then_b);
}

z3::expr
ite_gte_wrapper(z3::expr cond1, z3::expr cond2, z3::expr if_b, z3::expr then_b)
{
    return z3::ite(cond1 >= cond2, if_b, then_b);
}

z3::expr
div_wrapper(z3::expr const& e1, z3::expr const& e2)
{
    return z3::ite(e2 != 0, e1 / e2, e1);
}

z3::expr
mod_wrapper(z3::expr const& e1, z3::expr const& e2)
{
    return z3::ite(e2 != 0, z3::mod(e1, e2), e1);
}

} // namespace lib_helper_funcs
} // namespace fuzz

int
main(int argc, char** argv)
{
    z3::context ctx;
    z3::expr cnst_var1 = ctx.bv_const("x", BV_SIZE);
    z3::expr cnst_var2 = ctx.bv_const("y", BV_SIZE);
    z3::expr cnst_var3 = ctx.bv_const("z", BV_SIZE);

    fuzz::start();
    z3::expr lhs = fuzz::fuzz_new<z3::expr>();
    z3::expr rhs = fuzz::fuzz_new<z3::expr>();
    fuzz::output_var = std::make_pair(lhs, rhs);
    fuzz::end();
    assert(ctx.check_error() == Z3_OK);

    z3::solver s(ctx);
    s.add(z3::operator<(fuzz::output_var_get(0).first, fuzz::output_var_get(0).second));
    //std::cout << s.to_smt2() << std::endl;
    if (s.check() != z3::sat)
    {
        std::cout << "Non-SAT formula." << std::endl;
        exit(0);
    }
    z3::model out_model = s.get_model();

    for (z3::expr cnst_expr : {cnst_var1, cnst_var2, cnst_var3})
    {
        z3::func_decl cnst_decl = cnst_expr.decl();
        if (!out_model.has_interp(cnst_decl))
        {
            z3::expr zero_val = ctx.int_val(0);
            out_model.add_const_interp(cnst_decl, zero_val);
        }
    }

    fuzz::meta_test();
}
