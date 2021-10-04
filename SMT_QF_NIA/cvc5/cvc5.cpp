#define FV_COUNT 100

#include "spec_fuzz.hpp"

#ifdef EXECUTE
#include "cvc5/cvc5.h"
#include "cvc5_fuzz_type_defs.hpp"
#include "meta_spec_cvc5_nl.hpp"
#else
#include "cvc5_spec_defs.hpp"
#endif

int
main(int argc, char** argv)
{
    cvc5::api::Solver slv;
    slv.setLogic("QF_NIA");
    slv.setOption("produce-models", "true");

    cvc5::api::Sort int_s = slv.getIntegerSort();
    fuzz::FreeVars fvs;
    for (size_t i = 0; i < FV_COUNT; ++i)
    {
        fuzz::int_term new_term = slv.mkConst(int_s, "x" + std::to_string(i));
        fvs.vars[i] = new_term;
    }

    fuzz::fuzz_context ctx(slv, fvs);

    fuzz::start();
    fuzz::output_var = fuzz::fuzz_new<fuzz::int_term>();
    fuzz::end();
    fuzz::meta_test();
}
