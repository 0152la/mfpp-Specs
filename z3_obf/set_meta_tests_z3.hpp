namespace metalib {

namespace checks {

    void
    check_expr_same_sat(z3::context& c, z3::expr e1, z3::expr e2)
    {
        z3::solver solver(c);
        z3::expr conjecture = z3::operator==(e1, e2);
        solver.add(!conjecture);
        assert(solver.check() != z3::sat);
    }

}

namespace generators {

namespace one {

    z3::expr placeholder(z3::context&, z3::expr f);

    z3::expr
    get_one(z3::context& c, z3::expr f)
    {
        return c.int_val(1);
    }

    z3::expr
    one_by_div(z3::context& c, z3::expr f)
    {
        return ite(f == 0, placeholder(c, f), f/f);
    }

    z3::expr
    one_by_pw(z3::context& c, z3::expr f)
    {
        return ite(f == 0, placeholder(c, f), z3::pw(f, 0));
    }


} //namespace one

namespace zero {

    z3::expr placeholder(z3::context&, z3::expr e);

    z3::expr
    get_zero(z3::context& c, z3::expr e)
    {
        return c.int_val(0);
    }

    //z3::expr
    //zero_by_fuzz_sub(z3::context& c)
    //{
        //z3::expr fuzz = fuzz::fuzz_new<z3::expr>();
        //return fuzz - fuzz;
    //}

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

    z3::expr
    zero_by_mod(z3::context& c, z3::expr e)
    {
        z3::expr tmp_zero = placeholder(c, e);
        return ite(e != tmp_zero, z3::mod(e, e), tmp_zero);
    }

} // namespace zero

} //namespace generators

namespace relations {

namespace identity {

    z3::expr placeholder(z3::context& c, z3::expr e);

    z3::expr
    base_iden(z3::context& c, z3::expr e)
    {
        return e;
    }

    z3::expr
    add_zero(z3::context& c, z3::expr e)
    {
        return placeholder(e.ctx(), e) + generators::zero::placeholder(c, e);
    }

    z3::expr
    sub_zero(z3::context& c, z3::expr e)
    {
        return placeholder(c, e) - generators::zero::placeholder(c, e);
    }

    z3::expr
    mul_one(z3::context& c, z3::expr e)
    {
        return placeholder(e.ctx(), e) * generators::one::placeholder(c, e);
    }

    z3::expr
    min(z3::context& c, z3::expr e)
    {

        return z3::min(placeholder(c, e), placeholder(c, e));
    }

    z3::expr
    max(z3::context& c, z3::expr e)
    {
        return z3::max(relations::identity::placeholder(c, e), relations::identity::placeholder(c, e));
    }

    z3::expr
    max_with_zero(z3::context& c, z3::expr e)
    {
        z3::expr one = generators::one::placeholder(c, e);
        return z3::ite(e >= 0, one, -one) * z3::max(abs(placeholder(c, e)), generators::zero::placeholder(c, e));
    }

    z3::expr
    double_negative(z3::context& c, z3::expr e)
    {
        z3::expr tmp_e = -(e);
        return -(tmp_e);
    }

    /*z3::expr
    iden_simplify(z3::context& c, z3::expr e)
    {
        return placeholder(c, e).simplify();
    }*/

    z3::expr
    div_one(z3::context& c, z3::expr e)
    {
        return placeholder(c, e) / generators::one::placeholder(c, e);
    }

    //z3::expr
    //identity_by_mul(z3::context& c, z3::expr e1)
    //{
        //e2 = fuzz::new<z3::expr>();
        //return e1 * e2 - e1 * (e2 - generators::one::placeholder(e1.ctx()));
    //}

} // namespace identity

namespace add {

    z3::expr placeholder(z3::expr e1, z3::expr e2);

    z3::expr
    base_add(z3::expr e1, z3::expr e2)
    {
        return e1 + e2;
    }

    z3::expr
    add_commute(z3::expr e1, z3::expr e2)
    {
        return placeholder(e2, e1);
    }

    /*
    z3::expr
    add_by_ones(z3::expr e1, z3::expr e2)
    {
        z3::expr sum = identity::placeholder(e1.ctx(), e1);
        for (int i = 0; (i < z3::abs(e2)).simplify().is_true(); ++i)
        {
            z3::expr one = generators::one::placeholder(e1.ctx(), e1);
            sum = placeholder(sum, z3::ite(e2 >= 0, one, -one));
            //sum = placeholder(sum, generators::one::placeholder(e1.ctx()));
        }
        return sum;
    }
    */

} // namespace add

namespace multiply {

    z3::expr placeholder(z3::expr e1, z3::expr e2);

    z3::expr
    base_mul(z3::expr e1, z3::expr e2)
    {
        return e1 * e2;
    }

    z3::expr
    mul_commute(z3::expr e1, z3::expr e2)
    {
        return placeholder(e2, e1);
    }

    /*
    z3::expr
    mul_by_add(z3::expr e1, z3::expr e2)
    {
        z3::expr mul = generators::zero::placeholder(e1.ctx(), e1);
        for (int i = 0; (i < z3::abs(e2)).simplify().is_true(); ++i)
        {
            z3::expr e1_iden = identity::placeholder(e1.ctx(), e1);
            mul = add::placeholder(mul, z3::ite(e2 >= 0, e1_iden, -e1_iden));
        }
        return mul;
    }
    */

} // namespace multiply

namespace modulo
{

    z3::expr placeholder(z3::expr e1, z3::expr e2);

    z3::expr
    base_modulo(z3::expr e1, z3::expr e2)
    {
        return ite(e2 != 0, z3::mod(e1, e2), e1);
    }

    z3::expr
    mod_with_rem(z3::expr e1, z3::expr e2)
    {
        return ite(e2 != 0, z3::abs(z3::rem(e1, e2)), e1);
    }

    z3::expr
    mod_by_sub(z3::expr e1, z3::expr e2)
    {
        return ite(e2 != 0, e1 - (e2 * (e1 / e2)), e1);
    }

} // namespace modulo

} // namespace relations

} // namespace metalib
