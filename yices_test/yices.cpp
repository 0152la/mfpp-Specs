#define BV_SIZE 20
#define FV_COUNT 100

#include <cassert>
#include <string>

#ifdef EXECUTE
#include "yices.h"

typedef term_t bool_term;
typedef term_t bv_term;

namespace fuzz {
class FreeVars {
    public:
        bv_term vars[FV_COUNT];
};
}
#else
#include "yices_spec_defs.hpp"
#endif

int
main(int argc, char** argv)
{
    yices_init();

    ctx_config_t* config = yices_new_config();
    yices_default_config_for_logic(config, "QF_BV");
    yices_set_config(config, "mode", "one-shot");
    context_t* ctx = yices_new_context(config);

    fuzz::FreeVars fvs;
    for (size_t i = 0; i < FV_COUNT; ++i)
    {
        bv_term new_term = yices_new_uninterpreted_term(yices_bv_type(BV_SIZE));
        yices_set_term_name(new_term, ("x_" + std::to_string(i)).c_str());
        fvs.vars[i] = new_term;
    }

    fuzz::start();
    bv_term lhs = fuzz::fuzz_new<bv_term>();
    bv_term rhs = fuzz::fuzz_new<bv_term>();
    fuzz::output_var = yices_bvadd(lhs, rhs);
    fuzz::end();

    assert(!yices_error_code());

    fuzz::meta_test();

    yices_exit();
}

