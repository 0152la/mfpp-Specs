fuzz::set_term
mfr_set_term(fuzz::fuzz_context fctx)
{
    return isl::set::empty(fctx.space);
}

isl::set
mfr_isl_set(fuzz::fuzz_context fctx)
{
    return isl::set::empty(fctx.space);
}

isl::val
mfr_isl_val(fuzz::fuzz_context fctx)
{
    return isl::val(fctx.ctx, 1);
}

isl::point
mfr_isl_point(fuzz::fuzz_context fctx)
{
    return isl::point(fctx.space);
}
