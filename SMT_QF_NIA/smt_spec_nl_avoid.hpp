namespace metalib {

// Forward declarations
//
namespace generators {
namespace fuzz_int_term {
    fuzz::int_term placeholder(fuzz::fuzz_context);
}
namespace fuzz_bool_term {
    fuzz::bool_term placeholder(fuzz::fuzz_context);
}
namespace zero {
    fuzz::int_term placeholder(fuzz::fuzz_context, fuzz::int_term);
}
namespace one {
    fuzz::int_term placeholder(fuzz::fuzz_context, fuzz::int_term);
}
namespace true_expr {
    fuzz::bool_term placeholder(fuzz::fuzz_context, fuzz::bool_term);
}
namespace false_expr {
    fuzz::bool_term placeholder(fuzz::fuzz_context, fuzz::bool_term);
}
namespace iden_bool {
    fuzz::bool_term placeholder(fuzz::fuzz_context, fuzz::bool_term);
}
namespace not_expr {
    fuzz::bool_term placeholder(fuzz::fuzz_context, fuzz::bool_term);
}
namespace and_expr {
    fuzz::bool_term placeholder(fuzz::fuzz_context, fuzz::bool_term, fuzz::bool_term);
}
namespace or_expr {
    fuzz::bool_term placeholder(fuzz::fuzz_context, fuzz::bool_term, fuzz::bool_term);
}
namespace xor_expr {
    fuzz::bool_term placeholder(fuzz::fuzz_context, fuzz::bool_term, fuzz::bool_term);
}
namespace equal_bool {
    fuzz::bool_term placeholder(fuzz::fuzz_context, fuzz::bool_term, fuzz::bool_term);
}
namespace equal_int {
    fuzz::bool_term placeholder(fuzz::fuzz_context, fuzz::int_term, fuzz::int_term);
}
namespace ite_integer_term_cond {
    fuzz::int_term placeholder(fuzz::fuzz_context, fuzz::bool_term, fuzz::int_term, fuzz::int_term);
}
namespace lt {
    fuzz::bool_term placeholder(fuzz::fuzz_context, fuzz::int_term, fuzz::int_term);
}
namespace gt {
    fuzz::bool_term placeholder(fuzz::fuzz_context, fuzz::int_term, fuzz::int_term);
}
namespace leq {
    fuzz::bool_term placeholder(fuzz::fuzz_context, fuzz::int_term, fuzz::int_term);
}
namespace geq {
    fuzz::bool_term placeholder(fuzz::fuzz_context, fuzz::int_term, fuzz::int_term);
}
namespace ite_bool {
    fuzz::bool_term placeholder(fuzz::fuzz_context, fuzz::bool_term, fuzz::bool_term, fuzz::bool_term);
}
namespace mul {
    fuzz::int_term placeholder(fuzz::fuzz_context, fuzz::int_term, fuzz::int_term);
}
namespace division {
    fuzz::int_term placeholder(fuzz::fuzz_context, fuzz::int_term, fuzz::int_term);
}
namespace modulo {
    fuzz::int_term placeholder(fuzz::fuzz_context, fuzz::int_term, fuzz::int_term);
}

} // namespace generators

namespace relations {
namespace identity {
    fuzz::int_term placeholder(fuzz::fuzz_context, fuzz::int_term);
}
namespace add {
    fuzz::int_term placeholder(fuzz::fuzz_context, fuzz::int_term, fuzz::int_term);
}
namespace sub {
    fuzz::int_term placeholder(fuzz::fuzz_context, fuzz::int_term, fuzz::int_term);
}
namespace abs_expr {
    fuzz::int_term placeholder(fuzz::fuzz_context, fuzz::int_term);
}
namespace neg {
    fuzz::int_term placeholder(fuzz::fuzz_context, fuzz::int_term);
}
namespace ite_integer {
    fuzz::int_term placeholder(fuzz::fuzz_context, bool, fuzz::int_term, fuzz::int_term);
}
} //namespace relations

namespace generators {

namespace fuzz_int_term {

    fuzz::int_term
    get_expr_by_fuzz(fuzz::fuzz_context ctx)
    {
        fuzz::int_term fuzz = fuzz::fuzz_new<fuzz::int_term>();
        return fuzz;
    }

} // namespace fuzz_int_term

namespace fuzz_bool_term {

    fuzz::bool_term
    get_expr_by_fuzz(fuzz::fuzz_context ctx)
    {
        fuzz::bool_term fuzz = fuzz::fuzz_new<fuzz::bool_term>();
        return fuzz;
    }

} // namespace fuzz_bool_term

namespace zero {

    fuzz::int_term
    zero_by_mul(fuzz::fuzz_context ctx, fuzz::int_term t)
    {
        fuzz::int_term zero = generators::zero::placeholder(ctx, t);
        return generators::mul::placeholder(ctx, t, zero);
    }

    fuzz::int_term
    zero_by_sub(fuzz::fuzz_context ctx, fuzz::int_term t)
    {
        fuzz::int_term iden_term = relations::identity::placeholder(ctx, t);
        return relations::sub::placeholder(ctx, t, iden_term);
    }

    fuzz::int_term
    zero_by_fuzz_sub(fuzz::fuzz_context ctx, fuzz::int_term t)
    {
        fuzz::int_term fuzz = generators::fuzz_int_term::placeholder(ctx);
        fuzz::int_term iden_fuzz = relations::identity::placeholder(ctx, fuzz);
        return relations::sub::placeholder(ctx, fuzz, iden_fuzz);
    }

    fuzz::int_term
    zero_by_mod_one(fuzz::fuzz_context ctx, fuzz::int_term t)
    {
        t = relations::identity::placeholder(ctx, t);
        fuzz::int_term one = generators::one::placeholder(ctx, t);
        return generators::modulo::placeholder(ctx, t, one);
    }

    fuzz::int_term
    zero_by_mod_one_fuzz(fuzz::fuzz_context ctx, fuzz::int_term t)
    {
        fuzz::int_term fuzz = generators::fuzz_int_term::placeholder(ctx);
        fuzz::int_term one = generators::one::placeholder(ctx, t);
        return generators::modulo::placeholder(ctx, fuzz, one);
    }

    //fuzz::int_term
    //zero_by_mod(fuzz::fuzz_context ctx, fuzz::int_term t)
    //{
        //fuzz::int_term iden_term = relations::identity::placeholder(ctx, t);
        //fuzz::int_term tmp_zero = generators::zero::placeholder(ctx, t);
        //fuzz::int_term mod_ts = generators::modulo::placeholder(ctx, t, iden_term);
        //return t.eqTerm(tmp_zero).iteTerm(tmp_zero, mod_ts);
    //}

    //fuzz::int_term
    //zero_by_div(fuzz::fuzz_context ctx, fuzz::int_term t)
    //{
        //fuzz::int_term tmp_zero = generators::zero::placeholder(ctx, t);
        //fuzz::bool_term is_zero = tmp_zero.eqTerm(t);
        //fuzz::int_term tmp_zero_return = generators::zero::placeholder(ctx, t);
        //fuzz::int_term div_ts = generators::division::placeholder(ctx, tmp_zero, t);
        //return is_zero.iteTerm(tmp_zero_return, div_ts);
    //}

    //fuzz::int_term
    //zero_by_div_fuzz(fuzz::fuzz_context ctx, fuzz::int_term t)
    //{
        //fuzz::int_term fuzz = generators::fuzz_int_term::placeholder(ctx);
        //fuzz::int_term tmp_zero = generators::zero::placeholder(ctx, fuzz);
        //fuzz::bool_term is_zero = tmp_zero.eqTerm(fuzz);
        //fuzz::int_term tmp_zero_return = generators::zero::placeholder(ctx, fuzz);
        //fuzz::int_term div_ts = generators::division::placeholder(ctx, tmp_zero, iden_fuzz);
        //return is_zero.iteTerm(tmp_zero_return, div_ts);
    //}

} // namespace zero

namespace one {

    fuzz::int_term
    one_by_div(fuzz::fuzz_context ctx, fuzz::int_term t)
    {
        fuzz::int_term iden_term = relations::identity::placeholder(ctx, t);
        fuzz::int_term tmp_zero = generators::zero::placeholder(ctx, t);
        fuzz::bool_term is_zero = generators::equal_int::placeholder(ctx, tmp_zero, t);
        fuzz::int_term div_ts = generators::division::placeholder(ctx, t, iden_term);
        fuzz::int_term one = generators::one::placeholder(ctx, t);
        return generators::ite_integer_term_cond::placeholder(ctx, is_zero, one, div_ts);
    }

    fuzz::int_term
    one_by_fuzz_div(fuzz::fuzz_context ctx, fuzz::int_term t)
    {
        fuzz::int_term fuzz = generators::fuzz_int_term::placeholder(ctx);
        fuzz::int_term iden_fuzz = relations::identity::placeholder(ctx, fuzz);
        fuzz::int_term tmp_zero = generators::zero::placeholder(ctx, fuzz);
        fuzz::bool_term is_zero = generators::equal_int::placeholder(ctx, tmp_zero, fuzz);
        fuzz::int_term div_ts = generators::division::placeholder(ctx, fuzz, iden_fuzz);
        fuzz::int_term one = generators::one::placeholder(ctx, fuzz);
        return generators::ite_integer_term_cond::placeholder(ctx, is_zero, one, div_ts);
    }

    //fuzz::int_term
    //one_by_pw(CVC4::api::Solver& c, fuzz::FreeVars& fvs, fuzz::int_term f)
    //{
        //fuzz::int_term tmp_zero = zero::placeholder(c, f);
        //fuzz::int_term is_zero = tmp_zero.eqTerm(f);
        //return is_zero.iteTerm(placeholder(c, f),
            //c.mkTerm(CVC4::api::POW, f, tmp_zero));
    //}

} // namespace one

namespace true_expr {

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
        fuzz::bool_term false_term = generators::false_expr::placeholder(ctx, t);
        return generators::not_expr::placeholder(ctx, false_term);
    }

    fuzz::bool_term
    get_true_by_or_true(fuzz::fuzz_context ctx, fuzz::bool_term t)
    {
        t = generators::iden_bool::placeholder(ctx, t);
        fuzz::bool_term true_term = generators::true_expr::placeholder(ctx, t);
        return generators::or_expr::placeholder(ctx, true_term, t);
    }

    fuzz::bool_term
    get_true_by_or_true_fuzz(fuzz::fuzz_context ctx, fuzz::bool_term t)
    {
        fuzz::bool_term true_term = generators::true_expr::placeholder(ctx, t);
        fuzz::bool_term fuzz_term = generators::fuzz_bool_term::placeholder(ctx);
        return generators::or_expr::placeholder(ctx, true_term, t);
    }

    fuzz::bool_term
    get_true_by_nxor(fuzz::fuzz_context ctx, fuzz::bool_term t)
    {
        fuzz::bool_term iden_term = generators::iden_bool::placeholder(ctx, t);
        fuzz::bool_term xor_term = generators::xor_expr::placeholder(ctx, t, iden_term);
        return generators::not_expr::placeholder(ctx, xor_term);
    }

    fuzz::bool_term
    get_true_by_nxor_fuzz(fuzz::fuzz_context ctx, fuzz::bool_term t)
    {
        fuzz::bool_term fuzz_term = generators::fuzz_bool_term::placeholder(ctx);
        fuzz::bool_term iden_term = generators::iden_bool::placeholder(ctx, fuzz_term);
        fuzz::bool_term xor_term = generators::xor_expr::placeholder(ctx, fuzz_term, iden_term);
        return generators::not_expr::placeholder(ctx, xor_term);
    }

    fuzz::bool_term
    get_true_by_lte_fuzz(fuzz::fuzz_context ctx, fuzz::bool_term t)
    {
        fuzz::int_term fuzz_term = generators::fuzz_int_term::placeholder(ctx);
        fuzz::int_term iden_term = relations::identity::placeholder(ctx, fuzz_term);
        return generators::leq::placeholder(ctx, fuzz_term, iden_term);
    }

    fuzz::bool_term
    get_true_by_gte_fuzz(fuzz::fuzz_context ctx, fuzz::bool_term t)
    {
        fuzz::int_term fuzz_term = generators::fuzz_int_term::placeholder(ctx);
        fuzz::int_term iden_term = relations::identity::placeholder(ctx, fuzz_term);
        return generators::geq::placeholder(ctx, fuzz_term, iden_term);
    }

} // namespace true_expr

namespace false_expr {

    fuzz::bool_term
    get_false_by_equal(fuzz::fuzz_context ctx, fuzz::bool_term t)
    {
        fuzz::bool_term iden_term = generators::iden_bool::placeholder(ctx, t);
        fuzz::bool_term eq_term = generators::equal_bool::placeholder(ctx, t, iden_term);
        return generators::not_expr::placeholder(ctx, eq_term);
    }

    fuzz::bool_term
    get_false_by_not_true(fuzz::fuzz_context ctx, fuzz::bool_term t)
    {
        t = generators::iden_bool::placeholder(ctx, t);
        fuzz::bool_term true_term = generators::true_expr::placeholder(ctx, t);
        return generators::not_expr::placeholder(ctx, true_term);
    }

    fuzz::bool_term
    get_false_by_and_false(fuzz::fuzz_context ctx, fuzz::bool_term t)
    {
        t = generators::iden_bool::placeholder(ctx, t);
        fuzz::bool_term false_term = generators::false_expr::placeholder(ctx, t);
        return generators::and_expr::placeholder(ctx, false_term, t);
    }

    fuzz::bool_term
    get_false_by_and_false_fuzz(fuzz::fuzz_context ctx, fuzz::bool_term t)
    {
        fuzz::bool_term false_term = generators::false_expr::placeholder(ctx, t);
        fuzz::bool_term fuzz_term = generators::fuzz_bool_term::placeholder(ctx);
        return generators::and_expr::placeholder(ctx, false_term, t);
    }

    fuzz::bool_term
    get_false_by_xor(fuzz::fuzz_context ctx, fuzz::bool_term t)
    {
        fuzz::bool_term iden_term = generators::iden_bool::placeholder(ctx, t);
        return generators::xor_expr::placeholder(ctx, t, iden_term);
    }

    fuzz::bool_term
    get_false_by_xor_fuzz(fuzz::fuzz_context ctx, fuzz::bool_term t)
    {
        fuzz::bool_term fuzz_term = generators::fuzz_bool_term::placeholder(ctx);
        fuzz::bool_term iden_term = generators::iden_bool::placeholder(ctx, fuzz_term);
        return generators::xor_expr::placeholder(ctx, fuzz_term, iden_term);
    }

    fuzz::bool_term
    get_false_by_lt_fuzz(fuzz::fuzz_context ctx, fuzz::bool_term t)
    {
        fuzz::int_term fuzz_term = generators::fuzz_int_term::placeholder(ctx);
        fuzz::int_term iden_term = relations::identity::placeholder(ctx, fuzz_term);
        return generators::lt::placeholder(ctx, fuzz_term, iden_term);
    }

    fuzz::bool_term
    get_false_by_gt_fuzz(fuzz::fuzz_context ctx, fuzz::bool_term t)
    {
        fuzz::int_term fuzz_term = generators::fuzz_int_term::placeholder(ctx);
        fuzz::int_term iden_term = relations::identity::placeholder(ctx, fuzz_term);
        return generators::gt::placeholder(ctx, fuzz_term, iden_term);
    }

} // namespace false_expr

namespace iden_bool {

    fuzz::bool_term
    iden_by_and(fuzz::fuzz_context ctx, fuzz::bool_term t)
    {
        t = generators::iden_bool::placeholder(ctx, t);
        fuzz::bool_term true_term = generators::true_expr::placeholder(ctx, t);
        return generators::and_expr::placeholder(ctx, t, true_term);
    }

    fuzz::bool_term
    iden_by_or(fuzz::fuzz_context ctx, fuzz::bool_term t)
    {
        t = generators::iden_bool::placeholder(ctx, t);
        fuzz::bool_term false_term = generators::false_expr::placeholder(ctx, t);
        return generators::or_expr::placeholder(ctx, t, false_term);
    }

    fuzz::bool_term
    iden_by_xor(fuzz::fuzz_context ctx, fuzz::bool_term t)
    {
        fuzz::bool_term iden_term = generators::iden_bool::placeholder(ctx, t);
        fuzz::bool_term xor_once = generators::xor_expr::placeholder(ctx, iden_term, iden_term);
        return generators::xor_expr::placeholder(ctx, xor_once, iden_term);
    }
} // namespace iden_bool

namespace not_expr {

    fuzz::bool_term
    not_by_truth_value(fuzz::fuzz_context ctx, fuzz::bool_term t)
    {
        fuzz::bool_term false_term = generators::false_expr::placeholder(ctx, t);
        fuzz::bool_term true_term = generators::true_expr::placeholder(ctx, t);
        return generators::ite_bool::placeholder(ctx, t, false_term, true_term);
    }

} // namespace not_expr

namespace and_expr {

    fuzz::bool_term
    and_comm(fuzz::fuzz_context ctx, fuzz::bool_term t1, fuzz::bool_term t2)
    {
        return generators::and_expr::placeholder(ctx, t2, t1);
    }

    fuzz::bool_term
    and_demorgan(fuzz::fuzz_context ctx, fuzz::bool_term t1, fuzz::bool_term t2)
    {
        fuzz::bool_term nt1 = generators::not_expr::placeholder(ctx, t1);
        fuzz::bool_term nt2 = generators::not_expr::placeholder(ctx, t2);
        fuzz::bool_term or_nts = generators::or_expr::placeholder(ctx, nt1, nt2);
        return generators::not_expr::placeholder(ctx, or_nts);
    }

} // namespace and_expr

namespace or_expr {

    fuzz::bool_term
    or_comm(fuzz::fuzz_context ctx, fuzz::bool_term t1, fuzz::bool_term t2)
    {
        return generators::or_expr::placeholder(ctx, t2, t1);
    }

    fuzz::bool_term
    or_demorgan(fuzz::fuzz_context ctx, fuzz::bool_term t1, fuzz::bool_term t2)
    {
        fuzz::bool_term nt1 = generators::not_expr::placeholder(ctx, t1);
        fuzz::bool_term nt2 = generators::not_expr::placeholder(ctx, t2);
        fuzz::bool_term and_nts = generators::and_expr::placeholder(ctx, nt1, nt2);
        return generators::not_expr::placeholder(ctx, and_nts);
    }

} // namespace or_expr

namespace xor_expr {

    fuzz::bool_term
    xor_comm(fuzz::fuzz_context ctx, fuzz::bool_term t1, fuzz::bool_term t2)
    {
        return generators::xor_expr::placeholder(ctx, t2, t1);
    }

    fuzz::bool_term
    xor_disjunct(fuzz::fuzz_context ctx, fuzz::bool_term t1, fuzz::bool_term t2)
    {
        fuzz::bool_term nt1 = generators::not_expr::placeholder(ctx, t1);
        fuzz::bool_term nt2 = generators::not_expr::placeholder(ctx, t2);
        fuzz::bool_term t1_and_nt2 = generators::and_expr::placeholder(ctx, t1, nt2);
        fuzz::bool_term t2_and_nt1 = generators::and_expr::placeholder(ctx, t2, nt1);
        return generators::or_expr::placeholder(ctx, t1_and_nt2, t2_and_nt1);
    }

    fuzz::bool_term
    xor_conjunct(fuzz::fuzz_context ctx, fuzz::bool_term t1, fuzz::bool_term t2)
    {
        fuzz::bool_term nt1 = generators::not_expr::placeholder(ctx, t1);
        fuzz::bool_term nt2 = generators::not_expr::placeholder(ctx, t2);
        fuzz::bool_term t1_or_t2 = generators::or_expr::placeholder(ctx, t1, t2);
        fuzz::bool_term nt1_or_nt2 = generators::or_expr::placeholder(ctx, nt1, nt2);
        return generators::and_expr::placeholder(ctx, t1_or_t2, nt1_or_nt2);
    }

}

namespace equal_int {

    fuzz::bool_term
    check_equal_comm(fuzz::fuzz_context ctx, fuzz::int_term t1, fuzz::int_term t2)
    {
        return generators::equal_int::placeholder(ctx, t2, t1);
    }

    fuzz::bool_term
    check_equal_by_sub_is_zero(fuzz::fuzz_context ctx, fuzz::int_term t1, fuzz::int_term t2)
    {
        fuzz::int_term zero = generators::zero::placeholder(ctx, t1);
        fuzz::int_term sub_ts = relations::sub::placeholder(ctx, t1, t2);
        return generators::equal_int::placeholder(ctx, zero, sub_ts);
    }

    //fuzz::bool_term
    //check_equal_by_div_is_one(fuzz::fuzz_context ctx, fuzz::int_term t1, fuzz::int_term t2)
    //{
        //fuzz::int_term one = generators::one::placeholder(ctx, t1);
        //fuzz::int_expr zero = generators::zero::placeholder(ctx, fvs, e2);
        //fuzz::int_term div_ts = relations::division::placeholder(ctx, t1, t2);
        //fuzz::bool_expr check_zeroes = slv.mkTerm(CVC4::api::Kind::AND,
            //slv.mkTerm(CVC4::api::Kind::EQUAL, zero, e1),
            //slv.mkTerm(CVC4::api::Kind::EQUAL, zero, e2));
        //fuzz::bool_expr check_equal = generators::equal_int::placeholder(ctx, one, div_ts);
        //return slv.mkTerm(CVC4::api::Kind::OR, check_zeroes, check_equal);
    //}

} // namespace equal_int

namespace lt {

    fuzz::bool_term
    not_geq_base(fuzz::fuzz_context ctx, fuzz::int_term t1, fuzz::int_term t2)
    {
        fuzz::bool_term geq_term = generators::geq::placeholder(ctx, t1, t2);
        return generators::not_expr::placeholder(ctx, geq_term);
    }

} // namespace lt

namespace gt {

    fuzz::bool_term
    not_leq_base(fuzz::fuzz_context ctx, fuzz::int_term t1, fuzz::int_term t2)
    {
        fuzz::bool_term leq_term = generators::leq::placeholder(ctx, t1, t2);
        return generators::not_expr::placeholder(ctx, leq_term);
    }

} // namespace gt

namespace leq {

    fuzz::bool_term
    not_gt_base(fuzz::fuzz_context ctx, fuzz::int_term t1, fuzz::int_term t2)
    {
        fuzz::bool_term gt_term = generators::gt::placeholder(ctx, t1, t2);
        return generators::not_expr::placeholder(ctx, gt_term);
    }

} // namespace leq

namespace geq {

    fuzz::bool_term
    not_lt_base(fuzz::fuzz_context ctx, fuzz::int_term t1, fuzz::int_term t2)
    {
        fuzz::bool_term lt_term = generators::lt::placeholder(ctx, t1, t2);
        return generators::not_expr::placeholder(ctx, lt_term);
    }

} // namespace geq

namespace mul {

    fuzz::int_term
    mul_comm(fuzz::fuzz_context ctx, fuzz::int_term t1, fuzz::int_term t2)
    {
        t1 = relations::identity::placeholder(ctx, t1);
        t2 = relations::identity::placeholder(ctx, t2);
        return generators::mul::placeholder(ctx, t2, t1);
    }

} // namespace mul

namespace division {

} // namespace division

namespace modulo {

    fuzz::int_term
    mod_by_sub(fuzz::fuzz_context ctx, fuzz::int_term t1, fuzz::int_term t2)
    {
        t1 = relations::identity::placeholder(ctx, t1);
        t2 = relations::identity::placeholder(ctx, t2);
        fuzz::int_term zero = generators::zero::placeholder(ctx, t1);
        fuzz::bool_term chk_zero = generators::equal_int::placeholder(ctx, t2, zero);
        // make t1 - t2 * t1 / t2
        // TODO make base
        fuzz::int_term t1_div_t2 = generators::division::placeholder(ctx, t1, t2);
        fuzz::int_term t2_mul_div = generators::mul::placeholder(ctx, t2, t1_div_t2);
        fuzz::int_term t1_sub_mul = relations::sub::placeholder(ctx, t1, t2_mul_div);
        return generators::ite_integer_term_cond::placeholder(ctx, chk_zero, t1, t1_sub_mul);
        //return slv.mkTerm(CVC4::api::ITE,
            //slv.mkTerm(CVC4::api::EQUAL, t2, zero), t1,
            //slv.mkTerm(CVC4::api::MINUS, t1,
                //slv.mkTerm(CVC4::api::MULT, t2,
                    //slv.mkTerm(CVC4::api::INTS_DIVISION, t1, t2))));
    }

} // namespace modulo

} // namespace generators

