#define FV_COUNT 100


#ifdef EXECUTE
#include "cvc4/api/cvc4cpp.h"
#include <cassert>
namespace fuzz {
    typedef CVC4::api::Term bool_term;
    typedef CVC4::api::Term int_term;
    class FreeVars {
      public:
        fuzz::int_term* vars[FV_COUNT];
    };
}
#else
#include "cvc4_spec_defs.hpp"
#endif

namespace fuzz {
namespace lib_helper_funcs {

fuzz::int_term
ctor_yield_free_var(fuzz::FreeVars& fvs)
{
    return *fvs.vars[fuzz::fuzz_rand<int, int>(0, 99)];
}

fuzz::int_term
ctor_expr(int n, CVC4::api::Solver& slv)
{
    return slv.mkInteger(n);
}

//fuzz::int_term
//ctor_expr(CVC4::api::Term& t)
//{
    //return t;
//}

fuzz::int_term
make_abs_expr(CVC4::api::Solver& slv, fuzz::int_term lhs)
{
    return slv.mkTerm(CVC4::api::Kind::ABS, lhs);
}

fuzz::int_term
make_uminus_expr(CVC4::api::Solver& slv, fuzz::int_term lhs)
{
    return slv.mkTerm(CVC4::api::Kind::UMINUS, lhs);
}

fuzz::int_term
make_add_expr(CVC4::api::Solver& slv, fuzz::int_term lhs, fuzz::int_term rhs)
{
    return slv.mkTerm(CVC4::api::Kind::PLUS, lhs, rhs);
}

fuzz::int_term
make_sub_expr(CVC4::api::Solver& slv, fuzz::int_term lhs, fuzz::int_term rhs)
{
    return slv.mkTerm(CVC4::api::Kind::MINUS, lhs, rhs);
}

fuzz::int_term
make_mul_expr(CVC4::api::Solver& slv, fuzz::int_term lhs, fuzz::int_term rhs)
{
    return slv.mkTerm(CVC4::api::Kind::MULT, lhs, rhs);
}

fuzz::int_term
make_pow_expr(CVC4::api::Solver& slv, fuzz::int_term lhs, fuzz::int_term rhs)
{
    fuzz::int_term zero = slv.mkInteger(0);
    fuzz::bool_term is_zero = slv.mkTerm(CVC4::api::AND,
        slv.mkTerm(CVC4::api::EQUAL, lhs, zero),
        slv.mkTerm(CVC4::api::EQUAL, rhs, zero));
    return is_zero.iteTerm(lhs, slv.mkTerm(CVC4::api::Kind::POW, lhs, slv.mkTerm(CVC4::api::Kind::ABS, rhs)));
}

//fuzz::int_term
//make_real_div_expr(CVC4::api::Solver& slv, fuzz::int_term lhs, fuzz::int_term rhs)
//{
    //return slv.mkTerm(CVC4::api::Kind::TO_INTEGER, slv.mkTerm(CVC4::api::Kind::DIVISION, lhs, rhs));
//}

fuzz::int_term
make_int_div_expr(CVC4::api::Solver& slv, fuzz::int_term lhs, fuzz::int_term rhs)
{
    //return slv.mkTerm(CVC4::api::Kind::INTS_DIVISION, lhs, rhs);
    return slv.mkTerm(CVC4::api::Kind::ITE,
        slv.mkTerm(CVC4::api::Kind::EQUAL, slv.mkInteger(0), rhs),
        lhs, slv.mkTerm(CVC4::api::Kind::INTS_DIVISION, lhs, rhs));
}

fuzz::int_term
make_int_mod_expr(CVC4::api::Solver& slv, fuzz::int_term lhs, fuzz::int_term rhs)
{
    //return slv.mkTerm(CVC4::api::Kind::INTS_MODULUS, lhs, rhs);
    return slv.mkTerm(CVC4::api::Kind::ITE,
        slv.mkTerm(CVC4::api::Kind::EQUAL, slv.mkInteger(0), rhs),
        lhs, slv.mkTerm(CVC4::api::Kind::INTS_MODULUS, lhs, rhs));
}

fuzz::bool_term
make_lt_expr(CVC4::api::Solver& slv, fuzz::int_term lhs, fuzz::int_term rhs)
{
    return slv.mkTerm(CVC4::api::Kind::LT, lhs, rhs);
}

fuzz::bool_term
make_gt_expr(CVC4::api::Solver& slv, fuzz::int_term lhs, fuzz::int_term rhs)
{
    return slv.mkTerm(CVC4::api::Kind::GT, lhs, rhs);
}

fuzz::bool_term
make_leq_expr(CVC4::api::Solver& slv, fuzz::int_term lhs, fuzz::int_term rhs)
{
    return slv.mkTerm(CVC4::api::Kind::LEQ, lhs, rhs);
}

fuzz::bool_term
make_geq_expr(CVC4::api::Solver& slv, fuzz::int_term lhs, fuzz::int_term rhs)
{
    return slv.mkTerm(CVC4::api::Kind::GEQ, lhs, rhs);
}

fuzz::bool_term
make_eq_bool_expr(CVC4::api::Solver& slv, fuzz::bool_term lhs, fuzz::bool_term rhs)
{
    return slv.mkTerm(CVC4::api::Kind::EQUAL, lhs, rhs);
}

fuzz::bool_term
make_neq_bool_expr(CVC4::api::Solver& slv, fuzz::bool_term lhs, fuzz::bool_term rhs)
{
    return slv.mkTerm(CVC4::api::Kind::DISTINCT, lhs, rhs);
}

fuzz::bool_term
make_eq_int_expr(CVC4::api::Solver& slv, fuzz::int_term lhs, fuzz::int_term rhs)
{
    return slv.mkTerm(CVC4::api::Kind::EQUAL, lhs, rhs);
}

fuzz::bool_term
make_neq_int_expr(CVC4::api::Solver& slv, fuzz::int_term lhs, fuzz::int_term rhs)
{
    return slv.mkTerm(CVC4::api::Kind::DISTINCT, lhs, rhs);
}

fuzz::int_term
make_ite_int_expr(CVC4::api::Solver& slv, fuzz::bool_term cond, fuzz::int_term lhs, fuzz::int_term rhs)
{
    return slv.mkTerm(CVC4::api::Kind::ITE, cond, lhs, rhs);
}

fuzz::bool_term
make_ite_bool_expr(CVC4::api::Solver& slv, fuzz::bool_term cond, fuzz::bool_term lhs, fuzz::bool_term rhs)
{
    return slv.mkTerm(CVC4::api::Kind::ITE, cond, lhs, rhs);
}

fuzz::bool_term
make_const_bool(CVC4::api::Solver& slv)
{
    return slv.mkBoolean(fuzz::fuzz_rand<int, int>(1, 2) % 2);
}

fuzz::bool_term
make_not_expr(CVC4::api::Solver& slv, fuzz::bool_term lhs)
{
    return slv.mkTerm(CVC4::api::Kind::NOT, lhs);
}

fuzz::bool_term
make_and_expr(CVC4::api::Solver& slv, fuzz::bool_term lhs, fuzz::bool_term rhs)
{
    return slv.mkTerm(CVC4::api::Kind::AND, lhs, rhs);
}

fuzz::bool_term
make_implies_expr(CVC4::api::Solver& slv, fuzz::bool_term lhs, fuzz::bool_term rhs)
{
    return slv.mkTerm(CVC4::api::Kind::IMPLIES, lhs, rhs);
}

fuzz::bool_term
make_or_expr(CVC4::api::Solver& slv, fuzz::bool_term lhs, fuzz::bool_term rhs)
{
    return slv.mkTerm(CVC4::api::Kind::OR, lhs, rhs);
}

fuzz::bool_term
make_xor_expr(CVC4::api::Solver& slv, fuzz::bool_term lhs, fuzz::bool_term rhs)
{
    return slv.mkTerm(CVC4::api::Kind::XOR, lhs, rhs);
}

} // namespace lib_helper_funcs
} // namespace fuzz

int
main(int argc, char** argv)
{
    CVC4::api::Solver slv;
    slv.setLogic("QF_NIA");

    CVC4::api::Sort int_s = slv.getIntegerSort();
    fuzz::FreeVars fvs;
    for (size_t i = 0; i < FV_COUNT; ++i)
    {
        fuzz::int_term new_term = slv.mkConst(int_s, "x" + std::to_string(i));
        fvs.vars[i] = &new_term;
    }

    fuzz::start();
    fuzz::output_var = fuzz::fuzz_new<fuzz::int_term>();
    fuzz::end();
    fuzz::meta_test();
}
