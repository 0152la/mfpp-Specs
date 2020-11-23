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
        CVC4::api::Term fuzz = fuzz::fuzz_new<CVC4::api::Term>();
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

    //CVC4::api::Term
    //one_by_pw(CVC4::api::Solver& c, CVC4::api::Term f)
    //{
        //CVC4::api::Term tmp_zero = zero::placeholder(c, f);
        //CVC4::api::Term is_zero = tmp_zero.eqTerm(f);
        //return is_zero.iteTerm(placeholder(c, f),
            //c.mkTerm(CVC4::api::POW, f, tmp_zero));
    //}

} // namespace one

} //namespace generators

namespace relations {

namespace identity_lhs {

    mr_pair placeholder(CVC4::api::Solver& c, mr_pair p);

    mr_pair
    base_iden_lhs(CVC4::api::Solver& c, mr_pair p)
    {
        return p;
    }

    mr_pair
    add_zero_lhs(CVC4::api::Solver& c, mr_pair p)
    {
        return std::make_pair(
            c.mkTerm(CVC4::api::PLUS, placeholder(c, p).first,
                generators::zero::placeholder(c, p.first)),
            p.second);
    }

    mr_pair
    sub_zero_lhs(CVC4::api::Solver& c, mr_pair p)
    {
        return std::make_pair(
            c.mkTerm(CVC4::api::MINUS, placeholder(c, p).first,
                generators::zero::placeholder(c, p.first)),
            p.second);
    }

    mr_pair
    mul_one_lhs(CVC4::api::Solver& c, mr_pair p)
    {
        return std::make_pair(
            c.mkTerm(CVC4::api::MULT, placeholder(c, p).first,
                generators::one::placeholder(c, p.first)),
            p.second);
    }


    mr_pair
    double_negative_lhs(CVC4::api::Solver& c, mr_pair p)
    {
        CVC4::api::Term tmp_e = c.mkTerm(CVC4::api::UMINUS, placeholder(c, p).first);
        return std::make_pair(c.mkTerm(CVC4::api::UMINUS, tmp_e), p.second);
    }

    mr_pair
    iden_simplify_lhs(CVC4::api::Solver& c, mr_pair p)
    {
        return std::make_pair(c.simplify(placeholder(c, p).first), p.second);
    }

    mr_pair
    div_one_lhs(CVC4::api::Solver& c, mr_pair p)
    {
        return std::make_pair(
            c.mkTerm(CVC4::api::INTS_DIVISION, placeholder(c, p).first,
                generators::one::placeholder(c, p.first)),
            p.second);
    }

    mr_pair
    iden_by_ite_lt_lhs(CVC4::api::Solver& c, mr_pair p)
    {
        CVC4::api::Term dead = fuzz::fuzz_new<CVC4::api::Term>();
        return std::make_pair(
            c.mkTerm(CVC4::api::ITE, c.mkTerm(CVC4::api::LT, p.first, p.first),
                dead, placeholder(c, p).first),
            p.second);
    }
} // namespace identity_lhs

namespace identity_rhs {

    mr_pair placeholder(CVC4::api::Solver& c, mr_pair p);

    mr_pair
    base_iden_rhs(CVC4::api::Solver& c, mr_pair p)
    {
        return p;
    }

    mr_pair
    add_zero_rhs(CVC4::api::Solver& c, mr_pair p)
    {
        return std::make_pair(
            p.first,
            c.mkTerm(CVC4::api::PLUS, placeholder(c, p).second,
                generators::zero::placeholder(c, p.second)));
    }

    mr_pair
    sub_zero_rhs(CVC4::api::Solver& c, mr_pair p)
    {
        return std::make_pair(
            p.first,
            c.mkTerm(CVC4::api::MINUS, placeholder(c, p).second,
                generators::zero::placeholder(c, p.second)));
    }

    mr_pair
    mul_one_rhs(CVC4::api::Solver& c, mr_pair p)
    {
        return std::make_pair(
            p.first,
            c.mkTerm(CVC4::api::MULT, placeholder(c, p).second,
                generators::one::placeholder(c, p.second)));
    }


