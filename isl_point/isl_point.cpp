#include <cassert>

#ifdef EXECUTE
#include "isl-noexceptions.h"
#else
#include "isl-noexceptions-point.h"
#include "isl_spec_defs.hpp"
#include "spec_fuzz.hpp"
#endif
//#include "isl/options.h"

#define MAX_INT_EXP 64
#define SPACE_MIN 3
#define SPACE_MAX 6

namespace fuzz {
namespace lib_helper_funcs {

isl::point
set_coordinate_val(isl::point p, isl::val v)
{
    int i = fuzz::fuzz_rand<int>(0,2);
    return p.set_coordinate_val(isl::dim::set, i, v.trunc());
}

isl::val
two_exp(isl::val v)
{
    v = v.trunc().mod(isl::val(v.get_ctx(), MAX_INT_EXP));
    return v.trunc().two_exp();
}

isl::val
inv(isl::val v)
{
    return v.is_zero() ? isl::val::zero(v.get_ctx()) : v.inv();
}

isl::point
ctor_point(isl::space p_space, isl::val v1, isl::val v2, isl::val v3)
{
    isl::point p(p_space);
    p = p.set_coordinate_val(isl::dim::set, 0, v1.trunc());
    p = p.set_coordinate_val(isl::dim::set, 1, v2.trunc());
    return p.set_coordinate_val(isl::dim::set, 2, v3.trunc());
}

} // namespace lib_helper_funcs
} // namespace fuzz

int
main(int argc, char** argv)
{
    //isl_ctx* ctx_ptr = isl_ctx_alloc();
    //isl_options_set_on_error(ctx_ptr, ISL_ON_ERROR_ABORT);
    //isl::ctx ctx = isl::ctx(ctx_ptr);
    isl::ctx ctx = isl::ctx(isl_ctx_alloc());

    isl::space space(ctx, 0, fuzz::fuzz_rand<int, int>(SPACE_MIN, SPACE_MAX));
    isl::local_space local_space(space);
    fuzz::start();
    fuzz::output_var = isl::set::empty(space);
    isl::point tmp_p = fuzz::fuzz_new<isl::point>();
    fuzz::output_var = fuzz::output_var.unite(isl::set(tmp_p));
    fuzz::output_var = fuzz::output_var.unite(fuzz::fuzz_new<isl::set>());
    fuzz::output_var = fuzz::output_var.unite(fuzz::fuzz_new<isl::set>());
    fuzz::output_var = fuzz::output_var.unite(fuzz::fuzz_new<isl::set>());
    fuzz::output_var = fuzz::output_var.unite(fuzz::fuzz_new<isl::set>());
    fuzz::output_var = fuzz::output_var.convex_hull();
    //fuzz::output_var = fuzz::output_var.project_out(isl::dim::set, 0, SPACE_MIN / 2);
    fuzz::end();
    assert(isl_ctx_last_error(ctx.get()) == isl_error_none);
    fuzz::meta_test();
    assert(isl_ctx_last_error(ctx.get()) == isl_error_none);
}
