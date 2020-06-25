#include "/home/sentenced/Documents/Internships/2018_ETH/work/spec_ast/input/spec_repo/z3_bv/spec_fuzz.hpp"

#define BV_SIZE 32

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
    std::string var_name = "var" + std::to_string(fuzz::fuzz_rand(0, 2000));
    //z3::expr e1 = ctx.int_const(var_name.c_str());
    //z3::expr e2 = ctx.int_val(fuzz::fuzz_rand(20, 30));
    //fuzz::output_var = ctx.bv_val(fuzz::fuzz_rand(-20, 20));
    //fuzz::output_var = fuzz::lib_helper_funcs::ctor_expr(fuzz::fuzz_rand(-20, 20), ctx);
    fuzz::output_var = ctx.bv_val(fuzz::fuzz_rand(-20, 20), BV_SIZE);
    fuzz::output_var = z3::operator+(fuzz::fuzz_new<z3::expr>(), fuzz::output_var);
    fuzz::output_var = fuzz::output_var.simplify();
    fuzz::end();
    fuzz::meta_test();
}
