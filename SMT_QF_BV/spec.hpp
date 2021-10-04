#include "smt_spec_placeholders.hpp"

namespace metalib {

/*******************************************************************************
 * Generators
 ******************************************************************************/

namespace generators {

namespace fuzz_bv_term {

    fuzz::bv_term
    get_expr_by_fuzz(fuzz::fuzz_context ctx)
    {
        fuzz::bv_term fuzz = fuzz::fuzz_new<fuzz::bv_term>();
        return fuzz;
    }

} // namespace fuzz_bv_term

namespace fuzz_bool_term {

    fuzz::bool_term
    get_expr_by_fuzz(fuzz::fuzz_context ctx)
    {
        fuzz::bool_term fuzz = fuzz::fuzz_new<fuzz::bool_term>();
        return fuzz;
    }

} // namespace fuzz_bool_term

namespace zero {

    fuzz::bv_term
    zero_by_mul(fuzz::fuzz_context ctx, fuzz::bv_term t)
    {
        fuzz::bv_term zero = generators::zero::placeholder(ctx, t);
        return relations::mul::placeholder(ctx, t, zero);
    }

    fuzz::bv_term
    zero_by_sub(fuzz::fuzz_context ctx, fuzz::bv_term t)
    {
        fuzz::bv_term iden_term = relations::identity::placeholder(ctx, t);
        return relations::sub::placeholder(ctx, t, iden_term);
    }

    fuzz::bv_term
    zero_by_fuzz_sub(fuzz::fuzz_context ctx, fuzz::bv_term t)
    {
        fuzz::bv_term fuzz = generators::fuzz_bv_term::placeholder(ctx);
        fuzz::bv_term iden_fuzz = relations::identity::placeholder(ctx, fuzz);
        return relations::sub::placeholder(ctx, fuzz, iden_fuzz);
    }

    fuzz::bv_term
    zero_by_mod_one(fuzz::fuzz_context ctx, fuzz::bv_term t)
    {
        t = relations::identity::placeholder(ctx, t);
        fuzz::bv_term one = generators::one::placeholder(ctx, t);
        return relations::modulo::placeholder(ctx, t, one);
    }

    fuzz::bv_term
    zero_by_mod_one_fuzz(fuzz::fuzz_context ctx, fuzz::bv_term t)
    {
        fuzz::bv_term fuzz = generators::fuzz_bv_term::placeholder(ctx);
        fuzz::bv_term one = generators::one::placeholder(ctx, t);
        return relations::modulo::placeholder(ctx, fuzz, one);
    }

    fuzz::bv_term
    zero_by_xor(fuzz::fuzz_context ctx, fuzz::bv_term t)
    {
        return relations::xor_bv::placeholder(ctx, t, t);
    }

    fuzz::bv_term
    get_zero_by_shiftl(fuzz::fuzz_context ctx, fuzz::bv_term t)
    {
        return relations::shift_left_zero::placeholder(ctx, t, BV_SIZE);
    }

    fuzz::bv_term
    get_zero_by_shiftr(fuzz::fuzz_context ctx, fuzz::bv_term t)
    {
        return relations::shift_right_zero::placeholder(ctx, t, BV_SIZE);
    }

    fuzz::bv_term
    zero_by_mod(fuzz::fuzz_context ctx, fuzz::bv_term t)
    {
        fuzz::bv_term iden_term = relations::identity::placeholder(ctx, t);
        fuzz::bv_term tmp_zero = generators::zero::placeholder(ctx, t);
        fuzz::bool_term is_zero = generators::equal_bv::placeholder(ctx, iden_term, tmp_zero);
        fuzz::bv_term mod_ts = relations::modulo::placeholder(ctx, t, iden_term);
        fuzz::bv_term tmp_zero_return = generators::zero::placeholder(ctx, t);
        return generators::ite_bv_term_cond::placeholder(ctx, is_zero, tmp_zero_return, mod_ts);
    }

    fuzz::bv_term
    zero_by_div(fuzz::fuzz_context ctx, fuzz::bv_term t)
    {
        t = relations::identity::placeholder(ctx, t);
        fuzz::bv_term tmp_zero = generators::zero::placeholder(ctx, t);
        fuzz::bv_term tmp_zero_return = generators::zero::placeholder(ctx, t);
        fuzz::bool_term is_zero = generators::equal_bv::placeholder(ctx, t, tmp_zero);
        fuzz::bv_term div_ts = relations::division::placeholder(ctx, tmp_zero, t);
        return generators::ite_bv_term_cond::placeholder(ctx, is_zero, tmp_zero_return, div_ts);
    }

    fuzz::bv_term
    zero_by_div_fuzz(fuzz::fuzz_context ctx, fuzz::bv_term t)
    {
        fuzz::bv_term fuzz = generators::fuzz_bv_term::placeholder(ctx);
        fuzz::bv_term tmp_zero = generators::zero::placeholder(ctx, fuzz);
        fuzz::bool_term is_zero = generators::equal_bv::placeholder(ctx, fuzz, tmp_zero);
        fuzz::bv_term tmp_zero_return = generators::zero::placeholder(ctx, fuzz);
        fuzz::bv_term div_ts = relations::division::placeholder(ctx, tmp_zero, fuzz);
        return generators::ite_bv_term_cond::placeholder(ctx, is_zero, tmp_zero_return, div_ts);
    }

} // namespace zero

namespace one {