/*******************************************************************************
 * Relations
 ******************************************************************************/

namespace relations {

namespace identity {

    fuzz::int_term
    add_zero(fuzz::fuzz_context ctx, fuzz::int_term t)
    {
        t = relations::identity::placeholder(ctx, t);
        fuzz::int_term zero = generators::zero::placeholder(ctx, t);
        return relations::add::placeholder(ctx, t, zero);
    }

    fuzz::int_term
    sub_zero(fuzz::fuzz_context ctx, fuzz::int_term t)
    {
        t = relations::identity::placeholder(ctx, t);
        fuzz::int_term zero = generators::zero::placeholder(ctx, t);
        return relations::sub::placeholder(ctx, t, zero);
    }

    fuzz::int_term
    mul_one(fuzz::fuzz_context ctx, fuzz::int_term t)
    {
        t = relations::identity::placeholder(ctx, t);
        fuzz::int_term one = generators::one::placeholder(ctx, t);
        return generators::mul::placeholder(ctx, t, one);
    }

    fuzz::int_term
    div_one(fuzz::fuzz_context ctx, fuzz::int_term t)
    {
        t = relations::identity::placeholder(ctx, t);
        fuzz::int_term one = generators::one::placeholder(ctx, t);
        return generators::division::placeholder(ctx, t, one);
    }

