#define BV_SIZE 20

#ifdef EXECUTE
#include "boolector/boolector.h"
#include <cassert>
#else
#include "boolector_spec_defs.hpp"
#endif

namespace fuzz {
namespace lib_helper_funcs {

BoolectorNode*
ctor_expr(Btor* ctx, int n)
{
    return boolector_int(ctx, n, boolector_bitvec_sort(ctx, BV_SIZE));
}

BoolectorNode*
ite_lt_wrapper(Btor* ctx, BoolectorNode* cond1, BoolectorNode* cond2,
    BoolectorNode* then_n, BoolectorNode* else_n)
{
    return boolector_cond(ctx, boolector_slt(ctx, cond1, cond2), then_n, else_n);
}

BoolectorNode*
ite_gte_wrapper(Btor* ctx, BoolectorNode* cond1, BoolectorNode* cond2,
    BoolectorNode* then_n, BoolectorNode* else_n)
{
    return boolector_cond(ctx, boolector_sgte(ctx, cond1, cond2), then_n, else_n);
}

} // namespace lib_helper_funcs
} // namespace fuzz

int
main(int argc, char** argv)
{
    Btor* ctx = boolector_new();

    BoolectorNode* x = boolector_var(ctx, boolector_bitvec_sort(ctx, BV_SIZE), "x");
    BoolectorNode* y = boolector_var(ctx, boolector_bitvec_sort(ctx, BV_SIZE), "y");
    BoolectorNode* z = boolector_var(ctx, boolector_bitvec_sort(ctx, BV_SIZE), "z");

    fuzz::start();
    BoolectorNode* lhs = fuzz::fuzz_new<BoolectorNode*>();
    BoolectorNode* rhs = fuzz::fuzz_new<BoolectorNode*>();
    fuzz::output_var = boolector_add(ctx, lhs, rhs);
    fuzz::end();

    sat_stat status = -1;

    fuzz::meta_test();

    boolector_release_all(ctx);
    boolector_delete(ctx);
}