    fuzz::bv_term
    get_one_by_div(fuzz::fuzz_context ctx, fuzz::bv_term t)
    {
        fuzz::bv_term iden_term = relations::identity::placeholder(ctx, t);
        fuzz::bv_term tmp_zero = generators::zero::placeholder(ctx, t);
        fuzz::bool_term is_zero = generators::equal_bv::placeholder(ctx, tmp_zero, t);
        fuzz::bv_term div_ts = relations::division::placeholder(ctx, t, iden_term);
        fuzz::bv_term one = generators::one::placeholder(ctx, t);
        return generators::ite_bv_term_cond::placeholder(ctx, is_zero, one, div_ts);
    }

    fuzz::bv_term
    get_one_by_div_fuzz(fuzz::fuzz_context ctx, fuzz::bv_term t)
    {
        fuzz::bv_term fuzz = generators::fuzz_bv_term::placeholder(ctx);
        fuzz::bv_term iden_fuzz = relations::identity::placeholder(ctx, fuzz);
        fuzz::bv_term tmp_zero = generators::zero::placeholder(ctx, fuzz);
        fuzz::bool_term is_zero = generators::equal_bv::placeholder(ctx, tmp_zero, fuzz);
        fuzz::bv_term div_ts = relations::division::placeholder(ctx, fuzz, iden_fuzz);
        fuzz::bv_term one = generators::one::placeholder(ctx, fuzz);
        return generators::ite_bv_term_cond::placeholder(ctx, is_zero, one, div_ts);
    }

    fuzz::bv_term
    get_one_by_shiftl(fuzz::fuzz_context ctx, fuzz::bv_term t)
    {
        fuzz::bv_term neg_one = relations::shift_left_one::placeholder(ctx, t, BV_SIZE);
        return relations::neg_bv::placeholder(ctx, neg_one);

    }

    fuzz::bv_term
    get_one_by_shiftr(fuzz::fuzz_context ctx, fuzz::bv_term t)
    {
        fuzz::bv_term neg_one = relations::shift_right_one::placeholder(ctx, t, BV_SIZE);
        return relations::neg_bv::placeholder(ctx, neg_one);

    }

} // namespace one

namespace true_bool {

    fuzz::bool_term
    get_true_by_equal(fuzz::fuzz_context ctx, fuzz::bool_term t)
    {
        fuzz::bool_term iden_term = generators::iden_bool::placeholder(ctx, t);
        return generators::equal_bool::placeholder(ctx, t, iden_term);
    }

    fuzz::bool_term
    get_true_by_not_false(fuzz::fuzz_context ctx, fuzz::bool_term t)
    {
        t = generators::iden_bool::placeholder(ctx, t);
        fuzz::bool_term false_term = generators::false_bool::placeholder(ctx, t);
        return generators::not_bool::placeholder(ctx, false_term);
    }

    fuzz::bool_term
    get_true_by_or_true(fuzz::fuzz_context ctx, fuzz::bool_term t)
    {
        t = generators::iden_bool::placeholder(ctx, t);
        fuzz::bool_term true_term = generators::true_bool::placeholder(ctx, t);
        return generators::or_bool::placeholder(ctx, true_term, t);
    }

    fuzz::bool_term
    get_true_by_or_true_fuzz(fuzz::fuzz_context ctx, fuzz::bool_term t)
    {
        fuzz::bool_term true_term = generators::true_bool::placeholder(ctx, t);
        fuzz::bool_term fuzz_term = generators::fuzz_bool_term::placeholder(ctx);
        return generators::or_bool::placeholder(ctx, true_term, t);
    }

    fuzz::bool_term
    get_true_by_nxor(fuzz::fuzz_context ctx, fuzz::bool_term t)
    {
        fuzz::bool_term iden_term = generators::iden_bool::placeholder(ctx, t);
        fuzz::bool_term xor_term = generators::xor_bool::placeholder(ctx, t, iden_term);
        return generators::not_bool::placeholder(ctx, xor_term);
    }

    fuzz::bool_term
    get_true_by_nxor_fuzz(fuzz::fuzz_context ctx, fuzz::bool_term t)
    {
        fuzz::bool_term fuzz_term = generators::fuzz_bool_term::placeholder(ctx);
        fuzz::bool_term iden_term = generators::iden_bool::placeholder(ctx, fuzz_term);
        fuzz::bool_term xor_term = generators::xor_bool::placeholder(ctx, fuzz_term, iden_term);
        return generators::not_bool::placeholder(ctx, xor_term);
    }

    fuzz::bool_term
    get_true_by_lte_fuzz(fuzz::fuzz_context ctx, fuzz::bool_term t)
    {
        fuzz::bv_term fuzz_term = generators::fuzz_bv_term::placeholder(ctx);
        fuzz::bv_term iden_term = relations::identity::placeholder(ctx, fuzz_term);
        return generators::leq::placeholder(ctx, fuzz_term, iden_term);
    }

    fuzz::bool_term
    get_true_by_gte_fuzz(fuzz::fuzz_context ctx, fuzz::bool_term t)
    {
        fuzz::bv_term fuzz_term = generators::fuzz_bv_term::placeholder(ctx);
        fuzz::bv_term iden_term = relations::identity::placeholder(ctx, fuzz_term);
        return generators::geq::placeholder(ctx, fuzz_term, iden_term);
    }

} // namespace true_bool

namespace false_bool {

