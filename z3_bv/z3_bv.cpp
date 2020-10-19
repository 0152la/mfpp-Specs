#define BV_SIZE 32

#include "z3++.h"
#ifndef EXECUTE
#include "z3_bv_spec_defs.hpp"
#include "spec_fuzz.hpp"
#endif

namespace fuzz {
namespace lib_helper_funcs {

z3::expr
ctor_expr(int n, z3::context& ctx)
{
    return ctx.bv_val(n, BV_SIZE);
}

//} // namespace lib_helper_funcs

//namespace meta_helper_funcs {
z3::expr
get_one(z3::expr e)
{
    return e.ctx().bv_val(1, BV_SIZE);
}

z3::expr
get_zero(z3::expr e)
{
    return e.ctx().bv_val(0, BV_SIZE);
}

bool
checkValid(z3::expr& e1, z3::expr& e2)
{
    z3::solver solver(e1.ctx());
    z3::expr conjecture = z3::operator==(e1, e2);
    solver.add(!conjecture);
    return solver.check() != z3::sat;
}

} // namespace meta_helper_funcs
} // namespace fuzz

int
main(int argc, char** argv)
{
    z3::context ctx;
    fuzz::start();
    fuzz::output_var = ctx.bv_val(fuzz::fuzz_rand<int, int>(-20, 20), BV_SIZE);
    fuzz::output_var = ctx.bv_const(std::string(fuzz::fuzz_rand<std::string, uint8_t>(3, 3)).c_str(), BV_SIZE);
    fuzz::output_var = z3::operator+(fuzz::fuzz_new<z3::expr>(), fuzz::output_var);
    fuzz::output_var = fuzz::output_var.simplify();
    fuzz::end();
    assert(ctx.check_error() == Z3_OK);
    fuzz::meta_test();
}
