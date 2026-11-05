# RSpline

RSpline is a C++ library for cubic interpolation and ROOT fitting. It offers
optional interior slope limiting, base-10 logarithmic axes, configurable
endpoint slopes, linked ROOT functions and parameter-covariance error bands.

This manual explains how to choose and use those features. Start with
{doc}`getting-started`, then work through {doc}`interpolation` and {doc}`fitting`.
The {doc}`api-reference` explains how to build the generated API reference.

| Task | Read |
| --- | --- |
| Build, install and link the library | {doc}`getting-started` |
| Choose axes and understand the cubic model | {doc}`interpolation` |
| Configure behavior beyond the knots | {doc}`extrapolation` |
| Fit a graph and obtain uncertainties | {doc}`fitting` |
| Manage the linked TF1, copies and persistence | {doc}`ownership` |
| Interpret covariance bands and failures | {doc}`uncertainties` |
| Diagnose setup and numerical problems | {doc}`troubleshooting` |

```{toctree}
:maxdepth: 2
:hidden:
:caption: RSpline

getting-started
interpolation
extrapolation
fitting
ownership
uncertainties
troubleshooting
api-reference
```
