namespace fuzz
{
    typedef term_t bool_term;
    typedef term_t int_term;
    class FreeVars {
        public:
            fuzz::int_term vars[FV_COUNT];
    };

    class fuzz_context
    {
        public:
            fuzz::FreeVars& fvs;

            fuzz_context(fuzz::FreeVars& _fvs) : fvs(_fvs) {} ;

            term_t simplify(term_t t)
            {
                return t;
            }
    };
}
