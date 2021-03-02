namespace fuzz {
    class fuzz_context
    {
        public:
            z3::context& ctx;
            fuzz::FreeVars& fvs;

            fuzz_context(z3::context& _ctx, fuzz::FreeVars& _fvs) :
                ctx(_ctx), fvs(_fvs) {} ;
    };
} // namespace fuzz

namespace metalib {
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
    }
    namespace not_expr {
        fuzz::bool_term base(fuzz::fuzz_context ctx, fuzz::bool_term t) {
            return z3::operator-(t); }
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
} // namespace generators

namespace relations {
    namespace identity {
        fuzz::int_term base(fuzz::fuzz_context ctx, fuzz::int_term t) {
            return t; }
    }
    namespace add {
        fuzz::int_term base(fuzz::fuzz_context ctx, fuzz::int_term t1, fuzz::int_term t2) {
            return z3::operator+(t1, t2); }
    }
    namespace sub {
        fuzz::int_term base(fuzz::fuzz_context ctx, fuzz::int_term t1, fuzz::int_term t2) {
            return z3::operator-(t1, t2); }
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

} // namespace metalib

