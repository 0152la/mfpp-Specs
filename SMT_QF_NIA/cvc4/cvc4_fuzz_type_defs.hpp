namespace fuzz
{
    typedef CVC4::api::Term bool_term;
    typedef CVC4::api::Term int_term;
    class FreeVars {
      public:
        fuzz::int_term vars[FV_COUNT];
    };

    class fuzz_context
    {
        public:
            CVC4::api::Solver& slv;
            fuzz::FreeVars& fvs;

            fuzz_context(CVC4::api::Solver& _slv, fuzz::FreeVars& _fvs) :
                slv(_slv), fvs(_fvs) {} ;

            CVC4::api::Term simplify(CVC4::api::Term& t)
            {
                return this->slv.simplify(t);
            }
    };
} // namespace fuzz