    fuzz::bool_term
    get_false_by_equal(fuzz::fuzz_context ctx, fuzz::bool_term t)
    {
        fuzz::bool_term iden_term = generators::iden_bool::placeholder(ctx, t);
        fuzz::bool_term eq_term = generators::equal_bool::placeholder(ctx, t, iden_term);
        return generators::not_bool::placeholder(ctx, eq_term);
    }

    fuzz::bool_term
    get_false_by_not_true(fuzz::fuzz_context ctx, fuzz::bool_term t)
    {
        t = generators::iden_bool::placeholder(ctx, t);
        fuzz::bool_term true_term = generators::true_bool::placeholder(ctx, t);
        return generators::not_bool::placeholder(ctx, true_term);
    }

    fuzz::bool_term
    get_false_by_and_false(fuzz::fuzz_context ctx, fuzz::bool_term t)
    {
        t = generators::iden_bool::placeholder(ctx, t);
        fuzz::bool_term false_term = generators::false_bool::placeholder(ctx, t);
        return generators::and_bool::placeholder(ctx, false_term, t);
    }

    fuzz::bool_term
    get_false_by_and_false_fuzz(fuzz::fuzz_context ctx, fuzz::bool_term t)
    {
        fuzz::bool_term false_term = generators::false_bool::placeholder(ctx, t);
        fuzz::bool_term fuzz_term = generators::fuzz_bool_term::placeholder(ctx);
        return generators::and_bool::placeholder(ctx, false_term, t);
    }

    fuzz::bool_term
    get_false_by_xor(fuzz::fuzz_context ctx, fuzz::bool_term t)
    {
        fuzz::bool_term iden_term = generators::iden_bool::placeholder(ctx, t);
        return generators::xor_bool::placeholder(ctx, t, iden_term);
    }

    fuzz::bool_term
    get_false_by_xor_fuzz(fuzz::fuzz_context ctx, fuzz::bool_term t)
    {
        fuzz::bool_term fuzz_term = generators::fuzz_bool_term::placeholder(ctx);
        fuzz::bool_term iden_term = generators::iden_bool::placeholder(ctx, fuzz_term);
        return generators::xor_bool::placeholder(ctx, fuzz_term, iden_term);
    }

    fuzz::bool_term
    get_false_by_lt_fuzz(fuzz::fuzz_context ctx, fuzz::bool_term t)
    {
        fuzz::bv_term fuzz_term = generators::fuzz_bv_term::placeholder(ctx);
        fuzz::bv_term iden_term = relations::identity::placeholder(ctx, fuzz_term);
        return generators::lt::placeholder(ctx, fuzz_term, iden_term);
    }

    fuzz::bool_term
    get_false_by_gt_fuzz(fuzz::fuzz_context ctx, fuzz::bool_term t)
    {
        fuzz::bv_term fuzz_term = generators::fuzz_bv_term::placeholder(ctx);
        fuzz::bv_term iden_term = relations::identity::placeholder(ctx, fuzz_term);
        return generators::gt::placeholder(ctx, fuzz_term, iden_term);
    }

} // namespace false_bool

namespace iden_bool {

    fuzz::bool_term
    iden_by_and(fuzz::fuzz_context ctx, fuzz::bool_term t)
    {
        t = generators::iden_bool::placeholder(ctx, t);
        fuzz::bool_term true_term = generators::true_bool::placeholder(ctx, t);
        return generators::and_bool::placeholder(ctx, t, true_term);
    }

    fuzz::bool_term
    iden_by_or(fuzz::fuzz_context ctx, fuzz::bool_term t)
    {
        t = generators::iden_bool::placeholder(ctx, t);
        fuzz::bool_term false_term = generators::false_bool::placeholder(ctx, t);
        return generators::or_bool::placeholder(ctx, t, false_term);
    }

    fuzz::bool_term
    iden_by_xor(fuzz::fuzz_context ctx, fuzz::bool_term t)
    {
        fuzz::bool_term iden_term = generators::iden_bool::placeholder(ctx, t);
        fuzz::bool_term xor_once = generators::xor_bool::placeholder(ctx, iden_term, iden_term);
        return generators::xor_bool::placeholder(ctx, xor_once, iden_term);
    }

} // namespace iden_bool

namespace not_bool {

    fuzz::bool_term
    not_by_truth_value(fuzz::fuzz_context ctx, fuzz::bool_term t)
    {
        fuzz::bool_term false_term = generators::false_bool::placeholder(ctx, t);
        fuzz::bool_term true_term = generators::true_bool::placeholder(ctx, t);
        return generators::ite_bool::placeholder(ctx, t, false_term, true_term);
    }

} // namespace not_bool

namespace and_bool {

    fuzz::bool_term
    and_comm(fuzz::fuzz_context ctx, fuzz::bool_term t1, fuzz::bool_term t2)
    {
        return generators::and_bool::placeholder(ctx, t2, t1);
    }

    fuzz::bool_term
    and_demorgan(fuzz::fuzz_context ctx, fuzz::bool_term t1, fuzz::bool_term t2)
    {
        fuzz::bool_term nt1 = generators::not_bool::placeholder(ctx, t1);
        fuzz::bool_term nt2 = generators::not_bool::placeholder(ctx, t2);
        fuzz::bool_term or_nts = generators::or_bool::placeholder(ctx, nt1, nt2);
        return generators::not_bool::placeholder(ctx, or_nts);
    }

} // namespace and_bool

namespace or_bool {

    fuzz::bool_term
    or_comm(fuzz::fuzz_context ctx, fuzz::bool_term t1, fuzz::bool_term t2)
    {
        return generators::or_bool::placeholder(ctx, t2, t1);
    }

