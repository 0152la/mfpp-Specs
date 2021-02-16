namespace metalib {

/*******************************************************************************
 * Metamorphic checks
 ******************************************************************************/

namespace checks {

    void
    check_expr_same_sat(z3::context& c, fuzz::FreeVars& fvs, fuzz::int_expr e1, fuzz::int_expr e2)
    {
        check_count += 1;
        std::cout << "START CHECK COUNT " << check_count << std::endl;
        z3::solver solver(c);
        z3::expr conjecture = z3::operator==(e1, e2);
        solver.add(!conjecture);
        assert(solver.check() != z3::sat);
        assert(c.check_error() == Z3_OK);
        std::cout << "END CHECK COUNT " << check_count << std::endl;
    }

}

/*******************************************************************************
 * Forward Declarations
 ******************************************************************************/

namespace generators {
namespace fuzz_int_expr {
    fuzz::int_expr placeholder(z3::context& c, fuzz::FreeVars&);
}
namespace fuzz_bool_expr {
    fuzz::bool_expr placeholder(z3::context& c, fuzz::FreeVars&);
}
namespace zero {
    fuzz::int_expr placeholder(z3::context& c, fuzz::FreeVars&, fuzz::int_expr);
}
namespace one {
    fuzz::int_expr placeholder(z3::context& c, fuzz::FreeVars&, fuzz::int_expr);
}
namespace true_z3 {
    fuzz::bool_expr placeholder(z3::context& c, fuzz::FreeVars&, fuzz::bool_expr);
}
namespace false_z3 {
    fuzz::bool_expr placeholder(z3::context& c, fuzz::FreeVars&, fuzz::bool_expr);
}
namespace iden_bool {
    fuzz::bool_expr placeholder(z3::context& c, fuzz::FreeVars&, fuzz::bool_expr);
}
namespace not_z3 {
    fuzz::bool_expr placeholder(z3::context& c, fuzz::FreeVars&, fuzz::bool_expr);
}
namespace and_z3 {
    fuzz::bool_expr placeholder(z3::context& c, fuzz::FreeVars&, fuzz::bool_expr, fuzz::bool_expr);
}
namespace or_z3 {
    fuzz::bool_expr placeholder(z3::context& c, fuzz::FreeVars&, fuzz::bool_expr, fuzz::bool_expr);
}
namespace xor_z3 {
    fuzz::bool_expr placeholder(z3::context& c, fuzz::FreeVars&, fuzz::bool_expr, fuzz::bool_expr);
}
namespace equal_int {
    fuzz::bool_expr placeholder(z3::context& c, fuzz::FreeVars&, fuzz::int_expr, fuzz::int_expr);
}
namespace lt {
    fuzz::bool_expr placeholder(z3::context& c, fuzz::FreeVars&, fuzz::int_expr, fuzz::int_expr);
}
namespace gt {
    fuzz::bool_expr placeholder(z3::context& c, fuzz::FreeVars&, fuzz::int_expr, fuzz::int_expr);
}
namespace leq {
    fuzz::bool_expr placeholder(z3::context& c, fuzz::FreeVars&, fuzz::int_expr, fuzz::int_expr);
}
namespace geq {
    fuzz::bool_expr placeholder(z3::context& c, fuzz::FreeVars&, fuzz::int_expr, fuzz::int_expr);
}

} // namespace generators

namespace relations {
namespace identity {
    fuzz::int_expr placeholder(z3::context& c, fuzz::FreeVars&, fuzz::int_expr);
}
namespace add {
    fuzz::int_expr placeholder(z3::context& c, fuzz::FreeVars&, fuzz::int_expr, fuzz::int_expr);
}
namespace sub {
    fuzz::int_expr placeholder(z3::context& c, fuzz::FreeVars&, fuzz::int_expr, fuzz::int_expr);
}
namespace mul {
    fuzz::int_expr placeholder(z3::context& c, fuzz::FreeVars&, fuzz::int_expr, fuzz::int_expr);
}
namespace division {
    fuzz::int_expr placeholder(z3::context& c, fuzz::FreeVars&, fuzz::int_expr, fuzz::int_expr);
}
namespace modulo {
    fuzz::int_expr placeholder(z3::context& c, fuzz::FreeVars&, fuzz::int_expr, fuzz::int_expr);
}
namespace abs_z3 {
    fuzz::int_expr placeholder(z3::context& c, fuzz::FreeVars&, fuzz::int_expr);
}
} //namespace relations

/*******************************************************************************
 * Generators
 ******************************************************************************/

namespace generators {

namespace fuzz_int_expr {

    fuzz::int_expr
    get_expr_by_fuzz(z3::context& c, fuzz::FreeVars& fvs)
    {
        fuzz::int_expr fuzz = fuzz::fuzz_new<fuzz::int_expr>();
        return fuzz;
    }

} // namespace fuzz_int_expr

namespace fuzz_bool_expr {

    fuzz::bool_expr
    get_expr_by_fuzz(z3::context& c, fuzz::FreeVars& fvs)
    {
        fuzz::bool_expr fuzz = fuzz::fuzz_new<fuzz::bool_expr>();
        return fuzz;
    }

} // namespace fuzz_bool_expr

namespace zero {

    fuzz::int_expr
    get_zero(z3::context& ctx, fuzz::FreeVars& fvs, fuzz::int_expr t)
    {
        return ctx.int_val(0);
    }

    fuzz::int_expr
    zero_by_mul(z3::context& ctx, fuzz::FreeVars& fvs, fuzz::int_expr t)
    {
        fuzz::int_expr zero = generators::zero::placeholder(ctx, fvs, t);
        return relations::mul::placeholder(ctx, fvs, t, zero);
    }

    fuzz::int_expr
    zero_by_sub(z3::context& ctx, fuzz::FreeVars& fvs, fuzz::int_expr t)
    {
        fuzz::int_expr iden_expr = relations::identity::placeholder(ctx, fvs, t);
        return relations::sub::placeholder(ctx, fvs, t, iden_expr);
    }

    fuzz::int_expr
    zero_by_fuzz_sub(z3::context& ctx, fuzz::FreeVars& fvs, fuzz::int_expr t)
    {
        fuzz::int_expr fuzz = generators::fuzz_int_expr::placeholder(ctx, fvs);
        fuzz::int_expr iden_fuzz = relations::identity::placeholder(ctx, fvs, fuzz);
        return relations::sub::placeholder(ctx, fvs, fuzz, iden_fuzz);
    }

    fuzz::int_expr
    zero_by_mod(z3::context& ctx, fuzz::FreeVars& fvs, fuzz::int_expr t)
    {
        fuzz::int_expr iden_expr = relations::identity::placeholder(ctx, fvs, t);
        fuzz::int_expr tmp_zero = generators::zero::placeholder(ctx, fvs, t);
        fuzz::int_expr mod_ts = relations::modulo::placeholder(ctx, fvs, t, iden_expr);
        return z3::ite(z3::operator==(tmp_zero, t), tmp_zero, mod_ts);
    }

    fuzz::int_expr
    zero_by_div(z3::context& ctx, fuzz::FreeVars& fvs, fuzz::int_expr t)
    {
        fuzz::int_expr tmp_zero = generators::zero::placeholder(ctx, fvs, t);
        fuzz::int_expr is_zero = z3::operator==(tmp_zero, t);
        fuzz::int_expr tmp_zero_return = generators::zero::placeholder(ctx, fvs, t);
        fuzz::int_expr div_ts = relations::division::placeholder(ctx, fvs, tmp_zero, t);
        return z3::ite(is_zero, tmp_zero_return, div_ts);
    }

    fuzz::int_expr
    zero_by_div_fuzz(z3::context& ctx, fuzz::FreeVars& fvs, fuzz::int_expr t)
    {
        fuzz::int_expr fuzz = generators::fuzz_int_expr::placeholder(ctx, fvs);
        fuzz::int_expr tmp_zero = generators::zero::placeholder(ctx, fvs, fuzz);
        fuzz::int_expr is_zero = z3::operator==(tmp_zero, fuzz);
        fuzz::int_expr tmp_zero_return = generators::zero::placeholder(ctx, fvs, fuzz);
        fuzz::int_expr div_ts = relations::division::placeholder(ctx, fvs, tmp_zero, fuzz);
        return z3::ite(is_zero, tmp_zero_return, div_ts);
    }

} // namespace zero

namespace one {

    fuzz::int_expr
    get_one(z3::context& ctx, fuzz::FreeVars& fvs, fuzz::int_expr t)
    {
        return ctx.int_val(1);
    }

    fuzz::int_expr
    one_by_div(z3::context& ctx, fuzz::FreeVars& fvs, fuzz::int_expr t)
    {
        fuzz::int_expr iden_expr = relations::identity::placeholder(ctx, fvs, t);
        fuzz::int_expr tmp_zero = generators::zero::placeholder(ctx, fvs, t);
        fuzz::int_expr is_zero = generators::equal_int::placeholder(ctx, fvs, tmp_zero, t);
        fuzz::int_expr div_ts = relations::division::placeholder(ctx, fvs, t, iden_expr);
        return z3::ite(is_zero, generators::one::placeholder(ctx, fvs, t), div_ts);
    }

    fuzz::int_expr
    one_by_fuzz_div(z3::context& ctx, fuzz::FreeVars& fvs, fuzz::int_expr t)
    {
        fuzz::int_expr fuzz = generators::fuzz_int_expr::placeholder(ctx, fvs);
        fuzz::int_expr iden_fuzz = relations::identity::placeholder(ctx, fvs, fuzz);
        fuzz::int_expr tmp_zero = generators::zero::placeholder(ctx, fvs, fuzz);
        fuzz::int_expr is_zero = generators::equal_int::placeholder(ctx, fvs, tmp_zero, fuzz);
        fuzz::int_expr div_ts = relations::division::placeholder(ctx, fvs, fuzz, iden_fuzz);
        return z3::ite(is_zero, generators::one::placeholder(ctx, fvs, fuzz), div_ts);
    }

    //fuzz::int_expr
    //one_by_pw(CVC4::api::Solver& c, fuzz::FreeVars& fvs, fuzz::int_expr f)
    //{
        //fuzz::int_expr tmp_zero = zero::placeholder(c, f);
        //fuzz::int_expr is_zero = tmp_zero.eqTerm(f);
        //return is_zero.iteTerm(placeholder(c, f),
            //c.mkTerm(CVC4::api::POW, f, tmp_zero));
    //}

} // namespace one

namespace true_z3 {

    fuzz::bool_expr
    get_true(z3::context& ctx, fuzz::FreeVars& fvs, fuzz::bool_expr e)
    {
        return ctx.bool_val(true);
    }

    fuzz::bool_expr
    get_true_by_equal(z3::context& ctx, fuzz::FreeVars& fvs, fuzz::bool_expr e)
    {
        fuzz::bool_expr iden_expr = generators::iden_bool::placeholder(ctx, fvs, e);
        return z3::operator==(e, iden_expr);
    }

    fuzz::bool_expr
    get_true_by_not_false(z3::context& ctx, fuzz::FreeVars& fvs, fuzz::bool_expr e)
    {
        e = generators::iden_bool::placeholder(ctx, fvs, e);
        return z3::operator!(generators::false_z3::placeholder(ctx, fvs, e));
    }

    fuzz::bool_expr
    get_true_by_or_true(z3::context& ctx, fuzz::FreeVars& fvs, fuzz::bool_expr e)
    {
        e = generators::iden_bool::placeholder(ctx, fvs, e);
        fuzz::bool_expr true_expr = generators::true_z3::placeholder(ctx, fvs, e);
        return generators::or_z3::placeholder(ctx, fvs, true_expr, e);
    }

    fuzz::bool_expr
    get_true_by_or_true_fuzz(z3::context& ctx, fuzz::FreeVars& fvs, fuzz::bool_expr e)
    {
        fuzz::bool_expr true_expr = generators::true_z3::placeholder(ctx, fvs, e);
        fuzz::bool_expr fuzz_expr = generators::fuzz_bool_expr::placeholder(ctx, fvs);
        return generators::or_z3::placeholder(ctx, fvs, true_expr, e);
    }

    fuzz::bool_expr
    get_true_by_nxor(z3::context& ctx, fuzz::FreeVars& fvs, fuzz::bool_expr e)
    {
        fuzz::bool_expr iden_expr = generators::iden_bool::placeholder(ctx, fvs, e);
        return z3::operator!(z3::operator^(e, iden_expr));
    }

    fuzz::bool_expr
    get_true_by_nxor_fuzz(z3::context& ctx, fuzz::FreeVars& fvs, fuzz::bool_expr e)
    {
        fuzz::bool_expr fuzz_expr = generators::fuzz_bool_expr::placeholder(ctx, fvs);
        fuzz::bool_expr iden_expr = generators::iden_bool::placeholder(ctx, fvs, fuzz_expr);
        return z3::operator!(generators::xor_z3::placeholder(ctx, fvs, fuzz_expr, iden_expr));
    }

    fuzz::bool_expr
    get_true_by_lte_fuzz(z3::context& ctx, fuzz::FreeVars& fvs, fuzz::bool_expr e)
    {
        fuzz::int_expr fuzz_expr = generators::fuzz_int_expr::placeholder(ctx, fvs);
        fuzz::int_expr iden_expr = relations::identity::placeholder(ctx, fvs, fuzz_expr);
        return generators::leq::placeholder(ctx, fvs, fuzz_expr, iden_expr);
    }

    fuzz::bool_expr
    get_true_by_gte_fuzz(z3::context& ctx, fuzz::FreeVars& fvs, fuzz::bool_expr e)
    {
        fuzz::int_expr fuzz_expr = generators::fuzz_int_expr::placeholder(ctx, fvs);
        fuzz::int_expr iden_expr = relations::identity::placeholder(ctx, fvs, fuzz_expr);
        return generators::geq::placeholder(ctx, fvs, fuzz_expr, iden_expr);
    }

} // namespace true_z3

namespace false_z3 {

    fuzz::bool_expr
    get_false(z3::context& ctx, fuzz::FreeVars& fvs, fuzz::bool_expr e)
    {
        return ctx.bool_val(false);
    }

    fuzz::bool_expr
    get_false_by_equal(z3::context& ctx, fuzz::FreeVars& fvs, fuzz::bool_expr e)
    {
        fuzz::bool_expr iden_expr = generators::iden_bool::placeholder(ctx, fvs, e);
        return z3::operator!=(e, iden_expr);
    }

    fuzz::bool_expr
    get_false_by_not_true(z3::context& ctx, fuzz::FreeVars& fvs, fuzz::bool_expr e)
    {
        e = generators::iden_bool::placeholder(ctx, fvs, e);
        return z3::operator!(generators::true_z3::placeholder(ctx, fvs, e));
    }

    fuzz::bool_expr
    get_false_by_and_false(z3::context& ctx, fuzz::FreeVars& fvs, fuzz::bool_expr e)
    {
        e = generators::iden_bool::placeholder(ctx, fvs, e);
        fuzz::bool_expr false_expr = generators::false_z3::placeholder(ctx, fvs, e);
        return generators::and_z3::placeholder(ctx, fvs, false_expr, e);
    }

    fuzz::bool_expr
    get_false_by_and_false_fuzz(z3::context& ctx, fuzz::FreeVars& fvs, fuzz::bool_expr e)
    {
        fuzz::bool_expr false_expr = generators::false_z3::placeholder(ctx, fvs, e);
        fuzz::bool_expr fuzz_expr = generators::fuzz_bool_expr::placeholder(ctx, fvs);
        return generators::and_z3::placeholder(ctx, fvs, false_expr, e);
    }

    fuzz::bool_expr
    get_false_by_xor(z3::context& ctx, fuzz::FreeVars& fvs, fuzz::bool_expr e)
    {
        fuzz::bool_expr iden_expr = generators::iden_bool::placeholder(ctx, fvs, e);
        return generators::xor_z3::placeholder(ctx, fvs, e, iden_expr);
    }

    fuzz::bool_expr
    get_false_by_xor_fuzz(z3::context& ctx, fuzz::FreeVars& fvs, fuzz::bool_expr e)
    {
        fuzz::bool_expr fuzz_expr = generators::fuzz_bool_expr::placeholder(ctx, fvs);
        fuzz::bool_expr iden_expr = generators::iden_bool::placeholder(ctx, fvs, fuzz_expr);
        return generators::xor_z3::placeholder(ctx, fvs, fuzz_expr, iden_expr);
    }

    fuzz::bool_expr
    get_false_by_lt_fuzz(z3::context& ctx, fuzz::FreeVars& fvs, fuzz::bool_expr e)
    {
        fuzz::int_expr fuzz_expr = generators::fuzz_int_expr::placeholder(ctx, fvs);
        fuzz::int_expr iden_expr = relations::identity::placeholder(ctx, fvs, fuzz_expr);
        return generators::lt::placeholder(ctx, fvs, fuzz_expr, iden_expr);
    }

    fuzz::bool_expr
    get_false_by_gt_fuzz(z3::context& ctx, fuzz::FreeVars& fvs, fuzz::bool_expr e)
    {
        fuzz::int_expr fuzz_expr = generators::fuzz_int_expr::placeholder(ctx, fvs);
        fuzz::int_expr iden_expr = relations::identity::placeholder(ctx, fvs, fuzz_expr);
        return generators::gt::placeholder(ctx, fvs, fuzz_expr, iden_expr);
    }

} // namespace false_z3

namespace iden_bool {

    fuzz::bool_expr
    base_iden_bool(z3::context& ctx, fuzz::FreeVars& fvs, fuzz::bool_expr e)
    {
        return e;
    }

    fuzz::bool_expr
    iden_by_and(z3::context& ctx, fuzz::FreeVars& fvs, fuzz::bool_expr e)
    {
        e = generators::iden_bool::placeholder(ctx, fvs, e);
        fuzz::bool_expr true_expr = generators::true_z3::placeholder(ctx, fvs, e);
        return generators::and_z3::placeholder(ctx, fvs, e, true_expr);
    }

    fuzz::bool_expr
    iden_by_or(z3::context& ctx, fuzz::FreeVars& fvs, fuzz::bool_expr e)
    {
        e = generators::iden_bool::placeholder(ctx, fvs, e);
        fuzz::bool_expr false_expr = generators::false_z3::placeholder(ctx, fvs, e);
        return generators::or_z3::placeholder(ctx, fvs, e, false_expr);
    }

    fuzz::bool_expr
    iden_by_xor(z3::context& ctx, fuzz::FreeVars& fvs, fuzz::bool_expr e)
    {
        fuzz::bool_expr iden_expr = generators::iden_bool::placeholder(ctx, fvs, e);
        fuzz::bool_expr xor_once = generators::xor_z3::placeholder(ctx, fvs, iden_expr, iden_expr);
        return generators::xor_z3::placeholder(ctx, fvs, xor_once, iden_expr);
    }

    fuzz::bool_expr
    iden_by_simplify(z3::context& ctx, fuzz::FreeVars& fvs, fuzz::bool_expr e)
    {
        fuzz::bool_expr iden_expr = generators::iden_bool::placeholder(ctx, fvs, e);
        return iden_expr.simplify();
    }

} // namespace iden_bool

namespace not_z3 {

    fuzz::bool_expr
    base_not(z3::context& ctx, fuzz::FreeVars& fvs, fuzz::bool_expr e)
    {
        return z3::operator!(e);
    }

    fuzz::bool_expr
    not_by_truth_value(z3::context& ctx, fuzz::FreeVars& fvs, fuzz::bool_expr e)
    {
        fuzz::bool_expr false_expr = generators::false_z3::placeholder(ctx, fvs, e);
        fuzz::bool_expr true_expr = generators::true_z3::placeholder(ctx, fvs, e);
        return z3::ite(e, false_expr, true_expr);
    }

} // namespace not_z3

namespace and_z3 {

    fuzz::bool_expr
    base_and(z3::context& ctx, fuzz::FreeVars& fvs, fuzz::bool_expr e1, fuzz::bool_expr e2)
    {
        return z3::operator&&(e1, e2);
    }

    fuzz::bool_expr
    base_and2(z3::context& ctx, fuzz::FreeVars& fvs, fuzz::bool_expr e1, fuzz::bool_expr e2)
    {
        return z3::operator&(e1, e2);
    }

    fuzz::bool_expr
    and_comm(z3::context& ctx, fuzz::FreeVars& fvs, fuzz::bool_expr e1, fuzz::bool_expr e2)
    {
        return generators::and_z3::placeholder(ctx, fvs, e2, e1);
    }

    fuzz::bool_expr
    and_demorgan(z3::context& ctx, fuzz::FreeVars& fvs, fuzz::bool_expr e1, fuzz::bool_expr e2)
    {
        fuzz::bool_expr ne1 = z3::operator!(e1);
        fuzz::bool_expr ne2 = z3::operator!(e2);
        fuzz::bool_expr or_nes = generators::or_z3::placeholder(ctx, fvs, ne1, ne2);
        return generators::not_z3::placeholder(ctx, fvs, or_nes);
    }

} // namespace and_z3

namespace or_z3 {

    fuzz::bool_expr
    base_or(z3::context& ctx, fuzz::FreeVars& fvs, fuzz::bool_expr e1, fuzz::bool_expr e2)
    {
        return z3::operator||(e1, e2);
    }

    fuzz::bool_expr
    base_or2(z3::context& ctx, fuzz::FreeVars& fvs, fuzz::bool_expr e1, fuzz::bool_expr e2)
    {
        return z3::operator|(e1, e2);
    }

    fuzz::bool_expr
    or_comm(z3::context& ctx, fuzz::FreeVars& fvs, fuzz::bool_expr e1, fuzz::bool_expr e2)
    {
        return generators::or_z3::placeholder(ctx, fvs, e2, e1);
    }

    fuzz::bool_expr
    or_demorgan(z3::context& ctx, fuzz::FreeVars& fvs, fuzz::bool_expr e1, fuzz::bool_expr e2)
    {
        fuzz::bool_expr ne1 = z3::operator!(e1);
        fuzz::bool_expr ne2 = z3::operator!(e2);
        fuzz::bool_expr and_nes = generators::and_z3::placeholder(ctx, fvs, ne1, ne2);
        return generators::not_z3::placeholder(ctx, fvs, and_nes);
    }

} // namespace or_z3

namespace xor_z3 {

    fuzz::bool_expr
    base_xor(z3::context& ctx, fuzz::FreeVars& fvs, fuzz::bool_expr e1, fuzz::bool_expr e2)
    {
        return z3::operator^(e1, e2);
    }

    fuzz::bool_expr
    xor_comm(z3::context& ctx, fuzz::FreeVars& fvs, fuzz::bool_expr e1, fuzz::bool_expr e2)
    {
        return generators::xor_z3::placeholder(ctx, fvs, e2, e1);
    }

    fuzz::bool_expr
    xor_disjunct(z3::context& ctx, fuzz::FreeVars& fvs, fuzz::bool_expr e1, fuzz::bool_expr e2)
    {
        fuzz::bool_expr ne1 = z3::operator!(e1);
        fuzz::bool_expr ne2 = z3::operator!(e2);
        fuzz::bool_expr e1_and_ne2 = generators::and_z3::placeholder(ctx, fvs, e1, ne2);
        fuzz::bool_expr e2_and_ne1 = generators::and_z3::placeholder(ctx, fvs, e2, ne1);
        return generators::or_z3::placeholder(ctx, fvs, e1_and_ne2, e2_and_ne1);
    }

    fuzz::bool_expr
    xor_conjunct(z3::context& ctx, fuzz::FreeVars& fvs, fuzz::bool_expr e1, fuzz::bool_expr e2)
    {
        fuzz::bool_expr ne1 = z3::operator!(e1);
        fuzz::bool_expr ne2 = z3::operator!(e2);
        fuzz::bool_expr e1_or_e2 = generators::or_z3::placeholder(ctx, fvs, e1, e2);
        fuzz::bool_expr ne1_or_ne2 = generators::or_z3::placeholder(ctx, fvs, ne1, ne2);
        return generators::and_z3::placeholder(ctx, fvs, e1_or_e2, ne1_or_ne2);
    }

}

namespace equal_int {

    fuzz::bool_expr
    check_equal_by_call(z3::context& ctx, fuzz::FreeVars& fvs, fuzz::int_expr e1, fuzz::int_expr e2)
    {
        return z3::operator==(e1, e2);
    }

    fuzz::bool_expr
    check_equal_comm(z3::context& ctx, fuzz::FreeVars& fvs, fuzz::int_expr e1, fuzz::int_expr e2)
    {
        return generators::equal_int::placeholder(ctx, fvs, e2, e1);
    }

    fuzz::bool_expr
    check_equal_by_sub_is_zero(z3::context& ctx, fuzz::FreeVars& fvs, fuzz::int_expr e1, fuzz::int_expr e2)
    {
        fuzz::int_expr zero = generators::zero::placeholder(ctx, fvs, e1);
        fuzz::int_expr sub_ts = relations::sub::placeholder(ctx, fvs, e1, e2);
        return generators::equal_int::placeholder(ctx, fvs, zero, sub_ts);
    }

    fuzz::bool_expr
    check_equal_by_div_is_one(z3::context& ctx, fuzz::FreeVars& fvs, fuzz::int_expr e1, fuzz::int_expr e2)
    {
        fuzz::int_expr one = generators::one::placeholder(ctx, fvs, e1);
        fuzz::int_expr zero = generators::zero::placeholder(ctx, fvs, e2);
        fuzz::int_expr div_ts = relations::division::placeholder(ctx, fvs, e1, e2);
        return generators::equal_int::placeholder(ctx, fvs, one, div_ts);
    }

} // namespace equal_int

namespace lt {

    fuzz::bool_expr
    lt_base(z3::context& ctx, fuzz::FreeVars& fvs, fuzz::int_expr e1, fuzz::int_expr e2)
    {
        return z3::operator<(e1, e2);
    }

    fuzz::bool_expr
    not_geq_base(z3::context& ctx, fuzz::FreeVars& fvs, fuzz::int_expr e1, fuzz::int_expr e2)
    {
        fuzz::bool_expr geq_expr = generators::geq::placeholder(ctx, fvs, e1, e2);
        return generators::not_z3::placeholder(ctx, fvs, geq_expr);
    }

} // namespace lt

namespace gt {

    fuzz::bool_expr
    gt_base(z3::context& ctx, fuzz::FreeVars& fvs, fuzz::int_expr e1, fuzz::int_expr e2)
    {
        return z3::operator>(e1, e2);
    }

    fuzz::bool_expr
    not_geq_base(z3::context& ctx, fuzz::FreeVars& fvs, fuzz::int_expr e1, fuzz::int_expr e2)
    {
        fuzz::bool_expr leq_expr = generators::leq::placeholder(ctx, fvs, e1, e2);
        return generators::not_z3::placeholder(ctx, fvs, leq_expr);
    }

} // namespace gt

namespace leq {

    fuzz::bool_expr
    leq_base(z3::context& ctx, fuzz::FreeVars& fvs, fuzz::int_expr e1, fuzz::int_expr e2)
    {
        return z3::operator<=(e1, e2);
    }

    fuzz::bool_expr
    not_geq_base(z3::context& ctx, fuzz::FreeVars& fvs, fuzz::int_expr e1, fuzz::int_expr e2)
    {
        fuzz::bool_expr gt_expr = generators::gt::placeholder(ctx, fvs, e1, e2);
        return generators::not_z3::placeholder(ctx, fvs, gt_expr);
    }

} // namespace leq

namespace geq {

    fuzz::bool_expr
    geq_base(z3::context& ctx, fuzz::FreeVars& fvs, fuzz::int_expr e1, fuzz::int_expr e2)
    {
        return z3::operator>=(e1, e2);
    }

    fuzz::bool_expr
    not_geq_base(z3::context& ctx, fuzz::FreeVars& fvs, fuzz::int_expr e1, fuzz::int_expr e2)
    {
        fuzz::bool_expr lt_expr = generators::lt::placeholder(ctx, fvs, e1, e2);
        return generators::not_z3::placeholder(ctx, fvs, lt_expr);
    }

} // namespace geq

} //namespace generators

/*******************************************************************************
 * Relations
 ******************************************************************************/

namespace relations {

namespace identity {

    fuzz::int_expr
    base_iden(z3::context& ctx, fuzz::FreeVars& fvs, fuzz::int_expr e)
    {
        return e;
    }

    fuzz::int_expr
    add_zero(z3::context& ctx, fuzz::FreeVars& fvs, fuzz::int_expr e)
    {
        e = relations::identity::placeholder(ctx, fvs, e);
        fuzz::int_expr zero = generators::zero::placeholder(ctx, fvs, e);
        return relations::add::placeholder(ctx, fvs, e, zero);
    }

    fuzz::int_expr
    sub_zero(z3::context& ctx, fuzz::FreeVars& fvs, fuzz::int_expr e)
    {
        e = relations::identity::placeholder(ctx, fvs, e);
        fuzz::int_expr zero = generators::zero::placeholder(ctx, fvs, e);
        return relations::sub::placeholder(ctx, fvs, e, zero);
    }

    fuzz::int_expr
    mul_one(z3::context& ctx, fuzz::FreeVars& fvs, fuzz::int_expr e)
    {
        e = relations::identity::placeholder(ctx, fvs, e);
        fuzz::int_expr one = generators::one::placeholder(ctx, fvs, e);
        return relations::mul::placeholder(ctx, fvs, e, one);
    }

    fuzz::int_expr
    div_one(z3::context& ctx, fuzz::FreeVars& fvs, fuzz::int_expr e)
    {
        e = relations::identity::placeholder(ctx, fvs, e);
        fuzz::int_expr one = generators::one::placeholder(ctx, fvs, e);
        return relations::division::placeholder(ctx, fvs, e, one);
    }

    fuzz::int_expr
    double_negative(z3::context& ctx, fuzz::FreeVars& fvs, fuzz::int_expr e)
    {
        e = relations::identity::placeholder(ctx, fvs, e);
        fuzz::int_expr tmp_e = z3::operator-(e);
        tmp_e = relations::identity::placeholder(ctx, fvs, tmp_e);
        return z3::operator-(tmp_e);
    }

    fuzz::int_expr
    iden_by_abs(z3::context& ctx, fuzz::FreeVars& fvs, fuzz::int_expr e)
    {
        fuzz::int_expr iden_expr = relations::identity::placeholder(ctx, fvs, e);
        fuzz::int_expr abs_e = relations::abs_z3::placeholder(ctx, fvs, e);
        fuzz::bool_expr e_equal = generators::equal_int::placeholder(ctx, fvs, abs_e, e);
        return z3::ite(e_equal, abs_e, e);
    }

    fuzz::int_expr
    iden_min(z3::context& ctx, fuzz::FreeVars& fvs, fuzz::int_expr e)
    {

        fuzz::int_expr iden_expr = relations::identity::placeholder(ctx, fvs, e);
        return z3::min(e, iden_expr);
    }

    fuzz::int_expr
    iden_max(z3::context& ctx, fuzz::FreeVars& fvs, fuzz::int_expr e)
    {
        fuzz::int_expr iden_expr = relations::identity::placeholder(ctx, fvs, e);
        return z3::max(e, iden_expr);
    }

    fuzz::int_expr
    iden_max_with_zero(z3::context& ctx, fuzz::FreeVars& fvs, fuzz::int_expr e)
    {
        fuzz::int_expr one = generators::one::placeholder(ctx, fvs, e);
        fuzz::int_expr one_sgn = z3::ite(e >= 0, one, -one);
        fuzz::int_expr abs_e = relations::abs_z3::placeholder(ctx, fvs, e);
        fuzz::int_expr zero = generators::zero::placeholder(ctx, fvs, e);
        return one_sgn * z3::max(abs_e, zero);
    }

    fuzz::int_expr
    iden_by_ite_false(z3::context& ctx, fuzz::FreeVars& fvs, fuzz::int_expr e)
    {
        fuzz::bool_expr fuzz_expr = generators::fuzz_bool_expr::placeholder(ctx, fvs);
        fuzz::int_expr dead = generators::fuzz_int_expr::placeholder(ctx, fvs);
        e = relations::identity::placeholder(ctx, fvs, e);
        return z3::ite(generators::false_z3::placeholder(ctx, fvs, fuzz_expr), dead, e);
    }

    fuzz::int_expr
    iden_by_ite_true(z3::context& ctx, fuzz::FreeVars& fvs, fuzz::int_expr e)
    {
        fuzz::bool_expr fuzz_expr = generators::fuzz_bool_expr::placeholder(ctx, fvs);
        fuzz::int_expr dead = generators::fuzz_int_expr::placeholder(ctx, fvs);
        e = relations::identity::placeholder(ctx, fvs, e);
        return z3::ite(generators::true_z3::placeholder(ctx, fvs, fuzz_expr), e, dead);
    }

    fuzz::int_expr
    iden_simplify(z3::context& ctx, fuzz::FreeVars& fvs, fuzz::int_expr e)
    {
        fuzz::int_expr iden_expr = relations::identity::placeholder(ctx, fvs, e);
        return iden_expr.simplify();
    }

    //fuzz::int_expr
    //identity_by_mul(z3::context& ctx, fuzz::FreeVars& fvs, fuzz::int_expr e1)
    //{
        //e2 = fuzz::new<fuzz::int_expr>();
        //return e1 * e2 - e1 * (e2 - generators::one::placeholder(e1.ctx()));
    //}

} // namespace identity

namespace add {

    fuzz::int_expr
    base_add(z3::context& ctx, fuzz::FreeVars& fvs, fuzz::int_expr e1, fuzz::int_expr e2)
    {
        return z3::operator+(e1, e2);
    }

    fuzz::int_expr
    add_commute(z3::context& ctx, fuzz::FreeVars& fvs, fuzz::int_expr e1, fuzz::int_expr e2)
    {
        e1 = relations::identity::placeholder(ctx, fvs, e1);
        e2 = relations::identity::placeholder(ctx, fvs, e2);
        return relations::add::placeholder(ctx, fvs, e2, e1);
    }

    fuzz::int_expr
    add_by_sub(z3::context& ctx, fuzz::FreeVars& fvs, fuzz::int_expr e1, fuzz::int_expr e2)
    {
        e1 = relations::identity::placeholder(ctx, fvs, e1);
        e2 = relations::identity::placeholder(ctx, fvs, e2);
        return relations::sub::placeholder(ctx, fvs, e1, z3::operator-(e2));
    }

} // namespace add

namespace sub {

    fuzz::int_expr
    base_sub(z3::context& ctx, fuzz::FreeVars& fvs, fuzz::int_expr e1, fuzz::int_expr e2)
    {
        return z3::operator-(e1, e2);
    }

    fuzz::int_expr
    sub_by_add(z3::context& ctx, fuzz::FreeVars& fvs, fuzz::int_expr e1, fuzz::int_expr e2)
    {
        e1 = relations::identity::placeholder(ctx, fvs, e1);
        e2 = relations::identity::placeholder(ctx, fvs, e2);
        return relations::add::placeholder(ctx, fvs, e1, z3::operator-(e2));
    }

} // namespace sub

namespace mul {

    fuzz::int_expr
    base_mul(z3::context& ctx, fuzz::FreeVars& fvs, fuzz::int_expr e1, fuzz::int_expr e2)
    {
        return z3::operator*(e1, e2);
    }

    fuzz::int_expr
    mul_commute(z3::context& ctx, fuzz::FreeVars& fvs, fuzz::int_expr e1, fuzz::int_expr e2)
    {
        e1 = relations::identity::placeholder(ctx, fvs, e1);
        e2 = relations::identity::placeholder(ctx, fvs, e2);
        return relations::mul::placeholder(ctx, fvs, e2, e1);
    }

    /*
    fuzz::int_expr
    mul_by_add(fuzz::int_expr e1, fuzz::int_expr e2)
    {
        fuzz::int_expr mul = generators::zero::placeholder(e1.ctx(), e1);
        for (int i = 0; (i < z3::abs(e2)).simplify().is_true(); ++i)
        {
            fuzz::int_expr e1_iden = identity::placeholder(e1.ctx(), e1);
            mul = add::placeholder(mul, z3::ite(e2 >= 0, e1_iden, -e1_iden));
        }
        return mul;
    }
    */

} // namespace multiply

namespace division {

    fuzz::int_expr
    div_base(z3::context& ctx, fuzz::FreeVars& fvs, fuzz::int_expr t1, fuzz::int_expr t2)
    {
        return z3::ite(z3::operator==(t2, 0), t1, z3::operator/(t1, t2));
    }

} // namespace division

namespace modulo
{

    fuzz::int_expr
    base_modulo(z3::context& ctx, fuzz::FreeVars& fvs, fuzz::int_expr e1, fuzz::int_expr e2)
    {
        return z3::ite(z3::operator==(e2, 0), e1, z3::mod(e1, e2));
    }

    fuzz::int_expr
    mod_with_rem(z3::context& ctx, fuzz::FreeVars& fvs, fuzz::int_expr e1, fuzz::int_expr e2)
    {
        return z3::ite(z3::operator==(e2, 0), e1, z3::abs(z3::rem(e1, e2)));
    }

    fuzz::int_expr
    mod_by_sub(z3::context& ctx, fuzz::FreeVars& fvs, fuzz::int_expr e1, fuzz::int_expr e2)
    {
        e1 = relations::identity::placeholder(ctx, fvs, e1);
        e2 = relations::identity::placeholder(ctx, fvs, e2);
        fuzz::int_expr zero = generators::zero::placeholder(ctx, fvs, e1);
        return z3::ite(z3::operator==(e2, zero), e1,
            z3::operator-(e1, z3::operator*(e2, z3::operator/(e1, e2))));
    }

} // namespace modulo

namespace abs_z3 {

    fuzz::int_expr
    abs_base(z3::context& ctx, fuzz::FreeVars& fvs, fuzz::int_expr e)
    {
        return z3::abs(e);
    }

    fuzz::int_expr
    abs_by_check_gt_zero(z3::context& ctx, fuzz::FreeVars& fvs, fuzz::int_expr e)
    {
        fuzz::int_expr zero = generators::zero::placeholder(ctx, fvs, e);
        fuzz::bool_expr gt_expr = generators::gt::placeholder(ctx, fvs, e, zero);
        fuzz::int_expr abs_e = relations::abs_z3::placeholder(ctx, fvs, e);
        return z3::ite(gt_expr, e, abs_e);
    }

    fuzz::int_expr
    abs_by_check_lt_zero(z3::context& ctx, fuzz::FreeVars& fvs, fuzz::int_expr e)
    {
        fuzz::int_expr zero = generators::zero::placeholder(ctx, fvs, e);
        fuzz::bool_expr lt_expr = generators::lt::placeholder(ctx, fvs, e, zero);
        fuzz::int_expr abs_e = relations::abs_z3::placeholder(ctx, fvs, e);
        return z3::ite(lt_expr, abs_e, e);
    }

} // namespace abs_z3

} // namespace relations

} // namespace metalib
