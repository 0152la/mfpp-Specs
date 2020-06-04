namespace metalib {

namespace checks {

    void
    check_expr_same_sat(CVC4::api::Solver& slv, CVC4::api::Term t1, CVC4::api::Term t2)
    {
        CVC4::api::Term check = slv.mkTerm(CVC4::api::DISTINCT, t1, t2);
        slv.assertFormula(check);
        assert(!slv.checkSat().isSat());
    }

} // namespace checks

namespace generators {

namespace one {

    CVC4::api::Term placeholder(CVC4::api::Solver& slv, CVC4::api::Term t);

    CVC4::api::Term
    get_one(CVC4::api::Solver& slv, CVC4::api::Term t)
    {
        return slv.mkReal(1);
    }

    CVC4::api::Term
    one_by_div(CVC4::api::Solver& c, CVC4::api::Term f)
    {
        CVC4::api::Term tmp_zero = placeholder(c, f);
        CVC4::api::Term is_zero = tmp_zero.eqTerm(f);
        return is_zero.iteTerm(placeholder(c, f),
            c.mkTerm(CVC4::api::INTS_DIVISION, f, f));
    }

    CVC4::api::Term
    one_by_pw(CVC4::api::Solver& c, CVC4::api::Term f)
    {
        CVC4::api::Term tmp_zero = placeholder(c, f);
        CVC4::api::Term is_zero = tmp_zero.eqTerm(f);
        return is_zero.iteTerm(placeholder(c, f),
            c.mkTerm(CVC4::api::POW, f, tmp_zero));
    }


} // namespace one

namespace zero {

    CVC4::api::Term placeholder(CVC4::api::Solver& slv, CVC4::api::Term t);

    CVC4::api::Term
    get_zero(CVC4::api::Solver& slv, CVC4::api::Term t)
    {
        return slv.mkReal(0);
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
        return e.eqTerm(tmp_zero).iteTerm(
            c.mkTerm(CVC4::api::INTS_MODULUS_TOTAL, e, e), tmp_zero);
    }

} // namespace zero

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
        return slv.mkTerm(CVC4::api::PLUS, placeholder(slv, t),
            generators::zero::placeholder(slv, t));
    }

    CVC4::api::Term
    mul_one(CVC4::api::Solver& slv, CVC4::api::Term t)
    {
        return slv.mkTerm(CVC4::api::MULT, placeholder(slv, t),
            generators::one::placeholder(slv, t));
    }

    CVC4::api::Term
    double_negative(CVC4::api::Solver& c, CVC4::api::Term e)
    {
        CVC4::api::Term tmp_e = c.mkTerm(CVC4::api::UMINUS, e);
        return c.mkTerm(CVC4::api::UMINUS, tmp_e);
    }

} // namespace identity

} // namespace relations

} // namespace metalib