    fuzz::bool_term
    or_demorgan(fuzz::fuzz_context ctx, fuzz::bool_term t1, fuzz::bool_term t2)
    {
        fuzz::bool_term nt1 = generators::not_bool::placeholder(ctx, t1);
        fuzz::bool_term nt2 = generators::not_bool::placeholder(ctx, t2);
        fuzz::bool_term and_nts = generators::and_bool::placeholder(ctx, nt1, nt2);
        return generators::not_bool::placeholder(ctx, and_nts);
    }

} // namespace or_bool

namespace xor_bool {

    fuzz::bool_term
    xor_comm(fuzz::fuzz_context ctx, fuzz::bool_term t1, fuzz::bool_term t2)
    {
        return generators::xor_bool::placeholder(ctx, t2, t1);
    }

    fuzz::bool_term
    xor_disjunct(fuzz::fuzz_context ctx, fuzz::bool_term t1, fuzz::bool_term t2)
    {
        fuzz::bool_term nt1 = generators::not_bool::placeholder(ctx, t1);
        fuzz::bool_term nt2 = generators::not_bool::placeholder(ctx, t2);
        fuzz::bool_term t1_and_nt2 = generators::and_bool::placeholder(ctx, t1, nt2);
        fuzz::bool_term t2_and_nt1 = generators::and_bool::placeholder(ctx, t2, nt1);
        return generators::or_bool::placeholder(ctx, t1_and_nt2, t2_and_nt1);
    }

    fuzz::bool_term
    xor_conjunct(fuzz::fuzz_context ctx, fuzz::bool_term t1, fuzz::bool_term t2)
    {
        fuzz::bool_term nt1 = generators::not_bool::placeholder(ctx, t1);
        fuzz::bool_term nt2 = generators::not_bool::placeholder(ctx, t2);
        fuzz::bool_term t1_or_t2 = generators::or_bool::placeholder(ctx, t1, t2);
        fuzz::bool_term nt1_or_nt2 = generators::or_bool::placeholder(ctx, nt1, nt2);
        return generators::and_bool::placeholder(ctx, t1_or_t2, nt1_or_nt2);
    }
}

namespace equal_bv {

    fuzz::bool_term
    check_equal_comm(fuzz::fuzz_context ctx, fuzz::bv_term t1, fuzz::bv_term t2)
    {
        return generators::equal_bv::placeholder(ctx, t2, t1);
    }

    fuzz::bool_term
    check_equal_by_sub_is_zero(fuzz::fuzz_context ctx, fuzz::bv_term t1, fuzz::bv_term t2)
    {
        fuzz::bv_term zero = generators::zero::placeholder(ctx, t1);
        fuzz::bv_term sub_ts = relations::sub::placeholder(ctx, t1, t2);
        return generators::equal_bv::placeholder(ctx, zero, sub_ts);
    }

    //fuzz::bool_term
    //check_equal_by_div_is_one(fuzz::fuzz_context ctx, fuzz::int_term t1, fuzz::int_term t2)
    //{
        //fuzz::int_term one = generators::one::placeholder(ctx, t1);
        //fuzz::int_bool zero = generators::zero::placeholder(ctx, fvs, e2);
        //fuzz::int_term div_ts = relations::division::placeholder(ctx, t1, t2);
        //fuzz::bool_bool check_zeroes = slv.mkTerm(CVC4::api::Kind::AND,
            //slv.mkTerm(CVC4::api::Kind::EQUAL, zero, e1),
            //slv.mkTerm(CVC4::api::Kind::EQUAL, zero, e2));
        //fuzz::bool_bool check_equal = generators::equal_int::placeholder(ctx, one, div_ts);
        //return slv.mkTerm(CVC4::api::Kind::OR, check_zeroes, check_equal);
    //}

} // namespace equal_bv

namespace extract_bv
{

    fuzz::bv_term
    extract_bit_by_bit(fuzz::fuzz_context ctx, fuzz::bv_term t, size_t start, size_t end)
    {
        fuzz::bv_term extracted = generators::extract_bit_bv::placeholder(ctx, t, start);
        for (size_t i = start + 1; i <= end; ++i)
        {
            fuzz::bv_term bit = generators::extract_bit_bv::placeholder(ctx, t, i);
            extracted = generators::concat_bv::placeholder(ctx, extracted, bit);
        }
        return extracted;
    }

} // namespace extract_bv

namespace extract_bit_bv
{

    fuzz::bv_term
    extract_by_range(fuzz::fuzz_context ctx, fuzz::bv_term t, size_t bit)
    {
        return generators::extract_bv::placeholder(ctx, t, bit, bit);
    }

} // namespace extract_bit_bv

namespace concat_bv
{
} // namespace concat_bv

namespace lt {

    fuzz::bool_term
    not_geq_base(fuzz::fuzz_context ctx, fuzz::bv_term t1, fuzz::bv_term t2)
    {
        fuzz::bool_term geq_term = generators::geq::placeholder(ctx, t1, t2);
        return generators::not_bool::placeholder(ctx, geq_term);
    }

} // namespace lt

namespace gt {

    fuzz::bool_term
    not_leq_base(fuzz::fuzz_context ctx, fuzz::bv_term t1, fuzz::bv_term t2)
    {
        fuzz::bool_term leq_term = generators::leq::placeholder(ctx, t1, t2);
        return generators::not_bool::placeholder(ctx, leq_term);
    }

} // namespace gt

namespace leq {

