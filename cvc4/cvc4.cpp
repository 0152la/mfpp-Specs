#ifdef EXECUTE
#include "cvc4/api/cvc4cpp.h"
#include <cassert>
#else
#include "cvc4_spec_defs.hpp"
#endif

namespace fuzz {
namespace lib_helper_funcs {

CVC4::api::Term
ctor_expr(int n, CVC4::api::Solver& slv)
{
    return slv.mkInteger(n);
}

CVC4::api::Term
make_abs_expr(CVC4::api::Solver& slv, CVC4::api::Term lhs)
{
    return slv.mkTerm(CVC4::api::Kind::ABS, lhs);
}

CVC4::api::Term
make_uminus_expr(CVC4::api::Solver& slv, CVC4::api::Term lhs)
{
    return slv.mkTerm(CVC4::api::Kind::UMINUS, lhs);
}

CVC4::api::Term
make_add_expr(CVC4::api::Solver& slv, CVC4::api::Term lhs, CVC4::api::Term rhs)
{
    return slv.mkTerm(CVC4::api::Kind::PLUS, lhs, rhs);
}

CVC4::api::Term
make_sub_expr(CVC4::api::Solver& slv, CVC4::api::Term lhs, CVC4::api::Term rhs)
{
    return slv.mkTerm(CVC4::api::Kind::MINUS, lhs, rhs);
}

CVC4::api::Term
make_mul_expr(CVC4::api::Solver& slv, CVC4::api::Term lhs, CVC4::api::Term rhs)
{
    return slv.mkTerm(CVC4::api::Kind::MULT, lhs, rhs);
}

//CVC4::api::Term
//make_pow_expr(CVC4::api::Solver& slv, CVC4::api::Term lhs, CVC4::api::Term rhs)
//{
    //CVC4::api::Term zero = slv.mkReal(0);
    //CVC4::api::Term is_zero = slv.mkTerm(CVC4::api::AND,
        //slv.mkTerm(CVC4::api::EQUAL, lhs, zero),
        //slv.mkTerm(CVC4::api::EQUAL, rhs, zero));
    //return is_zero.iteTerm(lhs, slv.mkTerm(CVC4::api::Kind::POW, lhs, slv.mkTerm(CVC4::api::Kind::ABS, rhs)));
//}


//CVC4::api::Term
//make_real_div_expr(CVC4::api::Solver& slv, CVC4::api::Term lhs, CVC4::api::Term rhs)
//{
    //return slv.mkTerm(CVC4::api::Kind::TO_INTEGER, slv.mkTerm(CVC4::api::Kind::DIVISION, lhs, rhs));
//}

//CVC4::api::Term
//make_int_div_expr(CVC4::api::Solver& slv, CVC4::api::Term lhs, CVC4::api::Term rhs)
//{
    //return slv.mkTerm(CVC4::api::Kind::INTS_DIVISION, lhs, rhs);
//}

//CVC4::api::Term
//make_int_mod_expr(CVC4::api::Solver& slv, CVC4::api::Term lhs, CVC4::api::Term rhs)
//{
    //return slv.mkTerm(CVC4::api::Kind::INTS_MODULUS, lhs, rhs);
//}

} // namespace lib_helper_funcs
} // namespace fuzz

int
main(int argc, char** argv)
{
    CVC4::api::Solver slv;
    slv.setLogic("QF_NIA");

    CVC4::api::Sort int_s = slv.getIntegerSort();
    CVC4::api::Term x = slv.mkConst(int_s, "x");
    CVC4::api::Term y = slv.mkConst(int_s, "y");
    CVC4::api::Term z = slv.mkConst(int_s, "z");

    fuzz::start();
    fuzz::output_var = fuzz::fuzz_new<CVC4::api::Term>();
    fuzz::output_var = slv.mkTerm(CVC4::api::Kind::PLUS, fuzz::fuzz_new<CVC4::api::Term>(), fuzz::output_var);
    fuzz::end();
    fuzz::meta_test();
}

