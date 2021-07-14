namespace metalib {

// Forward declarations

namespace generators {
namespace fuzz_set_term {
    fuzz::set_term placeholder(fuzz::fuzz_context);
}
namespace universe {
    fuzz::set_term placeholder(fuzz::fuzz_context, fuzz::set_term);
}
namespace empty {
    fuzz::set_term placeholder(fuzz::fuzz_context, fuzz::set_term);
}
} // namespace generators

namespace relations {
namespace identity {
    fuzz::set_term placeholder(fuzz::fuzz_context, fuzz::set_term);
}
namespace complement {
    fuzz::set_term placeholder(fuzz::fuzz_context, fuzz::set_term);
}
namespace subtract {
    fuzz::set_term placeholder(fuzz::fuzz_context, fuzz::set_term, fuzz::set_term);
}
namespace unite {
    fuzz::set_term placeholder(fuzz::fuzz_context, fuzz::set_term, fuzz::set_term);
}
namespace intersect {
    fuzz::set_term placeholder(fuzz::fuzz_context, fuzz::set_term, fuzz::set_term);
}
namespace unite_assoc {
    fuzz::set_term placeholder(fuzz::fuzz_context, fuzz::set_term, fuzz::set_term, fuzz::set_term);
}
namespace intersect_assoc {
    fuzz::set_term placeholder(fuzz::fuzz_context, fuzz::set_term, fuzz::set_term, fuzz::set_term);
}
} // namespace relations

// Abstract implementations

namespace generators {

namespace fuzz_set_term {

    fuzz::set_term
    get_set_by_fuzz(fuzz::fuzz_context fctx)
    {
        fuzz::set_term fuzz = fuzz::fuzz_new<fuzz::set_term>();
        return fuzz;
    }

} // namespace fuzz_set_term

namespace universe {

    fuzz::set_term
    universe_complementarity(fuzz::fuzz_context fctx, fuzz::set_term s)
    {
        fuzz::set_term s_compl = relations::complement::placeholder(fctx, s);
        return relations::unite::placeholder(fctx, s, s_compl);
    }

    fuzz::set_term
    universe_logical_inverse(fuzz::fuzz_context fctx, fuzz::set_term s)
    {
        fuzz::set_term iden = relations::identity::placeholder(fctx, s);
        fuzz::set_term e = generators::empty::placeholder(fctx, iden);
        return relations::complement::placeholder(fctx, e);
    }

    fuzz::set_term
    universe_dominance(fuzz::fuzz_context fctx, fuzz::set_term s)
    {
        fuzz::set_term iden = relations::identity::placeholder(fctx, s);
        fuzz::set_term u = generators::universe::placeholder(fctx, iden);
        return relations::unite::placeholder(fctx, iden, u);
    }

} // namespace universe

namespace empty {

    fuzz::set_term
    empty_complementarity(fuzz::fuzz_context fctx, fuzz::set_term s)
    {
        fuzz::set_term s_compl = relations::complement::placeholder(fctx, s);
        return relations::intersect::placeholder(fctx, s, s_compl);
    }

    fuzz::set_term
    empty_by_sub(fuzz::fuzz_context fctx, fuzz::set_term s)
    {
        fuzz::set_term iden = relations::identity::placeholder(fctx, s);
        return relations::subtract::placeholder(fctx, s, iden);
    }

    fuzz::set_term
    empty_by_sub_universe(fuzz::fuzz_context fctx, fuzz::set_term s)
    {
        fuzz::set_term iden = relations::identity::placeholder(fctx, s);
        fuzz::set_term u = generators::universe::placeholder(fctx, iden);
        return relations::subtract::placeholder(fctx, iden, u);
    }

    fuzz::set_term
    empty_logical_inverse(fuzz::fuzz_context fctx, fuzz::set_term s)
    {
        fuzz::set_term iden = relations::identity::placeholder(fctx, s);
        fuzz::set_term u = generators::universe::placeholder(fctx, iden);
        return relations::complement::placeholder(fctx, u);
    }

    fuzz::set_term
    empty_dominance(fuzz::fuzz_context fctx, fuzz::set_term s)
    {
        fuzz::set_term iden = relations::identity::placeholder(fctx, s);
        fuzz::set_term e = generators::empty::placeholder(fctx, iden);
        return relations::intersect::placeholder(fctx, iden, e);
    }

} // namespace empty

} // namespace generators

namespace relations {

namespace identity {

    fuzz::set_term
    iden_by_unite_idempotence(fuzz::fuzz_context fctx, fuzz::set_term s)
    {
        fuzz::set_term iden = relations::identity::placeholder(fctx, s);
        return relations::unite::placeholder(fctx, s, iden);
    }

    fuzz::set_term
    iden_by_unite_identity(fuzz::fuzz_context fctx, fuzz::set_term s)
    {
        fuzz::set_term iden = relations::identity::placeholder(fctx, s);
        fuzz::set_term e = generators::empty::placeholder(fctx, iden);
        return relations::unite::placeholder(fctx, e, iden);
    }

    fuzz::set_term
    iden_by_intersect_idempotence(fuzz::fuzz_context fctx, fuzz::set_term s)
    {
        fuzz::set_term iden = relations::identity::placeholder(fctx, s);
        return relations::intersect::placeholder(fctx, s, iden);
    }

    fuzz::set_term
    iden_by_intersect_identity(fuzz::fuzz_context fctx, fuzz::set_term s)
    {
        fuzz::set_term iden = relations::identity::placeholder(fctx, s);
        fuzz::set_term u = generators::universe::placeholder(fctx, iden);
        return relations::intersect::placeholder(fctx, u, iden);
    }

    fuzz::set_term
    iden_by_double_complement(fuzz::fuzz_context fctx, fuzz::set_term s)
    {
        s = relations::identity::placeholder(fctx, s);
        s = relations::complement::placeholder(fctx, s);
        s = relations::identity::placeholder(fctx, s);
        return relations::complement::placeholder(fctx, s);
    }

} // namespace identity

namespace complement {

    fuzz::set_term
    complement_by_universe_subtract(fuzz::fuzz_context fctx, fuzz::set_term s)
    {
        fuzz::set_term iden = relations::identity::placeholder(fctx, s);
        fuzz::set_term u = generators::universe::placeholder(fctx, iden);
        return relations::subtract::placeholder(fctx, u, iden);
    }

} // namespace complement

namespace subtract {

    fuzz::set_term
    subtract_by_intersect(fuzz::fuzz_context fctx, fuzz::set_term s1, fuzz::set_term s2)
    {
        s1 = relations::identity::placeholder(fctx, s1);
        s2 = relations::identity::placeholder(fctx, s2);
        fuzz::set_term s2_compl = relations::complement::placeholder(fctx, s2);
        return relations::intersect::placeholder(fctx, s1, s2_compl);
    }

} // namespace subtract

namespace unite {

    fuzz::set_term
    unite_commutativity(fuzz::fuzz_context fctx, fuzz::set_term s1, fuzz::set_term s2)
    {
        s1 = relations::identity::placeholder(fctx, s1);
        s2 = relations::identity::placeholder(fctx, s2);
        return relations::unite::placeholder(fctx, s2, s1);
    }

    fuzz::set_term
    unite_demorgan(fuzz::fuzz_context fctx, fuzz::set_term s1, fuzz::set_term s2)
    {
        fuzz::set_term s1_compl = relations::complement::placeholder(fctx, s1);
        fuzz::set_term s2_compl = relations::complement::placeholder(fctx, s2);
        fuzz::set_term compl_int = relations::intersect::placeholder(fctx, s1_compl, s2_compl);
        return relations::complement::placeholder(fctx, compl_int);
    }

} // namespace unite

namespace intersect {

    fuzz::set_term
    intersect_commutativity(fuzz::fuzz_context fctx, fuzz::set_term s1, fuzz::set_term s2)
    {
        s1 = relations::identity::placeholder(fctx, s1);
        s2 = relations::identity::placeholder(fctx, s2);
        return relations::intersect::placeholder(fctx, s2, s1);
    }

    fuzz::set_term
    intersect_demorgan(fuzz::fuzz_context fctx, fuzz::set_term s1, fuzz::set_term s2)
    {
        fuzz::set_term s1_compl = relations::complement::placeholder(fctx, s1);
        fuzz::set_term s2_compl = relations::complement::placeholder(fctx, s2);
        fuzz::set_term compl_unite = relations::unite::placeholder(fctx, s1_compl, s2_compl);
        return relations::complement::placeholder(fctx, compl_unite);
    }

} // namespace intersect

namespace unite_assoc {

    fuzz::set_term
    unite_assoc_back(fuzz::fuzz_context fctx, fuzz::set_term s1, fuzz::set_term s2, fuzz::set_term s3)
    {
        s1 = relations::identity::placeholder(fctx, s1);
        fuzz::set_term back_unite = relations::unite::placeholder(fctx, s2, s3);
        back_unite = relations::identity::placeholder(fctx, back_unite);
        return relations::unite::placeholder(fctx, s1, back_unite);
    }

} // namespace unite_assoc

namespace intersect_assoc {

    fuzz::set_term
    intersect_assoc_back(fuzz::fuzz_context fctx, fuzz::set_term s1, fuzz::set_term s2, fuzz::set_term s3)
    {
        s1 = relations::identity::placeholder(fctx, s1);
        fuzz::set_term back_intersect = relations::intersect::placeholder(fctx, s2, s3);
        back_intersect = relations::identity::placeholder(fctx, back_intersect);
        return relations::intersect::placeholder(fctx, s1, back_intersect);
    }

} // namespace intersect_assoc

} // namespace relations

} // namespace metalib