    fuzz::bool_term
    not_gt_base(fuzz::fuzz_context ctx, fuzz::bv_term t1, fuzz::bv_term t2)
    {
        fuzz::bool_term gt_term = generators::gt::placeholder(ctx, t1, t2);
        return generators::not_bool::placeholder(ctx, gt_term);
    }

} // namespace leq

namespace geq {

    fuzz::bool_term
    not_lt_base(fuzz::fuzz_context ctx, fuzz::bv_term t1, fuzz::bv_term t2)
    {
        fuzz::bool_term lt_term = generators::lt::placeholder(ctx, t1, t2);
        return generators::not_bool::placeholder(ctx, lt_term);
    }

} // namespace geq

namespace slt {

    fuzz::bool_term
    not_sgeq_base(fuzz::fuzz_context ctx, fuzz::bv_term t1, fuzz::bv_term t2)
    {
        fuzz::bool_term sgeq_term = generators::sgeq::placeholder(ctx, t1, t2);
        return generators::not_bool::placeholder(ctx, sgeq_term);
    }

} // namespace slt

namespace sgt {

    fuzz::bool_term
    not_sleq_base(fuzz::fuzz_context ctx, fuzz::bv_term t1, fuzz::bv_term t2)
    {
        fuzz::bool_term sleq_term = generators::sleq::placeholder(ctx, t1, t2);
        return generators::not_bool::placeholder(ctx, sleq_term);
    }

} // namespace sgt

namespace sleq {

    fuzz::bool_term
    not_sgt_base(fuzz::fuzz_context ctx, fuzz::bv_term t1, fuzz::bv_term t2)
    {
        fuzz::bool_term sgt_term = generators::sgt::placeholder(ctx, t1, t2);
        return generators::not_bool::placeholder(ctx, sgt_term);
    }

} // namespace sleq

namespace sgeq {

    fuzz::bool_term
    not_slt_base(fuzz::fuzz_context ctx, fuzz::bv_term t1, fuzz::bv_term t2)
    {
        fuzz::bool_term slt_term = generators::slt::placeholder(ctx, t1, t2);
        return generators::not_bool::placeholder(ctx, slt_term);
    }

} // namespace sgeq

} // namespace generators

/*******************************************************************************
 * Relations
 ******************************************************************************/

namespace relations {

namespace identity {

    fuzz::bv_term
    add_zero(fuzz::fuzz_context ctx, fuzz::bv_term t)
    {
        t = relations::identity::placeholder(ctx, t);
        fuzz::bv_term zero = generators::zero::placeholder(ctx, t);
        return relations::add::placeholder(ctx, t, zero);
    }

    fuzz::bv_term
    sub_zero(fuzz::fuzz_context ctx, fuzz::bv_term t)
    {
        t = relations::identity::placeholder(ctx, t);
        fuzz::bv_term zero = generators::zero::placeholder(ctx, t);
        return relations::sub::placeholder(ctx, t, zero);
    }

    fuzz::bv_term
    mul_one(fuzz::fuzz_context ctx, fuzz::bv_term t)
    {
        t = relations::identity::placeholder(ctx, t);
        fuzz::bv_term one = generators::one::placeholder(ctx, t);
        return relations::mul::placeholder(ctx, t, one);
    }

    fuzz::bv_term
    div_one(fuzz::fuzz_context ctx, fuzz::bv_term t)
    {
        t = relations::identity::placeholder(ctx, t);
        fuzz::bv_term one = generators::one::placeholder(ctx, t);
        return relations::division::placeholder(ctx, t, one);
    }

    fuzz::bv_term
    double_negative(fuzz::fuzz_context ctx, fuzz::bv_term t)
    {
        t = relations::identity::placeholder(ctx, t);
        fuzz::bv_term tmp_t = relations::neg_bv::placeholder(ctx, t);
        tmp_t = relations::identity::placeholder(ctx, tmp_t);
        return relations::neg_bv::placeholder(ctx, tmp_t);
    }

    fuzz::bv_term
    double_not(fuzz::fuzz_context ctx, fuzz::bv_term t)
    {
        t = relations::identity::placeholder(ctx, t);
        fuzz::bv_term tmp_t = relations::not_bv::placeholder(ctx, t);
        tmp_t = relations::identity::placeholder(ctx, tmp_t);
        return relations::not_bv::placeholder(ctx, tmp_t);
    }

    fuzz::bv_term
    iden_by_abs(fuzz::fuzz_context ctx, fuzz::bv_term t)
    {
        fuzz::bv_term iden_term = relations::identity::placeholder(ctx, t);
        fuzz::bv_term abs_t = relations::abs_bv::placeholder(ctx, t);
        fuzz::bool_term t_equal = generators::equal_bv::placeholder(ctx, abs_t, t);
        return generators::ite_bv_term_cond::placeholder(ctx, t_equal, abs_t, t);
    }

    //fuzz::int_term
    //sqrt_square(CVC4::api::Solver& c, fuzz::FreeVars& fvs, fuzz::int_term e)
    //{
        //fuzz::int_term two = c.mkInteger(2);
        //e = relations::identity::placeholder(c, fvs, e);
        //return c.mkTerm(CVC4::api::TO_INTEGER, c.mkTerm(CVC4::api::SQRT, c.mkTerm(CVC4::api::POW, e, two));
    //}
    //
    fuzz::bv_term
    iden_by_shr0(fuzz::fuzz_context ctx, fuzz::bv_term t)
    {
        return relations::shift_right_zero::placeholder(ctx, t, 0);
    }

