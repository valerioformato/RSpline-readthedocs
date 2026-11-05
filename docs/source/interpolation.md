# Interpolation and coordinates

## The cubic model

`RSpline::Spline3` uses local cubic Hermite interpolation. Adjacent intervals
share their knot value and first derivative, giving C1 continuity. Their second
derivatives need not match: this is a different model from a globally coupled,
C2 classical cubic spline.

For interval $i$, the internal polynomial is

$$
v(u) = A_i + B_i\Delta u + C_i\Delta u^2 + D_i\Delta u^3,
\qquad \Delta u = u-u_i.
$$

`Coefficients()` returns copies of those four arrays, synchronizing parameters
and computing coefficients first. Entries through `NKnots()-2` describe the
interpolation intervals. Extrapolation uses the endpoint A/B entries; the final
C/D entries are not extrapolation terms. Editing a returned array does not
change the spline.

## Knot requirements

Supply at least two matching x/y arrays or vectors. Coordinates must be finite
and physical x positions strictly increasing. Logarithmic axes require positive
knots on that axis. Invalid construction throws `std::invalid_argument`.

`SetY()` changes ordinates without moving the x knots. Both overloads validate
the complete input before updating either the spline or its linked TF1, so an
invalid update leaves the previous model intact. Finite negative or zero y is
allowed when LogY is disabled.

## Options

Combine flags with `|`:

| Option | Meaning |
| --- | --- |
| `Default` | Linear x/y coordinates, interior slope limiting enabled |
| `LogX` | Interpolate in $u=\log_{10}(x)$ |
| `LogY` | Interpolate in $v=\log_{10}(y)$ |
| `NonMonotonic` | Disable the interior slope limiter |

The default limiter acts on interior derivatives. It does not reorder ordinates
or enforce a globally monotonic dataset. Explicit endpoint slopes take
precedence and can introduce overshoot. `NonMonotonic` permits overshoot; it
does not turn the local model into a classical C2 spline.

All inputs, `XKnots()`/`YKnots()` and `Eval()` use physical values. Logarithms and
the inverse transformation are internal. For LogY, apply parameter bounds when
{doc}`fitting` through ROOT.

## Worked example

This power-law example also demonstrates how a linked TF1 differs from a copy.
Its extrapolation slope is explained in {doc}`extrapolation`.

```{literalinclude} ../examples/interpolation.cpp
:language: cpp
```

`Eval()` accepts finite coordinates outside the knot range and uses the selected
extrapolation. It throws `std::domain_error` for NaN/infinity and for nonpositive
x with LogX. Very extreme models or unconstrained fitted ordinates can still
produce nonfinite y; valid x alone does not guarantee a numerically valid model.
