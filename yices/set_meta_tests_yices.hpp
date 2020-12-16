namespace metalib {

namespace checks {

    void
    check_sat_expr_maintained(context_t* ctx, term_t t1, term_t t2)
    {
        yices_reset_context(ctx);
        yices_assert_formula(ctx, yices_bveq_atom(t1, t2));
        assert(yices_check_context(ctx, NULL) == STATUS_SAT);
    }

} // namespace checks

namespace generators {


namespace zero {

    term_t placeholder(context_t* ctx, term_t t);

    term_t
    get_zero(context_t* ctx, term_t t)
    {
        return yices_bvconst_uint32(yices_bv_type(BV_SIZE), 0);
    }

    term_t
    get_zero_by_call(context_t* ctx, term_t t)
    {
        return yices_bvconst_zero(BV_SIZE);
    }


    term_t
    get_zero_by_sub(context_t* ctx, term_t t)
    {
        return yices_bvsub(t, t);
    }

    term_t
    get_zero_by_mul(context_t* ctx, term_t t)
    {
        return yices_bvmul(t, generators::zero::placeholder(ctx, t));
    }

    term_t
    get_zero_by_fuzz_sub(context_t* ctx, term_t t)
    {
        term_t t_fuzz = fuzz::fuzz_new<term_t>();
        return yices_bvsub(t_fuzz, t_fuzz);
    }

    term_t
    get_zero_by_shift_left(context_t* ctx, term_t t)
    {
        return yices_shift_left0(t, BV_SIZE);
    }


} // namespace zero

namespace one {

    term_t placeholder(context_t* ctx, term_t t);

    term_t
    get_one(context_t* ctx, term_t t)
    {
        return yices_bvconst_uint32(yices_bv_type(BV_SIZE), 1);
    }

    term_t
    get_one_by_call(context_t* ctx, term_t t)
    {
        return yices_bvconst_one(BV_SIZE);
    }

    term_t
    get_one_by_div(context_t* ctx, term_t t)
    {
        return yices_ite(
            yices_bvneq_atom(t, generators::zero::placeholder(ctx, t)),
            yices_bvsdiv(t, t), generators::one::placeholder(ctx, t));
    }

    term_t
    get_one_by_pw(context_t* ctx, term_t t)
    {
        term_t zero = generators::zero::placeholder(ctx, t);
        return yices_ite(
            yices_bvneq_atom(t, zero), yices_power(t, zero),
            generators::one::placeholder(ctx, t));
    }

} // namespace one

} // namespace generators

namespace relations {

namespace identity {

    term_t placeholder(context_t*, term_t);

    term_t
    base_identity(context_t* ctx, term_t t)
    {
        return t;
    }

    term_t
    add_zero(context_t* ctx, term_t t)
    {
        return yices_bvadd(relations::identity::placeholder(ctx, t), generators::zero::placeholder(ctx, t));
    }

    term_t
    sub_zero(context_t* ctx, term_t t)
    {
        return yices_bvsub(relations::identity::placeholder(ctx, t), generators::zero::placeholder(ctx, t));
    }

    term_t
    mul_one(context_t* ctx, term_t t)
    {
        return yices_bvmul(relations::identity::placeholder(ctx, t), generators::one::placeholder(ctx, t));
    }

    term_t
    double_negation(context_t* ctx, term_t t)
    {
        return yices_neg(yices_neg(relations::identity::placeholder(ctx, t)));
    }

} // namespace identity

namespace sub { term_t placeholder(context_t*, term_t, term_t); }

namespace add {

    term_t placeholder(context_t*, term_t, term_t);

    term_t
    base_add(context_t* ctx, term_t t1, term_t t2)
    {
        return yices_bvadd(t1, t2);
    }

    term_t
    commute_add(context_t* ctx, term_t t1, term_t t2)
    {
        return relations::add::placeholder(ctx, t2, t1);
    }

    term_t
    add_by_sum(context_t* ctx, term_t t1, term_t t2)
    {
        term_t sum_ts[] = { t1, t2 };
        return yices_bvsum(2, sum_ts);
    }

    term_t
    add_by_sub_neg(context_t* ctx, term_t t1, term_t t2)
    {
        return relations::sub::placeholder(ctx, t1, yices_bvneg(t2));
    }

} // namespace add

namespace sub {
    term_t
    base_add(context_t* ctx, term_t t1, term_t t2)
    {
        return yices_bvsub(t1, t2);
    }

    term_t
    sub_by_sum_neg(context_t* ctx, term_t t1, term_t t2)
    {
        term_t sum_ts[] = { t1, yices_bvneg(t2) };
        return yices_bvsum(2, sum_ts);
    }

    term_t
    sub_by_add_neg(context_t* ctx, term_t t1, term_t t2)
    {
        return relations::add::placeholder(ctx, t1, yices_bvneg(t2));
    }

} // namespace sub

namespace mul {

    term_t placeholder(context_t*, term_t, term_t);

    term_t
    base_mul(context_t* ctx, term_t t1, term_t t2)
    {
        return yices_bvmul(t1, t2);
    }

    term_t
    commute_mul(context_t* ctx, term_t t1, term_t t2)
    {
        return relations::mul::placeholder(ctx, t2, t1);
    }

    term_t
    add_by_sum(context_t* ctx, term_t t1, term_t t2)
    {
        term_t product_ts[] = { t1, t2 };
        return yices_bvproduct(2, product_ts);
    }

} // namespace mul



} // namespace relations

} // namespace metalib