    fuzz::bv_term
    iden_by_shl0(fuzz::fuzz_context ctx, fuzz::bv_term t)
    {
        return relations::shift_right_zero::placeholder(ctx, t, 0);
    }

    fuzz::bv_term
    iden_by_shr1(fuzz::fuzz_context ctx, fuzz::bv_term t)
    {
        return relations::shift_right_one::placeholder(ctx, t, 0);
    }

    fuzz::bv_term
    iden_by_shl1(fuzz::fuzz_context ctx, fuzz::bv_term t)
    {
        return relations::shift_right_one::placeholder(ctx, t, 0);
    }

    fuzz::bv_term
    iden_by_ror_rand(fuzz::fuzz_context ctx, fuzz::bv_term t)
    {
        size_t rotate_count = fuzz::fuzz_rand<unsigned int, unsigned int>(0, BV_SIZE - 1);
        t = relations::rotate_right_int::placeholder(ctx, t, rotate_count);
        size_t inverse_count = BV_SIZE - rotate_count;
        return relations::rotate_right_int::placeholder(ctx, t, inverse_count);
    }

    fuzz::bv_term
    iden_by_rol_rand(fuzz::fuzz_context ctx, fuzz::bv_term t)
    {
        size_t rotate_count = fuzz::fuzz_rand<unsigned int, unsigned int>(0, BV_SIZE - 1);
        t = relations::rotate_left_int::placeholder(ctx, t, rotate_count);
        size_t inverse_count = BV_SIZE - rotate_count;
        return relations::rotate_left_int::placeholder(ctx, t, inverse_count);
    }

    fuzz::bv_term
    iden_by_rolr_around(fuzz::fuzz_context ctx, fuzz::bv_term t)
    {
        size_t rotate_count = fuzz::fuzz_rand<unsigned int, unsigned int>(0, BV_SIZE - 1);
        t = relations::rotate_left_int::placeholder(ctx, t, rotate_count);
        return relations::rotate_right_int::placeholder(ctx, t, rotate_count);
    }

    fuzz::bv_term
    iden_by_rorl_around(fuzz::fuzz_context ctx, fuzz::bv_term t)
    {
        size_t rotate_count = fuzz::fuzz_rand<unsigned int, unsigned int>(0, BV_SIZE - 1);
        t = relations::rotate_right_int::placeholder(ctx, t, rotate_count);
        return relations::rotate_left_int::placeholder(ctx, t, rotate_count);
    }

    fuzz::bv_term
    iden_by_ite_false(fuzz::fuzz_context ctx, fuzz::bv_term t)
    {
        fuzz::bool_term fuzz_term = generators::fuzz_bool_term::placeholder(ctx);
        fuzz::bv_term dead = generators::fuzz_bv_term::placeholder(ctx);
        t = relations::identity::placeholder(ctx, t);
        fuzz::bool_term false_bool = generators::false_bool::placeholder(ctx, fuzz_term);
        return generators::ite_bv_term_cond::placeholder(ctx, false_bool, dead, t);
    }

    fuzz::bv_term
    iden_by_ite_true(fuzz::fuzz_context ctx, fuzz::bv_term t)
    {
        fuzz::bool_term fuzz_term = generators::fuzz_bool_term::placeholder(ctx);
        fuzz::bv_term dead = generators::fuzz_bv_term::placeholder(ctx);
        t = relations::identity::placeholder(ctx, t);
        fuzz::bool_term true_bool = generators::true_bool::placeholder(ctx, fuzz_term);
        return generators::ite_bv_term_cond::placeholder(ctx, true_bool, t, dead);
    }

    fuzz::bv_term
    iden_by_extract_concat(fuzz::fuzz_context ctx, fuzz::bv_term t)
    {
        size_t idx = fuzz::fuzz_rand<int, int>(0, BV_SIZE - 2);
        fuzz::bv_term rhs = generators::extract_bv::placeholder(ctx, t, 0, idx);
        size_t lhs_extract_bound = BV_SIZE - 1;
        fuzz::bv_term lhs = generators::extract_bv::placeholder(ctx, t, idx + 1, lhs_extract_bound);
        return generators::concat_bv::placeholder(ctx, lhs, rhs);
    }


} // namespace identity

namespace add {

    fuzz::bv_term
    add_comm(fuzz::fuzz_context ctx, fuzz::bv_term t1, fuzz::bv_term t2)
    {
        t1 = relations::identity::placeholder(ctx, t1);
        t2 = relations::identity::placeholder(ctx, t2);
        return relations::add::placeholder(ctx, t2, t1);
    }

    fuzz::bv_term
    add_by_sub(fuzz::fuzz_context ctx, fuzz::bv_term t1, fuzz::bv_term t2)
    {
        t1 = relations::identity::placeholder(ctx, t1);
        t2 = relations::identity::placeholder(ctx, t2);
        t2 = relations::neg_bv::placeholder(ctx, t2);
        return relations::sub::placeholder(ctx, t1, t2);
    }

} // namespace add

namespace sub {

    fuzz::bv_term
    sub_by_add(fuzz::fuzz_context ctx, fuzz::bv_term t1, fuzz::bv_term t2)
    {
        t1 = relations::identity::placeholder(ctx, t1);
        t2 = relations::identity::placeholder(ctx, t2);
        t2 = relations::neg_bv::placeholder(ctx, t2);
        return relations::add::placeholder(ctx, t1, t2);
    }

} // namespace sub

namespace mul {

