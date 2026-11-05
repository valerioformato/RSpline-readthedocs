# API reference

The generated Doxygen reference lives in the C++ RSpline repository. This
manual supplies tutorials; header contracts and implementation remain the
source of truth.

## Published reference

The [RSpline 1.0.0 API reference](https://rspline-docs.web.cern.ch/v1.0.0/index.html)
is published separately from this manual. Each C++ library release tag has its
own directory on the CERN web service, so API links can target a fixed release.

## Generate the reference

Like NAIA, RSpline discovers Doxygen automatically during normal configuration.
When Doxygen 1.9 or newer is found, build the reference without any documentation
configuration flag:

```sh
cmake --build build --target rspline-doxygen
```

Open `build/doc/doxygen/html/index.html`. Missing Doxygen does not prevent
building the library. Documentation generation fails on undocumented members,
missing parameter descriptions and invalid references.

For a standalone reference build requiring neither a compiler nor ROOT/fmt/spdlog,
configure the `doc` directory directly from an RSpline checkout:

```sh
cmake -S doc -B build/docs
cmake --build build/docs --target rspline-doxygen
```

Its output is `build/docs/doxygen/html/index.html`.

HTML, XML and the `RSpline.tag` cross-reference file are produced together.
The repository's documentation CI job retains them as artifacts; use the
[RSpline job list](https://gitlab.cern.ch/ams-italy/rspline/-/jobs) to select the
appropriate branch/build. An installed documentation copy can be generated
with the `install-rspline-doxygen` target.

## Header map

| Header | Contents |
| --- | --- |
| [Spline.h](https://gitlab.cern.ch/ams-italy/rspline/-/blob/master/src/rspline/Spline.h) | Options, extrapolation settings, validated knots, linked TF1, covariance bands |
| [Spline3.h](https://gitlab.cern.ch/ams-italy/rspline/-/blob/master/src/rspline/Spline3.h) | Cubic interpolation, evaluation and coefficient snapshots |
| [BitMask.h](https://gitlab.cern.ch/ams-italy/rspline/-/blob/master/src/rspline/BitMask.h) | Scoped-enum bitmask operators and pattern helpers |

The library also carries focused guides in `docs/TF1_OWNERSHIP.md` and
`docs/ERROR_BANDS.md`, included in the generated reference. API hosting and this
manual's Read the Docs hosting are configured separately; generating either
site does not publish it automatically.