    fuzz::int_term
    double_negative(fuzz::fuzz_context ctx, fuzz::int_term t)
    {
        t = relations::identity::placeholder(ctx, t);
        fuzz::int_term tmp_t = relations::neg::placeholder(ctx, t);
        tmp_t = relations::identity::placeholder(ctx, tmp_t);
        return relations::neg::placeholder(ctx, tmp_t);
    }

    fuzz::int_term
    iden_by_abs(fuzz::fuzz_context ctx, fuzz::int_term t)
    {
        fuzz::int_term iden_term = relations::identity::placeholder(ctx, t);
        fuzz::int_term abs_t = relations::abs_expr::placeholder(ctx, t);
        fuzz::bool_term t_equal = generators::equal_int::placeholder(ctx, abs_t, t);
        return generators::ite_integer_term_cond::placeholder(ctx, t_equal, abs_t, t);
    }

    fuzz::int_term
    iden_by_ite_false(fuzz::fuzz_context ctx, fuzz::int_term t)
    {
        fuzz::bool_term fuzz_term = generators::fuzz_bool_term::placeholder(ctx);
        fuzz::int_term dead = generators::fuzz_int_term::placeholder(ctx);
        t = relations::identity::placeholder(ctx, t);
        fuzz::bool_term false_expr = generators::false_expr::placeholder(ctx, fuzz_term);
        return generators::ite_integer_term_cond::placeholder(ctx, false_expr, dead, t);
    }

