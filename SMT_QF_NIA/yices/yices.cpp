#define BV_SIZE 20
#define FV_COUNT 100

#include <cassert>
#include <string>

#ifdef EXECUTE
#include "yices.h"


namespace fuzz {
typedef term_t bool_term;
typedef term_t int_term;
class FreeVars {
    public:
        int_term vars[FV_COUNT];
};
class fuzz_context
{
    public:
        fuzz::FreeVars& fvs;

        fuzz_context(fuzz::FreeVars& _fvs) : fvs(_fvs) {} ;

        term_t simplify(term_t t)
        {
            return t;
        }
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
    yices_set_config(config, "mode", "push-pop");
    context_t* ctx = yices_new_context(config);

    fuzz::FreeVars fvs;
    for (size_t i = 0; i < FV_COUNT; ++i)
    {
        fuzz::int_term new_term = yices_new_uninterpreted_term(yices_int_type());
        yices_set_term_name(new_term, ("x_" + std::to_string(i)).c_str());
        fvs.vars[i] = new_term;
    }

    fuzz::fuzz_context ctx(fvs);

    fuzz::start();
    fuzz::int_term i_var = fuzz::fuzz_new<fuzz::int_term>();
    fuzz::end();

    assert(!yices_error_code());

    fuzz::meta_test();

    yices_exit();
}

