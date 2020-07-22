#include "/home/sentenced/Documents/Internships/2018_ETH/work/spec_ast/input/spec_repo/isl/spec_fuzz.hpp"

int
main(int argc, char** argv)
{
    isl_ctx* c_ctx = isl_ctx_alloc();
    //isl_options_set_on_error(c_ctx, ISL_ON_ERROR_ABORT);
    isl::ctx ctx(isl_ctx_alloc());
    isl::space space(ctx, 0, 3);
    isl::local_space local_space(space);
    fuzz::start();
    isl::pw_aff dim0 = isl::pw_aff::var_on_domain(local_space, isl::dim::set, 0);
    isl::pw_aff dim1 = isl::pw_aff::var_on_domain(local_space, isl::dim::set, 1);
    isl::pw_aff dim2 = isl::pw_aff::var_on_domain(local_space, isl::dim::set, 2);
    fuzz::output_var = isl::set::universe(space);
    fuzz::output_var = fuzz::output_var.intersect(fuzz::fuzz_new<isl::set>());
    fuzz::output_var = fuzz::output_var.intersect(fuzz::fuzz_new<isl::set>());
    fuzz::output_var = fuzz::output_var.intersect(fuzz::fuzz_new<isl::set>());
    fuzz::output_var = fuzz::output_var.intersect(fuzz::fuzz_new<isl::set>());
    fuzz::output_var.dump();
    fuzz::end();
    fuzz::meta_test();
}