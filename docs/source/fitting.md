# Fitting with ROOT

## Use the linked representation

```cpp
auto &function = spline.AsTF1("fit", xmin, xmax);
auto result = graph.Fit(&function, "SQN0");
```

The reference keeps the spline and TF1 linked. After a successful fit, read
`YKnots()` and `ExtrapolationSlope()` directly; no extra evaluation or parameter
transfer is required. `auto function = ...` would instead create an independent
copy. See {doc}`ownership`.

The function has `NKnots()+2` parameters: physical knot ordinates followed by
lower and upper transformed-coordinate slopes. Flat and Linear endpoint slope
parameters are fixed; LinearFree slopes initially remain free.

## Positive models

LogY parameters remain **physical y**, not logarithmic fit coordinates. Direct
TF1 writes and minimizer trials bypass `SetY` validation. Set positive bounds
on free ordinate parameters before fitting. Choose meaningful bounds for your
model; RSpline does not impose them automatically.

The example below uses bounds appropriate to its synthetic values. It checks
status, validity and covariance quality before requesting an uncertainty band.

```{literalinclude} ../examples/fitting.cpp
:language: cpp
```

## ROOT options and uncertainties

The example uses `S` to retain `TFitResult`, `Q` for quiet output, `N` to avoid
attaching a hidden fitted-function copy to the graph, and `0` to avoid drawing.
If ROOT stores a fitted-function copy on a graph, that copy is independent of
the canonical spline. Do not assume changing it updates the original model.

Choose fit weighting and ROOT options explicitly. For example, horizontal errors
representing bin widths and genuine x measurement uncertainties have different
interpretations; the library does not select a physics convention for them.
Parameter-covariance bands are described in {doc}`uncertainties`.
