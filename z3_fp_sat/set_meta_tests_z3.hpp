namespace metalib {

namespace checks {

    void
    check_sat_expr_maintained(z3::context& c, mr_pair p, z3::model model,
        z3::expr (*chk_op)(z3::expr const&, z3::expr const&))
    {
        z3::solver solver(c);
        z3::expr check_expr = (*chk_op)(p.first, p.second);
        solver.add(check_expr);
        assert(solver.check() != z3::unsat);
        assert(model.eval(check_expr).bool_value() == Z3_L_TRUE);
    }
}

namespace generators {

namespace zero {

    z3::expr placeholder(z3::context&, z3::expr);

    z3::expr
    get_zero(z3::context& c, z3::expr e)
    {
        return c.fpa_val(0.0);
    }

    z3::expr
    zero_by_fuzz_sub(z3::context& c, z3::expr e)
    {
        z3::expr fuzz = fuzz::fuzz_new<z3::expr>();
        return fuzz - fuzz;
    }

    z3::expr
    zero_by_mul(z3::context& c, z3::expr e)
    {
        return e * placeholder(c, e);
    }

    z3::expr
    zero_by_sub(z3::context& c, z3::expr e)
    {
        return e - e;
    }

} // namespace zero


namespace one {

    z3::expr placeholder(z3::context&, z3::expr);

    z3::expr
    get_one(z3::context& c, z3::expr f)
    {
        return c.fpa_val(1.0);
    }

    z3::expr
    one_by_fuzz_div(z3::context& c, z3::expr f)
    {
        z3::expr fuzz = fuzz::fuzz_new<z3::expr>();
        z3::expr zero = generators::zero::placeholder(c, f);
        return ite(fuzz == zero, placeholder(c, fuzz), fuzz/fuzz);
    }

    z3::expr
    one_by_div(z3::context& c, z3::expr f)
    {
        z3::expr zero = generators::zero::placeholder(c, f);
        return ite(f == zero, placeholder(c, f), f/f);
    }
} //namespace one


namespace fuzz_expr {

    z3::expr placeholder(z3::context&);

    z3::expr
    get_expr_by_fuzz(z3::context& c)
    {
        z3::expr fuzz = fuzz::fuzz_new<z3::expr>();
        return fuzz;
    }
} // namespace fuzz

} //namespace generators

namespace relations {

namespace identity_lhs {

    mr_pair placeholder(z3::context& c, mr_pair p);

    mr_pair
    base_iden_lhs(z3::context& c, mr_pair p)
    {
        return p;
    }

    mr_pair
    add_zero_lhs(z3::context& c, mr_pair p)
    {
        return std::make_pair(
            placeholder(c, p).first + generators::zero::placeholder(c, p.first),
            p.second);
    }

    mr_pair
    sub_zero_lhs(z3::context& c, mr_pair p)
    {
        return std::make_pair(
            placeholder(c, p).first - generators::zero::placeholder(c, p.first),
            p.second);
    }

    mr_pair
    mul_one_lhs(z3::context& c, mr_pair p)
    {
        return std::make_pair(
            placeholder(c, p).first * generators::one::placeholder(c, p.first),
            p.second);
    }

    mr_pair
    min_lhs(z3::context& c, mr_pair p)
    {

        return std::make_pair(
            z3::min(placeholder(c, p).first, placeholder(c, p).first),
            p.second);
    }

    mr_pair
    max_lhs(z3::context& c, mr_pair p)
    {
        return std::make_pair(
            z3::max(placeholder(c, p).first, placeholder(c, p).first),
            p.second);
    }

    mr_pair
    max_with_zero_lhs(z3::context& c, mr_pair p)
    {
        z3::expr one = generators::one::placeholder(c, p.first);
        return std::make_pair(
            z3::ite(z3::abs(p.first) == p.first, one, -one) *
                z3::max(abs(placeholder(c, p).first),
                    generators::zero::placeholder(c, p.first)),
            p.second);
    }

    mr_pair
    double_negative_lhs(z3::context& c, mr_pair p)
    {
        z3::expr tmp_e = -(placeholder(c, p).first);
        return std::make_pair(-tmp_e, p.second);
    }

    mr_pair
    iden_simplify_lhs(z3::context& c, mr_pair p)
    {
        return std::make_pair(placeholder(c, p).first.simplify(), p.second);
    }

    mr_pair
    div_one_lhs(z3::context& c, mr_pair p)
    {
        return std::make_pair(
            placeholder(c, p).first / generators::one::placeholder(c, p.first),
            p.second);
    }

    mr_pair
    abs_lhs(z3::context& c, mr_pair p)
    {
        return std::make_pair(
            z3::ite(p.first == z3::abs(p.first), abs(placeholder(c, p).first), p.first),
            p.second);
    }

} // namespace identity_lhs

namespace identity_rhs {

    mr_pair placeholder(z3::context& c, mr_pair p);

    mr_pair
    base_iden_rhs(z3::context& c, mr_pair p)
    {
        return p;
    }

    mr_pair
    add_zero_rhs(z3::context& c, mr_pair p)
    {
        return std::make_pair(p.first,
            placeholder(c, p).second + generators::zero::placeholder(c, p.second));
    }

    mr_pair
    sub_zero_rhs(z3::context& c, mr_pair p)
    {
        return std::make_pair(p.first,
            placeholder(c, p).second - generators::zero::placeholder(c, p.second));
    }

    mr_pair
    mul_one_rhs(z3::context& c, mr_pair p)
    {
        return std::make_pair(p.first,
            placeholder(c, p).second * generators::one::placeholder(c, p.second));
    }

    mr_pair
    min_rhs(z3::context& c, mr_pair p)
    {

        return std::make_pair(p.first,
            z3::min(placeholder(c, p).second, placeholder(c, p).second));
    }

    mr_pair
    max_rhs(z3::context& c, mr_pair p)
    {
        return std::make_pair(p.first,
            z3::max(placeholder(c, p).second, placeholder(c, p).second));
    }

    mr_pair
    max_with_zero_rhs(z3::context& c, mr_pair p)
    {
        z3::expr one = generators::one::placeholder(c, p.second);
        z3::expr zero = generators::zero::placeholder(c, p.first);
        return std::make_pair(p.first,
            z3::ite(p.second >= zero, one, -one) *
                z3::max(abs(placeholder(c, p).second),
                generators::zero::placeholder(c, p.second)));
    }

    mr_pair
    double_negative_rhs(z3::context& c, mr_pair p)
    {
        z3::expr tmp_e = -(placeholder(c, p).second);
        return std::make_pair(p.first, -tmp_e);
    }

    mr_pair
    iden_simplify_rhs(z3::context& c, mr_pair p)
    {
        return std::make_pair(p.first, placeholder(c, p).second.simplify());
    }

    mr_pair
    div_one_rhs(z3::context& c, mr_pair p)
    {
        return std::make_pair(p.first,
            placeholder(c, p).second / generators::one::placeholder(c, p.second));
    }

    mr_pair
    abs_rhs(z3::context& c, mr_pair p)
    {
        return std::make_pair(
            p.first,
            z3::ite(p.second == z3::abs(p.second), abs(placeholder(c, p).second), p.second));
    }

} // namespace identity_rhs

//namespace add_rhs {

    //mr_pair placeholder(mr_pair p, z3::expr e);

    //mr_pair
    //base_add_rhs(mr_pair p, z3::expr e)
    //{
        //return std::make_pair(p.first, p.second + z3::abs(e));
    //}

    //mr_pair
    //add_pair_first_rhs(mr_pair p, z3::expr e)
    //{
        //return placeholder(p, p.first);
    //}

    //mr_pair
    //add_pair_second_rhs(mr_pair p, z3::expr e)
    //{
        //return placeholder(p, p.second);
    //}

    //mr_pair
    //add_by_fuzz_rhs(mr_pair p, z3::expr e)
    //{
        //z3::context& c = p.first.ctx();
        //z3::expr f = generators::fuzz_expr::placeholder(p.first.ctx());
        //return placeholder(p, f);
    //}

//} // namespace add_rhs

//namespace mul_rhs {

    //mr_pair placeholder(mr_pair p, z3::expr e);

    //mr_pair
    //base_mul_rhs(mr_pair p, z3::expr e)
    //{
        //return std::make_pair(p.first,
            //z3::ite(operator||(operator==(e, e.ctx().int_val(0)), operator<(z3::abs(e), e.ctx().int_val(1))),
               //p.second, z3::abs(p.second * e)));
    //}

    //mr_pair
    //mul_pair_first_rhs(mr_pair p, z3::expr e)
    //{
        //return placeholder(p, p.first);
    //}

    //mr_pair
    //mul_pair_second_rhs(mr_pair p, z3::expr e)
    //{
        //return placeholder(p, p.second);
    //}

    //mr_pair
    //mul_by_fuzz_rhs(mr_pair p, z3::expr e)
    //{
        //z3::context& c = p.first.ctx();
        //z3::expr f = generators::fuzz_expr::placeholder(p.first.ctx());
        //return placeholder(p, f);
    //}

//} // namespace mul_rhs

//namespace modulo
//{

    //z3::expr placeholder(z3::expr e1, z3::expr e2);

    //z3::expr
    //base_modulo(z3::expr e1, z3::expr e2)
    //{
        //return ite(e2 != 0, z3::mod(e1, e2), e1);
    //}

    //z3::expr
    //mod_with_rem(z3::expr e1, z3::expr e2)
    //{
        //return ite(e2 != 0, z3::abs(z3::rem(e1, e2)), e1);
    //}

    //z3::expr
    //mod_by_sub(z3::expr e1, z3::expr e2)
    //{
        //return ite(e2 != 0, e1 - (e2 * (e1 / e2)), e1);
    //}

//} // namespace modulo

} // namespace relations

} // namespace metalib
