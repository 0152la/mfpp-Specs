namespace metalib {

namespace checks {

    bool
    check_set_equals(isl::set s1, isl::set s2)
    {
        return s1.is_equal(s2);
    }

} // namespace checks

namespace generators {

namespace universe {
    isl::set placeholder(isl::set);
}

namespace empty {
    isl::set placeholder(isl::set);
}

namespace universe {

    isl::set
    complementarity(isl::set s)
    {
        return s.unite(s.complement());
    }

    isl::set
    logical_inverse(isl::set s)
    {
        return generators::empty::placeholder(s).complement();
    }

    isl::set
    dominance(isl::set s)
    {
        return s.unite(placeholder(s));
    }

} // namespace universe

namespace empty {

    isl::set
    complementarity(isl::set s)
    {
        return s.intersect(s.complement());
    }

    isl::set
    sub_self(isl::set s)
    {
        return s.subtract(s);
    }

    isl::set
    sub_universe(isl::set s)
    {
        return s.subtract(generators::universe::placeholder(s));
    }

    isl::set
    dominance(isl::set s)
    {
        return s.intersect(placeholder(s));
    }

    isl::set
    logical_inverse(isl::set s)
    {
        return generators::universe::placeholder(s).complement();
    }

} // namespace empty

} // namespace generators

namespace relations {

namespace complement {
    isl::set placeholder(isl::set);
}

namespace subtract {
    isl::set placeholder(isl::set, isl::set);
}

namespace unite {
    isl::set placeholder(isl::set, isl::set);
}

namespace intersect {
    isl::set placeholder(isl::set, isl::set);
}

namespace identity {

    isl::set placeholder(isl::set, isl::set);

    isl::set
    base_iden(isl::set s1, isl::set s2)
    {
        return s1;
    }

    isl::set
    idempotence_unite(isl::set s1, isl::set s2)
    {
        return s1.unite(s1);
    }

    isl::set
    identity_unite(isl::set s1, isl::set s2)
    {
        return s1.unite(generators::empty::placeholder(s1));
    }

    isl::set
    idempotence_intersect(isl::set s1, isl::set s2)
    {
        return s1.intersect(s1);
    }

    isl::set
    identity_intersect(isl::set s1, isl::set s2)
    {
        return s1.intersect(generators::universe::placeholder(s1));
    }

    isl::set
    double_complement(isl::set s1, isl::set s2)
    {
        isl::set tmp = relations::complement::placeholder(s1);
        return relations::complement::placeholder(tmp);
    }

    isl::set
    identity_coalesce(isl::set s1, isl::set s2)
    {
        return s1.coalesce();
    }

    isl::set
    identity_detect_equalities(isl::set s1, isl::set s2)
    {
        return s1.detect_equalities();
    }

} // namespace identity

namespace complement {

    isl::set
    base_complement(isl::set s1)
    {
        return s1.complement();
    }

    isl::set
    universe_subtract(isl::set s1)
    {
        return generators::universe::placeholder(s1).subtract(s1);
    }

} // namespace complement

namespace subtract {

    isl::set
    base_subtract(isl::set s1, isl::set s2)
    {
        return s1.subtract(s2);
    }

    isl::set
    sub_by_intersect(isl::set s1, isl::set s2)
    {
        isl::set tmp = relations::complement::placeholder(s2);
        return relations::intersect::placeholder(s1, tmp);
    }

} // namespace subtract

namespace unite {

    isl::set
    base_unite(isl::set s1, isl::set s2)
    {
        return s1.unite(s2);
    }

    isl::set
    unite_commutativity(isl::set s1, isl::set s2)
    {
        return s2.unite(s1);
    }

    isl::set
    unite_demorgan(isl::set s1, isl::set s2)
    {
        return s1.complement().intersect(s2.complement()).complement();
    }


} // namespace unite

namespace intersect {

    isl::set
    base_intersect(isl::set s1, isl::set s2)
    {
        return s1.intersect(s2);
    }

    isl::set
    intersect_commutativity(isl::set s1, isl::set s2)
    {
        return s2.intersect(s1);
    }

    isl::set
    intersect_demorgan(isl::set s1, isl::set s2)
    {
        return s1.complement().unite(s2.complement()).complement();
    }

} // namespace intersect

} // namespace relations

} // namespace metalib