    mr_pair
    double_negative_rhs(CVC4::api::Solver& c, mr_pair p)
    {
        CVC4::api::Term tmp_e = c.mkTerm(CVC4::api::UMINUS, placeholder(c, p).second);
        return std::make_pair(p.first, c.mkTerm(CVC4::api::UMINUS, tmp_e));
    }

    mr_pair
    iden_simplify_rhs(CVC4::api::Solver& c, mr_pair p)
    {
        return std::make_pair(p.first, c.simplify(placeholder(c, p).second));
    }

    mr_pair
    div_one_rhs(CVC4::api::Solver& c, mr_pair p)
    {
        return std::make_pair(
            p.first,
            c.mkTerm(CVC4::api::INTS_DIVISION, placeholder(c, p).second,
                generators::one::placeholder(c, p.second)));
    }

    mr_pair
    iden_by_ite_lt_rhs(CVC4::api::Solver& c, mr_pair p)
    {
        CVC4::api::Term dead = fuzz::fuzz_new<CVC4::api::Term>();
        return std::make_pair(
            p.second,
            c.mkTerm(CVC4::api::ITE, c.mkTerm(CVC4::api::LT, p.second, p.second),
                dead, placeholder(c, p).second));
    }
} // namespace identity_rhs

//namespace add {

    //CVC4::api::Term placeholder(CVC4::api::Term e1, CVC4::api::Term e2);

    //CVC4::api::Term
    //base_add(CVC4::api::Term e1, CVC4::api::Term e2)
    //{
        //return e1 + e2;
    //}

    //CVC4::api::Term
    //add_commute(CVC4::api::Term e1, CVC4::api::Term e2)
    //{
        //return placeholder(e2, e1);
    //}

    //[>
    //CVC4::api::Term
    //add_by_ones(CVC4::api::Term e1, CVC4::api::Term e2)
    //{
        //CVC4::api::Term sum = identity::placeholder(e1.ctx(), e1);
        //for (int i = 0; (i < z3::abs(e2)).simplify().is_true(); ++i)
        //{
            //CVC4::api::Term one = generators::one::placeholder(e1.ctx(), e1);
            //sum = placeholder(sum, z3::ite(e2 >= 0, one, -one));
            ////sum = placeholder(sum, generators::one::placeholder(e1.ctx()));
        //}
        //return sum;
    //}
    //*/

//} // namespace add

//namespace multiply {

    //CVC4::api::Term placeholder(CVC4::api::Term e1, CVC4::api::Term e2);

    //CVC4::api::Term
    //base_mul(CVC4::api::Term e1, CVC4::api::Term e2)
    //{
        //return e1 * e2;
    //}

    //CVC4::api::Term
    //mul_commute(CVC4::api::Term e1, CVC4::api::Term e2)
    //{
        //return placeholder(e2, e1);
    //}

    //[>
    //CVC4::api::Term
    //mul_by_add(CVC4::api::Term e1, CVC4::api::Term e2)
    //{
        //CVC4::api::Term mul = generators::zero::placeholder(e1.ctx(), e1);
        //for (int i = 0; (i < z3::abs(e2)).simplify().is_true(); ++i)
        //{
            //CVC4::api::Term e1_iden = identity::placeholder(e1.ctx(), e1);
            //mul = add::placeholder(mul, z3::ite(e2 >= 0, e1_iden, -e1_iden));
        //}
        //return mul;
    //}
    //*/

//} // namespace multiply

//namespace modulo
//{

    //CVC4::api::Term placeholder(CVC4::api::Term e1, CVC4::api::Term e2);

    //CVC4::api::Term
    //base_modulo(CVC4::api::Term e1, CVC4::api::Term e2)
    //{
        //return ite(e2 != 0, z3::mod(e1, e2), e1);
    //}

    //CVC4::api::Term
    //mod_with_rem(CVC4::api::Term e1, CVC4::api::Term e2)
    //{
        //return ite(e2 != 0, z3::abs(z3::rem(e1, e2)), e1);
    //}

    //CVC4::api::Term
    //mod_by_sub(CVC4::api::Term e1, CVC4::api::Term e2)
    //{
        //return ite(e2 != 0, e1 - (e2 * (e1 / e2)), e1);
    //}

//} // namespace modulo

} // namespace relations

} // namespace metalib
