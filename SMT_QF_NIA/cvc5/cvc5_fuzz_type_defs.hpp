namespace fuzz
{
    typedef cvc5::api::Term bool_term;
    typedef cvc5::api::Term int_term;
    class FreeVars {
      public:
        fuzz::int_term vars[FV_COUNT];
    };

    class fuzz_context
    {
        public:
            cvc5::api::Solver& slv;
            fuzz::FreeVars& fvs;

            fuzz_context(cvc5::api::Solver& _slv, fuzz::FreeVars& _fvs) :
                slv(_slv), fvs(_fvs) {} ;

            cvc5::api::Term simplify(cvc5::api::Term& t)
            {
                return this->slv.simplify(t);
            }
    };
} // namespace fuzz

