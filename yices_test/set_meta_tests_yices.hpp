namespace metalib {

namespace checks {

    void
    check_expr_eq(context_t* ctx, fuzz::FreeVars& fvs, bv_term t1, bv_term t2)
    {
        yices_reset_context(ctx);
        yices_assert_formula(ctx, yices_eq(t1, t2));
        bv_term f_arr[] = { t1, t2 };
        yices_assert_formula(ctx, yices_not(yices_distinct(2, f_arr)));
        assert(yices_check_context(ctx, NULL) == STATUS_SAT);
        assert(!yices_error_code());
    }

    void
    check_expr_equal_zero_sat(context_t* ctx, fuzz::FreeVars& fvs, bv_term t1, bv_term t2)
    {
        yices_reset_context(ctx);
        bv_term zero = yices_bvconst_zero(BV_SIZE);
        bool_term check_zero_t1 = yices_bveq_atom(zero, t1);
        bool_term check_zero_t2 = yices_bveq_atom(zero, t2);
        yices_push(ctx);
        yices_assert_formula(ctx, check_zero_t1);
        if (yices_check_context(ctx, NULL) == STATUS_SAT)
        {
            model_t* mdl = yices_get_model(ctx, true);
            bool_term val;
            assert(yices_get_bool_value(mdl, check_zero_t2, &val) == 0);
            assert(val);
        }
        else
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
        if (yices_check_context(ctx, NULL) == STATUS_SAT)
        {
            model_t* mdl = yices_get_model(ctx, true);
            bool_term val;
            assert(yices_get_bool_value(mdl, check_zero_t1, &val) == 0);
            assert(val);
        }
        else
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

/*******************************************************************************
 * Forward Declarations
 ******************************************************************************/

namespace generators {
namespace fuzz_bv_term {
    bv_term placeholder(context_t*, fuzz::FreeVars&);
}
namespace fuzz_bool_term {
    bool_term placeholder(context_t*, fuzz::FreeVars&);
}
namespace zero {
    bv_term placeholder(context_t*, fuzz::FreeVars&, bv_term);
}
namespace one {
    bv_term placeholder(context_t*, fuzz::FreeVars&, bv_term);
}
namespace true_yices {
    bool_term placeholder(context_t*, fuzz::FreeVars&, bool_term);
}
namespace false_yices {
    bool_term placeholder(context_t*, fuzz::FreeVars&, bool_term);
}
namespace iden_bool {
    bool_term placeholder(context_t*, fuzz::FreeVars&, bool_term);
}
namespace not_yices {
    bool_term placeholder(context_t*, fuzz::FreeVars&, bool_term);
}
namespace and_yices {
    bool_term placeholder(context_t*, fuzz::FreeVars&, bool_term, bool_term);
}
namespace or_yices {
    bool_term placeholder(context_t*, fuzz::FreeVars&, bool_term, bool_term);
}
namespace xor_yices {
    bool_term placeholder(context_t*, fuzz::FreeVars&, bool_term, bool_term);
}
namespace equal_bv {
    bool_term placeholder(context_t*, fuzz::FreeVars&, bv_term, bv_term);
}
namespace lt {
    bool_term placeholder(context_t*, fuzz::FreeVars&, bv_term, bv_term);
}
namespace gt {
    bool_term placeholder(context_t*, fuzz::FreeVars&, bv_term, bv_term);
}
namespace le {
    bool_term placeholder(context_t*, fuzz::FreeVars&, bv_term, bv_term);
}
namespace ge {
    bool_term placeholder(context_t*, fuzz::FreeVars&, bv_term, bv_term);
}
namespace slt {
    bool_term placeholder(context_t*, fuzz::FreeVars&, bv_term, bv_term);
}
namespace sgt {
    bool_term placeholder(context_t*, fuzz::FreeVars&, bv_term, bv_term);
}
namespace sle {
    bool_term placeholder(context_t*, fuzz::FreeVars&, bv_term, bv_term);
}
namespace sge {
    bool_term placeholder(context_t*, fuzz::FreeVars&, bv_term, bv_term);
}
} // namespace generators
namespace relations {
namespace identity {
    bv_term placeholder(context_t*, fuzz::FreeVars&, bv_term);
}
namespace neg {
    bv_term placeholder(context_t*, fuzz::FreeVars&, bv_term);
}
namespace bvnot {
    bv_term placeholder(context_t*, fuzz::FreeVars&, bv_term);
}
namespace sub {
    bv_term placeholder(context_t*, fuzz::FreeVars&, bv_term, bv_term);
}
namespace add {
    bv_term placeholder(context_t*, fuzz::FreeVars&, bv_term, bv_term);
}
namespace mul {
    bv_term placeholder(context_t*, fuzz::FreeVars&, bv_term, bv_term);
}
namespace square {
    bv_term placeholder(context_t*, fuzz::FreeVars&, bv_term);
}
namespace sdivision {
    bv_term placeholder(context_t*, fuzz::FreeVars&, bv_term, bv_term);
}
namespace division {
    bv_term placeholder(context_t*, fuzz::FreeVars&, bv_term, bv_term);
}
namespace smodulo {
    bv_term placeholder(context_t*, fuzz::FreeVars&, bv_term, bv_term);
}
namespace modulo {
    bv_term placeholder(context_t*, fuzz::FreeVars&, bv_term, bv_term);
}
namespace bvabs {
    bv_term placeholder(context_t*, fuzz::FreeVars&, bv_term);
}
namespace bvor {
    bv_term placeholder(context_t*, fuzz::FreeVars&, bv_term, bv_term);
}
namespace bvand {
    bv_term placeholder(context_t*, fuzz::FreeVars&, bv_term, bv_term);
}
} // namespace relations

/*******************************************************************************
 * Generators
 ******************************************************************************/

namespace generators {

namespace fuzz_bv_term {

    bv_term
    fuzz_bv_term(context_t* ctx, fuzz::FreeVars& fvs)
    {
        return fuzz::fuzz_new<bv_term>();
    }

} // namespace fuzz_bv_term

namespace fuzz_bool_term {

    bool_term
    fuzz_bool_term(context_t* ctx, fuzz::FreeVars& fvs)
    {
        return fuzz::fuzz_new<bool_term>();
    }

} // namespace fuzz_bool_term

namespace zero {


    bv_term
    get_zero(context_t* ctx, fuzz::FreeVars& fvs, bv_term t)
    {
        return yices_bvconst_uint32(BV_SIZE, 0);
    }

    bv_term
    get_zero_by_call(context_t* ctx, fuzz::FreeVars& fvs, bv_term t)
    {
        return yices_bvconst_zero(BV_SIZE);
    }

    bv_term
    get_zero_by_sub(context_t* ctx, fuzz::FreeVars& fvs, bv_term t)
    {
        bv_term iden_t = relations::identity::placeholder(ctx, fvs, t);
        return relations::sub::placeholder(ctx, fvs, t, iden_t);
    }

    bv_term
    get_zero_by_fuzz_sub(context_t* ctx, fuzz::FreeVars& fvs, bv_term t)
    {
        bv_term fuzz = generators::fuzz_bv_term::placeholder(ctx, fvs);
        bv_term iden_fuzz = relations::identity::placeholder(ctx, fvs, fuzz);
        return yices_bvsub(fuzz, iden_fuzz);
    }

    bv_term
    get_zero_by_mul(context_t* ctx, fuzz::FreeVars& fvs, bv_term t)
    {
        bv_term zero = generators::zero::placeholder(ctx, fvs, t);
        return relations::mul::placeholder(ctx, fvs, t, zero);
    }

    bv_term
    zero_by_mod(context_t* ctx, fuzz::FreeVars& fvs, bv_term t)
    {
        bv_term iden_term = relations::identity::placeholder(ctx, fvs, t);
        return relations::modulo::placeholder(ctx, fvs, t, iden_term);
    }

    bv_term
    zero_by_smod(context_t* ctx, fuzz::FreeVars& fvs, bv_term t)
    {
        bv_term iden_term = relations::identity::placeholder(ctx, fvs, t);
        return relations::smodulo::placeholder(ctx, fvs, t, iden_term);
    }

    bv_term
    zero_by_mod_zero(context_t* ctx, fuzz::FreeVars& fvs, bv_term t)
    {
        bv_term iden_term = relations::identity::placeholder(ctx, fvs, t);
        bv_term zero = generators::zero::placeholder(ctx, fvs, t);
        return relations::modulo::placeholder(ctx, fvs, zero, iden_term);
    }

    bv_term
    zero_by_mod_one(context_t* ctx, fuzz::FreeVars& fvs, bv_term t)
    {
        bv_term iden_term = relations::identity::placeholder(ctx, fvs, t);
        bv_term one = generators::one::placeholder(ctx, fvs, t);
        return relations::modulo::placeholder(ctx, fvs, iden_term, one);
    }

    bv_term
    zero_by_div(context_t* ctx, fuzz::FreeVars& fvs, bv_term t)
    {
        bv_term iden_term = relations::identity::placeholder(ctx, fvs, t);
        bv_term zero = generators::zero::placeholder(ctx, fvs, t);
        bool_term zero_check = generators::equal_bv::placeholder(ctx, fvs, t, zero);
        bv_term div_ts = relations::division::placeholder(ctx, fvs, zero, iden_term);
        return yices_ite(zero_check, zero, div_ts);
    }

    bv_term
    zero_by_sdiv(context_t* ctx, fuzz::FreeVars& fvs, bv_term t)
    {
        bv_term iden_term = relations::identity::placeholder(ctx, fvs, t);
        bv_term zero = generators::zero::placeholder(ctx, fvs, t);
        bool_term zero_check = generators::equal_bv::placeholder(ctx, fvs, t, zero);
        bv_term sdiv_ts = relations::sdivision::placeholder(ctx, fvs, zero, iden_term);
        return yices_ite(zero_check, zero, sdiv_ts);
    }

    bv_term
    get_zero_by_shift_left(context_t* ctx, fuzz::FreeVars& fvs, bv_term t)
    {

        return yices_shift_left0(t, BV_SIZE);
    }

    bv_term
    get_zero_by_shift_right(context_t* ctx, fuzz::FreeVars& fvs, bv_term t)
    {

        return yices_shift_right0(t, BV_SIZE);
    }


} // namespace zero

namespace one {

    bv_term
    get_one(context_t* ctx, fuzz::FreeVars& fvs, bv_term t)
    {
        return yices_bvconst_uint32(BV_SIZE, 1);
    }

    bv_term
    get_one_by_call(context_t* ctx, fuzz::FreeVars& fvs, bv_term t)
    {
        return yices_bvconst_one(BV_SIZE);
    }

    bv_term
    get_one_by_neg_minus_one(context_t* ctx, fuzz::FreeVars& fvs, bv_term t)
    {
        bv_term neg_one = yices_bvconst_minus_one(BV_SIZE);
        return relations::neg::placeholder(ctx, fvs, neg_one);
    }

    bv_term
    get_one_by_div(context_t* ctx, fuzz::FreeVars& fvs, bv_term t)
    {
        bv_term zero = generators::zero::placeholder(ctx, fvs, t);
        bv_term one = generators::one::placeholder(ctx, fvs, t);
        bool_term zero_check = generators::equal_bv::placeholder(ctx, fvs, t, zero);
        bv_term iden_term = relations::identity::placeholder(ctx, fvs, t);
        bv_term div_ts = relations::division::placeholder(ctx, fvs, t, iden_term);
        return yices_ite(zero_check, one, div_ts);
    }

    bv_term
    get_one_by_fuzz_div(context_t* ctx, fuzz::FreeVars& fvs, bv_term t)
    {
        bv_term zero = generators::zero::placeholder(ctx, fvs, t);
        bv_term one = generators::one::placeholder(ctx, fvs, t);
        bv_term fuzz = generators::fuzz_bv_term::placeholder(ctx, fvs);
        bv_term fuzz_iden = relations::identity::placeholder(ctx, fvs, fuzz);
        bool_term zero_check = generators::equal_bv::placeholder(ctx, fvs, fuzz, zero);
        bv_term div_fs = relations::division::placeholder(ctx, fvs, fuzz, fuzz_iden);
        return yices_ite(zero_check, one, div_fs);
    }

    bv_term
    get_one_by_add_zero(context_t* ctx, fuzz::FreeVars& fvs, bv_term t)
    {
        bv_term zero = generators::zero::placeholder(ctx, fvs, t);
        bv_term one = generators::one::placeholder(ctx, fvs, t);
        return relations::add::placeholder(ctx, fvs, zero, one);
    }

    bv_term
    get_one_by_pw(context_t* ctx, fuzz::FreeVars& fvs, bv_term t)
    {
        bv_term iden_term = relations::identity::placeholder(ctx, fvs, t);
        return yices_bvpower(iden_term, 0);
    }

} // namespace one

namespace true_yices {

    bool_term
    get_true(context_t* ctx, fuzz::FreeVars& fvs, bool_term t)
    {
        return yices_true();
    }

    bool_term
    get_true_by_equal(context_t* ctx, fuzz::FreeVars& fvs, bool_term t)
    {
        bool_term iden_term = generators::iden_bool::placeholder(ctx, fvs, t);
        return yices_eq(t, iden_term);
    }

    bool_term
    get_true_by_not_false(context_t* ctx, fuzz::FreeVars& fvs, bool_term t)
    {
        t = generators::iden_bool::placeholder(ctx, fvs, t);
        return yices_not(generators::false_yices::placeholder(ctx, fvs, t));
    }

    bool_term
    get_true_by_or_true(context_t* ctx, fuzz::FreeVars& fvs, bool_term t)
    {
        t = generators::iden_bool::placeholder(ctx, fvs, t);
        bool_term true_term = generators::true_yices::placeholder(ctx, fvs, t);
        return generators::or_yices::placeholder(ctx, fvs, true_term, t);
    }

} // namespace true_yices

namespace false_yices {

    bool_term
    get_false(context_t* ctx, fuzz::FreeVars& fvs, bool_term t)
    {
        return yices_false();
    }

    bool_term
    get_false_by_equal(context_t* ctx, fuzz::FreeVars& fvs, bool_term t)
    {
        bool_term iden_term = generators::iden_bool::placeholder(ctx, fvs, t);
        return yices_neq(t, iden_term);
    }

    bool_term
    get_false_by_not_true(context_t* ctx, fuzz::FreeVars& fvs, bool_term t)
    {
        t = generators::iden_bool::placeholder(ctx, fvs, t);
        return yices_not(generators::true_yices::placeholder(ctx, fvs, t));
    }

    bool_term
    get_false_by_and_false(context_t* ctx, fuzz::FreeVars& fvs, bool_term t)
    {
        t = generators::iden_bool::placeholder(ctx, fvs, t);
        bool_term false_term = generators::false_yices::placeholder(ctx, fvs, t);
        return generators::and_yices::placeholder(ctx, fvs, false_term, t);
    }

    bool_term
    get_false_by_and_false_fuzz(context_t* ctx, fuzz::FreeVars& fvs, bool_term t)
    {
        bool_term false_term = generators::false_yices::placeholder(ctx, fvs, t);
        bool_term fuzz_term = generators::fuzz_bool_term::placeholder(ctx, fvs);
        return generators::and_yices::placeholder(ctx, fvs, false_term, t);
    }

    bool_term
    get_false_by_xor(context_t* ctx, fuzz::FreeVars& fvs, bool_term t)
    {
        bool_term iden_term = generators::iden_bool::placeholder(ctx, fvs, t);
        return generators::xor_yices::placeholder(ctx, fvs, t, iden_term);
    }

    bool_term
    get_false_by_xor_fuzz(context_t* ctx, fuzz::FreeVars& fvs, bool_term t)
    {
        bool_term fuzz_term = generators::fuzz_bool_term::placeholder(ctx, fvs);
        bool_term iden_term = generators::iden_bool::placeholder(ctx, fvs, fuzz_term);
        return generators::xor_yices::placeholder(ctx, fvs, fuzz_term, iden_term);
    }

    bool_term
    get_false_by_lt_fuzz(context_t* ctx, fuzz::FreeVars& fvs, bool_term t)
    {
        bv_term fuzz_term = generators::fuzz_bv_term::placeholder(ctx, fvs);
        bv_term iden_term = relations::identity::placeholder(ctx, fvs, fuzz_term);
        return generators::lt::placeholder(ctx, fvs, fuzz_term, iden_term);
    }

    bool_term
    get_false_by_gt_fuzz(context_t* ctx, fuzz::FreeVars& fvs, bool_term t)
    {
        bv_term fuzz_term = generators::fuzz_bv_term::placeholder(ctx, fvs);
        bv_term iden_term = relations::identity::placeholder(ctx, fvs, fuzz_term);
        return generators::gt::placeholder(ctx, fvs, fuzz_term, iden_term);
    }

} // namespace false yices

namespace iden_bool {

    bool_term
    base_iden_bool(context_t* ctx, fuzz::FreeVars& fvs, bool_term t)
    {
        return t;
    }

    bool_term
    iden_by_and(context_t* ctx, fuzz::FreeVars& fvs, bool_term t)
    {
        t = generators::iden_bool::placeholder(ctx, fvs, t);
        bool_term true_term = generators::true_yices::placeholder(ctx, fvs, t);
        return generators::and_yices::placeholder(ctx, fvs, t, true_term);
    }

    bool_term
    iden_by_or(context_t* ctx, fuzz::FreeVars& fvs, bool_term t)
    {
        t = generators::iden_bool::placeholder(ctx, fvs, t);
        bool_term false_term = generators::false_yices::placeholder(ctx, fvs, t);
        return generators::or_yices::placeholder(ctx, fvs, t, false_term);
    }

    bool_term
    iden_by_xor(context_t* ctx, fuzz::FreeVars& fvs, bool_term t)
    {
        bool_term iden_term = generators::iden_bool::placeholder(ctx, fvs, t);
        bool_term xor_once = generators::xor_yices::placeholder(ctx, fvs, t, iden_term);
        return generators::xor_yices::placeholder(ctx, fvs, xor_once, iden_term);
    }

    bool_term
    iden_by_double_not(context_t* ctx, fuzz::FreeVars& fvs, bool_term t)
    {
        bool_term iden_term = generators::iden_bool::placeholder(ctx, fvs, t);
        iden_term = generators::not_yices::placeholder(ctx, fvs, iden_term);
        return generators::not_yices::placeholder(ctx, fvs, iden_term);
    }

} // namespace iden_bool

namespace not_yices {

    bool_term
    base_not(context_t* ctx, fuzz::FreeVars& fvs, bool_term t)
    {
        return yices_not(t);
    }

    bool_term
    not_by_truth_value(context_t* ctx, fuzz::FreeVars& fvs, bool_term t)
    {
        bool_term false_term = generators::false_yices::placeholder(ctx, fvs, t);
        bool_term true_term = generators::true_yices::placeholder(ctx, fvs, t);
        return yices_ite(t, false_term, true_term);
    }

} // namespace not_yices

namespace and_yices {

    bool_term
    base_and(context_t* ctx, fuzz::FreeVars& fvs, bool_term t1, bool_term t2)
    {
        return yices_and2(t1, t2);
    }

    bool_term
    and_comm(context_t* ctx, fuzz::FreeVars& fvs, bool_term t1, bool_term t2)
    {
        return generators::and_yices::placeholder(ctx, fvs, t2, t1);
    }

    bool_term
    and_array(context_t* ctx, fuzz::FreeVars& fvs, bool_term t1, bool_term t2)
    {
        bool_term and_arr[2] = {t1, t2};
        return yices_and(2, and_arr);
    }

    bool_term
    and_three_with_true(context_t* ctx, fuzz::FreeVars& fvs, bool_term t1, bool_term t2)
    {
        bool_term true_term = generators::true_yices::placeholder(ctx, fvs, t1);
        return yices_and3(t1, t2, true_term);
    }

    bool_term
    and_demorgan(context_t* ctx, fuzz::FreeVars& fvs, bool_term t1, bool_term t2)
    {
        bool_term nt1 = yices_not(t1);
        bool_term nt2 = yices_not(t2);
        bool_term or_nts = generators::or_yices::placeholder(ctx, fvs, nt1, nt2);
        return generators::not_yices::placeholder(ctx, fvs, or_nts);
    }

} // namespace and_yices

namespace or_yices {

    bool_term
    base_or(context_t* ctx, fuzz::FreeVars& fvs, bool_term t1, bool_term t2)
    {
        return yices_or2(t1, t2);
    }

    bool_term
    or_comm(context_t* ctx, fuzz::FreeVars& fvs, bool_term t1, bool_term t2)
    {
        return generators::or_yices::placeholder(ctx, fvs, t2, t1);
    }

    bool_term
    or_array(context_t* ctx, fuzz::FreeVars& fvs, bool_term t1, bool_term t2)
    {
        bool_term or_arr[2] = {t1, t2};
        return yices_or(2, or_arr);
    }

    bool_term
    or_three_with_false(context_t* ctx, fuzz::FreeVars& fvs, bool_term t1, bool_term t2)
    {
        bool_term false_term = generators::false_yices::placeholder(ctx, fvs, t1);
        return yices_or3(t1, t2, false_term);
    }

    bool_term
    or_demorgan(context_t* ctx, fuzz::FreeVars& fvs, bool_term t1, bool_term t2)
    {
        bool_term nt1 = yices_not(t1);
        bool_term nt2 = yices_not(t2);
        bool_term and_nts = generators::and_yices::placeholder(ctx, fvs, nt1, nt2);
        return generators::not_yices::placeholder(ctx, fvs, and_nts);
    }

} // namespace or_yices

namespace xor_yices {

    bool_term
    base_xor(context_t* ctx, fuzz::FreeVars& fvs, bool_term t1, bool_term t2)
    {
        return yices_xor2(t1, t2);
    }

    bool_term
    xor_comm(context_t* ctx, fuzz::FreeVars& fvs, bool_term t1, bool_term t2)
    {
        return generators::xor_yices::placeholder(ctx, fvs, t2, t1);
    }

    bool_term
    xor_array(context_t* ctx, fuzz::FreeVars& fvs, bool_term t1, bool_term t2)
    {
        bool_term xor_arr[2] = {t1, t2};
        return yices_xor(2, xor_arr);
    }

    bool_term
    xor_three_with_false(context_t* ctx, fuzz::FreeVars& fvs, bool_term t1, bool_term t2)
    {
        bool_term false_term = generators::false_yices::placeholder(ctx, fvs, t1);
        return yices_xor3(t1, t2, false_term);
    }

    bool_term
    xor_disjunct(context_t* ctx, fuzz::FreeVars& fvs, bool_term t1, bool_term t2)
    {
        bool_term nt1 = yices_not(t1);
        bool_term nt2 = yices_not(t2);
        bool_term t1_and_nt2 = generators::and_yices::placeholder(ctx, fvs, t1, nt2);
        bool_term t2_and_nt1 = generators::and_yices::placeholder(ctx, fvs, t2, nt1);
        return generators::or_yices::placeholder(ctx, fvs, t1_and_nt2, t2_and_nt1);
    }

    bool_term
    xor_conjunct(context_t* ctx, fuzz::FreeVars& fvs, bool_term t1, bool_term t2)
    {
        bool_term nt1 = yices_not(t1);
        bool_term nt2 = yices_not(t2);
        bool_term t1_or_t2 = generators::or_yices::placeholder(ctx, fvs, t1, t2);
        bool_term nt1_or_nt2 = generators::or_yices::placeholder(ctx, fvs, nt1, nt2);
        return generators::and_yices::placeholder(ctx, fvs, t1_or_t2, nt1_or_nt2);
    }

} // namespace xor_yices

namespace equal_bv {

    bool_term
    check_equal_by_call(context_t* ctx, fuzz::FreeVars& fvs, bv_term t1, bv_term t2)
    {
        return yices_bveq_atom(t1, t2);
    }

    bool_term
    check_equal_comm(context_t* ctx, fuzz::FreeVars& fvs, bv_term t1, bv_term t2)
    {
        return generators::equal_bv::placeholder(ctx, fvs, t2, t1);
    }

    bool_term
    check_equal_by_sub_is_zero(context_t* ctx, fuzz::FreeVars& fvs, bv_term t1, bv_term t2)
    {
        bv_term zero = generators::zero::placeholder(ctx, fvs, t1);
        bv_term sub_ts = relations::sub::placeholder(ctx, fvs, t1, t2);
        return generators::equal_bv::placeholder(ctx, fvs, zero, sub_ts);
    }

    bool_term
    check_equal_by_div_is_one(context_t* ctx, fuzz::FreeVars& fvs, bv_term t1, bv_term t2)
    {
        bv_term one = generators::one::placeholder(ctx, fvs, t1);
        bv_term zero = generators::zero::placeholder(ctx, fvs, t2);
        bv_term div_ts = relations::division::placeholder(ctx, fvs, t1, t2);
        bool_term check_zeroes = yices_and2(yices_bveq_atom(zero, t1), yices_bveq_atom(zero, t2));
        bool_term check_equal = generators::equal_bv::placeholder(ctx, fvs, one, div_ts);
        return yices_or2(check_zeroes, check_equal);
    }

} // namespace equal_bv

namespace lt {

    bool_term
    lt_base(context_t* ctx, fuzz::FreeVars& fvs, bv_term t1, bv_term t2)
    {
        return yices_bvlt_atom(t1, t2);
    }

    bool_term
    lt_by_slt(context_t* ctx, fuzz::FreeVars& fvs, bv_term t1, bv_term t2)
    {
        return generators::slt::placeholder(ctx, fvs, t1, t2);
    }


    bool_term
    not_ge_base(context_t* ctx, fuzz::FreeVars& fvs, bv_term t1, bv_term t2)
    {
        bool_term ge_term = generators::ge::placeholder(ctx, fvs, t1, t2);
        return generators::not_yices::placeholder(ctx, fvs, ge_term);
    }

} // namespace lt

namespace gt {

    bool_term
    gt_base(context_t* ctx, fuzz::FreeVars& fvs, bv_term t1, bv_term t2)
    {
        return yices_bvgt_atom(t1, t2);
    }

    bool_term
    gt_by_sgt(context_t* ctx, fuzz::FreeVars& fvs, bv_term t1, bv_term t2)
    {
        return generators::sgt::placeholder(ctx, fvs, t1, t2);
    }

    bool_term
    not_le_base(context_t* ctx, fuzz::FreeVars& fvs, bv_term t1, bv_term t2)
    {
        bool_term le_term = generators::le::placeholder(ctx, fvs, t1, t2);
        return generators::not_yices::placeholder(ctx, fvs, le_term);
    }

} // namespace gt

namespace le {

    bool_term
    le_base(context_t* ctx, fuzz::FreeVars& fvs, bv_term t1, bv_term t2)
    {
        return yices_bvle_atom(t1, t2);
    }

    bool_term
    le_by_sle(context_t* ctx, fuzz::FreeVars& fvs, bv_term t1, bv_term t2)
    {
        return generators::sle::placeholder(ctx, fvs, t1, t2);
    }

    bool_term
    not_gt_base(context_t* ctx, fuzz::FreeVars& fvs, bv_term t1, bv_term t2)
    {
        bool_term gt_term = generators::gt::placeholder(ctx, fvs, t1, t2);
        return generators::not_yices::placeholder(ctx, fvs, gt_term);
    }

} // namespace le

namespace ge {

    bool_term
    ge_base(context_t* ctx, fuzz::FreeVars& fvs, bv_term t1, bv_term t2)
    {
        return yices_bvge_atom(t1, t2);
    }

    bool_term
    ge_by_sge(context_t* ctx, fuzz::FreeVars& fvs, bv_term t1, bv_term t2)
    {
        return generators::sge::placeholder(ctx, fvs, t1, t2);
    }

    bool_term
    not_lt_base(context_t* ctx, fuzz::FreeVars& fvs, bv_term t1, bv_term t2)
    {
        bool_term lt_term = generators::lt::placeholder(ctx, fvs, t1, t2);
        return generators::not_yices::placeholder(ctx, fvs, lt_term);
    }

} // namespace ge

namespace slt {

    bool_term
    slt_base(context_t* ctx, fuzz::FreeVars& fvs, bv_term t1, bv_term t2)
    {
        return yices_bvslt_atom(t1, t2);
    }

    bool_term
    not_sge_base(context_t* ctx, fuzz::FreeVars& fvs, bv_term t1, bv_term t2)
    {
        bool_term sge_term = generators::sge::placeholder(ctx, fvs, t1, t2);
        return generators::not_yices::placeholder(ctx, fvs, sge_term);
    }

} // namespace slt

namespace sgt {

    bool_term
    sgt_base(context_t* ctx, fuzz::FreeVars& fvs, bv_term t1, bv_term t2)
    {
        return yices_bvsgt_atom(t1, t2);
    }

    bool_term
    not_sle_base(context_t* ctx, fuzz::FreeVars& fvs, bv_term t1, bv_term t2)
    {
        bool_term sle_term = generators::sle::placeholder(ctx, fvs, t1, t2);
        return generators::not_yices::placeholder(ctx, fvs, sle_term);
    }

} // namespace sgt

namespace sle {

    bool_term
    sle_base(context_t* ctx, fuzz::FreeVars& fvs, bv_term t1, bv_term t2)
    {
        return yices_bvsle_atom(t1, t2);
    }

    bool_term
    not_sgt_base(context_t* ctx, fuzz::FreeVars& fvs, bv_term t1, bv_term t2)
    {
        bool_term sgt_term = generators::sgt::placeholder(ctx, fvs, t1, t2);
        return generators::not_yices::placeholder(ctx, fvs, sgt_term);
    }

} // namespace sle

namespace sge {

    bool_term
    sge_base(context_t* ctx, fuzz::FreeVars& fvs, bv_term t1, bv_term t2)
    {
        return yices_bvsge_atom(t1, t2);
    }

    bool_term
    not_slt_base(context_t* ctx, fuzz::FreeVars& fvs, bv_term t1, bv_term t2)
    {
        bool_term slt_term = generators::slt::placeholder(ctx, fvs, t1, t2);
        return generators::not_yices::placeholder(ctx, fvs, slt_term);
    }

} // namespace sge

} // namespace generators

/*******************************************************************************
 * Relations
 ******************************************************************************/

namespace relations {

namespace identity {

    bv_term
    base_identity(context_t* ctx, fuzz::FreeVars& fvs, bv_term t)
    {
        return t;
    }

    bv_term
    add_zero(context_t* ctx, fuzz::FreeVars& fvs, bv_term t)
    {
        bv_term iden_term = relations::identity::placeholder(ctx, fvs, t);
        bv_term zero = generators::zero::placeholder(ctx, fvs, t);
        return relations::add::placeholder(ctx, fvs, iden_term, zero);
    }

    bv_term
    sub_zero(context_t* ctx, fuzz::FreeVars& fvs, bv_term t)
    {
        bv_term iden_term = relations::identity::placeholder(ctx, fvs, t);
        bv_term zero = generators::zero::placeholder(ctx, fvs, t);
        return relations::sub::placeholder(ctx, fvs, iden_term, zero);
    }

    bv_term
    mul_one(context_t* ctx, fuzz::FreeVars& fvs, bv_term t)
    {
        bv_term iden_term = relations::identity::placeholder(ctx, fvs, t);
        bv_term one = generators::one::placeholder(ctx, fvs, t);
        return relations::mul::placeholder(ctx, fvs, iden_term, one);
    }

    bv_term
    div_one(context_t* ctx, fuzz::FreeVars& fvs, bv_term t)
    {
        bv_term iden_term = relations::identity::placeholder(ctx, fvs, t);
        bv_term one = generators::one::placeholder(ctx, fvs, t);
        return relations::division::placeholder(ctx, fvs, iden_term, one);
    }

    bv_term
    double_negation(context_t* ctx, fuzz::FreeVars& fvs, bv_term t)
    {
        t = relations::neg::placeholder(ctx, fvs, t);
        return relations::neg::placeholder(ctx, fvs, t);
    }

    bv_term
    double_not(context_t* ctx, fuzz::FreeVars& fvs, bv_term t)
    {
        t = relations::identity::placeholder(ctx, fvs, t);
        t = relations::bvnot::placeholder(ctx, fvs, t);
        return relations::bvnot::placeholder(ctx, fvs, t);
    }

    bv_term
    iden_by_abs(context_t* ctx, fuzz::FreeVars& fvs, bv_term t)
    {
        bv_term iden_term = relations::identity::placeholder(ctx, fvs, t);
        bv_term abs_t = relations::bvabs::placeholder(ctx, fvs, t);
        bool_term t_equal = generators::equal_bv::placeholder(ctx, fvs, abs_t, t);
        return yices_ite(t_equal, abs_t, t);
    }

    bv_term
    iden_by_concat_extract(context_t* ctx, fuzz::FreeVars& fvs, bv_term t)
    {
        size_t middle = fuzz::fuzz_rand<int, int>(1, BV_SIZE - 3);
        bv_term lo = yices_bvextract(t, 0, middle);
        bv_term hi = yices_bvextract(t, middle + 1, BV_SIZE - 1);
        return yices_bvconcat2(hi, lo);
    }

    bv_term
    iden_by_ror_0(context_t* ctx, fuzz::FreeVars& fvs, bv_term t)
    {
        return yices_shift_right0(t, 0);
    }

    bv_term
    iden_by_rol_0(context_t* ctx, fuzz::FreeVars& fvs, bv_term t)
    {
        return yices_shift_left0(t, 0);
    }

    bv_term
    iden_by_shr_0(context_t* ctx, fuzz::FreeVars& fvs, bv_term t)
    {
        return yices_shift_right0(t, 0);
    }

    bv_term
    iden_by_shl_0(context_t* ctx, fuzz::FreeVars& fvs, bv_term t)
    {
        return yices_shift_left0(t, 0);
    }

    bv_term
    iden_by_ashr(context_t* ctx, fuzz::FreeVars& fvs, bv_term t)
    {
        return yices_ashift_right(t, 0);
    }

    bv_term
    iden_by_rotate_left(context_t* ctx, fuzz::FreeVars& fvs, bv_term t)
    {
        size_t rotate_count = fuzz::fuzz_rand<unsigned int, unsigned int>(0, BV_SIZE - 1);
        return yices_rotate_left(yices_rotate_left(t, rotate_count), BV_SIZE - rotate_count);
    }

    bv_term
    iden_by_rotate_around(context_t* ctx, fuzz::FreeVars& fvs, bv_term t)
    {
        size_t rotate_count = fuzz::fuzz_rand<unsigned int, unsigned int>(0, BV_SIZE - 1);
        return yices_rotate_left(yices_rotate_right(t, rotate_count), rotate_count);
    }

    bv_term
    iden_by_ite_false(context_t* ctx, fuzz::FreeVars& fvs, bv_term t)
    {
        bool_term fuzz_bool = generators::fuzz_bool_term::placeholder(ctx, fvs);
        bool_term false_term = generators::false_yices::placeholder(ctx, fvs, fuzz_bool);
        bv_term dead = generators::fuzz_bv_term::placeholder(ctx, fvs);
        t = relations::identity::placeholder(ctx, fvs, t);
        return yices_ite(false_term, dead, t);
    }

    bv_term
    iden_by_ite_true(context_t* ctx, fuzz::FreeVars& fvs, bv_term t)
    {
        bool_term fuzz_bool = generators::fuzz_bool_term::placeholder(ctx, fvs);
        bool_term true_term = generators::true_yices::placeholder(ctx, fvs, fuzz_bool);
        bv_term dead = generators::fuzz_bv_term::placeholder(ctx, fvs);
        t = relations::identity::placeholder(ctx, fvs, t);
        return yices_ite(true_term, t, dead);
    }

} // namespace identity

namespace neg {

    bv_term
    base_neg(context_t* ctx, fuzz::FreeVars& fvs, bv_term t)
    {
        return yices_bvneg(t);
    }

    bv_term
    neg_by_zero_sub(context_t* ctx, fuzz::FreeVars& fvs, bv_term t)
    {
        bv_term zero = generators::zero::placeholder(ctx, fvs, t);
        return relations::sub::placeholder(ctx, fvs, zero, t);
    }

    bv_term
    neg_by_one_mul(context_t* ctx, fuzz::FreeVars& fvs, bv_term t)
    {
        bv_term neg_one = generators::one::placeholder(ctx, fvs, t);
        neg_one = relations::neg::placeholder(ctx, fvs, neg_one);
        return relations::mul::placeholder(ctx, fvs, neg_one, t);
    }

    bv_term
    neg_by_flip_plus_one(context_t* ctx, fuzz::FreeVars& fvs, bv_term t)
    {
        bv_term flip_term = relations::bvnot::placeholder(ctx, fvs, t);
        bv_term one = generators::one::placeholder(ctx, fvs, t);
        return relations::add::placeholder(ctx, fvs, one, flip_term);
    }

}

namespace bvnot {

    bv_term
    base_neg(context_t* ctx, fuzz::FreeVars& fvs, bv_term t)
    {
        return yices_bvnot(t);
    }

    bv_term
    not_by_xor_mask(context_t* ctx, fuzz::FreeVars& fvs, bv_term t)
    {
        bv_term mask = yices_bvconst_minus_one(BV_SIZE);
        return yices_bvxor2(mask, t);
    }

} //namespace bvnot

namespace add {

    bv_term
    base_add(context_t* ctx, fuzz::FreeVars& fvs, bv_term t1, bv_term t2)
    {
        return yices_bvadd(t1, t2);
    }

    bv_term
    commute_add(context_t* ctx, fuzz::FreeVars& fvs, bv_term t1, bv_term t2)
    {
        return relations::add::placeholder(ctx, fvs, t2, t1);
    }

    bv_term
    add_by_sum(context_t* ctx, fuzz::FreeVars& fvs, bv_term t1, bv_term t2)
    {
        bv_term sum_ts[] = { t1, t2 };
        return yices_bvsum(2, sum_ts);
    }

    bv_term
    add_by_sub_neg(context_t* ctx, fuzz::FreeVars& fvs, bv_term t1, bv_term t2)
    {
        return relations::sub::placeholder(ctx, fvs, t1, yices_bvneg(t2));
    }

} // namespace add

namespace sub {

    bv_term
    base_sub(context_t* ctx, fuzz::FreeVars& fvs, bv_term t1, bv_term t2)
    {
        return yices_bvsub(t1, t2);
    }

    bv_term
    sub_by_sum_neg(context_t* ctx, fuzz::FreeVars& fvs, bv_term t1, bv_term t2)
    {
        bv_term sum_ts[] = { t1, yices_bvneg(t2) };
        return yices_bvsum(2, sum_ts);
    }

    bv_term
    sub_by_add_neg(context_t* ctx, fuzz::FreeVars& fvs, bv_term t1, bv_term t2)
    {
        return relations::add::placeholder(ctx, fvs, t1, yices_bvneg(t2));
    }

} // namespace sub

namespace mul {

    bv_term
    base_mul(context_t* ctx, fuzz::FreeVars& fvs, bv_term t1, bv_term t2)
    {
        return yices_bvmul(t1, t2);
    }

    bv_term
    commute_mul(context_t* ctx, fuzz::FreeVars& fvs, bv_term t1, bv_term t2)
    {
        return relations::mul::placeholder(ctx, fvs, t2, t1);
    }

    bv_term
    mul_by_product(context_t* ctx, fuzz::FreeVars& fvs, bv_term t1, bv_term t2)
    {
        bv_term product_ts[] = { t1, t2 };
        return yices_bvproduct(2, product_ts);
    }

} // namespace mul

namespace square
{

    bv_term
    base_square(context_t* ctx, fuzz::FreeVars& fvs, bv_term t)
    {
        return yices_bvsquare(t);
    }

    bv_term
    square_by_mul(context_t* ctx, fuzz::FreeVars& fvs, bv_term t)
    {
        return relations::mul::placeholder(ctx, fvs, t, t);
    }

    bv_term
    square_by_pow(context_t* ctx, fuzz::FreeVars& fvs, bv_term t)
    {
        return yices_bvpower(relations::identity::placeholder(ctx, fvs, t), 2);
    }

} // namespace square

namespace sdivision
{
    bv_term
    base_sdiv(context_t* ctx, fuzz::FreeVars& fvs, bv_term t1, bv_term t2)
    {
        return yices_bvsdiv(t1, t2);
    }
} // namespace division

namespace division
{
    bv_term
    base_div(context_t* ctx, fuzz::FreeVars& fvs, bv_term t1, bv_term t2)
    {
        return yices_bvdiv(t1, t2);
    }
} // namespace division

namespace smodulo
{
    // TODO check
    bv_term
    base_srem(context_t* ctx, fuzz::FreeVars& fvs, bv_term t1, bv_term t2)
    {
        return yices_bvsrem(t1, t2);
    }

    bv_term
    base_smod(context_t* ctx, fuzz::FreeVars& fvs, bv_term t1, bv_term t2)
    {
        t2 = relations::bvabs::placeholder(ctx, fvs, t2);
        return yices_bvsmod(t1, t2);
    }

    bv_term
    smod_by_sub(context_t* ctx, fuzz::FreeVars& fvs, bv_term t1, bv_term t2)
    {
        t1 = relations::identity::placeholder(ctx, fvs, t1);
        t2 = relations::identity::placeholder(ctx, fvs, t2);
        bv_term div_ts = relations::sdivision::placeholder(ctx, fvs, t1, t2);
        return yices_bvsub(t1, yices_bvmul(t2, div_ts));
    }
} // namespace modulo

namespace modulo
{
    // TODO check
    bv_term
    base_rem(context_t* ctx, fuzz::FreeVars& fvs, bv_term t1, bv_term t2)
    {
        return yices_bvrem(t1, t2);
    }

    bv_term
    mod_by_sub(context_t* ctx, fuzz::FreeVars& fvs, bv_term t1, bv_term t2)
    {
        t1 = relations::identity::placeholder(ctx, fvs, t1);
        t2 = relations::identity::placeholder(ctx, fvs, t2);
        bv_term div_ts = relations::division::placeholder(ctx, fvs, t1, t2);
        return yices_bvsub(t1, yices_bvmul(t2, div_ts));
    }
} // namespace modulo

// TODO does most negative number affect this?
namespace bvabs
{
    bv_term
    abs_by_compare_zero_base(context_t* ctx, fuzz::FreeVars& fvs, bv_term t)
    {
        bv_term zero = yices_bvconst_zero(BV_SIZE);
        bool_term cmp_zero = yices_bvslt_atom(t, zero);
        bv_term neg_t = yices_bvneg(t);
        return yices_ite(cmp_zero, neg_t, t);
    }

    bv_term
    abs_by_compare_zero(context_t* ctx, fuzz::FreeVars& fvs, bv_term t)
    {
        bv_term zero = generators::zero::placeholder(ctx, fvs, t);
        bool_term cmp_zero = generators::slt::placeholder(ctx, fvs, t, zero);
        bv_term neg_t = relations::neg::placeholder(ctx, fvs, t);
        return yices_ite(cmp_zero, neg_t, t);
    }

    bv_term
    abs_by_bitextract(context_t* ctx, fuzz::FreeVars& fvs, bv_term t)
    {
        bv_term lead = yices_bitextract(t, BV_SIZE - 1);
        bv_term neg_t = relations::neg::placeholder(ctx, fvs, t);
        return yices_ite(lead, neg_t, t);
    }

}

namespace bvand
{

    bv_term
    base_and(context_t* ctx, fuzz::FreeVars& fvs, bv_term t1, bv_term t2)
    {
        return yices_bvand2(t1, t2);
    }

    bv_term
    commute_and(context_t* ctx, fuzz::FreeVars& fvs, bv_term t1, bv_term t2)
    {
        return relations::bvand::placeholder(ctx, fvs, t2, t1);
    }

    bv_term
    nnand(context_t* ctx, fuzz::FreeVars& fvs, bv_term t1, bv_term t2)
    {
        bv_term nand = yices_bvnand(t1, t2);
        return relations::bvnot::placeholder(ctx, fvs, nand);
    }


    bv_term
    demorgan_and(context_t* ctx, fuzz::FreeVars& fvs, bv_term t1, bv_term t2)
    {
        bv_term bvor = relations::bvor::placeholder(ctx, fvs, yices_bvnot(t1), yices_bvnot(t2));
        return relations::bvnot::placeholder(ctx, fvs, bvor);
    }

} // namespace bvand

namespace bvor
{
    bv_term
    base_or(context_t* ctx, fuzz::FreeVars& fvs, bv_term t1, bv_term t2)
    {
        return yices_bvor2(t1, t2);
    }

    bv_term
    commute_or(context_t* ctx, fuzz::FreeVars& fvs, bv_term t1, bv_term t2)
    {
        return relations::bvor::placeholder(ctx, fvs, t2, t1);
    }

    bv_term
    nnor(context_t* ctx, fuzz::FreeVars& fvs, bv_term t1, bv_term t2)
    {
        bv_term nor = yices_bvnor(t1, t2);
        return relations::bvnot::placeholder(ctx, fvs, nor);
    }

    bv_term
    demorgan_or(context_t* ctx, fuzz::FreeVars& fvs, bv_term t1, bv_term t2)
    {
        bv_term bvand = relations::bvand::placeholder(ctx, fvs, yices_bvnot(t1), yices_bvnot(t2));
        return relations::bvnot::placeholder(ctx, fvs, bvand);
    }

} // namespace bvor

} // namespace relations

} // namespace metalib
