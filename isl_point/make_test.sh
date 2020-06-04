mkdir -p output
./build/mtFuzzer `pwd`/isl_point/isl_point.cpp -o `pwd`/output/test.cpp --lib-list=`pwd`/isl_point/isl-noexceptions-point.h --set-meta-path=`pwd`/isl_point/set_meta_tests_isl.yaml
