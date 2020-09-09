#ifdef EXECUTE
#include "z3++.h"
#include <cassert>
typedef std::pair<z3::expr, z3::expr> mr_pair;
#else
#include "z3_spec_defs.hpp"
#endif

namespace fuzz {
namespace lib_helper_funcs {

//z3::expr
//ctor_expr(int n, z3::context& ctx)
//{
    //return ctx.int_val(n);
//}

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
    return z3::ite(e2 != 0, e1 / e2, e1);
}

z3::expr
mod_wrapper(z3::expr const& e1, z3::expr const& e2)
{
    return z3::ite(e2 != 0, z3::mod(e1, e2), e1);
}

z3::expr
rem_wrapper(z3::expr const& e1, z3::expr const& e2)
{
    return z3::ite(e2 != 0, z3::rem(e1, e2), e1);
}

z3::expr
pw_wrapper(z3::expr const& e1, z3::expr const& e2)
{
    return z3::ite(e1 != 0 && e2 != 0, z3::pw(e1, e2), e1);
}


} // namespace lib_helper_funcs
} // namespace fuzz

int
main(int argc, char** argv)
{
    z3::context ctx;
    z3::expr cnst_var1 = ctx.int_const("x");
    z3::expr cnst_var2 = ctx.int_const("y");
    z3::expr cnst_var3 = ctx.int_const("z");
    fuzz::start();
    z3::expr t = ctx.int_val(23);
    z3::expr lhs = fuzz::fuzz_new<z3::expr>();
    z3::expr rhs = fuzz::fuzz_new<z3::expr>();
    //fuzz::output_var = std::make_pair(lhs, rhs);
    fuzz::output_var = std::make_pair(lhs, rhs);
    fuzz::end();
    z3::solver s(ctx);
    s.add(z3::operator<(fuzz::output_var_get(0).first, fuzz::output_var_get(0).second));
    std::cout << s.to_smt2() << std::endl;
    if (s.check() != z3::sat)
    {
        std::cout << "Non-SAT formula." << std::endl;
        exit(0);
    }
    z3::model out_model = s.get_model();
    fuzz::meta_test();
}
