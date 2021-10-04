namespace metalib {

namespace generators {

namespace fuzz_expr {

    BoolectorNode* placeholder(Btor*, BoolectorNode*);

    BoolectorNode*
    fuzz_term(Btor* ctx, BoolectorNode* t)
    {
        return fuzz::fuzz_new<BoolectorNode*>();
    }

} // namespace fuzz_expr

namespace zero {

    BoolectorNode* placeholder(Btor*, BoolectorNode*);

    BoolectorNode*
    get_zero_by_fuzz_sub(Btor* ctx, BoolectorNode* t)
    {
        BoolectorNode* t_fuzz = generators::fuzz_expr::placeholder(ctx, t);
        return boolector_sub(ctx, t_fuzz, t_fuzz);
    }

    BoolectorNode*
    get_zero_by_mul(Btor* ctx, BoolectorNode* t)
    {
        return boolector_mul(ctx, t, generators::zero::placeholder(ctx, t));
    }

} // namespace zero

namespace one {

    BoolectorNode* placeholder(Btor*, BoolectorNode*);

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
        BoolectorNode* fuzz = generators::fuzz_expr::placeholder(ctx, t);
        return boolector_cond(ctx,
            boolector_ne(ctx, fuzz, generators::zero::placeholder(ctx, fuzz)),
            boolector_sdiv(ctx, fuzz, fuzz), generators::one::placeholder(ctx, fuzz));
    }


} // namespace one

} // namespace generators

namespace relations {

namespace identity {

    BoolectorNode* placeholder(Btor*, BoolectorNode*);

    BoolectorNode*
    add_zero(Btor* ctx, BoolectorNode* n)
    {
        return boolector_add(ctx, n, generators::zero::placeholder(ctx, n));
    }

    BoolectorNode*
    sub_zero(Btor* ctx, BoolectorNode* n)
    {
        return boolector_sub(ctx, n, generators::zero::placeholder(ctx, n));
    }

    BoolectorNode*
    mul_one(Btor* ctx, BoolectorNode* n)
    {
        return boolector_mul(ctx, n, generators::one::placeholder(ctx, n));
    }

    BoolectorNode*
    double_negation(Btor* ctx, BoolectorNode* n)
    {
        return boolector_neg(ctx,
                boolector_neg(ctx, relations::identity::placeholder(ctx, n)));
    }

    BoolectorNode*
    double_not(Btor* ctx, BoolectorNode* n)
    {
        return boolector_not(ctx,
                boolector_not(ctx, relations::identity::placeholder(ctx, n)));
    }

    BoolectorNode*
    iden_by_rotate_same(Btor* ctx, BoolectorNode* n)
    {
        unsigned int rotate_count_int =
            fuzz::fuzz_rand<unsigned int, unsigned int>(0, BV_SIZE - 1);
        BoolectorNode* rotate_count =
            boolector_int(ctx, rotate_count_int, boolector_bitvec_sort(ctx, BV_SIZE));
        return boolector_rol(ctx,
                boolector_rol(ctx, relations::identity::placeholder(ctx, n), rotate_count),
                boolector_int(ctx, BV_SIZE - rotate_count_int, boolector_bitvec_sort(ctx, BV_SIZE)));
    }

    BoolectorNode*
    iden_by_rotate_opposite(Btor* ctx, BoolectorNode* n)
    {
        unsigned int rotate_count_int =
            fuzz::fuzz_rand<unsigned int, unsigned int>(0, BV_SIZE - 1);
        BoolectorNode* rotate_count =
            boolector_int(ctx, rotate_count_int, boolector_bitvec_sort(ctx, BV_SIZE));
        return boolector_rol(ctx,
                boolector_ror(ctx, relations::identity::placeholder(ctx, n), rotate_count),
                rotate_count);
    }

    BoolectorNode*
    iden_by_false_ite(Btor* ctx, BoolectorNode* n)
    {
        BoolectorNode* fuzz = generators::fuzz_expr::placeholder(ctx, n);
        return boolector_cond(ctx,
            boolector_eq(ctx, relations::identity::placeholder(ctx, n), fuzz),
            fuzz, n);
    }

} // namespace identity

namespace sub { BoolectorNode* placeholder(Btor*, BoolectorNode*, BoolectorNode*); }

namespace add
{

    BoolectorNode* placeholder(Btor*, BoolectorNode*, BoolectorNode*);

    BoolectorNode*
    commute_add(Btor* ctx, BoolectorNode* n1, BoolectorNode* n2)
    {
        return relations::add::placeholder(ctx, n2, n1);
    }

    BoolectorNode*
    add_by_sub_neg(Btor* ctx, BoolectorNode* n1, BoolectorNode* n2)
    {
        return relations::sub::placeholder(ctx, n1, boolector_neg(ctx, n2));
    }
} // namespace add

namespace sub
{

    BoolectorNode*
    sub_by_add_neg(Btor* ctx, BoolectorNode* n1, BoolectorNode* n2)
    {
        return relations::add::placeholder(ctx, n1, boolector_neg(ctx, n2));
    }

} // namespace sub

namespace mul
{

    BoolectorNode* placeholder(Btor*, BoolectorNode*, BoolectorNode*);

    BoolectorNode*
    commute_mul(Btor* ctx, BoolectorNode* n1, BoolectorNode* n2)
    {
        return relations::mul::placeholder(ctx, n2, n1);
    }

} // namespace mul

namespace bvor { BoolectorNode* placeholder(Btor*, BoolectorNode*, BoolectorNode*); }

namespace bvand
{

    BoolectorNode* placeholder(Btor*, BoolectorNode*, BoolectorNode*);

    BoolectorNode*
    commute_and(Btor* ctx, BoolectorNode* n1, BoolectorNode* n2)
    {
        return relations::bvand::placeholder(ctx, n2, n1);
    }

    BoolectorNode*
    demorgan_and(Btor* ctx, BoolectorNode* n1, BoolectorNode* n2)
    {
        return boolector_not(ctx,
            relations::bvor::placeholder(ctx,
                boolector_not(ctx, n1), boolector_not(ctx, n2)));
    }

} // namespace bvand

namespace bvor
{

    BoolectorNode* placeholder(Btor*, BoolectorNode*, BoolectorNode*);

    BoolectorNode*
    commute_or(Btor* ctx, BoolectorNode* n1, BoolectorNode* n2)
    {
        return relations::bvor::placeholder(ctx, n2, n1);
    }

    BoolectorNode*
    demorgan_or(Btor* ctx, BoolectorNode* n1, BoolectorNode* n2)
    {
        return boolector_not(ctx,
            relations::bvand::placeholder(ctx,
                boolector_not(ctx, n1), boolector_not(ctx, n2)));
    }

} // namespace bvor

namespace rotate_left {
    BoolectorNode* placeholder(Btor*, BoolectorNode*, size_t);
}

namespace rotate_right
{
    BoolectorNode* placeholder(Btor*, BoolectorNode*, size_t);

    BoolectorNode*
    ror_by_rol(Btor* ctx, BoolectorNode* n, size_t i)
    {
        i = i % (BV_SIZE + 1);
        i = BV_SIZE - i;
        return relations::rotate_left::placeholder(ctx, n, i);
    }

} // namespace rotate_right

namespace rotate_left
{

    BoolectorNode*
    rol_by_ror(Btor* ctx, BoolectorNode* n, size_t i)
    {
        i = i % (BV_SIZE + 1);
        i = BV_SIZE - i;
        return relations::rotate_right::placeholder(ctx, n, i);
    }
}

} // namespace relations

} // namespace metalib

