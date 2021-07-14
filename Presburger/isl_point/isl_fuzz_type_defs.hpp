namespace fuzz {
    typedef isl::set set_term;

    class fuzz_context
    {
        public:
            isl::ctx& ctx;
            isl::space& space;

            fuzz_context(isl::ctx& _ctx, isl::space& _space) :
                ctx(_ctx), space(_space) {};
    };

} // namespace fuzz
