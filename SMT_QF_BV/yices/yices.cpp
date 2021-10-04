#define BV_SIZE 20
#define FV_COUNT 100

#include "spec_fuzz.hpp"

#ifdef EXECUTE
#include "yices.h"
#include "yices_fuzz_type_defs.hpp"
#include "meta_spec_yices.hpp"
#else
#include "yices_spec_defs.hpp"
#endif

int
main(int argc, char** argv)
{
    yices_init();

    ctx_config_t* config = yices_new_config();
    yices_default_config_for_logic(config, "QF_BV");
    yices_set_config(config, "mode", "push-pop");
    context_t* ctx = yices_new_context(config);

    fuzz::FreeVars fvs;
    for (size_t i = 0; i < FV_COUNT; ++i)
    {
        fuzz::bv_term new_term = yices_new_uninterpreted_term(yices_bv_type(BV_SIZE));
        yices_set_term_name(new_term, ("x_" + std::to_string(i)).c_str());
        fvs.vars[i] = new_term;
    }

    fuzz::fuzz_context fctx(fvs);

    fuzz::start();
    fuzz::bv_term lhs = fuzz::fuzz_new<fuzz::bv_term>();
    fuzz::bv_term rhs = fuzz::fuzz_new<fuzz::bv_term>();
    fuzz::output_var = yices_bvadd(lhs, rhs);
    fuzz::end();

    assert(!yices_error_code());

    fuzz::meta_test();

    yices_exit();
}