    fuzz::bv_term
    mul_comm(fuzz::fuzz_context ctx, fuzz::bv_term t1, fuzz::bv_term t2)
    {
        t1 = relations::identity::placeholder(ctx, t1);
        t2 = relations::identity::placeholder(ctx, t2);
        return relations::mul::placeholder(ctx, t2, t1);
    }

} // namespace mul

namespace division {

} // namespace division

namespace modulo {

    fuzz::bv_term
    mod_by_sub(fuzz::fuzz_context ctx, fuzz::bv_term t1, fuzz::bv_term t2)
    {
        t1 = relations::identity::placeholder(ctx, t1);
        t2 = relations::identity::placeholder(ctx, t2);
        fuzz::bv_term zero = generators::zero::placeholder(ctx, t1);
        fuzz::bool_term chk_zero = generators::equal_bv::placeholder(ctx, t2, zero);
        // make t1 - t2 * t1 / t2
        // TODO make base
        fuzz::bv_term t1_div_t2 = relations::division::placeholder(ctx, t1, t2);
        fuzz::bv_term t2_mul_div = relations::mul::placeholder(ctx, t2, t1_div_t2);
        fuzz::bv_term t1_sub_mul = relations::sub::placeholder(ctx, t1, t2_mul_div);
        return generators::ite_bv_term_cond::placeholder(ctx, chk_zero, t1, t1_sub_mul);
    }

} // namespace modulo

namespace abs_bv
{
    fuzz::bv_term
    abs_by_check_gt_zero(fuzz::fuzz_context ctx, fuzz::bv_term t)
    {
        fuzz::bv_term zero = generators::zero::placeholder(ctx, t);
        fuzz::bool_term gt_term = generators::sgt::placeholder(ctx, t, zero);
        fuzz::bv_term abs_t = relations::abs_bv::placeholder(ctx, t);
        return generators::ite_bv_term_cond::placeholder(ctx, gt_term, t, abs_t);
    }

    fuzz::bv_term
    abs_by_check_lt_zero(fuzz::fuzz_context ctx, fuzz::bv_term t)
    {
        fuzz::bv_term zero = generators::zero::placeholder(ctx, t);
        fuzz::bool_term lt_term = generators::slt::placeholder(ctx, t, zero);
        fuzz::bv_term abs_t = relations::abs_bv::placeholder(ctx, t);
        return generators::ite_bv_term_cond::placeholder(ctx, lt_term, abs_t, t);
    }

} // namespace abs

namespace neg_bv {

    fuzz::bv_term
    neg_by_sub_zero(fuzz::fuzz_context ctx, fuzz::bv_term t)
    {
        fuzz::bv_term zero = generators::zero::placeholder(ctx, t);
        return relations::sub::placeholder(ctx, zero, t);
    }

    fuzz::bv_term
    neg_by_sub_times_two(fuzz::fuzz_context ctx, fuzz::bv_term t)
    {
        fuzz::bv_term one = generators::one::placeholder(ctx, t);
        fuzz::bv_term two = generators::one::placeholder(ctx, t);
        two = relations::add::placeholder(ctx, one, two);
        fuzz::bv_term two_t = relations::mul::placeholder(ctx, t, two);
        return relations::sub::placeholder(ctx, t, two_t);
    }

} // namespace neg

namespace not_bv {

    fuzz::bv_term
    not_by_xor_mask(fuzz::fuzz_context ctx, fuzz::bv_term t)
    {
        fuzz::bv_term mask = generators::one::placeholder(ctx, t);
        mask = relations::neg_bv::placeholder(ctx, mask);
        return relations::xor_bv::placeholder(ctx, t, mask);
    }

}

namespace or_bv {

    fuzz::bv_term
    commute_or(fuzz::fuzz_context ctx, fuzz::bv_term t1, fuzz::bv_term t2)
    {
        return relations::or_bv::placeholder(ctx, t2, t1);
    }

    fuzz::bv_term
    demorgan_or(fuzz::fuzz_context ctx, fuzz::bv_term t1, fuzz::bv_term t2)
    {
        fuzz::bv_term not_t1  = relations::not_bv::placeholder(ctx, t1);
        fuzz::bv_term not_t2  = relations::not_bv::placeholder(ctx, t2);
        fuzz::bv_term and_nots = relations::and_bv::placeholder(ctx, not_t1, not_t2);
        return relations::not_bv::placeholder(ctx, and_nots);
    }

} // namespace or_bv

namespace and_bv {

    fuzz::bv_term
    commute_and(fuzz::fuzz_context ctx, fuzz::bv_term t1, fuzz::bv_term t2)
    {
        return relations::and_bv::placeholder(ctx, t2, t1);
    }

    fuzz::bv_term
    demorgan_and(fuzz::fuzz_context ctx, fuzz::bv_term t1, fuzz::bv_term t2)
    {
        fuzz::bv_term not_t1  = relations::not_bv::placeholder(ctx, t1);
        fuzz::bv_term not_t2  = relations::not_bv::placeholder(ctx, t2);
        fuzz::bv_term or_nots = relations::or_bv::placeholder(ctx, not_t1, not_t2);
        return relations::not_bv::placeholder(ctx, or_nots);
    }

} // namespace and_bv

namespace xor_bv {

