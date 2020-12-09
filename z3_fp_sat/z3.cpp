#ifdef EXECUTE
#include "z3++.h"
#include <cassert>
typedef std::pair<z3::expr, z3::expr> mr_pair;
#else
#include "z3_spec_defs.hpp"
#endif

#define POW_LIM 32.0
#define FPA_PREC 64

namespace fuzz {
namespace lib_helper_funcs {

z3::expr
ctor_expr(double n, z3::context& ctx)
{
    return ctx.fpa_val(n);
}

//z3::expr
//ctor_expr(std::string s, z3::context& ctx)
//{
    //return ctx.int_const(std::string(s).c_str());
//}

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
    return z3::ite(e2 != e1.ctx().fpa_val(0.0), e1 / e2, e1);
}

} // namespace lib_helper_funcs
} // namespace fuzz

int
main(int argc, char** argv)
{
    z3::context ctx;

    z3::expr cnst_var1 = ctx.fpa_const<FPA_PREC>("x");
    z3::expr cnst_var2 = ctx.fpa_const<FPA_PREC>("y");
    z3::expr cnst_var3 = ctx.fpa_const<FPA_PREC>("z");

    fuzz::start();
    z3::expr lhs = fuzz::fuzz_new<z3::expr>();
    z3::expr rhs = fuzz::fuzz_new<z3::expr>();
    fuzz::output_var = std::make_pair(lhs, rhs);
    fuzz::end();
    assert(ctx.check_error() == Z3_OK);

    z3::solver s(ctx);
    z3::expr (*chk_op)(z3::expr const&, z3::expr const&){ &z3::operator< };
    s.add((*chk_op)(fuzz::output_var_get(0).first, fuzz::output_var_get(0).second));
    if (s.check() != z3::sat)
    {
        chk_op = &z3::operator>=;
        s.reset();
        s.add((*chk_op)(fuzz::output_var_get(0).first, fuzz::output_var_get(0).second));
        if (s.check() != z3::sat)
        {
            std::cout << "Non-SAT formula." << std::endl;
            exit(0);
        }
    }
    z3::model out_model = s.get_model();

    for (z3::expr cnst_expr : {cnst_var1, cnst_var2, cnst_var3})
    {
        z3::func_decl cnst_decl = cnst_expr.decl();
        if (!out_model.has_interp(cnst_decl))
        {
            z3::expr zero_val = ctx.fpa_val(0.0);
            out_model.add_const_interp(cnst_decl, zero_val);
        }
    }
    fuzz::meta_test();
}
