#define BV_SIZE 20

#include <utility>

#ifdef EXECUTE
#include "boolector/boolector.h"
typedef int32_t sat_stat;
#include <cassert>
typedef std::pair<BoolectorNode*, BoolectorNode*> mr_pair;
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
    boolector_set_opt(ctx, BTOR_OPT_INCREMENTAL, 1);

    BoolectorNode* x = boolector_var(ctx, boolector_bitvec_sort(ctx, BV_SIZE), "x");
    BoolectorNode* y = boolector_var(ctx, boolector_bitvec_sort(ctx, BV_SIZE), "y");
    BoolectorNode* z = boolector_var(ctx, boolector_bitvec_sort(ctx, BV_SIZE), "z");

    fuzz::start();
    BoolectorNode* lhs = fuzz::fuzz_new<BoolectorNode*>();
    BoolectorNode* rhs = fuzz::fuzz_new<BoolectorNode*>();
    fuzz::output_var = std::make_pair(lhs, rhs);
    fuzz::end();

    BoolectorNode* check = boolector_slt(ctx,
        fuzz::output_var_get(0).first, fuzz::output_var_get(0).second);
    boolector_assert(ctx, check);
    sat_stat status = boolector_sat(ctx);
    if (status == BOOLECTOR_UNKNOWN)
    {
        return 0;
    }

    fuzz::meta_test();

    boolector_release_all(ctx);
    boolector_delete(ctx);
}

