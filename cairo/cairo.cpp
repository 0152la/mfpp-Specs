//#include "cairo_spec_ast.hpp"
#include "/home/sentenced/Documents/Internships/2018_ETH/work/spec_ast/input/cairo/cairo_spec_ast.hpp"

namespace fuzz {
namespace lib_helper_funcs {

}
}

int main(int, char**)
{
    const double HEIGHT = fuzz::fuzz_rand(100.0, 400.0);
    const double WIDTH = fuzz::fuzz_rand(100.0, 400.0);
    //const double ORIGIN_X = fuzz::fuzz_rand(WIDTH*0.25, WIDTH*0.75);
    //const double ORIGIN_Y = fuzz::fuzz_rand(HEIGHT*0.25, HEIGHT*0.75);

    fuzz::start();
    Cairo::RefPtr<Cairo::ImageSurface> surface =
        Cairo::ImageSurface::create(Cairo::Surface::Format::ARGB32, WIDTH, HEIGHT);
    fuzz::output_var = Cairo::Context::create(surface);
    fuzz::output_var->set_source_rgb(1.0, 1.0, 0.0);
    fuzz::output_var->paint();
    fuzz::end();
    fuzz::meta_test();
}
