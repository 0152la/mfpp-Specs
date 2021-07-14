#ifndef _ISL_SPEC_DEFS_HPP
#define _ISL_SPEC_DEFS_HPP

#define MAX_INT_EXP 64

#define VAL_MIN_VAL -20
#define VAL_MAX_VAL 20

#include "isl-noexceptions-point.h"
#include "isl_fuzz_type_defs.hpp"

namespace fuzz
{
    fuzz::set_term output_var;
} // namespace fuzz

#include "meta_spec_isl.hpp"
#include "spec.hpp"

namespace fuzz {
namespace lib_helper_funcs {

/*******************************************************************************
 * CONSTRUCTORS
 ******************************************************************************/

isl::point
ctor_point(fuzz::fuzz_context fctx)
{
    isl::point p(fctx.space);
    isl::val v1(fctx.ctx, fuzz::fuzz_rand<int, int>(VAL_MIN_VAL, VAL_MAX_VAL));
    p = p.set_coordinate_val(isl::dim::set, 0, v1.trunc());
    isl::val v2(fctx.ctx, fuzz::fuzz_rand<int, int>(VAL_MIN_VAL, VAL_MAX_VAL));
    p = p.set_coordinate_val(isl::dim::set, 1, v2.trunc());
    isl::val v3(fctx.ctx, fuzz::fuzz_rand<int, int>(VAL_MIN_VAL, VAL_MAX_VAL));
    return p.set_coordinate_val(isl::dim::set, 2, v3.trunc());
}

/*******************************************************************************
 * ISL::POINT OPERATION WRAPPERS
 ******************************************************************************/

isl::point
set_coordinate_val(isl::point p, isl::val v)
{
    int i = fuzz::fuzz_rand<int>(0,2);
    return p.set_coordinate_val(isl::dim::set, i, v.trunc());
}

isl::point
ctor_point_with_val(isl::space p_space, isl::val v1, isl::val v2, isl::val v3)
{
    isl::point p(p_space);
    p = p.set_coordinate_val(isl::dim::set, 0, v1.trunc());
    p = p.set_coordinate_val(isl::dim::set, 1, v2.trunc());
    return p.set_coordinate_val(isl::dim::set, 2, v3.trunc());
}

/*******************************************************************************
 * ISL::VAL OPERATION WRAPPERS
 ******************************************************************************/

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

} // namespace lib_helper_funcs
} // namespace fuzz


#endif // _ISL_SPEC_DEFS_HPP
