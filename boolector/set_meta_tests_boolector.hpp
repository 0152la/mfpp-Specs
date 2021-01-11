namespace metalib {

namespace checks {

    void
    check_sat_expr_maintained(Btor* ctx, BoolectorNode* t1, BoolectorNode* t2, sat_stat& stat)
    {

    }

} // namespace checks

namespace generators {

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

} // namespace one

} // namespace generators

namespace relations {

namespace identity {

    BoolectorNode* placeholder(Btor*, BoolectorNode*);

    BoolectorNode*
    base_identity(Btor* ctx, BoolectorNode* n)
    {
        return n;
    }

    BoolectorNode*
    add_zero(Btor* ctx, BoolectorNode* n)
    {
        return boolector_add(ctx, n, generators::zero::placeholder(ctx, n));
    }

    BoolectorNode*
    mul_one(Btor* ctx, BoolectorNode* n)
    {
        return boolector_mul(ctx, n, generators::one::placeholder(ctx, n));
    }

} // namespace identity

} // namespace relations

} // namespace metalib

