namespace fuzz
{
    class FreeVars {
        public:
            fuzz::bv_term vars[FV_COUNT];
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
} // namespace fuzz
