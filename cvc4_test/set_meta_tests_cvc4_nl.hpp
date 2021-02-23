namespace metalib {

namespace checks {

    void
    check_expr_same_sat(CVC4::api::Solver& slv, fuzz::int_term t1, fuzz::int_term t2)
    {
        std::cout << "START CHECK" << std::endl;
        fuzz::bool_term check = slv.mkTerm(CVC4::api::DISTINCT, t1, t2);
        slv.assertFormula(check);
        assert(!slv.checkSat().isSat());
        slv.resetAssertions();
        std::cout << "END CHECK" << std::endl;
    }

    void
    check_exprs_are_zero(CVC4::api::Solver& slv, fuzz::FreeVars& fvs, fuzz::int_term t1, fuzz::int_term t2)
    {
        fuzz::int_term zero = slv.mkInteger(0);
        fuzz::int_term check_zero_t1 = slv.mkTerm(CVC4::api::Kind::EQUAL, t1, zero);
        fuzz::int_term check_zero_t2 = slv.mkTerm(CVC4::api::Kind::EQUAL, t2, zero);
        slv.push();
        slv.assertFormula(check_zero_t1);
        CVC4::api::Result r_1 = slv.checkSat();
        if (r_1.isSat())
        {
            assert(!slv.getValue(check_zero_t2).toString().compare("true"));
        }
        else if (r_1.isUnsat())
        {
            slv.pop();
            slv.push();
            slv.assertFormula(check_zero_t2);
            assert(!slv.checkSat().isSat());
        }
        slv.pop();
        slv.push();
        slv.assertFormula(check_zero_t2);
        CVC4::api::Result r_2 = slv.checkSat();
        if (r_2.isSat())
        {
            assert(!slv.getValue(check_zero_t1).toString().compare("true"));
        }
        else if (r_2.isUnsat())
        {
            slv.pop();
            slv.push();
            slv.assertFormula(check_zero_t1);
            assert(!slv.checkSat().isSat());
        }
        slv.pop();
        slv.resetAssertions();
    }

} // namespace checks

// Forward declarations
//
namespace generators {
namespace fuzz_int_term {
    fuzz::int_term placeholder(CVC4::api::Solver&, fuzz::FreeVars&);
}
namespace fuzz_bool_term {
    fuzz::bool_term placeholder(CVC4::api::Solver&, fuzz::FreeVars&);
}
namespace zero {
    fuzz::int_term placeholder(CVC4::api::Solver&, fuzz::FreeVars&, fuzz::int_term);
}
namespace one {
    fuzz::int_term placeholder(CVC4::api::Solver&, fuzz::FreeVars&, fuzz::int_term);
}
namespace true_cvc4 {
    fuzz::bool_term placeholder(CVC4::api::Solver&, fuzz::FreeVars&, fuzz::bool_term);
}
namespace false_cvc4 {
    fuzz::bool_term placeholder(CVC4::api::Solver&, fuzz::FreeVars&, fuzz::bool_term);
}
namespace iden_bool {
    fuzz::bool_term placeholder(CVC4::api::Solver&, fuzz::FreeVars&, fuzz::bool_term);
}
namespace not_cvc4 {
    fuzz::bool_term placeholder(CVC4::api::Solver&, fuzz::FreeVars&, fuzz::bool_term);
}
namespace and_cvc4 {
    fuzz::bool_term placeholder(CVC4::api::Solver&, fuzz::FreeVars&, fuzz::bool_term, fuzz::bool_term);
}
namespace or_cvc4 {
    fuzz::bool_term placeholder(CVC4::api::Solver&, fuzz::FreeVars&, fuzz::bool_term, fuzz::bool_term);
}
namespace xor_cvc4 {
    fuzz::bool_term placeholder(CVC4::api::Solver&, fuzz::FreeVars&, fuzz::bool_term, fuzz::bool_term);
}
namespace equal_int {
    fuzz::bool_term placeholder(CVC4::api::Solver&, fuzz::FreeVars&, fuzz::int_term, fuzz::int_term);
}
namespace lt {
    fuzz::bool_term placeholder(CVC4::api::Solver&, fuzz::FreeVars&, fuzz::int_term, fuzz::int_term);
}
namespace gt {
    fuzz::bool_term placeholder(CVC4::api::Solver&, fuzz::FreeVars&, fuzz::int_term, fuzz::int_term);
}
namespace leq {
    fuzz::bool_term placeholder(CVC4::api::Solver&, fuzz::FreeVars&, fuzz::int_term, fuzz::int_term);
}
namespace geq {
    fuzz::bool_term placeholder(CVC4::api::Solver&, fuzz::FreeVars&, fuzz::int_term, fuzz::int_term);
}
namespace mul {
    fuzz::int_term placeholder(CVC4::api::Solver&, fuzz::FreeVars&, fuzz::int_term, fuzz::int_term);
}
namespace division {
    fuzz::int_term placeholder(CVC4::api::Solver&, fuzz::FreeVars&, fuzz::int_term, fuzz::int_term);
}
namespace modulo {
    fuzz::int_term placeholder(CVC4::api::Solver&, fuzz::FreeVars&, fuzz::int_term, fuzz::int_term);
}

} // namespace generators

namespace relations {
namespace identity {
    fuzz::int_term placeholder(CVC4::api::Solver&, fuzz::FreeVars&, fuzz::int_term);
}
namespace add {
    fuzz::int_term placeholder(CVC4::api::Solver&, fuzz::FreeVars&, fuzz::int_term, fuzz::int_term);
}
namespace sub {
    fuzz::int_term placeholder(CVC4::api::Solver&, fuzz::FreeVars&, fuzz::int_term, fuzz::int_term);
}
namespace abs_cvc4 {
    fuzz::int_term placeholder(CVC4::api::Solver&, fuzz::FreeVars&, fuzz::int_term);
}
} //namespace relations

namespace generators {

namespace fuzz_int_term {

    fuzz::int_term
    get_expr_by_fuzz(CVC4::api::Solver& slv, fuzz::FreeVars& fvs)
    {
        fuzz::int_term fuzz = fuzz::fuzz_new<fuzz::int_term>();
        return fuzz;
    }

} // namespace fuzz_int_term

namespace fuzz_bool_term {

    fuzz::bool_term
    get_expr_by_fuzz(CVC4::api::Solver& slv, fuzz::FreeVars& fvs)
    {
        fuzz::bool_term fuzz = fuzz::fuzz_new<fuzz::bool_term>();
        return fuzz;
    }

} // namespace fuzz_bool_term

namespace zero {

    fuzz::int_term
    get_zero(CVC4::api::Solver& slv, fuzz::FreeVars& fvs, fuzz::int_term t)
    {
        return slv.mkInteger(0);
    }

    fuzz::int_term
    zero_by_mul(CVC4::api::Solver& slv, fuzz::FreeVars& fvs, fuzz::int_term t)
    {
        fuzz::int_term zero = generators::zero::placeholder(slv, fvs, t);
        return generators::mul::placeholder(slv, fvs, t, zero);
    }

    fuzz::int_term
    zero_by_sub(CVC4::api::Solver& slv, fuzz::FreeVars& fvs, fuzz::int_term t)
    {
        fuzz::int_term iden_term = relations::identity::placeholder(slv, fvs, t);
        return relations::sub::placeholder(slv, fvs, t, iden_term);
    }

    fuzz::int_term
    zero_by_fuzz_sub(CVC4::api::Solver& slv, fuzz::FreeVars& fvs, fuzz::int_term t)
    {
        fuzz::int_term fuzz = generators::fuzz_int_term::placeholder(slv, fvs);
        fuzz::int_term iden_fuzz = relations::identity::placeholder(slv, fvs, fuzz);
        return relations::sub::placeholder(slv, fvs, fuzz, iden_fuzz);
    }

    fuzz::int_term
    zero_by_mod_one(CVC4::api::Solver& slv, fuzz::FreeVars& fvs, fuzz::int_term t)
    {
        t = relations::identity::placeholder(slv, fvs, t);
        fuzz::int_term one = generators::one::placeholder(slv, fvs, t);
        return generators::modulo::placeholder(slv, fvs, t, one);
    }

    fuzz::int_term
    zero_by_mod_one_fuzz(CVC4::api::Solver& slv, fuzz::FreeVars& fvs, fuzz::int_term t)
    {
        fuzz::int_term fuzz = generators::fuzz_int_term::placeholder(slv, fvs);
        fuzz::int_term one = generators::one::placeholder(slv, fvs, t);
        return generators::modulo::placeholder(slv, fvs, fuzz, one);
    }

    //fuzz::int_term
    //zero_by_mod(CVC4::api::Solver& slv, fuzz::FreeVars& fvs, fuzz::int_term t)
    //{
        //fuzz::int_term iden_term = relations::identity::placeholder(slv, fvs, t);
        //fuzz::int_term tmp_zero = generators::zero::placeholder(slv, fvs, t);
        //fuzz::int_term mod_ts = generators::modulo::placeholder(slv, fvs, t, iden_term);
        //return t.eqTerm(tmp_zero).iteTerm(tmp_zero, mod_ts);
    //}

    //fuzz::int_term
    //zero_by_div(CVC4::api::Solver& slv, fuzz::FreeVars& fvs, fuzz::int_term t)
    //{
        //fuzz::int_term tmp_zero = generators::zero::placeholder(slv, fvs, t);
        //fuzz::bool_term is_zero = tmp_zero.eqTerm(t);
        //fuzz::int_term tmp_zero_return = generators::zero::placeholder(slv, fvs, t);
        //fuzz::int_term div_ts = generators::division::placeholder(slv, fvs, tmp_zero, t);
        //return is_zero.iteTerm(tmp_zero_return, div_ts);
    //}

    //fuzz::int_term
    //zero_by_div_fuzz(CVC4::api::Solver& slv, fuzz::FreeVars& fvs, fuzz::int_term t)
    //{
        //fuzz::int_term fuzz = generators::fuzz_int_term::placeholder(slv, fvs);
        //fuzz::int_term tmp_zero = generators::zero::placeholder(slv, fvs, fuzz);
        //fuzz::bool_term is_zero = tmp_zero.eqTerm(fuzz);
        //fuzz::int_term tmp_zero_return = generators::zero::placeholder(slv, fvs, fuzz);
        //fuzz::int_term div_ts = generators::division::placeholder(slv, fvs, tmp_zero, iden_fuzz);
        //return is_zero.iteTerm(tmp_zero_return, div_ts);
    //}

} // namespace zero

namespace one {

    fuzz::int_term
    get_one(CVC4::api::Solver& slv, fuzz::FreeVars& fvs, fuzz::int_term t)
    {
        return slv.mkInteger(1);
    }

    fuzz::int_term
    one_by_div(CVC4::api::Solver& slv, fuzz::FreeVars& fvs, fuzz::int_term t)
    {
        fuzz::int_term iden_term = relations::identity::placeholder(slv, fvs, t);
        fuzz::int_term tmp_zero = generators::zero::placeholder(slv, fvs, t);
        fuzz::bool_term is_zero = generators::equal_int::placeholder(slv, fvs, tmp_zero, t);
        fuzz::int_term div_ts = generators::division::placeholder(slv, fvs, t, iden_term);
        return is_zero.iteTerm(generators::one::placeholder(slv, fvs, t), div_ts);
    }

    fuzz::int_term
    one_by_fuzz_div(CVC4::api::Solver& slv, fuzz::FreeVars& fvs, fuzz::int_term t)
    {
        fuzz::int_term fuzz = generators::fuzz_int_term::placeholder(slv, fvs);
        fuzz::int_term iden_fuzz = relations::identity::placeholder(slv, fvs, fuzz);
        fuzz::int_term tmp_zero = generators::zero::placeholder(slv, fvs, fuzz);
        fuzz::bool_term is_zero = generators::equal_int::placeholder(slv, fvs, tmp_zero, fuzz);
        fuzz::int_term div_ts = generators::division::placeholder(slv, fvs, fuzz, iden_fuzz);
        return is_zero.iteTerm(generators::one::placeholder(slv, fvs, fuzz), div_ts);
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

namespace true_cvc4 {

    fuzz::bool_term
    get_true(CVC4::api::Solver& slv, fuzz::FreeVars& fvs, fuzz::bool_term t)
    {
        return slv.mkTrue();
    }

    fuzz::bool_term
    get_true_by_equal(CVC4::api::Solver& slv, fuzz::FreeVars& fvs, fuzz::bool_term t)
    {
        fuzz::bool_term iden_term = generators::iden_bool::placeholder(slv, fvs, t);
        return slv.mkTerm(CVC4::api::Kind::EQUAL, t, iden_term);
    }

    fuzz::bool_term
    get_true_by_not_false(CVC4::api::Solver& slv, fuzz::FreeVars& fvs, fuzz::bool_term t)
    {
        t = generators::iden_bool::placeholder(slv, fvs, t);
        return slv.mkTerm(CVC4::api::Kind::NOT, generators::false_cvc4::placeholder(slv, fvs, t));
    }

    fuzz::bool_term
    get_true_by_or_true(CVC4::api::Solver& slv, fuzz::FreeVars& fvs, fuzz::bool_term t)
    {
        t = generators::iden_bool::placeholder(slv, fvs, t);
        fuzz::bool_term true_term = generators::true_cvc4::placeholder(slv, fvs, t);
        return generators::or_cvc4::placeholder(slv, fvs, true_term, t);
    }

    fuzz::bool_term
    get_true_by_or_true_fuzz(CVC4::api::Solver& slv, fuzz::FreeVars& fvs, fuzz::bool_term t)
    {
        fuzz::bool_term true_term = generators::true_cvc4::placeholder(slv, fvs, t);
        fuzz::bool_term fuzz_term = generators::fuzz_bool_term::placeholder(slv, fvs);
        return generators::or_cvc4::placeholder(slv, fvs, true_term, t);
    }

    fuzz::bool_term
    get_true_by_nxor(CVC4::api::Solver& slv, fuzz::FreeVars& fvs, fuzz::bool_term t)
    {
        fuzz::bool_term iden_term = generators::iden_bool::placeholder(slv, fvs, t);
        return slv.mkTerm(CVC4::api::NOT, generators::xor_cvc4::placeholder(slv, fvs, t, iden_term));
    }

    fuzz::bool_term
    get_true_by_nxor_fuzz(CVC4::api::Solver& slv, fuzz::FreeVars& fvs, fuzz::bool_term t)
    {
        fuzz::bool_term fuzz_term = generators::fuzz_bool_term::placeholder(slv, fvs);
        fuzz::bool_term iden_term = generators::iden_bool::placeholder(slv, fvs, fuzz_term);
        return slv.mkTerm(CVC4::api::NOT,
            generators::xor_cvc4::placeholder(slv, fvs, fuzz_term, iden_term));
    }

    fuzz::bool_term
    get_true_by_lte_fuzz(CVC4::api::Solver& slv, fuzz::FreeVars& fvs, fuzz::bool_term t)
    {
        fuzz::int_term fuzz_term = generators::fuzz_int_term::placeholder(slv, fvs);
        fuzz::int_term iden_term = relations::identity::placeholder(slv, fvs, fuzz_term);
        return generators::leq::placeholder(slv, fvs, fuzz_term, iden_term);
    }

    fuzz::bool_term
    get_true_by_gte_fuzz(CVC4::api::Solver& slv, fuzz::FreeVars& fvs, fuzz::bool_term t)
    {
        fuzz::int_term fuzz_term = generators::fuzz_int_term::placeholder(slv, fvs);
        fuzz::int_term iden_term = relations::identity::placeholder(slv, fvs, fuzz_term);
        return generators::geq::placeholder(slv, fvs, fuzz_term, iden_term);
    }

} // namespace true_cvc4

namespace false_cvc4 {

    fuzz::bool_term
    get_false(CVC4::api::Solver& slv, fuzz::FreeVars& fvs, fuzz::bool_term t)
    {
        return slv.mkFalse();
    }

    fuzz::bool_term
    get_false_by_equal(CVC4::api::Solver& slv, fuzz::FreeVars& fvs, fuzz::bool_term t)
    {
        fuzz::bool_term iden_term = generators::iden_bool::placeholder(slv, fvs, t);
        return slv.mkTerm(CVC4::api::Kind::DISTINCT, t, iden_term);
    }

    fuzz::bool_term
    get_false_by_not_true(CVC4::api::Solver& slv, fuzz::FreeVars& fvs, fuzz::bool_term t)
    {
        t = generators::iden_bool::placeholder(slv, fvs, t);
        return slv.mkTerm(CVC4::api::Kind::NOT, generators::true_cvc4::placeholder(slv, fvs, t));
    }

    fuzz::bool_term
    get_false_by_and_false(CVC4::api::Solver& slv, fuzz::FreeVars& fvs, fuzz::bool_term t)
    {
        t = generators::iden_bool::placeholder(slv, fvs, t);
        fuzz::bool_term false_term = generators::false_cvc4::placeholder(slv, fvs, t);
        return generators::and_cvc4::placeholder(slv, fvs, false_term, t);
    }

    fuzz::bool_term
    get_false_by_and_false_fuzz(CVC4::api::Solver& slv, fuzz::FreeVars& fvs, fuzz::bool_term t)
    {
        fuzz::bool_term false_term = generators::false_cvc4::placeholder(slv, fvs, t);
        fuzz::bool_term fuzz_term = generators::fuzz_bool_term::placeholder(slv, fvs);
        return generators::and_cvc4::placeholder(slv, fvs, false_term, t);
    }

    fuzz::bool_term
    get_false_by_xor(CVC4::api::Solver& slv, fuzz::FreeVars& fvs, fuzz::bool_term t)
    {
        fuzz::bool_term iden_term = generators::iden_bool::placeholder(slv, fvs, t);
        return generators::xor_cvc4::placeholder(slv, fvs, t, iden_term);
    }

    fuzz::bool_term
    get_false_by_xor_fuzz(CVC4::api::Solver& slv, fuzz::FreeVars& fvs, fuzz::bool_term t)
    {
        fuzz::bool_term fuzz_term = generators::fuzz_bool_term::placeholder(slv, fvs);
        fuzz::bool_term iden_term = generators::iden_bool::placeholder(slv, fvs, fuzz_term);
        return generators::xor_cvc4::placeholder(slv, fvs, fuzz_term, iden_term);
    }

    fuzz::bool_term
    get_false_by_lt_fuzz(CVC4::api::Solver& slv, fuzz::FreeVars& fvs, fuzz::bool_term t)
    {
        fuzz::int_term fuzz_term = generators::fuzz_int_term::placeholder(slv, fvs);
        fuzz::int_term iden_term = relations::identity::placeholder(slv, fvs, fuzz_term);
        return generators::lt::placeholder(slv, fvs, fuzz_term, iden_term);
    }

    fuzz::bool_term
    get_false_by_gt_fuzz(CVC4::api::Solver& slv, fuzz::FreeVars& fvs, fuzz::bool_term t)
    {
        fuzz::int_term fuzz_term = generators::fuzz_int_term::placeholder(slv, fvs);
        fuzz::int_term iden_term = relations::identity::placeholder(slv, fvs, fuzz_term);
        return generators::gt::placeholder(slv, fvs, fuzz_term, iden_term);
    }

} // namespace false_cvc4

namespace iden_bool {

    fuzz::bool_term
    base_iden_bool(CVC4::api::Solver& slv, fuzz::FreeVars& fvs, fuzz::bool_term t)
    {
        return t;
    }

    fuzz::bool_term
    iden_by_and(CVC4::api::Solver& slv, fuzz::FreeVars& fvs, fuzz::bool_term t)
    {
        t = generators::iden_bool::placeholder(slv, fvs, t);
        fuzz::bool_term true_term = generators::true_cvc4::placeholder(slv, fvs, t);
        return generators::and_cvc4::placeholder(slv, fvs, t, true_term);
    }

    fuzz::bool_term
    iden_by_or(CVC4::api::Solver& slv, fuzz::FreeVars& fvs, fuzz::bool_term t)
    {
        t = generators::iden_bool::placeholder(slv, fvs, t);
        fuzz::bool_term false_term = generators::false_cvc4::placeholder(slv, fvs, t);
        return generators::or_cvc4::placeholder(slv, fvs, t, false_term);
    }

    fuzz::bool_term
    iden_by_xor(CVC4::api::Solver& slv, fuzz::FreeVars& fvs, fuzz::bool_term t)
    {
        fuzz::bool_term iden_term = generators::iden_bool::placeholder(slv, fvs, t);
        fuzz::bool_term xor_once = generators::xor_cvc4::placeholder(slv, fvs, iden_term, iden_term);
        return generators::xor_cvc4::placeholder(slv, fvs, xor_once, iden_term);
    }

    //fuzz::bool_term
    //iden_bool_by_ite_false(CVC4::api::Solver& slv, fuzz::FreeVars& fvs, fuzz::bool_term t)
    //{
        //fuzz::bool_term dead = generators::fuzz_bool_term::placeholder(slv, fvs);
        //t = generators::iden_bool::placeholder(slv, fvs, t);
        //return slv.mkTerm(CVC4::api::ITE,
            //generators::false_cvc4::placeholder(slv, fvs, t), dead, t);
    //}

    //fuzz::bool_term
    //iden_bool_by_ite_true(CVC4::api::Solver& slv, fuzz::FreeVars& fvs, fuzz::bool_term t)
    //{
        //fuzz::bool_term dead = generators::fuzz_bool_term::placeholder(slv, fvs);
        //t = generators::iden_bool::placeholder(slv, fvs, t);
        //return slv.mkTerm(CVC4::api::ITE,
            //generators::true_cvc4::placeholder(slv, fvs, t), t, dead);
    //}
    //
    fuzz::bool_term
    iden_by_simplify(CVC4::api::Solver& slv, fuzz::FreeVars& fvs, fuzz::bool_term t)
    {
        return slv.simplify(generators::iden_bool::placeholder(slv, fvs, t));
    }

} // namespace iden_bool

namespace not_cvc4 {

    fuzz::bool_term
    base_not(CVC4::api::Solver& slv, fuzz::FreeVars& fvs, fuzz::bool_term t)
    {
        return slv.mkTerm(CVC4::api::Kind::NOT, t);
    }

    fuzz::bool_term
    not_by_truth_value(CVC4::api::Solver& slv, fuzz::FreeVars& fvs, fuzz::bool_term t)
    {
        fuzz::bool_term false_term = generators::false_cvc4::placeholder(slv, fvs, t);
        fuzz::bool_term true_term = generators::true_cvc4::placeholder(slv, fvs, t);
        return slv.mkTerm(CVC4::api::Kind::ITE, t, false_term, true_term);
    }

} // namespace not_cvc4

namespace and_cvc4 {

    fuzz::bool_term
    base_and(CVC4::api::Solver& slv, fuzz::FreeVars& fvs, fuzz::bool_term t1, fuzz::bool_term t2)
    {
        return slv.mkTerm(CVC4::api::Kind::AND, t1, t2);
    }

    fuzz::bool_term
    and_comm(CVC4::api::Solver& slv, fuzz::FreeVars& fvs, fuzz::bool_term t1, fuzz::bool_term t2)
    {
        return generators::and_cvc4::placeholder(slv, fvs, t2, t1);
    }

    fuzz::bool_term
    and_demorgan(CVC4::api::Solver& slv, fuzz::FreeVars& fvs, fuzz::bool_term t1, fuzz::bool_term t2)
    {
        fuzz::bool_term nt1 = slv.mkTerm(CVC4::api::Kind::NOT, t1);
        fuzz::bool_term nt2 = slv.mkTerm(CVC4::api::Kind::NOT, t2);
        fuzz::bool_term or_nts = generators::or_cvc4::placeholder(slv, fvs, nt1, nt2);
        return generators::not_cvc4::placeholder(slv, fvs, or_nts);
    }

} // namespace and_cvc4

namespace or_cvc4 {

    fuzz::bool_term
    base_or(CVC4::api::Solver& slv, fuzz::FreeVars& fvs, fuzz::bool_term t1, fuzz::bool_term t2)
    {
        return slv.mkTerm(CVC4::api::Kind::OR, t1, t2);
    }

    fuzz::bool_term
    or_comm(CVC4::api::Solver& slv, fuzz::FreeVars& fvs, fuzz::bool_term t1, fuzz::bool_term t2)
    {
        return generators::or_cvc4::placeholder(slv, fvs, t2, t1);
    }

    fuzz::bool_term
    or_demorgan(CVC4::api::Solver& slv, fuzz::FreeVars& fvs, fuzz::bool_term t1, fuzz::bool_term t2)
    {
        fuzz::bool_term nt1 = slv.mkTerm(CVC4::api::Kind::NOT, t1);
        fuzz::bool_term nt2 = slv.mkTerm(CVC4::api::Kind::NOT, t2);
        fuzz::bool_term and_nts = generators::and_cvc4::placeholder(slv, fvs, nt1, nt2);
        return generators::not_cvc4::placeholder(slv, fvs, and_nts);
    }

} // namespace or_cvc4

namespace xor_cvc4 {

    fuzz::bool_term
    base_xor(CVC4::api::Solver& slv, fuzz::FreeVars& fvs, fuzz::bool_term t1, fuzz::bool_term t2)
    {
        return slv.mkTerm(CVC4::api::Kind::XOR, t1, t2);
    }

    fuzz::bool_term
    xor_comm(CVC4::api::Solver& slv, fuzz::FreeVars& fvs, fuzz::bool_term t1, fuzz::bool_term t2)
    {
        return generators::xor_cvc4::placeholder(slv, fvs, t2, t1);
    }

    fuzz::bool_term
    xor_disjunct(CVC4::api::Solver& slv, fuzz::FreeVars& fvs, fuzz::bool_term t1, fuzz::bool_term t2)
    {
        fuzz::bool_term nt1 = slv.mkTerm(CVC4::api::Kind::NOT, t1);
        fuzz::bool_term nt2 = slv.mkTerm(CVC4::api::Kind::NOT, t2);
        fuzz::bool_term t1_and_nt2 = generators::and_cvc4::placeholder(slv, fvs, t1, nt2);
        fuzz::bool_term t2_and_nt1 = generators::and_cvc4::placeholder(slv, fvs, t2, nt1);
        return generators::or_cvc4::placeholder(slv, fvs, t1_and_nt2, t2_and_nt1);
    }

    fuzz::bool_term
    xor_conjunct(CVC4::api::Solver& slv, fuzz::FreeVars& fvs, fuzz::bool_term t1, fuzz::bool_term t2)
    {
        fuzz::bool_term nt1 = slv.mkTerm(CVC4::api::Kind::NOT, t1);
        fuzz::bool_term nt2 = slv.mkTerm(CVC4::api::Kind::NOT, t2);
        fuzz::bool_term t1_or_t2 = generators::or_cvc4::placeholder(slv, fvs, t1, t2);
        fuzz::bool_term nt1_or_nt2 = generators::or_cvc4::placeholder(slv, fvs, nt1, nt2);
        return generators::and_cvc4::placeholder(slv, fvs, t1_or_t2, nt1_or_nt2);
    }

}

namespace equal_int {

    fuzz::bool_term
    check_equal_by_call(CVC4::api::Solver& slv, fuzz::FreeVars& fvs, fuzz::int_term t1, fuzz::int_term t2)
    {
        return slv.mkTerm(CVC4::api::Kind::EQUAL, t1, t2);
    }

    fuzz::bool_term
    check_equal_comm(CVC4::api::Solver& slv, fuzz::FreeVars& fvs, fuzz::int_term t1, fuzz::int_term t2)
    {
        return generators::equal_int::placeholder(slv, fvs, t2, t1);
    }

    fuzz::bool_term
    check_equal_by_sub_is_zero(CVC4::api::Solver& slv, fuzz::FreeVars& fvs, fuzz::int_term t1, fuzz::int_term t2)
    {
        fuzz::int_term zero = generators::zero::placeholder(slv, fvs, t1);
        fuzz::int_term sub_ts = relations::sub::placeholder(slv, fvs, t1, t2);
        return generators::equal_int::placeholder(slv, fvs, zero, sub_ts);
    }

    //fuzz::bool_term
    //check_equal_by_div_is_one(CVC4::api::Solver& slv, fuzz::FreeVars& fvs, fuzz::int_term t1, fuzz::int_term t2)
    //{
        //fuzz::int_term one = generators::one::placeholder(slv, fvs, t1);
        //fuzz::int_expr zero = generators::zero::placeholder(ctx, fvs, e2);
        //fuzz::int_term div_ts = relations::division::placeholder(slv, fvs, t1, t2);
        //fuzz::bool_expr check_zeroes = slv.mkTerm(CVC4::api::Kind::AND,
            //slv.mkTerm(CVC4::api::Kind::EQUAL, zero, e1),
            //slv.mkTerm(CVC4::api::Kind::EQUAL, zero, e2));
        //fuzz::bool_expr check_equal = generators::equal_int::placeholder(slv, fvs, one, div_ts);
        //return slv.mkTerm(CVC4::api::Kind::OR, check_zeroes, check_equal);
    //}

} // namespace equal_int

namespace lt {

    fuzz::bool_term
    lt_base(CVC4::api::Solver& slv, fuzz::FreeVars& fvs, fuzz::int_term t1, fuzz::int_term t2)
    {
        return slv.mkTerm(CVC4::api::Kind::LT, t1, t2);
    }

    fuzz::bool_term
    not_geq_base(CVC4::api::Solver& slv, fuzz::FreeVars& fvs, fuzz::int_term t1, fuzz::int_term t2)
    {
        fuzz::bool_term geq_term = generators::geq::placeholder(slv, fvs, t1, t2);
        return generators::not_cvc4::placeholder(slv, fvs, geq_term);
    }

} // namespace lt

namespace gt {

    fuzz::bool_term
    gt_base(CVC4::api::Solver& slv, fuzz::FreeVars& fvs, fuzz::int_term t1, fuzz::int_term t2)
    {
        return slv.mkTerm(CVC4::api::Kind::GT, t1, t2);
    }

    fuzz::bool_term
    not_leq_base(CVC4::api::Solver& slv, fuzz::FreeVars& fvs, fuzz::int_term t1, fuzz::int_term t2)
    {
        fuzz::bool_term leq_term = generators::leq::placeholder(slv, fvs, t1, t2);
        return generators::not_cvc4::placeholder(slv, fvs, leq_term);
    }

} // namespace gt

namespace leq {

    fuzz::bool_term
    leq_base(CVC4::api::Solver& slv, fuzz::FreeVars& fvs, fuzz::int_term t1, fuzz::int_term t2)
    {
        return slv.mkTerm(CVC4::api::Kind::LEQ, t1, t2);
    }

    fuzz::bool_term
    not_gt_base(CVC4::api::Solver& slv, fuzz::FreeVars& fvs, fuzz::int_term t1, fuzz::int_term t2)
    {
        fuzz::bool_term gt_term = generators::gt::placeholder(slv, fvs, t1, t2);
        return generators::not_cvc4::placeholder(slv, fvs, gt_term);
    }

} // namespace leq

namespace geq {

    fuzz::bool_term
    geq_base(CVC4::api::Solver& slv, fuzz::FreeVars& fvs, fuzz::int_term t1, fuzz::int_term t2)
    {
        return slv.mkTerm(CVC4::api::Kind::GEQ, t1, t2);
    }

    fuzz::bool_term
    not_lt_base(CVC4::api::Solver& slv, fuzz::FreeVars& fvs, fuzz::int_term t1, fuzz::int_term t2)
    {
        fuzz::bool_term lt_term = generators::lt::placeholder(slv, fvs, t1, t2);
        return generators::not_cvc4::placeholder(slv, fvs, lt_term);
    }

} // namespace geq

namespace mul {

    fuzz::int_term
    mul_base(CVC4::api::Solver& slv, fuzz::FreeVars& fvs, fuzz::int_term t1, fuzz::int_term t2)
    {
        return slv.mkTerm(CVC4::api::MULT, t1, t2);
    }

    fuzz::int_term
    mul_comm(CVC4::api::Solver& slv, fuzz::FreeVars& fvs, fuzz::int_term t1, fuzz::int_term t2)
    {
        t1 = relations::identity::placeholder(slv, fvs, t1);
        t2 = relations::identity::placeholder(slv, fvs, t2);
        return generators::mul::placeholder(slv, fvs, t2, t1);
    }

} // namespace mul

namespace division {

    fuzz::int_term
    div_base(CVC4::api::Solver& slv, fuzz::FreeVars& fvs, fuzz::int_term t1, fuzz::int_term t2)
    {
        return slv.mkTerm(CVC4::api::Kind::ITE,
            slv.mkTerm(CVC4::api::Kind::EQUAL, t2, slv.mkInteger(0)),
            t1, slv.mkTerm(CVC4::api::INTS_DIVISION, t1, t2));
    }

} // namespace division

namespace modulo {

    fuzz::int_term
    mod_base(CVC4::api::Solver& slv, fuzz::FreeVars& fvs, fuzz::int_term t1, fuzz::int_term t2)
    {
        return slv.mkTerm(CVC4::api::ITE,
            slv.mkTerm(CVC4::api::EQUAL, t2, slv.mkInteger(0)), t1,
            slv.mkTerm(CVC4::api::INTS_MODULUS, t1, t2));
    }

    fuzz::int_term
    mod_by_sub(CVC4::api::Solver& slv, fuzz::FreeVars& fvs, fuzz::int_term t1, fuzz::int_term t2)
    {
        t1 = relations::identity::placeholder(slv, fvs, t1);
        t2 = relations::identity::placeholder(slv, fvs, t2);
        fuzz::int_term zero = generators::zero::placeholder(slv, fvs, t1);
        return slv.mkTerm(CVC4::api::ITE,
            slv.mkTerm(CVC4::api::EQUAL, t2, zero), t1,
            slv.mkTerm(CVC4::api::MINUS, t1,
                slv.mkTerm(CVC4::api::MULT, t2,
                    slv.mkTerm(CVC4::api::INTS_DIVISION, t1, t2))));
    }

} // namespace modulo

} // namespace generators

/*******************************************************************************
 * Relations
 ******************************************************************************/

namespace relations {

namespace identity {

    fuzz::int_term
    base_iden(CVC4::api::Solver& slv, fuzz::FreeVars& fvs, fuzz::int_term t)
    {
        return t;
    }

    fuzz::int_term
    add_zero(CVC4::api::Solver& slv, fuzz::FreeVars& fvs, fuzz::int_term t)
    {
        t = relations::identity::placeholder(slv, fvs, t);
        fuzz::int_term zero = generators::zero::placeholder(slv, fvs, t);
        return relations::add::placeholder(slv, fvs, t, zero);
    }

    fuzz::int_term
    sub_zero(CVC4::api::Solver& slv, fuzz::FreeVars& fvs, fuzz::int_term t)
    {
        t = relations::identity::placeholder(slv, fvs, t);
        fuzz::int_term zero = generators::zero::placeholder(slv, fvs, t);
        return relations::sub::placeholder(slv, fvs, t, zero);
    }

    fuzz::int_term
    mul_one(CVC4::api::Solver& slv, fuzz::FreeVars& fvs, fuzz::int_term t)
    {
        t = relations::identity::placeholder(slv, fvs, t);
        fuzz::int_term one = generators::one::placeholder(slv, fvs, t);
        return generators::mul::placeholder(slv, fvs, t, one);
    }

    fuzz::int_term
    div_one(CVC4::api::Solver& slv, fuzz::FreeVars& fvs, fuzz::int_term t)
    {
        t = relations::identity::placeholder(slv, fvs, t);
        fuzz::int_term one = generators::one::placeholder(slv, fvs, t);
        return generators::division::placeholder(slv, fvs, t, one);
    }

    fuzz::int_term
    double_negative(CVC4::api::Solver& slv, fuzz::FreeVars& fvs, fuzz::int_term t)
    {
        t = relations::identity::placeholder(slv, fvs, t);
        fuzz::int_term tmp_t = slv.mkTerm(CVC4::api::UMINUS, t);
        tmp_t = relations::identity::placeholder(slv, fvs, tmp_t);
        return slv.mkTerm(CVC4::api::UMINUS, tmp_t);
    }

    fuzz::int_term
    iden_by_abs(CVC4::api::Solver& slv, fuzz::FreeVars& fvs, fuzz::int_term t)
    {
        fuzz::int_term iden_term = relations::identity::placeholder(slv, fvs, t);
        fuzz::int_term abs_t = relations::abs_cvc4::placeholder(slv, fvs, t);
        fuzz::bool_term t_equal = generators::equal_int::placeholder(slv, fvs, abs_t, t);
        return slv.mkTerm(CVC4::api::ITE, t_equal, abs_t, t);
    }

    //fuzz::int_term
    //sqrt_square(CVC4::api::Solver& c, fuzz::FreeVars& fvs, fuzz::int_term e)
    //{
        //fuzz::int_term two = c.mkInteger(2);
        //e = relations::identity::placeholder(c, fvs, e);
        //return c.mkTerm(CVC4::api::TO_INTEGER, c.mkTerm(CVC4::api::SQRT, c.mkTerm(CVC4::api::POW, e, two));
    //}

    fuzz::int_term
    iden_by_ite_false(CVC4::api::Solver& slv, fuzz::FreeVars& fvs, fuzz::int_term t)
    {
        fuzz::bool_term fuzz_term = generators::fuzz_bool_term::placeholder(slv, fvs);
        fuzz::int_term dead = generators::fuzz_int_term::placeholder(slv, fvs);
        t = relations::identity::placeholder(slv, fvs, t);
        return slv.mkTerm(CVC4::api::ITE,
            generators::false_cvc4::placeholder(slv, fvs, fuzz_term), dead, t);
    }

    fuzz::int_term
    iden_by_ite_true(CVC4::api::Solver& slv, fuzz::FreeVars& fvs, fuzz::int_term t)
    {
        fuzz::bool_term fuzz_term = generators::fuzz_bool_term::placeholder(slv, fvs);
        fuzz::int_term dead = generators::fuzz_int_term::placeholder(slv, fvs);
        t = relations::identity::placeholder(slv, fvs, t);
        return slv.mkTerm(CVC4::api::ITE,
            generators::true_cvc4::placeholder(slv, fvs, fuzz_term), t, dead);
    }

    //fuzz::int_term
    //iden_by_ite_fuzz(CVC4::api::Solver& c, fuzz::FreeVars& fvs, fuzz::int_term e)
    //{
        //fuzz::int_term dead = generators::fuzz_int_term::placeholder(c, fvs);
        //e = relations::identity::placeholder(c, fvs, e);
        //return c.mkTerm(CVC4::api::ITE,
            //c.mkTerm(CVC4::api::EQUAL, e, dead), dead, e);
    //}

    fuzz::int_term
    iden_by_simplify(CVC4::api::Solver& slv, fuzz::FreeVars& fvs, fuzz::int_term t)
    {
        return slv.simplify(relations::identity::placeholder(slv, fvs, t));
    }


} // namespace identity

namespace add {

    fuzz::int_term
    add_base(CVC4::api::Solver& slv, fuzz::FreeVars& fvs, fuzz::int_term t1, fuzz::int_term t2)
    {
        return slv.mkTerm(CVC4::api::PLUS, t1, t2);
    }

    fuzz::int_term
    add_comm(CVC4::api::Solver& slv, fuzz::FreeVars& fvs, fuzz::int_term t1, fuzz::int_term t2)
    {
        t1 = relations::identity::placeholder(slv, fvs, t1);
        t2 = relations::identity::placeholder(slv, fvs, t2);
        return relations::add::placeholder(slv, fvs, t2, t1);
    }

    fuzz::int_term
    add_by_sub(CVC4::api::Solver& slv, fuzz::FreeVars& fvs, fuzz::int_term t1, fuzz::int_term t2)
    {
        t1 = relations::identity::placeholder(slv, fvs, t1);
        t2 = relations::identity::placeholder(slv, fvs, t2);
        return relations::sub::placeholder(slv, fvs, t1, slv.mkTerm(CVC4::api::UMINUS, t2));
    }

} // namespace add

namespace sub {

    fuzz::int_term
    sub_base(CVC4::api::Solver& slv, fuzz::FreeVars& fvs, fuzz::int_term t1, fuzz::int_term t2)
    {
        return slv.mkTerm(CVC4::api::MINUS, t1, t2);
    }

    fuzz::int_term
    sub_by_add(CVC4::api::Solver& slv, fuzz::FreeVars& fvs, fuzz::int_term t1, fuzz::int_term t2)
    {
        t1 = relations::identity::placeholder(slv, fvs, t1);
        t2 = relations::identity::placeholder(slv, fvs, t2);
        return relations::add::placeholder(slv, fvs, t1, slv.mkTerm(CVC4::api::UMINUS, t2));
    }

} // namespace sub

namespace abs_cvc4
{

    fuzz::int_term
    abs_base(CVC4::api::Solver& slv, fuzz::FreeVars& fvs, fuzz::int_term t)
    {
        return slv.mkTerm(CVC4::api::Kind::ABS, t);
    }

    fuzz::int_term
    abs_by_check_gt_zero(CVC4::api::Solver& slv, fuzz::FreeVars& fvs, fuzz::int_term t)
    {
        fuzz::int_term zero = generators::zero::placeholder(slv, fvs, t);
        fuzz::bool_term gt_term = generators::gt::placeholder(slv, fvs, t, zero);
        fuzz::int_term abs_t = relations::abs_cvc4::placeholder(slv, fvs, t);
        return slv.mkTerm(CVC4::api::Kind::ITE, gt_term, t, abs_t);
    }

    fuzz::int_term
    abs_by_check_lt_zero(CVC4::api::Solver& slv, fuzz::FreeVars& fvs, fuzz::int_term t)
    {
        fuzz::int_term zero = generators::zero::placeholder(slv, fvs, t);
        fuzz::bool_term lt_term = generators::lt::placeholder(slv, fvs, t, zero);
        fuzz::int_term abs_t = relations::abs_cvc4::placeholder(slv, fvs, t);
        return slv.mkTerm(CVC4::api::Kind::ITE, lt_term, abs_t, t);
    }

} // namespace abs

} // namespace relations

} // namespace metalib