    fuzz::int_term
    iden_by_ite_true(fuzz::fuzz_context ctx, fuzz::int_term t)
    {
        fuzz::bool_term fuzz_term = generators::fuzz_bool_term::placeholder(ctx);
        fuzz::int_term dead = generators::fuzz_int_term::placeholder(ctx);
        t = relations::identity::placeholder(ctx, t);
        fuzz::bool_term true_expr = generators::true_expr::placeholder(ctx, fuzz_term);
        return generators::ite_integer_term_cond::placeholder(ctx, true_expr, t, dead);
    }

} // namespace identity

namespace add {

    fuzz::int_term
    add_comm(fuzz::fuzz_context ctx, fuzz::int_term t1, fuzz::int_term t2)
    {
        t1 = relations::identity::placeholder(ctx, t1);
        t2 = relations::identity::placeholder(ctx, t2);
        return relations::add::placeholder(ctx, t2, t1);
    }

    fuzz::int_term
    add_by_sub(fuzz::fuzz_context ctx, fuzz::int_term t1, fuzz::int_term t2)
    {
        t1 = relations::identity::placeholder(ctx, t1);
        t2 = relations::identity::placeholder(ctx, t2);
        t2 = relations::neg::placeholder(ctx, t2);
        return relations::sub::placeholder(ctx, t1, t2);
    }

} // namespace add

namespace sub {

