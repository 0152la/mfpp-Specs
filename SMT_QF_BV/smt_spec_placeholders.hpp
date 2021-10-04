namespace metalib {

/*******************************************************************************
 * Forward declarations
 ******************************************************************************/

namespace generators {
namespace fuzz_bv_term {
    fuzz::bv_term placeholder(fuzz::fuzz_context);
}
namespace fuzz_bool_term {
    fuzz::bool_term placeholder(fuzz::fuzz_context);
}
namespace zero {
    fuzz::bv_term placeholder(fuzz::fuzz_context, fuzz::bv_term);
}
namespace one {
    fuzz::bv_term placeholder(fuzz::fuzz_context, fuzz::bv_term);
}
namespace true_bool {
    fuzz::bool_term placeholder(fuzz::fuzz_context, fuzz::bool_term);
}
namespace false_bool {
    fuzz::bool_term placeholder(fuzz::fuzz_context, fuzz::bool_term);
}
namespace iden_bool {
    fuzz::bool_term placeholder(fuzz::fuzz_context, fuzz::bool_term);
}
namespace not_bool {
    fuzz::bool_term placeholder(fuzz::fuzz_context, fuzz::bool_term);
}
namespace and_bool {
    fuzz::bool_term placeholder(fuzz::fuzz_context, fuzz::bool_term, fuzz::bool_term);
}
namespace or_bool {
    fuzz::bool_term placeholder(fuzz::fuzz_context, fuzz::bool_term, fuzz::bool_term);
}
namespace xor_bool {
    fuzz::bool_term placeholder(fuzz::fuzz_context, fuzz::bool_term, fuzz::bool_term);
}
namespace equal_bool {
    fuzz::bool_term placeholder(fuzz::fuzz_context, fuzz::bool_term, fuzz::bool_term);
}
namespace equal_bv {
    fuzz::bool_term placeholder(fuzz::fuzz_context, fuzz::bv_term, fuzz::bv_term);
}
namespace extract_bv {
    fuzz::bv_term placeholder(fuzz::fuzz_context, fuzz::bv_term, size_t, size_t);
}
namespace extract_bit_bv {
    fuzz::bv_term placeholder(fuzz::fuzz_context, fuzz::bv_term, size_t);
}
namespace concat_bv {
    fuzz::bv_term placeholder(fuzz::fuzz_context, fuzz::bv_term, fuzz::bv_term);
}
namespace ite_bv_term_cond {
    fuzz::bv_term placeholder(fuzz::fuzz_context, fuzz::bool_term, fuzz::bv_term, fuzz::bv_term);
}
namespace ite_bool {
    fuzz::bool_term placeholder(fuzz::fuzz_context, fuzz::bool_term, fuzz::bool_term, fuzz::bool_term);
}
namespace lt {
    fuzz::bool_term placeholder(fuzz::fuzz_context, fuzz::bv_term, fuzz::bv_term);
}
namespace gt {
    fuzz::bool_term placeholder(fuzz::fuzz_context, fuzz::bv_term, fuzz::bv_term);
}
namespace leq {
    fuzz::bool_term placeholder(fuzz::fuzz_context, fuzz::bv_term, fuzz::bv_term);
}
namespace geq {
    fuzz::bool_term placeholder(fuzz::fuzz_context, fuzz::bv_term, fuzz::bv_term);
}
namespace slt {
    fuzz::bool_term placeholder(fuzz::fuzz_context, fuzz::bv_term, fuzz::bv_term);
}
namespace sgt {
    fuzz::bool_term placeholder(fuzz::fuzz_context, fuzz::bv_term, fuzz::bv_term);
}
namespace sleq {
    fuzz::bool_term placeholder(fuzz::fuzz_context, fuzz::bv_term, fuzz::bv_term);
}
namespace sgeq {
    fuzz::bool_term placeholder(fuzz::fuzz_context, fuzz::bv_term, fuzz::bv_term);
}
} // namespace generators

namespace relations {
namespace identity {
    fuzz::bv_term placeholder(fuzz::fuzz_context, fuzz::bv_term);
}
namespace add {
    fuzz::bv_term placeholder(fuzz::fuzz_context, fuzz::bv_term, fuzz::bv_term);
}
namespace sub {
    fuzz::bv_term placeholder(fuzz::fuzz_context, fuzz::bv_term, fuzz::bv_term);
}
namespace mul {
    fuzz::bv_term placeholder(fuzz::fuzz_context, fuzz::bv_term, fuzz::bv_term);
}
namespace division {
    fuzz::bv_term placeholder(fuzz::fuzz_context, fuzz::bv_term, fuzz::bv_term);
}
namespace modulo {
    fuzz::bv_term placeholder(fuzz::fuzz_context, fuzz::bv_term, fuzz::bv_term);
}
namespace abs_bv {
    fuzz::bv_term placeholder(fuzz::fuzz_context, fuzz::bv_term);
}
namespace neg_bv {
    fuzz::bv_term placeholder(fuzz::fuzz_context, fuzz::bv_term);
}
namespace not_bv {
    fuzz::bv_term placeholder(fuzz::fuzz_context, fuzz::bv_term);
}
namespace or_bv {
    fuzz::bv_term placeholder(fuzz::fuzz_context, fuzz::bv_term, fuzz::bv_term);
}
namespace and_bv {
    fuzz::bv_term placeholder(fuzz::fuzz_context, fuzz::bv_term, fuzz::bv_term);
}
namespace xor_bv {
    fuzz::bv_term placeholder(fuzz::fuzz_context, fuzz::bv_term, fuzz::bv_term);
}
namespace rotate_left_int {
    fuzz::bv_term placeholder(fuzz::fuzz_context, fuzz::bv_term, size_t);
}
namespace rotate_right_int {
    fuzz::bv_term placeholder(fuzz::fuzz_context, fuzz::bv_term, size_t);
}
namespace shift_left_zero {
    fuzz::bv_term placeholder(fuzz::fuzz_context, fuzz::bv_term, size_t);
}
namespace shift_right_zero {
    fuzz::bv_term placeholder(fuzz::fuzz_context, fuzz::bv_term, size_t);
}
namespace shift_left_one {
    fuzz::bv_term placeholder(fuzz::fuzz_context, fuzz::bv_term, size_t);
}
namespace shift_right_one {
    fuzz::bv_term placeholder(fuzz::fuzz_context, fuzz::bv_term, size_t);
}
namespace ite_bv {
    fuzz::bv_term placeholder(fuzz::fuzz_context, bool, fuzz::bv_term, fuzz::bv_term);
}

} // namespace relations

} // namespace metalib
