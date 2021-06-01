namespace fuzz {
    typedef z3::expr bool_term;
    typedef z3::expr int_term;

    class FreeVars {
      public:
        std::vector<int_term> vars;
    };

    class fuzz_context
    {
        public:
            z3::context& ctx;
            fuzz::FreeVars& fvs;

            fuzz_context(z3::context& _ctx, fuzz::FreeVars& _fvs) :
                ctx(_ctx), fvs(_fvs) {} ;
    };

} // namespace fuzz
