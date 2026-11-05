# Ownership, copies and persistence

## One spline, one canonical TF1

`AsTF1()` lazily creates a function owned by the spline and returns a reference.
Once created, its parameters are authoritative. Spline evaluation and ordinate/
slope getters synchronize from them; `SetY` and `SetExtrapolation` update the
owned function. The borrowed reference is valid until the spline is destroyed.

```cpp
auto &linked = spline.AsTF1("correction");
linked.SetParameter(0, 1.2);
// spline.YKnots()[0] now reads 1.2.
TF1 independent = linked;
independent.SetParameter(0, 1.3);
// The original spline still has 1.2.
```

Repeated calls return the same object. `AsTF1()` without arguments preserves its
current name/range; first creation uses name `spline` and the outer knots.
`AsTF1(name)` sets that name and resets the range to the outer knots.
`AsTF1(name,xlow,xhigh)` sets the supplied name/range. Repeated calls preserve
fitted parameters. Changing the range does not move the knots.

## Independent copies

A TF1 value copy owns an independent evaluator and parameter array. `Clone()`
on the owned function uses a copying implementation that also retains the
parameterized evaluator. Copies and these clones can outlive the source spline
and be changed or fitted independently. ROOT's graph-owned fitted copies are
independent as well.

The cloning guarantee concerns the spline-owned function. Explicitly slicing
it into a plain TF1 value loses its specialized Clone override; subsequent
operations on that plain value follow ROOT's own TF1 behavior. Evaluating or
fitting the value copy itself still uses its independent evaluator.

Numerical parameter trials and gradients use a private evaluation cache and do
not leave the spline holding perturbed parameters. The same mutable spline/TF1
must not be accessed concurrently; independent copies have independent caches.

## Saving results

An in-memory owning copy and ROOT file persistence are different operations.
Writing a C++-callable TF1 does not provide a general reconstruction of the
parameterized spline model. ROOT may retain sampled evaluation values; a
successful write or in-range readback is not proof of preserved fitting or
extrapolation behavior.

For reproducible reconstruction, save physical x/y knots, axis options, the
configured endpoint types and slopes, and the fit parameters/covariance needed
by your analysis. Reconstruct the spline explicitly and test a fresh-process
readback over your required range. RSpline itself does not expose a dedicated
model-file serialization API.
