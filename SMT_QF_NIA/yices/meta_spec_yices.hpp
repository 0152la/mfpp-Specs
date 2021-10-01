namespace fuzz {
} // namespace fuzz

namespace metalib {

namespace checks {

    void
    check_expr_eq(context_t* ctx, fuzz::FreeVars& fvs, fuzz::int_term t1, fuzz::int_term t2)
    {
        yices_reset_context(ctx);
        yices_assert_formula(ctx, yices_eq(t1, t2));
        fuzz::int_term f_arr[] = { t1, t2 };
        yices_assert_formula(ctx, yices_not(yices_distinct(2, f_arr)));
        assert(yices_check_context(ctx, NULL) == STATUS_SAT);
        assert(!yices_error_code());
    }

    void
    check_expr_equal_zero_sat(context_t* ctx, fuzz::FreeVars& fvs, fuzz::int_term t1, fuzz::int_term t2)
    {
        yices_reset_context(ctx);
        fuzz::int_term zero = yices_zero();
        fuzz::bool_term check_zero_t1 = yices_arith_eq_atom(zero, t1);
        fuzz::bool_term check_zero_t2 = yices_arith_eq_atom(zero, t2);
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
        fuzz::int_term base(fuzz::fuzz_context ctx, fuzz::int_term t) {
            return yices_zero(); }
    }
    namespace one {
        fuzz::int_term base(fuzz::fuzz_context ctx, fuzz::int_term t) {
            return yices_int32(1); }
    }
    namespace true_expr {
        fuzz::bool_term base(fuzz::fuzz_context ctx, fuzz::bool_term t) {
            return yices_true(); }
    }
    namespace false_expr {
        fuzz::bool_term base(fuzz::fuzz_context ctx, fuzz::bool_term t) {
            return yices_false(); }
    }
    namespace iden_bool {
        fuzz::bool_term base(fuzz::fuzz_context ctx, fuzz::bool_term t) {
            return t; }
    }
    namespace not_expr {
        fuzz::bool_term base(fuzz::fuzz_context ctx, fuzz::bool_term t) {
            return yices_not(t); }
    }
    namespace and_expr {
        fuzz::bool_term base(fuzz::fuzz_context ctx, fuzz::bool_term t1, fuzz::bool_term t2) {
            return yices_and2(t1, t2); }
    }
    namespace or_expr {
        fuzz::bool_term base(fuzz::fuzz_context ctx, fuzz::bool_term t1, fuzz::bool_term t2) {
            return yices_or2(t1, t2); }
    }
    namespace xor_expr {
        fuzz::bool_term base(fuzz::fuzz_context ctx, fuzz::bool_term t1, fuzz::bool_term t2) {
            return yices_xor2(t1, t2); }
    }
    namespace equal_bool {
        fuzz::bool_term base(fuzz::fuzz_context ctx, fuzz::bool_term t1, fuzz::bool_term t2) {
            return yices_eq(t1, t2); }
    }
    namespace equal_int {
        fuzz::bool_term base(fuzz::fuzz_context ctx, fuzz::int_term t1, fuzz::int_term t2) {
            return yices_eq(t1, t2); }
    }
    namespace ite_integer_term_cond {
        fuzz::int_term base(fuzz::fuzz_context ctx, fuzz::bool_term b, fuzz::int_term t, fuzz::int_term e) {
            return yices_ite(b, t, e); }
    }
    namespace lt {
        fuzz::bool_term base(fuzz::fuzz_context ctx, fuzz::int_term t1, fuzz::int_term t2) {
            return yices_arith_lt_atom(t1, t2); }
    }
    namespace gt {
        fuzz::bool_term base(fuzz::fuzz_context ctx, fuzz::int_term t1, fuzz::int_term t2) {
            return yices_arith_gt_atom(t1, t2); }
    }
    namespace leq {
        fuzz::bool_term base(fuzz::fuzz_context ctx, fuzz::int_term t1, fuzz::int_term t2) {
            return yices_arith_leq_atom(t1, t2); }
    }
    namespace geq {
        fuzz::bool_term base(fuzz::fuzz_context ctx, fuzz::int_term t1, fuzz::int_term t2) {
            return yices_arith_geq_atom(t1, t2); }
    }
    namespace ite_bool {
        fuzz::bool_term base(fuzz::fuzz_context ctx, fuzz::bool_term c, fuzz::bool_term t, fuzz::bool_term e) {
            return yices_ite(c, t, e); }
    }
} // namespace generators

namespace relations {
    namespace identity {
        fuzz::int_term base(fuzz::fuzz_context ctx, fuzz::int_term t) {
            return t; }
    }
    namespace add {
        fuzz::int_term base(fuzz::fuzz_context ctx, fuzz::int_term t1, fuzz::int_term t2) {
            return yices_add(t1, t2); }
    }
    namespace sub {
        fuzz::int_term base(fuzz::fuzz_context ctx, fuzz::int_term t1, fuzz::int_term t2) {
            return yices_sub(t1, t2); }
    }
    namespace abs_expr {
        fuzz::int_term base(fuzz::fuzz_context ctx, fuzz::int_term t) {
            return yices_abs(t); }
    }
    namespace neg {
        fuzz::int_term base(fuzz::fuzz_context ctx, fuzz::int_term t) {
            return yices_neg(t); }
    }
    namespace ite_integer {
        fuzz::int_term base(fuzz::fuzz_context ctx, bool b, fuzz::int_term t, fuzz::int_term e) {
            term_t bool_term = b ? yices_true() : yices_false();
            return yices_ite(bool_term, t, e); }
    }
    // Second class non-linear operations to control parameters (if called
    // appropriately, ensures that it won't be the case that both operands
    // contain free variables
    namespace mul {
        fuzz::int_term base(fuzz::fuzz_context ctx, fuzz::int_term t1, fuzz::int_term t2) {
            return yices_mul(t1, t2); }
    }
    namespace division {
        fuzz::int_term base(fuzz::fuzz_context ctx, fuzz::int_term t1, fuzz::int_term t2) {
            return yices_ite(yices_arith_eq0_atom(t2), t1, yices_idiv(t1, t2)); }
    }
    namespace modulo {
        fuzz::int_term base(fuzz::fuzz_context ctx, fuzz::int_term t1, fuzz::int_term t2) {
            return yices_ite(yices_arith_eq0_atom(t2), t1, yices_imod(t1, t2)); }
    }

} // namespace relations

} // namespace metalib
