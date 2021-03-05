#define FV_COUNT 100

#include "spec_fuzz.hpp"

#ifdef EXECUTE
#include "cvc4/api/cvc4cpp.h"
#include "cvc4_fuzz_type_defs.hpp"
#else
#include "cvc4_spec_defs.hpp"
#endif

int
main(int argc, char** argv)
{
    CVC4::api::Solver slv;
    slv.setLogic("QF_NIA");
    slv.setOption("produce-models", "true");

    CVC4::api::Sort int_s = slv.getIntegerSort();
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
