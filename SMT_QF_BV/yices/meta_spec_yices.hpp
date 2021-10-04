namespace metalib {

namespace checks {

    void
    check_expr_eq(context_t* ctx, fuzz::FreeVars& fvs, fuzz::bv_term t1, fuzz::bv_term t2)
    {
        yices_reset_context(ctx);
        yices_assert_formula(ctx, yices_eq(t1, t2));
        fuzz::bv_term f_arr[] = { t1, t2 };
        yices_assert_formula(ctx, yices_not(yices_distinct(2, f_arr)));
        assert(yices_check_context(ctx, NULL) == STATUS_SAT);
        assert(!yices_error_code());
    }

    void
    check_expr_equal_zero_sat(context_t* ctx, fuzz::FreeVars& fvs, fuzz::bv_term t1, fuzz::bv_term t2)
    {
        yices_reset_context(ctx);
        fuzz::bv_term zero = yices_bvconst_zero(BV_SIZE);
        fuzz::bool_term check_zero_t1 = yices_bveq_atom(zero, t1);
        fuzz::bool_term check_zero_t2 = yices_bveq_atom(zero, t2);
        yices_push(ctx);
        yices_assert_formula(ctx, check_zero_t1);
        smt_status_t stat_1 = yices_check_context(ctx, NULL);
        if (stat_1 == STATUS_SAT)
        {
            model_t* mdl = yices_get_model(ctx, true);
            fuzz::bool_term val;
            assert(yices_get_bool_value(mdl, check_zero_t2, &val) == 0);
            assert(val);
        }
        else if (stat_1 == STATUS_UNSAT)
        {
            yices_pop(ctx);
            yices_push(ctx);
            yices_assert_formula(ctx, check_zero_t2);
            assert(yices_check_context(ctx, NULL) != STATUS_SAT);
        }
        yices_pop(ctx);
        assert(!yices_error_code());
        yices_push(ctx);
        yices_assert_formula(ctx, check_zero_t2);
        smt_status_t stat_2 = yices_check_context(ctx, NULL);
        if (stat_2 == STATUS_SAT)
        {
            model_t* mdl = yices_get_model(ctx, true);
            fuzz::bool_term val;
            assert(yices_get_bool_value(mdl, check_zero_t1, &val) == 0);
            assert(val);
        }
        else if (stat_2 == STATUS_UNSAT)
        {
            yices_pop(ctx);
            yices_push(ctx);
            yices_assert_formula(ctx, check_zero_t1);
            assert(yices_check_context(ctx, NULL) != STATUS_SAT);
        }
        yices_pop(ctx);
        assert(!yices_error_code());

    }

} // namespace checks

namespace generators {
    namespace zero {
        fuzz::bv_term base(fuzz::fuzz_context ctx, fuzz::bv_term t) {
            return yices_bvconst_zero(BV_SIZE); }
        fuzz::bv_term base2(fuzz::fuzz_context ctx, fuzz::bv_term t) {
            return yices_bvconst_int32(BV_SIZE, 0); }
    }
    namespace one {
        fuzz::bv_term base(fuzz::fuzz_context ctx, fuzz::bv_term t) {
            return yices_bvconst_one(BV_SIZE); }
        fuzz::bv_term base2(fuzz::fuzz_context ctx, fuzz::bv_term t) {
            return yices_bvconst_int32(BV_SIZE, 1); }
    }
    namespace true_bool {
        fuzz::bool_term base(fuzz::fuzz_context ctx, fuzz::bool_term t) {
            return yices_true(); }
    }
    namespace false_bool {
        fuzz::bool_term base(fuzz::fuzz_context ctx, fuzz::bool_term t) {
            return yices_false(); }
    }
    namespace iden_bool {
        fuzz::bool_term base(fuzz::fuzz_context ctx, fuzz::bool_term t) {
            return t; }
    }
    namespace not_bool {
        fuzz::bool_term base(fuzz::fuzz_context ctx, fuzz::bool_term t) {
            return yices_not(t); }
    }
    namespace and_bool {
        fuzz::bool_term base(fuzz::fuzz_context ctx, fuzz::bool_term t1, fuzz::bool_term t2) {
            return yices_and2(t1, t2); }
    }
    namespace or_bool {
        fuzz::bool_term base(fuzz::fuzz_context ctx, fuzz::bool_term t1, fuzz::bool_term t2) {
            return yices_or2(t1, t2); }
    }
    namespace xor_bool {
        fuzz::bool_term base(fuzz::fuzz_context ctx, fuzz::bool_term t1, fuzz::bool_term t2) {
            return yices_xor2(t1, t2); }
    }
    namespace equal_bool {
        fuzz::bool_term base(fuzz::fuzz_context ctx, fuzz::bool_term t1, fuzz::bool_term t2) {
            return yices_eq(t1, t2); }
    }
    namespace equal_bv {
        fuzz::bool_term base(fuzz::fuzz_context ctx, fuzz::bv_term t1, fuzz::bv_term t2) {
            return yices_bveq_atom(t1, t2); }
    }
    namespace extract_bv {
        fuzz::bv_term base(fuzz::fuzz_context ctx, fuzz::bv_term t, size_t start, size_t end) {
            return yices_bvextract(t, start, end); }
    }
    namespace extract_bit_bv {
        fuzz::bv_term base(fuzz::fuzz_context ctx, fuzz::bv_term t, size_t bit) {
            return yices_bitextract(t, bit); }
    }
    namespace concat_bv {
        fuzz::bv_term base(fuzz::fuzz_context ctx, fuzz::bv_term t1, fuzz::bv_term t2) {
            return yices_bvconcat2(t1, t2); }
    }
    namespace ite_bv_term_cond {
        fuzz::bv_term base(fuzz::fuzz_context ctx, fuzz::bool_term b, fuzz::bv_term t, fuzz::bv_term e) {
            return yices_ite(b, t, e); }
    }
    namespace ite_bool {
        fuzz::bool_term base(fuzz::fuzz_context ctx, fuzz::bool_term c, fuzz::bool_term t, fuzz::bool_term e) {
            return yices_ite(c, t, e); }
    }
    namespace lt {
        fuzz::bool_term base(fuzz::fuzz_context ctx, fuzz::bv_term t1, fuzz::bv_term t2) {
            return yices_bvlt_atom(t1, t2); }
    }
    namespace gt {
        fuzz::bool_term base(fuzz::fuzz_context ctx, fuzz::bv_term t1, fuzz::bv_term t2) {
            return yices_bvgt_atom(t1, t2); }
    }
    namespace leq {
        fuzz::bool_term base(fuzz::fuzz_context ctx, fuzz::bv_term t1, fuzz::bv_term t2) {
            return yices_bvle_atom(t1, t2); }
    }
    namespace geq {
        fuzz::bool_term base(fuzz::fuzz_context ctx, fuzz::bv_term t1, fuzz::bv_term t2) {
            return yices_bvge_atom(t1, t2); }
    }
    namespace slt {
        fuzz::bool_term base(fuzz::fuzz_context ctx, fuzz::bv_term t1, fuzz::bv_term t2) {
            return yices_bvslt_atom(t1, t2); }
    }
    namespace sgt {
        fuzz::bool_term base(fuzz::fuzz_context ctx, fuzz::bv_term t1, fuzz::bv_term t2) {
            return yices_bvsgt_atom(t1, t2); }
    }
} // namespace generators

namespace relations {
    namespace identity {
        fuzz::bv_term base(fuzz::fuzz_context ctx, fuzz::bv_term t) {
            return t; }
    }
    namespace add {
        fuzz::bv_term base(fuzz::fuzz_context ctx, fuzz::bv_term t1, fuzz::bv_term t2) {
            return yices_bvadd(t1, t2); }
    }
    namespace sub {
        fuzz::bv_term base(fuzz::fuzz_context ctx, fuzz::bv_term t1, fuzz::bv_term t2) {
            return yices_bvsub(t1, t2); }
    }
    namespace mul {
        fuzz::bv_term base(fuzz::fuzz_context ctx, fuzz::bv_term t1, fuzz::bv_term t2) {
            return yices_bvmul(t1, t2); }
    }
    namespace division {
        fuzz::bv_term base(fuzz::fuzz_context ctx, fuzz::bv_term t1, fuzz::bv_term t2) {
            return yices_ite(yices_bveq_atom(t2, yices_bvconst_zero(BV_SIZE)), t1, yices_bvdiv(t1, t2)); }
    }
    namespace modulo {
        fuzz::bv_term base(fuzz::fuzz_context ctx, fuzz::bv_term t1, fuzz::bv_term t2) {
            return yices_ite(yices_bveq_atom(t2, yices_bvconst_zero(BV_SIZE)), t1, yices_bvrem(t1, t2)); }
    }
    namespace abs_bv {
        fuzz::bv_term base(fuzz::fuzz_context ctx, fuzz::bv_term t) {
            return yices_ite(yices_bvslt_atom(t, yices_bvconst_zero(BV_SIZE)), yices_bvneg(t), t); }
    }
    namespace neg_bv {
        fuzz::bv_term base(fuzz::fuzz_context ctx, fuzz::bv_term t) {
            return yices_bvneg(t); }
    }
    namespace not_bv {
        fuzz::bv_term base(fuzz::fuzz_context ctx, fuzz::bv_term t) {
            return yices_bvnot(t); }
    }
    namespace or_bv {
        fuzz::bv_term base(fuzz::fuzz_context ctx, fuzz::bv_term t1, fuzz::bv_term t2) {
            return yices_bvor2(t1, t2); }
    }
    namespace and_bv {
        fuzz::bv_term base(fuzz::fuzz_context ctx, fuzz::bv_term t1, fuzz::bv_term t2) {
            return yices_bvand2(t1, t2); }
    }
    namespace xor_bv {
        fuzz::bv_term base(fuzz::fuzz_context ctx, fuzz::bv_term t1, fuzz::bv_term t2) {
            return yices_bvxor2(t1, t2); }
    }
    namespace rotate_left_int {
        fuzz::bv_term base(fuzz::fuzz_context ctx, fuzz::bv_term t, size_t r) {
            return yices_rotate_left(t, r % (BV_SIZE + 1)); }
    }
    namespace rotate_right_int {
        fuzz::bv_term base(fuzz::fuzz_context ctx, fuzz::bv_term t, size_t r) {
            return yices_rotate_right(t, r % (BV_SIZE + 1)); }
    }
    namespace shift_left_zero {
        fuzz::bv_term base(fuzz::fuzz_context ctx, fuzz::bv_term t, size_t r) {
            return yices_shift_left0(t, r % (BV_SIZE + 1)); }
    }
    namespace shift_right_zero {
        fuzz::bv_term base(fuzz::fuzz_context ctx, fuzz::bv_term t, size_t r) {
            return yices_shift_right0(t, r % (BV_SIZE + 1)); }
    }
    namespace shift_left_one {
        fuzz::bv_term base(fuzz::fuzz_context ctx, fuzz::bv_term t, size_t r) {
            return yices_shift_left1(t, r % (BV_SIZE + 1)); }
    }
    namespace shift_right_one {
        fuzz::bv_term base(fuzz::fuzz_context ctx, fuzz::bv_term t, size_t r) {
            return yices_shift_right1(t, r % (BV_SIZE + 1)); }
    }
    namespace ite_bv {
        fuzz::bv_term base(fuzz::fuzz_context ctx, bool b, fuzz::bv_term t, fuzz::bv_term e) {
            term_t bool_term = b ? yices_true() : yices_false();
            return yices_ite(bool_term, t, e); }
    }

} // namespace relations

} // namespace metalib
