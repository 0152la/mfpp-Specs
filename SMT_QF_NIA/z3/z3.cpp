#define FV_COUNT 100

#include "z3++.h"
#include <vector>

static size_t check_count = 0;

#ifdef EXECUTE
#include <cassert>
namespace fuzz {
    typedef z3::expr bool_term;
    typedef z3::expr int_term;
    class FreeVars {
      public:
        std::vector<fuzz::int_term> vars;
    };
    class fuzz_context
    {
        public:
            z3::context& ctx;
            fuzz::FreeVars& fvs;

            fuzz_context(z3::context& _ctx, fuzz::FreeVars& _fvs) :
                ctx(_ctx), fvs(_fvs) {} ;

            z3::expr simplify(z3::expr& e)
            {
                return e.simplify();
            }
    };
}
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
