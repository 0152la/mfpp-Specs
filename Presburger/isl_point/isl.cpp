#define MAX_INT_EXP 64
#include <cassert>

#include "spec_fuzz.hpp"

#ifdef EXECUTE
#include "isl-noexceptions.h"
#include "isl_fuzz_type_defs.hpp"
#include "meta_spec_isl.hpp"
#else
#include "isl-noexceptions-point.h"
#include "isl_spec_defs.hpp"
#endif

#define SPACE_MIN 3
#define SPACE_MAX 6

int
main(int argc, char** argv)
{
    //isl_ctx* ctx_ptr = isl_ctx_alloc();
    //isl_options_set_on_error(ctx_ptr, ISL_ON_ERROR_ABORT);
    //isl::ctx ctx = isl::ctx(ctx_ptr);
    isl::ctx ctx = isl::ctx(isl_ctx_alloc());
    isl::space space(ctx, 0, fuzz::fuzz_rand<int, int>(SPACE_MIN, SPACE_MAX));
    isl::local_space local_space(space);

    fuzz::fuzz_context fctx(ctx, space);

    fuzz::start();
    fuzz::output_var = isl::set::empty(space);
    isl::point tmp_p = fuzz::fuzz_new<isl::point>();
    fuzz::output_var = fuzz::output_var.unite(isl::set(tmp_p));
    fuzz::output_var = fuzz::output_var.unite(fuzz::fuzz_new<isl::set>());
    fuzz::output_var = fuzz::output_var.unite(fuzz::fuzz_new<isl::set>());
    fuzz::output_var = fuzz::output_var.unite(fuzz::fuzz_new<isl::set>());
    fuzz::output_var = fuzz::output_var.unite(fuzz::fuzz_new<isl::set>());
    fuzz::output_var = fuzz::output_var.convex_hull();
    fuzz::output_var = fuzz::output_var.project_out(isl::dim::set, 0, SPACE_MIN / 2);
    fuzz::end();
    assert(isl_ctx_last_error(ctx.get()) == isl_error_none);

    fuzz::meta_test();
    assert(isl_ctx_last_error(ctx.get()) == isl_error_none);
}
