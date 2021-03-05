#define FV_COUNT 100

#include "spec_fuzz.hpp"

#include <vector>

#ifdef EXECUTE
#include "z3++.h"
#include "z3_fuzz_type_defs.hpp"
#else
#include "z3_spec_defs.hpp"
#endif

int
main(int argc, char** argv)
{
    z3::context ctx;
    fuzz::FreeVars fvs;
    for (size_t i = 0; i < FV_COUNT; ++i)
    {
        std::string new_var_name = "x" + std::to_string(i);
        fuzz::int_term new_expr = ctx.int_const(new_var_name.c_str());
        fvs.vars.push_back(new_expr);
    }

    fuzz::fuzz_context fctx(ctx, fvs);

    fuzz::start();
    fuzz::output_var = fuzz::fuzz_new<fuzz::int_term>();
    fuzz::end();
    assert(ctx.check_error() == Z3_OK);
    fuzz::meta_test();
}
