fuzz::int_term
mfr_int_term(fuzz::fuzz_context ctx)
{
    return ctx.ctx.int_val(1);
}

fuzz::bool_term
mfr_bool_term(fuzz::fuzz_context ctx)
{
    return ctx.ctx.bool_val(true);
}