    fuzz::bv_term
    commute_xor(fuzz::fuzz_context ctx, fuzz::bv_term t1, fuzz::bv_term t2)
    {
        return relations::xor_bv::placeholder(ctx, t2, t1);
    }

    fuzz::bv_term
    xor_disjunct(fuzz::fuzz_context ctx, fuzz::bv_term t1, fuzz::bv_term t2)
    {
        fuzz::bv_term nt1  = relations::not_bv::placeholder(ctx, t1);
        fuzz::bv_term nt2  = relations::not_bv::placeholder(ctx, t2);
        fuzz::bv_term t1_and_nt2 = relations::and_bv::placeholder(ctx, t1, nt2);
        fuzz::bv_term t2_and_nt1 = relations::and_bv::placeholder(ctx, t2, nt1);
        return relations::or_bv::placeholder(ctx, t1_and_nt2, t2_and_nt1);
    }

    fuzz::bv_term
    xor_conjunct(fuzz::fuzz_context ctx, fuzz::bv_term t1, fuzz::bv_term t2)
    {
        fuzz::bv_term nt1  = relations::not_bv::placeholder(ctx, t1);
        fuzz::bv_term nt2  = relations::not_bv::placeholder(ctx, t2);
        fuzz::bv_term t1_or_t2 = relations::or_bv::placeholder(ctx, t1, t2);
        fuzz::bv_term nt1_or_nt2 = relations::or_bv::placeholder(ctx, nt1, nt2);
        return relations::and_bv::placeholder(ctx, t1_or_t2, nt1_or_nt2);
    }

}

namespace rotate_left_int {

    fuzz::bv_term
    rol_by_ror(fuzz::fuzz_context ctx, fuzz::bv_term t, size_t rot_count)
    {
        size_t rot_value = BV_SIZE - rot_count;
        return relations::rotate_right_int::placeholder(ctx, t, rot_value);
    }

}

namespace rotate_right_int {

    fuzz::bv_term
    ror_by_rol(fuzz::fuzz_context ctx, fuzz::bv_term t, size_t rot_count)
    {
        size_t rot_value = BV_SIZE - rot_count;
        return relations::rotate_left_int::placeholder(ctx, t, rot_value);
    }

}

namespace shift_left_zero {

    fuzz::bv_term
    shl0_by_mask(fuzz::fuzz_context ctx, fuzz::bv_term t, size_t sh_count)
    {
        fuzz::bv_term mask = generators::one::placeholder(ctx, t);
        mask = relations::neg_bv::placeholder(ctx, mask);
        mask = relations::shift_left_zero::placeholder(ctx, mask, sh_count);
        t = relations::rotate_left_int::placeholder(ctx, t, sh_count);
        return relations::and_bv::placeholder(ctx, mask, t);
    }
    //
    //fuzz::bv_term
    //shl0_by_mask(fuzz::fuzz_context ctx, fuzz::bv_term t, size_t sh_count)
    //{
        //fuzz::bv_term mask = generators::zero::placeholder(ctx, t);
        //mask = generators::extract_bv::placeholder(ctx, mask, 0, sh_count - 1);
        //size_t ex_val = BV_SIZE - sh_count;
        //t = generators::extract_bv::placeholder(ctx, t, 0, ex_val);
        //fuzz::bool_term cond_gte_size = generators::geq::placeholder(ctx,
        //relations::and_bv::placeholder(ctx, mask, t);
        //return yices_ite(sh_count == 0, t, yices_ite(sh_count >= BV_SIZE, zero, concat(t, mask)));
    //}

}

namespace shift_right_zero {

    fuzz::bv_term
    shr0_by_mask(fuzz::fuzz_context ctx, fuzz::bv_term t, size_t sh_count)
    {
        fuzz::bv_term mask = generators::one::placeholder(ctx, t);
        mask = relations::neg_bv::placeholder(ctx, mask);
        mask = relations::shift_right_zero::placeholder(ctx, mask, sh_count);
        t = relations::rotate_right_int::placeholder(ctx, t, sh_count);
        return relations::and_bv::placeholder(ctx, mask, t);
    }

}

namespace shift_left_one {

    fuzz::bv_term
    shl1_by_mask(fuzz::fuzz_context ctx, fuzz::bv_term t, size_t sh_count)
    {
        fuzz::bv_term mask = generators::zero::placeholder(ctx, t);
        mask = relations::shift_left_one::placeholder(ctx, mask, sh_count);
        t = relations::rotate_left_int::placeholder(ctx, t, sh_count);
        return relations::or_bv::placeholder(ctx, mask, t);
    }

}

namespace shift_right_one {

    fuzz::bv_term
    shr1_by_mask(fuzz::fuzz_context ctx, fuzz::bv_term t, size_t sh_count)
    {
        fuzz::bv_term mask = generators::zero::placeholder(ctx, t);
        mask = relations::shift_right_one::placeholder(ctx, mask, sh_count);
        t = relations::rotate_right_int::placeholder(ctx, t, sh_count);
        return relations::or_bv::placeholder(ctx, mask, t);
    }

}

namespace ite_bv {

    fuzz::bv_term
    ite_by_cpp_check(fuzz::fuzz_context ctx, bool b, fuzz::bv_term t, fuzz::bv_term e)
    {
        if (b)
        {
            return relations::identity::placeholder(ctx, t);
        }
        return relations::identity::placeholder(ctx, e);
    }

} // namespace ite_bv

} // namespace relations

} // namespace metalib
