namespace metalib {

namespace checks {

    void
    check_expr_same_sat(z3::context& c, fuzz::int_term e1, fuzz::int_term e2)
    {
        z3::solver solver(c);
        z3::expr conjecture = z3::operator==(e1, e2);
        solver.add(!conjecture);
        assert(solver.check() != z3::sat);
        assert(c.check_error() == Z3_OK);
    }

    void
    check_exprs_are_zero(z3::context& c, fuzz::FreeVars& fvs, fuzz::int_term e1, fuzz::int_term e2)
    {
        z3::solver solver(c);
        solver.push();
        solver.add(z3::operator==(e1, 0));
        z3::check_result result_1 = solver.check();
        assert(c.check_error() == Z3_OK);
        z3::model mdl_1(c);
        if (result_1 == z3::sat)
        {
            mdl_1 = solver.get_model();
            for (fuzz::int_term e : fvs.vars)
            {
                z3::func_decl cnst_decl = e.decl();
                if (!mdl_1.has_interp(cnst_decl))
                {
                    z3::expr zero_val = c.int_val(0);
                    mdl_1.add_const_interp(cnst_decl, zero_val);
                }
            }
        }
        solver.pop();
        solver.push();
        solver.add(z3::operator==(e2, 0));
        z3::check_result result_2 = solver.check();
        assert(c.check_error() == Z3_OK);
        z3::model mdl_2(c);
        if (result_2 == z3::sat)
        {
            mdl_2 = solver.get_model();
            for (fuzz::int_term e : fvs.vars)
            {
                z3::func_decl cnst_decl = e.decl();
                if (!mdl_2.has_interp(cnst_decl))
                {
                    z3::expr zero_val = c.int_val(0);
                    mdl_2.add_const_interp(cnst_decl, zero_val);
                }
            }
        }
        solver.pop();
        if (result_1 == z3::sat)
        {
            assert(result_2 != z3::unsat);
        }
        if (result_2 == z3::sat)
        {
            assert(result_1 != z3::unsat);
        }
        if (result_1 == z3::sat && result_2 == z3::sat)
        {
            assert(mdl_1.eval(z3::operator==(e2, 0)).bool_value() == Z3_L_TRUE);
            assert(mdl_2.eval(z3::operator==(e1, 0)).bool_value() == Z3_L_TRUE);
        }
        assert(c.check_error() == Z3_OK);
    }

}

namespace generators {
    namespace zero {
        fuzz::int_term base(fuzz::fuzz_context ctx, fuzz::int_term t) {
            return ctx.ctx.int_val(0); }
    }
    namespace one {
        fuzz::int_term base(fuzz::fuzz_context ctx, fuzz::int_term t) {
            return ctx.ctx.int_val(1); }
    }
    namespace true_expr {
        fuzz::bool_term base(fuzz::fuzz_context ctx, fuzz::bool_term t) {
            return ctx.ctx.bool_val(true); }
    }
    namespace false_expr {
        fuzz::bool_term base(fuzz::fuzz_context ctx, fuzz::bool_term t) {
            return ctx.ctx.bool_val(false); }
    }
    namespace iden_bool {
        fuzz::bool_term base(fuzz::fuzz_context ctx, fuzz::bool_term t) {
            return t; }
        fuzz::bool_term iden_by_simplify(fuzz::fuzz_context fctx, fuzz::bool_term t) {
            return t.simplify(); }
    }
    namespace not_expr {
        fuzz::bool_term base(fuzz::fuzz_context ctx, fuzz::bool_term t) {
            return z3::operator!(t); }
    }
    namespace and_expr {
        fuzz::bool_term base(fuzz::fuzz_context ctx, fuzz::bool_term t1, fuzz::bool_term t2) {
            return z3::operator&&(t1, t2); }
    }
    namespace or_expr {
        fuzz::bool_term base(fuzz::fuzz_context ctx, fuzz::bool_term t1, fuzz::bool_term t2) {
            return z3::operator||(t1, t2); }
    }
    namespace xor_expr {
        fuzz::bool_term base(fuzz::fuzz_context ctx, fuzz::bool_term t1, fuzz::bool_term t2) {
            return z3::operator^(t1, t2); }
    }
    namespace equal_bool {
        fuzz::bool_term base(fuzz::fuzz_context ctx, fuzz::bool_term t1, fuzz::bool_term t2) {
            return z3::operator==(t1, t2); }
    }
    namespace equal_int {
        fuzz::bool_term base(fuzz::fuzz_context ctx, fuzz::int_term t1, fuzz::int_term t2) {
            return z3::operator==(t1, t2); }
    }
    namespace ite_integer_term_cond {
        fuzz::int_term base(fuzz::fuzz_context ctx, fuzz::bool_term b, fuzz::int_term t, fuzz::int_term e) {
            return z3::ite(b, t, e); }
    }
    namespace lt {
        fuzz::bool_term base(fuzz::fuzz_context ctx, fuzz::int_term t1, fuzz::int_term t2) {
            return z3::operator<(t1, t2); }
    }
    namespace gt {
        fuzz::bool_term base(fuzz::fuzz_context ctx, fuzz::int_term t1, fuzz::int_term t2) {
            return z3::operator>(t1, t2); }
    }
    namespace leq {
        fuzz::bool_term base(fuzz::fuzz_context ctx, fuzz::int_term t1, fuzz::int_term t2) {
            return z3::operator<=(t1, t2); }
    }
    namespace geq {
        fuzz::bool_term base(fuzz::fuzz_context ctx, fuzz::int_term t1, fuzz::int_term t2) {
            return z3::operator>=(t1, t2); }
    }
    namespace ite_bool {
        fuzz::bool_term base(fuzz::fuzz_context ctx, fuzz::bool_term c, fuzz::bool_term t, fuzz::bool_term e) {
            return z3::ite(c, t, e); }
    }
} // namespace generators

namespace relations {
    namespace identity {
        fuzz::int_term base(fuzz::fuzz_context ctx, fuzz::int_term t) {
            return t; }
        fuzz::int_term iden_by_simplify(fuzz::fuzz_context fctx, fuzz::int_term t) {
            return t.simplify(); }
    }
    namespace add {
        fuzz::int_term base(fuzz::fuzz_context ctx, fuzz::int_term t1, fuzz::int_term t2) {
            return z3::operator+(t1, t2); }
    }
    namespace sub {
        fuzz::int_term base(fuzz::fuzz_context ctx, fuzz::int_term t1, fuzz::int_term t2) {
            return z3::operator-(t1, t2); }
    }
    namespace mul {
        fuzz::int_term base(fuzz::fuzz_context ctx, fuzz::int_term t1, fuzz::int_term t2) {
            return z3::operator*(t1, t2); }
    }
    namespace division {
        fuzz::int_term base(fuzz::fuzz_context ctx, fuzz::int_term t1, fuzz::int_term t2) {
            return z3::ite(z3::operator==(t2, ctx.ctx.int_val(0)), t1, z3::operator/(t1, t2)); }
    }
    namespace modulo {
        fuzz::int_term base(fuzz::fuzz_context ctx, fuzz::int_term t1, fuzz::int_term t2) {
            return z3::ite(z3::operator==(t2, ctx.ctx.int_val(0)), t1, z3::mod(t1, t2)); }
    }
    namespace abs_expr {
        fuzz::int_term base(fuzz::fuzz_context ctx, fuzz::int_term t) {
            return z3::abs(t); }
    }
    namespace neg {
        fuzz::int_term base(fuzz::fuzz_context ctx, fuzz::int_term t) {
            return z3::operator-(t); }
    }
    namespace ite_integer {
        fuzz::int_term base(fuzz::fuzz_context ctx, bool b, fuzz::int_term t, fuzz::int_term e) {
            return z3::ite(ctx.ctx.bool_val(b), t, e); }
    }

} // namespace relations

#ifndef EXECUTE

namespace generators {

namespace iden_bool {


} // namespace iden_bool

} // namespace generators

namespace relations {

namespace identity {

}

} // namespace relations

#endif

} // namespace metalib

