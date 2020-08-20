#ifdef EXECUTE
#include "isl-noexceptions.h"
#include <cassert>
#else
#include "isl-noexceptions-cons.h"
#include "isl_spec_defs.hpp"
#include "spec_fuzz.hpp"
#endif
//#include "isl/options.h"

#define MAX_INT_EXP 64
#define SPACE_MIN 3
#define SPACE_MAX 6

namespace fuzz {
namespace lib_helper_funcs {

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

}

int
main(int argc, char** argv)
{
    //isl_ctx* ctx_ptr = isl_ctx_alloc();
    //isl_options_set_on_error(ctx_ptr, ISL_ON_ERROR_ABORT);
    //isl::ctx ctx = isl::ctx(ctx_ptr);
    isl::ctx ctx(isl_ctx_alloc());

    isl::space space(ctx, 0, fuzz::fuzz_rand<int, int>(SPACE_MIN, SPACE_MAX));
    isl::local_space local_space(space);
    fuzz::start();
    isl::pw_aff dim0 = isl::pw_aff::var_on_domain(local_space, isl::dim::set, 0);
    isl::pw_aff dim1 = isl::pw_aff::var_on_domain(local_space, isl::dim::set, 1);
    isl::pw_aff dim2 = isl::pw_aff::var_on_domain(local_space, isl::dim::set, 2);
    fuzz::output_var = isl::set::universe(space);
    fuzz::output_var = fuzz::output_var.intersect(fuzz::fuzz_new<isl::set>());
    fuzz::output_var = fuzz::output_var.intersect(fuzz::fuzz_new<isl::set>());
    fuzz::output_var = fuzz::output_var.intersect(fuzz::fuzz_new<isl::set>());
    fuzz::output_var = fuzz::output_var.intersect(fuzz::fuzz_new<isl::set>());
    fuzz::end();
    fuzz::meta_test();
}
