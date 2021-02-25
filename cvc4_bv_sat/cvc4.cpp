#define BV_SIZE 32

#ifdef EXECUTE
#include "cvc4/api/cvc4cpp.h"
#include <cassert>
typedef std::pair<CVC4::api::Term, CVC4::api::Term> mr_pair;
typedef std::pair<CVC4::api::Term, CVC4::api::Term> check_pair;
#else
#include "cvc4_spec_defs.hpp"
#endif

namespace fuzz {
namespace lib_helper_funcs {

CVC4::api::Term
ctor_expr(int n, CVC4::api::Solver& slv)
{
    return slv.mkBitVector(BV_SIZE, n);
}

CVC4::api::Term
make_bvnot_expr(CVC4::api::Solver& slv, CVC4::api::Term lhs)
{
    return slv.mkTerm(CVC4::api::Kind::BITVECTOR_NOT, lhs);
}

CVC4::api::Term
make_bvneg_expr(CVC4::api::Solver& slv, CVC4::api::Term lhs)
{
    return slv.mkTerm(CVC4::api::Kind::BITVECTOR_NEG, lhs);
}

CVC4::api::Term
make_bvand_expr(CVC4::api::Solver& slv, CVC4::api::Term lhs, CVC4::api::Term rhs)
{
    return slv.mkTerm(CVC4::api::Kind::BITVECTOR_AND, lhs, rhs);
}

CVC4::api::Term
make_bvor_expr(CVC4::api::Solver& slv, CVC4::api::Term lhs, CVC4::api::Term rhs)
{
    return slv.mkTerm(CVC4::api::Kind::BITVECTOR_OR, lhs, rhs);
}

CVC4::api::Term
make_bvxor_expr(CVC4::api::Solver& slv, CVC4::api::Term lhs, CVC4::api::Term rhs)
{
    return slv.mkTerm(CVC4::api::Kind::BITVECTOR_XOR, lhs, rhs);
}

CVC4::api::Term
make_bvnand_expr(CVC4::api::Solver& slv, CVC4::api::Term lhs, CVC4::api::Term rhs)
{
    return slv.mkTerm(CVC4::api::Kind::BITVECTOR_NAND, lhs, rhs);
}

CVC4::api::Term
make_bvnor_expr(CVC4::api::Solver& slv, CVC4::api::Term lhs, CVC4::api::Term rhs)
{
    return slv.mkTerm(CVC4::api::Kind::BITVECTOR_NOR, lhs, rhs);
}

CVC4::api::Term
make_bvxnor_expr(CVC4::api::Solver& slv, CVC4::api::Term lhs, CVC4::api::Term rhs)
{
    return slv.mkTerm(CVC4::api::Kind::BITVECTOR_XNOR, lhs, rhs);
}

CVC4::api::Term
make_bvadd_expr(CVC4::api::Solver& slv, CVC4::api::Term lhs, CVC4::api::Term rhs)
{
    return slv.mkTerm(CVC4::api::Kind::BITVECTOR_PLUS, lhs, rhs);
}

CVC4::api::Term
make_bvsub_expr(CVC4::api::Solver& slv, CVC4::api::Term lhs, CVC4::api::Term rhs)
{
    return slv.mkTerm(CVC4::api::Kind::BITVECTOR_SUB, lhs, rhs);
}

CVC4::api::Term
make_bvmul_expr(CVC4::api::Solver& slv, CVC4::api::Term lhs, CVC4::api::Term rhs)
{
    return slv.mkTerm(CVC4::api::Kind::BITVECTOR_MULT, lhs, rhs);
}

CVC4::api::Term
make_bvsdiv_expr(CVC4::api::Solver& slv, CVC4::api::Term lhs, CVC4::api::Term rhs)
{
    return slv.mkTerm(CVC4::api::Kind::BITVECTOR_SDIV, lhs, rhs);
}

CVC4::api::Term
make_bvsmod_expr(CVC4::api::Solver& slv, CVC4::api::Term lhs, CVC4::api::Term rhs)
{
    return slv.mkTerm(CVC4::api::Kind::BITVECTOR_SMOD, lhs, rhs);
}

CVC4::api::Term
make_bvsrem_expr(CVC4::api::Solver& slv, CVC4::api::Term lhs, CVC4::api::Term rhs)
{
    return slv.mkTerm(CVC4::api::Kind::BITVECTOR_SREM, lhs, rhs);
}

CVC4::api::Term
make_lt_ite_expr(CVC4::api::Solver& slv, CVC4::api::Term lhs, CVC4::api::Term rhs,
    CVC4::api::Term b_then, CVC4::api::Term b_else)
{
    return slv.mkTerm(CVC4::api::Kind::BITVECTOR_ITE,
        slv.mkTerm(CVC4::api::Kind::BITVECTOR_SLTBV, lhs, rhs), b_then, b_else);
}

CVC4::api::Term
make_gte_ite_expr(CVC4::api::Solver& slv, CVC4::api::Term lhs, CVC4::api::Term rhs,
    CVC4::api::Term b_then, CVC4::api::Term b_else)
{
    return slv.mkTerm(CVC4::api::Kind::ITE,
        slv.mkTerm(CVC4::api::Kind::BITVECTOR_SGE, lhs, rhs), b_then, b_else);
}

} // namespace lib_helper_funcs
} // namespace fuzz

int
main(int argc, char** argv)
{
    CVC4::api::Solver slv;
    CVC4::api::Term cnst_var1 = slv.mkConst(slv.mkBitVectorSort(BV_SIZE), "x");
    CVC4::api::Term cnst_var2 = slv.mkConst(slv.mkBitVectorSort(BV_SIZE), "y");
    CVC4::api::Term cnst_var3 = slv.mkConst(slv.mkBitVectorSort(BV_SIZE), "z");
    slv.setLogic("QF_BV");
    slv.setOption("produce-models", "true");
    fuzz::start();
    CVC4::api::Term lhs = fuzz::fuzz_new<CVC4::api::Term>();
    CVC4::api::Term rhs = fuzz::fuzz_new<CVC4::api::Term>();
    fuzz::output_var = std::make_pair(lhs, rhs);
    fuzz::end();

    CVC4::api::Kind op = CVC4::api::Kind::BITVECTOR_SLT;
    CVC4::api::Term check = slv.mkTerm(op,
        fuzz::output_var_get(0).first, fuzz::output_var_get(0).second);
    slv.assertFormula(check);
    if (!slv.checkSat().isSat())
    {
        slv.resetAssertions();
        op = CVC4::api::Kind::BITVECTOR_SGE;
        CVC4::api::Term check = slv.mkTerm(op,
            fuzz::output_var_get(0).first, fuzz::output_var_get(0).second);
        slv.assertFormula(check);
        if (!slv.checkSat().isSat())
        {
            std::cout << "Non-SAT formula." << std::endl;
            exit(0);
        }
    }
    check_pair cp = std::make_pair(fuzz::output_var_get(0).first, fuzz::output_var_get(0).second);
    //slv.printModel(std::cout);
    slv.resetAssertions();

    fuzz::meta_test();
}

