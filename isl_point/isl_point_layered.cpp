#ifdef TEST
#include "isl-noexceptions.h"
#include <cassert>
#else
#include "spec_fuzz_point.hpp"
#endif

#define MAX_INT_EXP 64

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
    isl::ctx ctx = isl::ctx(isl_ctx_alloc());
    isl::space space(ctx, 0, 3);
    isl::local_space local_space(space);
    fuzz::start();
    isl::pw_aff dim0 = isl::pw_aff::var_on_domain(local_space, isl::dim::set, 0);
    isl::pw_aff dim1 = isl::pw_aff::var_on_domain(local_space, isl::dim::set, 1);
    isl::pw_aff dim2 = isl::pw_aff::var_on_domain(local_space, isl::dim::set, 2);
    fuzz::output_var = isl::set::empty(space);
    // Unite set 1
    isl::set tmp = isl::set::empty(space);
    tmp = fuzz::fuzz_new<isl::set>();
    tmp = tmp.unite(fuzz::fuzz_new<isl::set>());
    tmp = tmp.unite(fuzz::fuzz_new<isl::set>());
    tmp = tmp.unite(fuzz::fuzz_new<isl::set>());
    tmp = tmp.unite(fuzz::fuzz_new<isl::set>());
    fuzz::output_var = tmp.convex_hull();
    // Unite set 2
    tmp = fuzz::fuzz_new<isl::set>();
    tmp = tmp.unite(fuzz::fuzz_new<isl::set>());
    tmp = tmp.unite(fuzz::fuzz_new<isl::set>());
    tmp = tmp.unite(fuzz::fuzz_new<isl::set>());
    tmp = tmp.unite(fuzz::fuzz_new<isl::set>());
    tmp = tmp.convex_hull();
    fuzz::output_var = fuzz::output_var.unite(tmp);
    // Unite set 3
    tmp = fuzz::fuzz_new<isl::set>();
    tmp = tmp.unite(fuzz::fuzz_new<isl::set>());
    tmp = tmp.unite(fuzz::fuzz_new<isl::set>());
    tmp = tmp.unite(fuzz::fuzz_new<isl::set>());
    tmp = tmp.unite(fuzz::fuzz_new<isl::set>());
    tmp = tmp.convex_hull();
    fuzz::output_var = fuzz::output_var.unite(tmp);
    fuzz::end();
    assert(isl_ctx_last_error(ctx.get()) == isl_error_none);
    fuzz::meta_test();
}
