# SpecASTSpecs

Helper repository for [SpecAST](https://github.com/0152la/SpecAST), providing
some specifications for a number of libraries.

### Usage

**NOTE** This section assumes `SpecAST` is already installed and this repository is
cloned at the root of the `SpecAST` repo.

Each specifications comes with a number of components:
* `<lib_name>.cpp` - the template file to generate test cases
* `set_meta_tests_<lib_name>.hpp` - specification file, containing metamorphic
relations and metamorphic checks
* `<spec_name>.yaml` - required `yaml` file to execute `run_experiments.py` with
* `CMakeLists.txt` - cmake file used to generate a `compile_commands.json`
* `runtime/` - cmake file used to compile a generated test case
* some additional header files required for the specific library under test.
These might be outdated compared to the latest/tree version of the respective
library.

In order to use `run_experiments.py`, the paths must be updated in the
respective `yaml` file for the library to be tested. The `update_work_dir.sh`
script can take a parameter to update the `working_dir` field of all `yaml`
files, which *should* be sufficient to execute tests.