    fuzz::int_term
    sub_by_add(fuzz::fuzz_context ctx, fuzz::int_term t1, fuzz::int_term t2)
    {
        t1 = relations::identity::placeholder(ctx, t1);
        t2 = relations::identity::placeholder(ctx, t2);
        t2 = relations::neg::placeholder(ctx, t2);
        return relations::add::placeholder(ctx, t1, t2);
    }

} // namespace sub

namespace abs_expr
{
    fuzz::int_term
    abs_by_check_gt_zero(fuzz::fuzz_context ctx, fuzz::int_term t)
    {
        fuzz::int_term zero = generators::zero::placeholder(ctx, t);
        fuzz::bool_term gt_term = generators::gt::placeholder(ctx, t, zero);
        fuzz::int_term abs_t = relations::abs_expr::placeholder(ctx, t);
        return generators::ite_integer_term_cond::placeholder(ctx, gt_term, t, abs_t);
    }

    fuzz::int_term
    abs_by_check_lt_zero(fuzz::fuzz_context ctx, fuzz::int_term t)
    {
        fuzz::int_term zero = generators::zero::placeholder(ctx, t);
        fuzz::bool_term lt_term = generators::lt::placeholder(ctx, t, zero);
        fuzz::int_term abs_t = relations::abs_expr::placeholder(ctx, t);
        return generators::ite_integer_term_cond::placeholder(ctx, lt_term, abs_t, t);
    }

} // namespace abs

namespace neg {

    fuzz::int_term
    neg_by_sub_zero(fuzz::fuzz_context ctx, fuzz::int_term t)
    {
        fuzz::int_term zero = generators::zero::placeholder(ctx, t);
        return relations::sub::placeholder(ctx, zero, t);
    }

    fuzz::int_term
    neg_by_sub_times_two(fuzz::fuzz_context ctx, fuzz::int_term t)
    {
        fuzz::int_term one = generators::one::placeholder(ctx, t);
        fuzz::int_term two = generators::one::placeholder(ctx, t);
        two = relations::add::placeholder(ctx, one, two);
        fuzz::int_term two_t = generators::mul::placeholder(ctx, t, two);
        return relations::sub::placeholder(ctx, t, two_t);
    }

} // namespace neg

namespace ite_integer {

    fuzz::int_term
    ite_by_cpp_check(fuzz::fuzz_context ctx, bool b, fuzz::int_term t, fuzz::int_term e)
    {
        if (b)
        {
            return relations::identity::placeholder(ctx, t);
        }
        return relations::identity::placeholder(ctx, e);
    }

} // namespace ite_integer

} // namespace relations

} // namespace metalib
