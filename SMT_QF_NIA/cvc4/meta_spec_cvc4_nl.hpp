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

namespace generators {
    namespace zero {
        fuzz::int_term base(fuzz::fuzz_context ctx, fuzz::int_term t) {
            return ctx.slv.mkInteger(0); }
    }
    namespace one {
        fuzz::int_term base(fuzz::fuzz_context ctx, fuzz::int_term t) {
            return ctx.slv.mkInteger(1); }
    }
    namespace true_expr {
        fuzz::bool_term base(fuzz::fuzz_context ctx, fuzz::bool_term t) {
            return ctx.slv.mkTrue(); }
    }
    namespace false_expr {
        fuzz::bool_term base(fuzz::fuzz_context ctx, fuzz::bool_term t) {
            return ctx.slv.mkFalse(); }
    }
    namespace iden_bool {
        fuzz::bool_term base(fuzz::fuzz_context ctx, fuzz::bool_term t) {
            return t; }
        fuzz::bool_term iden_by_simplify(fuzz::fuzz_context ctx, fuzz::bool_term t) {
            return ctx.slv.simplify(t); }
    }
    namespace not_expr {
        fuzz::bool_term base(fuzz::fuzz_context ctx, fuzz::bool_term t) {
            return ctx.slv.mkTerm(CVC4::api::Kind::NOT, t); }
    }
    namespace and_expr {
        fuzz::bool_term base(fuzz::fuzz_context ctx, fuzz::bool_term t1, fuzz::bool_term t2) {
            return ctx.slv.mkTerm(CVC4::api::Kind::AND, t1, t2); }
    }
    namespace or_expr {
        fuzz::bool_term base(fuzz::fuzz_context ctx, fuzz::bool_term t1, fuzz::bool_term t2) {
            return ctx.slv.mkTerm(CVC4::api::Kind::OR, t1, t2); }
    }
    namespace xor_expr {
        fuzz::bool_term base(fuzz::fuzz_context ctx, fuzz::bool_term t1, fuzz::bool_term t2) {
            return ctx.slv.mkTerm(CVC4::api::Kind::XOR, t1, t2); }
    }
    namespace equal_bool {
        fuzz::bool_term base(fuzz::fuzz_context ctx, fuzz::bool_term t1, fuzz::bool_term t2) {
            return ctx.slv.mkTerm(CVC4::api::Kind::EQUAL, t1, t2); }
    }
    namespace equal_int {
        fuzz::bool_term base(fuzz::fuzz_context ctx, fuzz::int_term t1, fuzz::int_term t2) {
            return ctx.slv.mkTerm(CVC4::api::Kind::EQUAL, t1, t2); }
    }
    namespace ite_integer_term_cond {
        fuzz::int_term base(fuzz::fuzz_context ctx, fuzz::bool_term b, fuzz::int_term t, fuzz::int_term e) {
            return ctx.slv.mkTerm(CVC4::api::Kind::ITE, b, t, e); }
    }
    namespace lt {
        fuzz::bool_term base(fuzz::fuzz_context ctx, fuzz::int_term t1, fuzz::int_term t2) {
            return ctx.slv.mkTerm(CVC4::api::Kind::LT, t1, t2); }
    }
    namespace gt {
        fuzz::bool_term base(fuzz::fuzz_context ctx, fuzz::int_term t1, fuzz::int_term t2) {
            return ctx.slv.mkTerm(CVC4::api::Kind::GT, t1, t2); }
    }
    namespace leq {
        fuzz::bool_term base(fuzz::fuzz_context ctx, fuzz::int_term t1, fuzz::int_term t2) {
            return ctx.slv.mkTerm(CVC4::api::Kind::LEQ, t1, t2); }
    }
    namespace geq {
        fuzz::bool_term base(fuzz::fuzz_context ctx, fuzz::int_term t1, fuzz::int_term t2) {
            return ctx.slv.mkTerm(CVC4::api::Kind::GEQ, t1, t2); }
    }
    namespace ite_bool {
        fuzz::bool_term base(fuzz::fuzz_context ctx, fuzz::bool_term c, fuzz::bool_term t, fuzz::bool_term e) {
            return ctx.slv.mkTerm(CVC4::api::Kind::ITE, c, t, e); }
    }
    // Second class non-linear operations to control parameters (if called
    // appropriately, ensures that it won't be the case that both operands
    // contain free variables
    namespace mul {
        fuzz::int_term base(fuzz::fuzz_context ctx, fuzz::int_term t1, fuzz::int_term t2) {
            return ctx.slv.mkTerm(CVC4::api::Kind::MULT, t1, t2); }
    }
    namespace division {
        fuzz::int_term base(fuzz::fuzz_context ctx, fuzz::int_term t1, fuzz::int_term t2) {
            CVC4::api::Solver& slv = ctx.slv;
            return slv.mkTerm(CVC4::api::Kind::ITE,
                slv.mkTerm(CVC4::api::Kind::EQUAL, t2, slv.mkInteger(0)),
                t1, slv.mkTerm(CVC4::api::INTS_DIVISION, t1, t2)); }
    }
    namespace modulo {
        fuzz::int_term base(fuzz::fuzz_context ctx, fuzz::int_term t1, fuzz::int_term t2) {
            CVC4::api::Solver& slv = ctx.slv;
            return slv.mkTerm(CVC4::api::ITE,
                slv.mkTerm(CVC4::api::EQUAL, t2, slv.mkInteger(0)), t1,
                slv.mkTerm(CVC4::api::INTS_MODULUS, t1, t2)); }
    }
} // namespace generators

namespace relations {
    namespace identity {
        fuzz::int_term base(fuzz::fuzz_context ctx, fuzz::int_term t) {
            return t; }
        fuzz::int_term iden_by_simplify(fuzz::fuzz_context ctx, fuzz::int_term t) {
            return ctx.slv.simplify(t); }
    }
    namespace add {
        fuzz::int_term base(fuzz::fuzz_context ctx, fuzz::int_term t1, fuzz::int_term t2) {
            return ctx.slv.mkTerm(CVC4::api::Kind::PLUS, t1, t2); }
    }
    namespace sub {
        fuzz::int_term base(fuzz::fuzz_context ctx, fuzz::int_term t1, fuzz::int_term t2) {
            return ctx.slv.mkTerm(CVC4::api::Kind::MINUS, t1, t2); }
    }
    namespace abs_expr {
        fuzz::int_term base(fuzz::fuzz_context ctx, fuzz::int_term t) {
            return ctx.slv.mkTerm(CVC4::api::Kind::ABS, t); }
    }
    namespace neg {
        fuzz::int_term base(fuzz::fuzz_context ctx, fuzz::int_term t) {
            return ctx.slv.mkTerm(CVC4::api::Kind::UMINUS, t); }
    }
    namespace ite_integer {
        fuzz::int_term base(fuzz::fuzz_context ctx, bool b, fuzz::int_term t, fuzz::int_term e) {
            return ctx.slv.mkTerm(CVC4::api::Kind::ITE, ctx.slv.mkBoolean(b), t, e); }
    }

} // namespace relations

} // namespace metalib
