namespace metalib {

namespace checks {

    void
    check_equal(Btor* ctx, BoolectorNode* t1, BoolectorNode* t2)
    {
        boolector_push(ctx, 1);
        BoolectorNode* check = boolector_eq(ctx, t1, t2);
        boolector_assert(ctx, check);
        assert(boolector_sat(ctx) == BOOLECTOR_SAT);
        boolector_pop(ctx, 1);
    }

    void
    check_not_distinct(Btor* ctx, BoolectorNode* t1, BoolectorNode* t2)
    {
        boolector_push(ctx, 1);
        BoolectorNode* check = boolector_ne(ctx, t1, t2);
        boolector_assert(ctx, check);
        assert(boolector_sat(ctx) != BOOLECTOR_SAT);
        boolector_pop(ctx, 1);
    }

} // namespace checks

namespace generators {

namespace zero {


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


} // namespace one

} // namespace generators

namespace relations {

namespace identity {

    BoolectorNode*
    base_identity(Btor* ctx, BoolectorNode* n)
    {
        return n;
    }

    BoolectorNode*
    iden_by_and_self(Btor* ctx, BoolectorNode* n)
    {
        return boolector_and(ctx, n, n);
    }

    BoolectorNode*
    iden_by_or_self(Btor* ctx, BoolectorNode* n)
    {
        return boolector_or(ctx, n, n);
    }

} // namespace identity

namespace add
{

    BoolectorNode*
    base_add(Btor* ctx, BoolectorNode* n1, BoolectorNode* n2)
    {
        return boolector_add(ctx, n1, n2);
    }

} // namespace add

namespace sub
{

    BoolectorNode*
    base_sub(Btor* ctx, BoolectorNode* n1, BoolectorNode* n2)
    {
        return boolector_sub(ctx, n1, n2);
    }

} // namespace sub

namespace mul
{

    BoolectorNode*
    base_mul(Btor* ctx, BoolectorNode* n1, BoolectorNode* n2)
    {
        return boolector_mul(ctx, n1, n2);
    }

} // namespace mul

namespace bvand
{

    BoolectorNode*
    base_and(Btor* ctx, BoolectorNode* n1, BoolectorNode* n2)
    {
        return boolector_and(ctx, n1, n2);
    }


    BoolectorNode*
    nnand(Btor* ctx, BoolectorNode* n1, BoolectorNode* n2)
    {
        return boolector_not(ctx, boolector_nand(ctx, n1, n2));
    }

} // namespace bvand

namespace bvor
{

    BoolectorNode*
    base_or(Btor* ctx, BoolectorNode* n1, BoolectorNode* n2)
    {
        return boolector_or(ctx, n1, n2);
    }

    BoolectorNode*
    nnor(Btor* ctx, BoolectorNode* n1, BoolectorNode* n2)
    {
        return boolector_not(ctx, boolector_nor(ctx, n1, n2));
    }

} // namespace bvor

namespace rotate_right
{
    BoolectorNode*
    base_ror(Btor* ctx, BoolectorNode* n, size_t i)
    {
        return boolector_rori(ctx, n, i);
    }

    BoolectorNode*
    bv_ror(Btor* ctx, BoolectorNode* n, size_t i)
    {
        return boolector_ror(ctx, n,
            boolector_int(ctx, i, boolector_bitvec_sort(ctx, BV_SIZE)));
    }

} // namespace rotate_right

namespace rotate_left
{

    BoolectorNode*
    base_rol(Btor* ctx, BoolectorNode* n, size_t i)
    {
        return boolector_roli(ctx, n, i);
    }

    BoolectorNode*
    bv_ror(Btor* ctx, BoolectorNode* n, size_t i)
    {
        return boolector_rol(ctx, n,
            boolector_int(ctx, i, boolector_bitvec_sort(ctx, BV_SIZE)));
    }

}

} // namespace relations

} // namespace metalib

