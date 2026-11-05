# Endpoint slopes and extrapolation

Both endpoints start as `Flat`. Configure them independently with
`SetExtrapolation(SplineExtrapolationRange::Below/Above, type, initial_value)`.

| Type | Endpoint derivative | ROOT fit behavior |
| --- | --- | --- |
| `Flat` | Zero | Slope parameter fixed; constant extrapolation |
| `Linear` | Adjacent knot secant | Slope parameter fixed; derivative follows the knot values |
| `LinearFree` | Supplied `initial_value` | Explicit slope parameter initially free |

The prescribed derivative also controls the cubic endpoint behavior inside the
knot range. Changing it can therefore change interpolation near that endpoint,
as well as the extrapolated tail.

## Which derivative?

Slopes are $dv/du$ in the selected interpolation coordinates:

| Axes | Slope |
| --- | --- |
| Linear x/y | $dy/dx$ |
| LogX | $dy/d\log_{10}(x)$ |
| LogY | $d\log_{10}(y)/dx$ |
| LogX and LogY | $d\log_{10}(y)/d\log_{10}(x)$ |

A log-log slope of 1 therefore extrapolates a proportional power law. A fixed
physical derivative is generally a different constraint from a fixed log-axis
slope; transform it deliberately.

## Fix a custom slope during fitting

Choose `LinearFree` to make the supplied derivative active, then fix its TF1
parameter explicitly:

```cpp
spline.SetExtrapolation(RSpline::SplineExtrapolationRange::Above,
                       RSpline::SplineExtrapolationType::LinearFree, -2.7);
auto &function = spline.AsTF1("spectrum");
function.FixParameter(spline.NKnots() + 1, -2.7);
```

The lower slope index is `NKnots()`, the upper `NKnots()+1`. Using `Linear` with
an `initial_value` does not fix that supplied derivative: `Linear` computes the
adjacent secant instead. `ExtrapolationSlope()` reads the stored setting/current
TF1 parameter; for Flat/Linear it is not a calculation of the actual derivative.

Changing extrapolation updates an existing owned TF1 in place, preserving its
address, other parameter settings and the independence of earlier copies.
Extrapolation is a model choice; successful fitting does not validate a distant
extrapolated tail.
