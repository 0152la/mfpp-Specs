namespace metalib {

namespace checks {

    void
    check_sat_expr_maintained(context_t* ctx, mr_pair p, smt_status_t stat, model_t* mdl)
    {
        assert(!yices_error_code());
        yices_reset_context(ctx);
        term_t check = yices_bvslt_atom(p.first, p.second);
        yices_assert_formula(ctx, check);
        assert(yices_check_context(ctx, NULL) == stat);
        assert(yices_formula_true_in_model(mdl, check));
    }

} // namespace checks

namespace generators {

namespace fuzz_gen {

    term_t placeholder(context_t*, term_t);

    term_t
    fuzz_term(context_t* ctx, term_t t)
    {
        return fuzz::fuzz_new<term_t>();
    }

} // namespace fuzz_gen

namespace zero {

    term_t placeholder(context_t* ctx, term_t t);

    term_t
    get_zero(context_t* ctx, term_t t)
    {
        return yices_bvconst_uint32(BV_SIZE, 0);
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
    get_zero_by_fuzz_sub(context_t* ctx, term_t t)
    {
        term_t t_fuzz = generators::fuzz_gen::placeholder(ctx, t);
        return yices_bvsub(t_fuzz, t_fuzz);
    }

    term_t
    get_zero_by_mul(context_t* ctx, term_t t)
    {
        return yices_bvmul(t, generators::zero::placeholder(ctx, t));
    }

    term_t
    get_zero_by_shiftl(context_t* ctx, term_t t)
    {
        return yices_shift_left0(t, BV_SIZE);
    }

    term_t
    get_zero_by_shiftr(context_t* ctx, term_t t)
    {
        return yices_shift_right0(t, BV_SIZE);
    }

} // namespace zero

namespace one {

    term_t placeholder(context_t* ctx, term_t t);

    term_t
    get_one(context_t* ctx, term_t t)
    {
        return yices_bvconst_uint32(BV_SIZE, 1);
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
    get_one_by_div_fuzz(context_t* ctx, term_t t)
    {
        term_t fuzz = generators::fuzz_gen::placeholder(ctx, t);
        return yices_ite(
            yices_bvneq_atom(fuzz, generators::zero::placeholder(ctx, t)),
            yices_bvsdiv(fuzz, fuzz), generators::one::placeholder(ctx, fuzz));
    }

    term_t
    get_one_by_pw(context_t* ctx, term_t t)
    {
        term_t zero = generators::zero::placeholder(ctx, t);
        return yices_ite(
            yices_bvneq_atom(t, zero), yices_bvpower(t, zero),
            generators::one::placeholder(ctx, t));
    }

    term_t
    get_one_by_shiftl(context_t* ctx, term_t t)
    {
        return yices_bvneg(yices_shift_left1(t, BV_SIZE));
    }

    term_t
    get_one_by_shiftr(context_t* ctx, term_t t)
    {
        return yices_bvneg(yices_shift_right1(t, BV_SIZE));
    }

} // namespace one

} // namespace generators

namespace relations {

namespace identity_lhs {

    mr_pair placeholder(context_t*, mr_pair);

    mr_pair
    base_identity_lhs(context_t* ctx, mr_pair p)
    {
        return p;
    }

    mr_pair
    add_zero_lhs(context_t* ctx, mr_pair p)
    {
        return std::make_pair(
            yices_bvadd(
                relations::identity_lhs::placeholder(ctx, p).first,
                generators::zero::placeholder(ctx, p.first)),
            p.second);
    }

    mr_pair
    sum_zero_lhs(context_t* ctx, mr_pair p)
    {
        term_t sum[] = { relations::identity_lhs::placeholder(ctx, p).first,
            generators::zero::placeholder(ctx, p.first) };
        return std::make_pair(yices_bvsum(2, sum), p.second);
    }

    mr_pair
    sub_zero_lhs(context_t* ctx, mr_pair p)
    {
        return std::make_pair(
            yices_bvsub(
                relations::identity_lhs::placeholder(ctx, p).first,
                generators::zero::placeholder(ctx, p.first)),
            p.second);
    }

    mr_pair
    mul_one_lhs(context_t* ctx, mr_pair p)
    {
        return std::make_pair(
            yices_bvmul(
                relations::identity_lhs::placeholder(ctx, p).first,
                generators::one::placeholder(ctx, p.first)),
            p.second);
    }

    mr_pair
    prod_one_lhs(context_t* ctx, mr_pair p)
    {
        term_t prod[] = { relations::identity_lhs::placeholder(ctx, p).first,
            generators::one::placeholder(ctx, p.first) };
        return std::make_pair(yices_bvproduct(2, prod), p.second);
    }

    mr_pair
    double_negation_lhs(context_t* ctx, mr_pair p)
    {
        return std::make_pair(
            yices_bvneg(yices_bvneg(relations::identity_lhs::placeholder(ctx, p).first)),
            p.second);
    }

    mr_pair
    iden_by_rotate_same_lhs(context_t* ctx, mr_pair p)
    {
        unsigned int rotate_count = fuzz::fuzz_rand<unsigned int, unsigned int>(0, BV_SIZE - 1);
        return std::make_pair(
            yices_rotate_left(yices_rotate_left(
                relations::identity_lhs::placeholder(ctx, p).first, rotate_count),
                BV_SIZE - rotate_count),
            p.second);
    }

    mr_pair
    iden_by_rotate_opposite_lhs(context_t* ctx, mr_pair p)
    {
        unsigned int rotate_count = fuzz::fuzz_rand<unsigned int, unsigned int>(0, BV_SIZE - 1);
        return std::make_pair(
            yices_rotate_left(yices_rotate_right(
                relations::identity_lhs::placeholder(ctx, p).first, rotate_count),
                rotate_count),
            p.second);
    }

    mr_pair
    iden_by_extract_concat_lhs(context_t* ctx, mr_pair p)
    {
        unsigned int extract_count = fuzz::fuzz_rand<unsigned int, unsigned int>(0, BV_SIZE - 2);
        return std::make_pair(
            yices_bvconcat2(
                yices_bvextract(p.first, extract_count + 1, BV_SIZE - 1)),
                yices_bvextract(p.first, 0, extract_count),
            p.second);
    }

    mr_pair
    iden_by_ite_bitextract_lhs(context_t* ctx, mr_pair p)
    {
        unsigned int extract_count = fuzz::fuzz_rand<unsigned int, unsigned int>(0, BV_SIZE - 1);
        return std::make_pair(
            yices_ite(yices_bitextract(p.first, extract_count),
                relations::identity_lhs::placeholder(ctx, p).first,
                relations::identity_lhs::placeholder(ctx, p).first),
            p.second);
    }

    mr_pair
    iden_by_false_ite_lhs(context_t* ctx, mr_pair p)
    {
        term_t fuzz = generators::fuzz_gen::placeholder(ctx, p.first);
        return std::make_pair(
            yices_ite(yices_eq(p.first, fuzz), fuzz, p.first),
            p.second);
    }

} // namespace identity_lhs

namespace identity_rhs {

    mr_pair placeholder(context_t*, mr_pair);

    mr_pair
    base_identity_rhs(context_t* ctx, mr_pair p)
    {
        return p;
    }

    mr_pair
    add_zero_rhs(context_t* ctx, mr_pair p)
    {
        return std::make_pair(
            p.first,
            yices_bvadd(
                relations::identity_rhs::placeholder(ctx, p).second,
                generators::zero::placeholder(ctx, p.second)));
    }

    mr_pair
    sum_zero_rhs(context_t* ctx, mr_pair p)
    {
        term_t sum[] = { p.second, generators::zero::placeholder(ctx, p.second) };
        return std::make_pair(p.first, yices_bvsum(2, sum));
    }

    mr_pair
    sub_zero_rhs(context_t* ctx, mr_pair p)
    {
        return std::make_pair(
            p.first,
            yices_bvsub(
                relations::identity_rhs::placeholder(ctx, p).second,
                generators::zero::placeholder(ctx, p.second)));
    }

    mr_pair
    mul_one_rhs(context_t* ctx, mr_pair p)
    {
        return std::make_pair(
            p.first,
            yices_bvmul(
                relations::identity_rhs::placeholder(ctx, p).second,
                generators::one::placeholder(ctx, p.second)));
    }

    mr_pair
    prod_one_rhs(context_t* ctx, mr_pair p)
    {
        term_t prod[] = { p.second, generators::one::placeholder(ctx, p.second) };
        return std::make_pair(p.first, yices_bvproduct(2, prod));
    }

    mr_pair
    double_negation_rhs(context_t* ctx, mr_pair p)
    {
        return std::make_pair(
            p.first,
            yices_bvneg(yices_bvneg(relations::identity_rhs::placeholder(ctx, p).second)));
    }

    mr_pair
    iden_by_rotate_same_rhs(context_t* ctx, mr_pair p)
    {
        unsigned int rotate_count = fuzz::fuzz_rand<unsigned int, unsigned int>(0, BV_SIZE - 1);
        return std::make_pair(
            p.first,
            yices_rotate_left(yices_rotate_left(p.second, rotate_count), BV_SIZE - rotate_count));
    }

    mr_pair
    iden_by_rotate_opposite_rhs(context_t* ctx, mr_pair p)
    {
        unsigned int rotate_count = fuzz::fuzz_rand<unsigned int, unsigned int>(0, BV_SIZE - 1);
        return std::make_pair(
            p.first,
            yices_rotate_left(yices_rotate_right(p.second, rotate_count), rotate_count));
    }

    mr_pair
    iden_by_extract_concat_rhs(context_t* ctx, mr_pair p)
    {
        unsigned int extract_count = fuzz::fuzz_rand<unsigned int, unsigned int>(0, BV_SIZE - 2);
        return std::make_pair(
            p.first,
            yices_bvconcat2(
                yices_bvextract(p.second, extract_count + 1, BV_SIZE - 1)));
                yices_bvextract(p.second, 0, extract_count),
    }

    mr_pair
    iden_by_ite_bitextract_rhs(context_t* ctx, mr_pair p)
    {
        unsigned int extract_count = fuzz::fuzz_rand<unsigned int, unsigned int>(0, BV_SIZE - 1);
        return std::make_pair(
            p.first,
            yices_ite(yices_bitextract(p.second, extract_count),
                relations::identity_rhs::placeholder(ctx, p).second,
                relations::identity_rhs::placeholder(ctx, p).second));
    }

    mr_pair
    iden_by_false_ite_rhs(context_t* ctx, mr_pair p)
    {
        term_t fuzz = generators::fuzz_gen::placeholder(ctx, p.second);
        return std::make_pair(
            p.first,
            yices_ite(yices_eq(p.second, fuzz), fuzz, p.second));
    }

} // namespace identity_rhs

//namespace sub { term_t placeholder(mr_pair, term_t); }

//namespace add {

    //term_t placeholder(mr_pair, term_t);

    //term_t
    //base_add(mr_pair p, term_t t)
    //{
        //return std::make_pair(yices_bvadd(p.first, t), yices_bvadd(p.second, t));
    //}

    //term_t
    //add_by_sum(mr_pair p, term_t t)
    //{
        //term_t fst_sum[] = { p.first, t };
        //term_t snd_sum[] = { p.second, t };
        //return std::make_pair(yices_bv_sum(2, fst_sum), yices_bv_sum(2, snd_sum));
    //}

    //term_t
    //add_by_sub_neg(mr_pair p, term_t t)
    //{
        //return relations::sub::placeholder(p, yices_bvneg(t));
    //}

//} // namespace add

//namespace sub {
    //term_t
    //base_sub(mr_pair p, term_t)
    //{
        //return std::make_pair(yices_bvsub(p.first, t), yices_bvsub(p.second, t));
    //}

    //term_t
    //sub_by_sum_neg(mr_pair p, term_t t)
    //{
        //term_t fst_sum[] = { p.first, yices_bvneg(t2) };
        //term_t snd_sum[] = { p.second, yices_bvneg(t2) };
        //return std::make_pair(yices_bv_sum(2, fst_sum), yices_bv_sum(2, snd_sum));
    //}

    //term_t
    //sub_by_add_neg(mr_pair p, term_t t)
    //{
        //return relations::add::placeholder(p, yices_bvneg(t));
    //}

//} // namespace sub

//namespace mul {

    //term_t placeholder(mr_pair, term_t);

    //term_t
    //base_mul(mr_pair p, term_t t)
    //{
        //return std::make_pair(yices_bvmul(p.first, t) yices_bvmul(p.second, t));
    //}

    //term_t
    //mul_by_product(mr_pair p, term_t t)
    //{
        //term_t fst_prod[] = { p.first, t };
        //term_t snd_prod[] = { p.second, t };
        //return std::make_pair(yices_bvproduct(2, fst_prod), yices_bvproduct(2, snd_prod));
    //}

//} // namespace mul



} // namespace relations

} // namespace metalib
