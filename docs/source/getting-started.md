# Getting started

## Requirements

Using RSpline requires CMake 3.13 or newer, ROOT and a compatible C++ compiler.
Use the same compiler/runtime environment as ROOT. RSpline takes its effective
language standard from ROOT; the examples request at least C++17. The CI matrix
covers LCG 104/GCC 12, LCG 107/GCC 14 and LCG 109/GCC 15 on EL9.
RSpline itself does not require NAIA, AMS ntuples or an analysis dataset.

Configure with ROOT discoverable through its environment or an explicit
`ROOT_DIR` pointing at the installation's CMake package directory.

## Build and install

```sh
git clone ssh://git@gitlab.cern.ch:7999/ams-italy/rspline.git
cd rspline
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release \
  -DCMAKE_INSTALL_PREFIX="$PWD/rspline.install" \
  -DRSPLINE_INSTALL_PRECOMMIT_HOOKS=OFF
cmake --build build --parallel
cmake --install build
```

By default, configure fetches pinned fmt/spdlog releases, so initial setup needs
network access. To reuse a host application's logging packages, configure with
`-DRSPLINE_USE_EXTERNAL_DEPENDENCIES=ON` and provide the compatible installed
fmt/spdlog CMake packages. Avoid mixing headers from different logging stacks.
The pre-commit option controls development-hook installation; it does not change
spline calculations.

## Link a consumer

```cmake
cmake_minimum_required(VERSION 3.13)
project(MySplineAnalysis LANGUAGES CXX)
find_package(RSpline CONFIG REQUIRED)
add_executable(my_analysis main.cpp)
target_compile_features(my_analysis PRIVATE cxx_std_17)
target_link_libraries(my_analysis PRIVATE RSpline::RSpline)
```

Configure the consumer with:

```sh
cmake -S . -B build -DRSpline_DIR=/path/to/rspline.install/cmake
cmake --build build
```

The exported target supplies the include paths and ROOT link dependencies.
Use `#include <rspline/Spline3.h>` in C++ code.

## Run the examples and tests

The C++ repository ships an installed-package `examples` project. Configure it
with `RSpline_DIR`, build, then run its `interpolation` and `fitting` programs.
Both examples in this manual are literal copies of those checked programs.

For the upstream suite, configure RSpline with `-DCOMPILE_UNIT_TESTS=ON`, build,
and run `build/src/testsuite/run_tests` from a disposable directory: some tests
write demonstration plots. See the repository's `ci/README.md` for its complete
build/test workflow. Passing numerical tests does not choose a physically
appropriate knot set or fit model for your measurements.
