#include "/home/sentenced/Documents/Internships/2018_ETH/work/spec_ast/input/z3/spec_fuzz.hpp"

namespace fuzz {
namespace lib_helper_funcs {

z3::expr
ctor_expr(int n, z3::context& ctx)
{
    return ctx.int_val(n);
}

//z3::context&
//get_ctx_from_expr(z3::expr& e)
//{
    //return e.ctx();
//}

z3::expr
get_one(z3::expr e)
{
    return e.ctx().int_val(1);
}

z3::expr
get_zero(z3::expr e)
{
    return e.ctx().int_val(0);
}

bool
checkValid(z3::expr& e1, z3::expr& e2)
{
    z3::solver solver(e1.ctx());
    z3::expr conjecture = z3::operator==(e1, e2);
    solver.add(!conjecture);
    return solver.check() != z3::sat;
}

} // namespace lib_helper_funcs
} // namespace fuzz

int
main(int argc, char** argv)
{
    z3::context ctx;
    fuzz::start();
    //std::string var_name = "var" + std::to_string(fuzz::fuzz_rand(0, 2000));
    //z3::expr e1 = ctx.int_const(var_name.c_str());
    //z3::expr e2 = ctx.int_val(fuzz::fuzz_rand(20, 30));
    fuzz::output_var = ctx.int_val(fuzz::fuzz_rand(-20, 20));
    fuzz::output_var = z3::operator+(fuzz::fuzz_new<z3::expr>(), fuzz::output_var);
    fuzz::end();
    fuzz::meta_test();
}
