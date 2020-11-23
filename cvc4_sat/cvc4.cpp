#ifdef EXECUTE
#include "cvc4/api/cvc4cpp.h"
#include <cassert>
typedef std::pair<CVC4::api::Term, CVC4::api::Term> mr_pair;
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

CVC4::api::Term
make_lt_ite_expr(CVC4::api::Solver& slv, CVC4::api::Term lhs, CVC4::api::Term rhs,
    CVC4::api::Term b_then, CVC4::api::Term b_else)
{
    return slv.mkTerm(CVC4::api::Kind::ITE,
        slv.mkTerm(CVC4::api::Kind::LT, lhs, rhs), b_then, b_else);
}

CVC4::api::Term
make_gte_ite_expr(CVC4::api::Solver& slv, CVC4::api::Term lhs, CVC4::api::Term rhs,
    CVC4::api::Term b_then, CVC4::api::Term b_else)
{
    return slv.mkTerm(CVC4::api::Kind::ITE,
        slv.mkTerm(CVC4::api::Kind::GEQ, lhs, rhs), b_then, b_else);
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
    CVC4::api::Term cnst_var1 = slv.mkConst(slv.getIntegerSort(), "x");
    CVC4::api::Term cnst_var2 = slv.mkConst(slv.getIntegerSort(), "y");
    CVC4::api::Term cnst_var3 = slv.mkConst(slv.getIntegerSort(), "z");
    slv.setLogic("QF_NIA");
    fuzz::start();
    CVC4::api::Term lhs = fuzz::fuzz_new<CVC4::api::Term>();
    CVC4::api::Term rhs = fuzz::fuzz_new<CVC4::api::Term>();
    fuzz::output_var = std::make_pair(lhs, rhs);
    fuzz::end();

    CVC4::api::Term check = slv.mkTerm(CVC4::api::Kind::LT,
        fuzz::output_var_get(0).first, fuzz::output_var_get(0).second);
    slv.assertFormula(check);
    if (!slv.checkSat().isSat())
    {
        std::cout << "Non-SAT formula." << std::endl;
        exit(0);
    }
    //slv.printModel(std::cout);

    fuzz::meta_test();
}

