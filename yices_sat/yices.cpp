#define BV_SIZE 20

#include <utility>

#ifdef EXECUTE
#include "yices.h"
#include <cassert>
typedef std::pair<term_t, term_t> mr_pair;
#else
#include "yices_spec_defs.hpp"
#endif

namespace fuzz {
namespace lib_helper_funcs {

term_t
ctor_expr(int n)
{
    return yices_bvconst_uint32(BV_SIZE, n);
}

term_t
ite_lt_wrapper(term_t cond1, term_t cond2, term_t then_e, term_t else_e)
{
    return yices_ite(yices_bvlt_atom(cond1, cond2), then_e, else_e);
}

term_t
ite_gte_wrapper(term_t cond1, term_t cond2, term_t then_e, term_t else_e)
{
    return yices_ite(yices_bvge_atom(cond1, cond2), then_e, else_e);
}

} // namespace lib_helper_funcs
} // namespace fuzz

int
main(int argc, char** argv)
{
    yices_init();

    ctx_config_t* config = yices_new_config();
    yices_default_config_for_logic(config, "QF_BV");
    yices_set_config(config, "mode", "one-shot");
    context_t* ctx = yices_new_context(config);

    term_t x = yices_new_uninterpreted_term(yices_bv_type(BV_SIZE));
    term_t y = yices_new_uninterpreted_term(yices_bv_type(BV_SIZE));
    term_t z = yices_new_uninterpreted_term(yices_bv_type(BV_SIZE));

    fuzz::start();
    term_t lhs = fuzz::fuzz_new<term_t>();
    term_t rhs = fuzz::fuzz_new<term_t>();
    fuzz::output_var = std::make_pair(lhs, rhs);
    fuzz::end();

    assert(!yices_error_code());

    yices_assert_formula(ctx, yices_bvslt_atom(
        fuzz::output_var_get(0).first, fuzz::output_var_get(0).second));
    smt_status_t stat = yices_check_context(ctx, NULL);
    model_t* mdl = yices_get_model(ctx, true);

    fuzz::meta_test();

    yices_exit();
}

