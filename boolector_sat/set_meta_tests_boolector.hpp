namespace metalib {

namespace checks {

    void
    check_sat_expr_maintained(Btor* ctx, mr_pair p, sat_stat& stat)
    {
        BoolectorNode* check = boolector_slt(ctx, p.first, p.second);
        boolector_assert(ctx, check);
        assert(boolector_sat(ctx) == stat);
        //if (stat == BOOLECTOR_SAT)
        //{
            //assert(yices_formula_true_in_model(mdl, check));
        //}
    }

} // namespace checks

namespace generators {

namespace fuzz_gen {

    BoolectorNode* placeholder(Btor*, BoolectorNode*);

    BoolectorNode*
    fuzz_term(Btor* ctx, BoolectorNode* t)
    {
        return fuzz::fuzz_new<BoolectorNode*>();
    }

} // namespace fuzz_gen

namespace zero {

    BoolectorNode* placeholder(Btor*, BoolectorNode*);

    BoolectorNode*
    get_zero(Btor* ctx, BoolectorNode* n)
    {
        return boolector_int(ctx, 0, boolector_bitvec_sort(ctx, BV_SIZE));
    }

    BoolectorNode*
    get_zero_by_call(Btor* ctx, BoolectorNode* n)
    {
        return boolector_zero(ctx, boolector_bitvec_sort(ctx, BV_SIZE));
    }

    BoolectorNode*
    get_zero_by_sub(Btor* ctx, BoolectorNode* t)
    {
        return boolector_sub(ctx, t, t);
    }

    BoolectorNode*
    get_zero_by_fuzz_sub(Btor* ctx, BoolectorNode* t)
    {
        BoolectorNode* t_fuzz = generators::fuzz_gen::placeholder(ctx, t);
        return boolector_sub(ctx, t_fuzz, t_fuzz);
    }

    BoolectorNode*
    get_zero_by_mul(Btor* ctx, BoolectorNode* t)
    {
        return boolector_mul(ctx, t, generators::zero::placeholder(ctx, t));
    }

    BoolectorNode*
    get_zero_by_xor(Btor* ctx, BoolectorNode* t)
    {
        return boolector_xor(ctx, t, t);
    }

    BoolectorNode*
    get_zero_by_shiftl(Btor* ctx, BoolectorNode* t)
    {
        return boolector_sll(ctx, t, boolector_int(ctx, BV_SIZE,
            boolector_bitvec_sort(ctx, BV_SIZE)));
    }

    BoolectorNode*
    get_zero_by_shiftr(Btor* ctx, BoolectorNode* t)
    {
        return boolector_srl(ctx, t, boolector_int(ctx, BV_SIZE,
            boolector_bitvec_sort(ctx, BV_SIZE)));
    }

} // namespace zero

namespace one {

    BoolectorNode* placeholder(Btor*, BoolectorNode*);

    BoolectorNode*
    get_one(Btor* ctx, BoolectorNode* n)
    {
        return boolector_int(ctx, 1, boolector_bitvec_sort(ctx, BV_SIZE));
    }

    BoolectorNode*
    get_one_by_call(Btor* ctx, BoolectorNode* n)
    {
        return boolector_one(ctx, boolector_bitvec_sort(ctx, BV_SIZE));
    }

    BoolectorNode*
    get_one_by_div(Btor* ctx, BoolectorNode* t)
    {
        return boolector_cond(ctx,
            boolector_ne(ctx, t, generators::zero::placeholder(ctx, t)),
            boolector_sdiv(ctx, t, t), generators::one::placeholder(ctx, t));
    }

    BoolectorNode*
    get_one_by_div_fuzz(Btor* ctx, BoolectorNode* t)
    {
        BoolectorNode* fuzz = generators::fuzz_gen::placeholder(ctx, t);
        return boolector_cond(ctx,
            boolector_ne(ctx, fuzz, generators::zero::placeholder(ctx, fuzz)),
            boolector_sdiv(ctx, fuzz, fuzz), generators::one::placeholder(ctx, fuzz));
    }

    //BoolectorNode*
    //get_one_by_pw(Btor* ctx, BoolectorNode* t)
    //{
        //BoolectorNode* zero = generators::zero::placeholder(ctx, t);
        //return boolector_cond(
            //boolector_ne(ctx, t, zero), yices_bvpower(t, 0),
            //generators::one::placeholder(ctx, t));
    //}

    //BoolectorNode*
    //get_one_by_shiftl(Btor* ctx, BoolectorNode* t)
    //{
        //return yices_bvneg(yices_shift_left1(t, BV_SIZE));
    //}

    //BoolectorNode*
    //get_one_by_shiftr(Btor* ctx, BoolectorNode* t)
    //{
        //return yices_bvneg(yices_shift_right1(t, BV_SIZE));
    //}

} // namespace one

} // namespace generators

namespace relations {

namespace identity_lhs {

    mr_pair placeholder(Btor*, mr_pair);

    mr_pair
    base_identity_lhs(Btor* ctx, mr_pair p)
    {
        return p;
    }

    mr_pair
    add_zero_lhs(Btor* ctx, mr_pair p)
    {
        return std::make_pair(
            boolector_add(ctx,
                relations::identity_lhs::placeholder(ctx, p).first,
                generators::zero::placeholder(ctx, p.first)),
            p.second);
    }

    mr_pair
    mul_one_lhs(Btor* ctx, mr_pair p)
    {
        return std::make_pair(
            boolector_mul(ctx,
                relations::identity_lhs::placeholder(ctx, p).first,
                generators::zero::placeholder(ctx, p.first)),
            p.second);
    }

    mr_pair
    double_negate_lhs(Btor* ctx, mr_pair p)
    {
        return std::make_pair(
            boolector_neg(ctx, boolector_neg(ctx,
                relations::identity_lhs::placeholder(ctx, p).first)),
            p.second);
    }

    mr_pair
    iden_by_rotate_same_lhs(Btor* ctx, mr_pair p)
    {
        unsigned int rotate_count_int =
            fuzz::fuzz_rand<unsigned int, unsigned int>(0, BV_SIZE - 1);
        BoolectorNode* rotate_count =
            boolector_int(ctx, rotate_count_int, boolector_bitvec_sort(ctx, BV_SIZE));
        return std::make_pair(
            boolector_rol(ctx,
                boolector_rol(
                    ctx, relations::identity_lhs::placeholder(ctx, p).first,
                    rotate_count),
                boolector_int(ctx, BV_SIZE - rotate_count_int,
                    boolector_bitvec_sort(ctx, BV_SIZE))),
            p.second);
    }

    mr_pair
    iden_by_rotate_opposite_lhs(Btor* ctx, mr_pair p)
    {
        unsigned int rotate_count_int =
            fuzz::fuzz_rand<unsigned int, unsigned int>(0, BV_SIZE - 1);
        BoolectorNode* rotate_count =
            boolector_int(ctx, rotate_count_int, boolector_bitvec_sort(ctx, BV_SIZE));
        return std::make_pair(
            boolector_rol(ctx,
                boolector_ror(
                    ctx, relations::identity_lhs::placeholder(ctx, p).first,
                    rotate_count),
                rotate_count),
            p.second);
    }

    mr_pair
    iden_by_false_ite_lhs(Btor* ctx, mr_pair p)
    {
        BoolectorNode* fuzz = generators::fuzz_gen::placeholder(ctx, p.first);
        return std::make_pair(
            boolector_cond(
                ctx,
                boolector_eq(ctx, relations::identity_lhs::placeholder(ctx, p).first, fuzz),
                fuzz,
                p.first),
            p.second);
    }

    mr_pair
    iden_by_and_self(Btor* ctx, mr_pair p)
    {
        return std::make_pair(
            boolector_and(
                ctx,
                relations::identity_lhs::placeholder(ctx, p).first,
                relations::identity_lhs::placeholder(ctx, p).first),
            p.second);
    }

    mr_pair
    iden_by_or_self(Btor* ctx, mr_pair p)
    {
        return std::make_pair(
            boolector_or(
                ctx,
                relations::identity_lhs::placeholder(ctx, p).first,
                relations::identity_lhs::placeholder(ctx, p).first),
            p.second);
    }

} // namespace identity

} // namespace relations

} // namespace metalib

