namespace metalib {

namespace checks {

    void
    check_is_equal(fuzz::set_term s1, fuzz::set_term s2)
    {
        assert(s1.is_equal(s2));
    }

} // namespace checks

namespace generators {
    namespace universe {
        fuzz::set_term base(fuzz::fuzz_context fctx, fuzz::set_term s) {
            return isl::set::universe(fctx.space); }
    }
    namespace empty {
        fuzz::set_term base(fuzz::fuzz_context fctx, fuzz::set_term s) {
            return isl::set::empty(fctx.space); }
    }
} // namespace generators

namespace relations {
    namespace identity {
        fuzz::set_term base(fuzz::fuzz_context fctx, fuzz::set_term s) {
            return s; }
        fuzz::set_term iden_by_coalesce(fuzz::fuzz_context fctx, fuzz::set_term s) {
            return s.coalesce(); }
        fuzz::set_term iden_by_detect_equalities(fuzz::fuzz_context fctx, fuzz::set_term s) {
            return s.detect_equalities(); }
    }
    namespace complement {
        fuzz::set_term base(fuzz::fuzz_context fctx, fuzz::set_term s) {
            return s.complement();
        }
    }
    namespace subtract {
        fuzz::set_term base(fuzz::fuzz_context fctx, fuzz::set_term s1, fuzz::set_term s2) {
            return s1.subtract(s2); }
    }
    namespace unite {
        fuzz::set_term base(fuzz::fuzz_context fctx, fuzz::set_term s1, fuzz::set_term s2) {
            return s1.unite(s2); }
    }
    namespace intersect {
        fuzz::set_term base(fuzz::fuzz_context fctx, fuzz::set_term s1, fuzz::set_term s2) {
            return s1.intersect(s2); }
    }
    namespace unite_assoc {
        fuzz::set_term base_front(fuzz::fuzz_context fctx, fuzz::set_term s1, fuzz::set_term s2, fuzz::set_term s3) {
            return (s1.unite(s2)).unite(s3); }
    }
    namespace intersect_assoc {
        fuzz::set_term base_front(fuzz::fuzz_context fctx, fuzz::set_term s1, fuzz::set_term s2, fuzz::set_term s3) {
            return (s1.intersect(s2)).intersect(s3); }
    }
} // namespace relations

} // namespace metalib
