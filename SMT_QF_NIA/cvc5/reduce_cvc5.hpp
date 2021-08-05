fuzz::int_term
mfr_int_term(fuzz::fuzz_context ctx)
{
    return ctx.slv.mkInteger(1);
}

fuzz::bool_term
mfr_bool_term(fuzz::fuzz_context ctx)
{
    return ctx.slv.mkTrue();
}

fuzz::FreeVars
mfr_fvs(fuzz::fuzz_context ctx)
{
    return ctx.fvs;
}

