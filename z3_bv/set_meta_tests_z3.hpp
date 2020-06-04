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

    z3::expr placeholder(z3::context&, z3::expr e);

    z3::expr
    get_one(z3::context& c, z3::expr e)
    {
        return c.bv_val(1);
    }

    z3::expr
    one_by_div(z3::context& c, z3::expr f)
    {
        return ite(f == 0, generators::one::placeholder(c), f/f);
    }

    z3::expr
    one_by_pw(z3::context& c, z3::expr f)
    {
        return ite(f == 0, generators::one::placeholder(c), z3::pw(f, 0));
    }

}

namespace zero {

    z3::expr placeholder(z3::context&, z3::expr e);

    z3::expr
    get_zero(z3::context& c, z3::expr e)
    {
        return c.bv_val(0);
    }

    z3::expr
    zero_by_mul(z3::context& c, z3::expr e)
    {
        return e * placeholder(c);
    }

    z3::expr
    zero_by_sub(z3::context& c, z3::expr e)
    {
        return e - e;
    }

    z3::expr
    zero_by_mod(z3::context& c, z3::expr e)
    {
        return ite(e != 0, mod(e, e), placholder(c, e));
    }

} // namespace zero

} //namespace generators

namespace relations {

namespace identity {

    z3::expr placeholder(z3::context& c, z3::expr e);

    z3::expr
    base(z3::context& c, z3::expr e)
    {
        return e;
    }

    z3::expr
    add_zero(z3::context& c, z3::expr e)
    {
        return placeholder(c, e) + generators::zero::placeholder(c);
    }

    z3::expr
    sub_zero(z3::context& c, z3::expr e)
    {
        return placeholder(c, e) - generators::zero::placeholder(c);
    }

    z3::expr
    mul_one(z3::context& c, z3::expr e)
    {
        return placeholder(c, e) * generators::one::placeholder(c);
    }

    z3::expr
    div_one(z3::context& c, z3::expr e)
    {
        return placeholder(c, e) / generators::one::placeholder(c);
    }

    z3::expr
    simplify(z3::context& c, z3::expr e)
    {
        return placholder(c, e).simplify();
    }

    z3::expr
    double_negative(z3::context& c, z3::expr e)
    {
        return -(-(placholder(c, e));
    }


} // namespace identity

} // namespace relations

} // namespace metalib
