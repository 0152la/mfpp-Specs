namespace fuzz {
    class fuzz_context
    {
        public:
            CVC4::api::Solver& slv;
            fuzz::FreeVars& fvs;

            fuzz_context(CVC4::api::Solver& _slv, fuzz::FreeVars& _fvs) :
                slv(_slv), fvs(_fvs) {} ;
    };
} // namespace fuzz

namespace metalib {
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
