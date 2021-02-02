namespace metalib {

namespace checks {

    void
    check_expr_same_sat(CVC4::api::Solver& slv, CVC4::api::Term t1, CVC4::api::Term t2)
    {
        CVC4::api::Term check = slv.mkTerm(CVC4::api::DISTINCT, t1, t2);
        slv.assertFormula(check);
        assert(!slv.checkSat().isSat());
        slv.resetAssertions();
    }

} // namespace checks

namespace generators {

namespace fuzz_expr {

    CVC4::api::Term placeholder(CVC4::api::Solver& slv);

    CVC4::api::Term
    get_expr_by_fuzz(CVC4::api::Solver& c)
    {
        CVC4::api::Term fuzz = fuzz::fuzz_new<CVC4::api::Term>();
        return fuzz;
    }

} // namespace fuzz_expr

namespace zero {

    CVC4::api::Term placeholder(CVC4::api::Solver& slv, CVC4::api::Term t);

    CVC4::api::Term
    get_zero(CVC4::api::Solver& slv, CVC4::api::Term t)
    {
        return slv.mkInteger(0);
    }

    CVC4::api::Term
    zero_by_fuzz_sub(CVC4::api::Solver& c)
    {
        CVC4::api::Term fuzz = generators::fuzz_expr::placeholder(c);
        return c.mkTerm(CVC4::api::MINUS, fuzz, fuzz);
    }

    CVC4::api::Term
    zero_by_mul(CVC4::api::Solver& c, CVC4::api::Term e)
    {
        return c.mkTerm(CVC4::api::MULT, e, placeholder(c, e));
    }

    CVC4::api::Term
    zero_by_sub(CVC4::api::Solver& c, CVC4::api::Term e)
    {
        return c.mkTerm(CVC4::api::MINUS, e, e);
    }

    CVC4::api::Term
    zero_by_mod(CVC4::api::Solver& c, CVC4::api::Term e)
    {
        CVC4::api::Term tmp_zero = placeholder(c, e);
        return e.eqTerm(tmp_zero).iteTerm(tmp_zero,
            c.mkTerm(CVC4::api::INTS_MODULUS, e, e));
    }

} // namespace zero

namespace one {

    CVC4::api::Term placeholder(CVC4::api::Solver& slv, CVC4::api::Term t);

    CVC4::api::Term
    get_one(CVC4::api::Solver& slv, CVC4::api::Term t)
    {
        return slv.mkInteger(1);
    }

    CVC4::api::Term
    one_by_div(CVC4::api::Solver& c, CVC4::api::Term f)
    {
        CVC4::api::Term tmp_zero = zero::placeholder(c, f);
        CVC4::api::Term is_zero = tmp_zero.eqTerm(f);
        return is_zero.iteTerm(placeholder(c, f),
            c.mkTerm(CVC4::api::INTS_DIVISION, f, f));
    }

    CVC4::api::Term
    one_by_fuzz_div(CVC4::api::Solver& c, CVC4::api::Term f)
    {
        CVC4::api::Term fuzz = generators::fuzz_expr::placeholder(c);
        CVC4::api::Term tmp_zero = zero::placeholder(c, fuzz);
        CVC4::api::Term is_zero = tmp_zero.eqTerm(fuzz);
        return is_zero.iteTerm(generators::one::placeholder(c, fuzz),
            c.mkTerm(CVC4::api::INTS_DIVISION, fuzz, fuzz));
    }

    //CVC4::api::Term
    //one_by_pw(CVC4::api::Solver& c, CVC4::api::Term f)
    //{
        //CVC4::api::Term tmp_zero = zero::placeholder(c, f);
        //CVC4::api::Term is_zero = tmp_zero.eqTerm(f);
        //return is_zero.iteTerm(placeholder(c, f),
            //c.mkTerm(CVC4::api::POW, f, tmp_zero));
    //}


} // namespace one

} // namespace generators

namespace relations {

namespace identity {

    CVC4::api::Term placeholder(CVC4::api::Solver& slv, CVC4::api::Term t);

    CVC4::api::Term
    base_iden(CVC4::api::Solver& slv, CVC4::api::Term t)
    {
        return t;
    }

    CVC4::api::Term
    add_zero(CVC4::api::Solver& slv, CVC4::api::Term t)
    {
        t = relations::identity::placeholder(slv, t);
        return slv.mkTerm(CVC4::api::PLUS, placeholder(slv, t),
            generators::zero::placeholder(slv, t));
    }

    CVC4::api::Term
    sub_zero(CVC4::api::Solver& slv, CVC4::api::Term t)
    {
        t = relations::identity::placeholder(slv, t);
        return slv.mkTerm(CVC4::api::MINUS, placeholder(slv, t),
            generators::zero::placeholder(slv, t));
    }

    CVC4::api::Term
    mul_one(CVC4::api::Solver& slv, CVC4::api::Term t)
    {
        t = relations::identity::placeholder(slv, t);
        return slv.mkTerm(CVC4::api::MULT, placeholder(slv, t),
            generators::one::placeholder(slv, t));
    }

    CVC4::api::Term
    double_negative(CVC4::api::Solver& c, CVC4::api::Term e)
    {
        e = relations::identity::placeholder(c, e);
        CVC4::api::Term tmp_e = c.mkTerm(CVC4::api::UMINUS, e);
        return c.mkTerm(CVC4::api::UMINUS, tmp_e);
    }

    CVC4::api::Term
    abs(CVC4::api::Solver& c, CVC4::api::Term e)
    {
        e = relations::identity::placeholder(c, e);
        return c.mkTerm(CVC4::api::ITE,
            c.mkTerm(CVC4::api::EQUAL, c.mkTerm(CVC4::api::ABS, e), e),
            c.mkTerm(CVC4::api::ABS, e), e);
    }

    //CVC4::api::Term
    //sqrt_square(CVC4::api::Solver& c, CVC4::api::Term e)
    //{
        //CVC4::api::Term two = c.mkInteger(2);
        //e = relations::identity::placeholder(c, e);
        //return c.mkTerm(CVC4::api::TO_INTEGER,
            //c.mkTerm(CVC4::api::SQRT, c.mkTerm(CVC4::api::POW, e, two)));
    //}

    CVC4::api::Term
    iden_by_ite(CVC4::api::Solver& c, CVC4::api::Term e)
    {
        CVC4::api::Term dead = generators::fuzz_expr::placeholder(c);
        e = relations::identity::placeholder(c, e);
        return c.mkTerm(CVC4::api::ITE,
            c.mkTerm(CVC4::api::EQUAL, e, dead), dead, e);
    }

    CVC4::api::Term
    iden_by_simplify(CVC4::api::Solver& c, CVC4::api::Term e)
    {
        return c.simplify(relations::identity::placeholder(c, e));
    }


} // namespace identity

namespace sub {
    CVC4::api::Term placeholder(CVC4::api::Solver&, CVC4::api::Term, CVC4::api::Term);
}

namespace add {

    CVC4::api::Term placeholder(CVC4::api::Solver&, CVC4::api::Term, CVC4::api::Term);

    CVC4::api::Term
    add_base(CVC4::api::Solver& c, CVC4::api::Term e1, CVC4::api::Term e2)
    {
        return c.mkTerm(CVC4::api::PLUS, e1, e2);
    }

    CVC4::api::Term
    add_comm(CVC4::api::Solver& c, CVC4::api::Term e1, CVC4::api::Term e2)
    {
        e1 = relations::identity::placeholder(c, e1);
        e2 = relations::identity::placeholder(c, e2);
        return relations::add::placeholder(c, e2, e1);
    }

    CVC4::api::Term
    add_by_sub(CVC4::api::Solver& c, CVC4::api::Term e1, CVC4::api::Term e2)
    {
        e1 = relations::identity::placeholder(c, e1);
        e2 = relations::identity::placeholder(c, e2);
        return relations::sub::placeholder(c, e1, c.mkTerm(CVC4::api::UMINUS, e2));
    }

} // namespace add

namespace sub {

    CVC4::api::Term
    sub_base(CVC4::api::Solver& c, CVC4::api::Term e1, CVC4::api::Term e2)
    {
        return c.mkTerm(CVC4::api::MINUS, e1, e2);
    }

    CVC4::api::Term
    sub_by_add(CVC4::api::Solver& c, CVC4::api::Term e1, CVC4::api::Term e2)
    {
        e1 = relations::identity::placeholder(c, e1);
        e2 = relations::identity::placeholder(c, e2);
        return relations::add::placeholder(c, e1, c.mkTerm(CVC4::api::UMINUS, e2));
    }

} // namespace sub

namespace mul {

    CVC4::api::Term placeholder(CVC4::api::Solver&, CVC4::api::Term, CVC4::api::Term);

    CVC4::api::Term
    mul_base(CVC4::api::Solver& c, CVC4::api::Term e1, CVC4::api::Term e2)
    {
        return c.mkTerm(CVC4::api::MULT, e1, e2);
    }

    CVC4::api::Term
    mul_comm(CVC4::api::Solver& c, CVC4::api::Term e1, CVC4::api::Term e2)
    {
        e1 = relations::identity::placeholder(c, e1);
        e2 = relations::identity::placeholder(c, e2);
        return relations::mul::placeholder(c, e2, e1);
    }

} // namespace mul

namespace modulo {

    CVC4::api::Term placeholder(CVC4::api::Solver&, CVC4::api::Term, CVC4::api::Term);

    CVC4::api::Term
    mod_base(CVC4::api::Solver& c, CVC4::api::Term e1, CVC4::api::Term e2)
    {
        e1 = relations::identity::placeholder(c, e1);
        e2 = relations::identity::placeholder(c, e2);
        CVC4::api::Term zero = generators::zero::placeholder(c, e1);
        return c.mkTerm(CVC4::api::ITE,
            c.mkTerm(CVC4::api::EQUAL, e2, zero), e1,
            c.mkTerm(CVC4::api::INTS_MODULUS, e1, e2));
    }

    CVC4::api::Term
    mod_by_sub(CVC4::api::Solver& c, CVC4::api::Term e1, CVC4::api::Term e2)
    {
        e1 = relations::identity::placeholder(c, e1);
        e2 = relations::identity::placeholder(c, e2);
        CVC4::api::Term zero = generators::zero::placeholder(c, e1);
        return c.mkTerm(CVC4::api::ITE,
            c.mkTerm(CVC4::api::EQUAL, e2, zero), e1,
            c.mkTerm(CVC4::api::MINUS, e1,
                c.mkTerm(CVC4::api::MULT, e2,
                    c.mkTerm(CVC4::api::INTS_DIVISION, e1, e2))));
    }

} // namespace modulo


} // namespace relations

} // namespace metalib
