# Troubleshooting

## ROOT or compiler cannot be found

Configure and build in the same ROOT/compiler environment. Point `ROOT_DIR`
at the actual installed CMake package if discovery finds a different stack.
Create a fresh build directory after changing machines, compiler or ROOT.
An old Ninja cache can invoke a different CMake/runtime from the current shell.

A `GLIBCXX_* not found` failure before compilation commonly indicates that a
cached tool is loading the wrong C++ runtime. Activate its matching environment
before configuring or building.

## Logging header errors

With external dependencies, use a compatible fmt/spdlog pair. Inspect the include
paths in the failing compiler command: an umbrella LCG view include directory
can place another logging stack before the selected packages. Errors mentioning
missing fmt types can therefore arise even when `find_package` selected the
intended versions. Avoid mixing installations and point ROOT at its actual
package prefix when a view alias introduces conflicting umbrella headers.

## FetchContent is offline

`FETCHCONTENT_FULLY_DISCONNECTED=ON` assumes dependency sources already exist.
Turn it off for the first configure after adding a dependency or using a fresh
build directory; restore offline operation only after sources are populated.
A missing target can otherwise be the consequence of a skipped download.

## Invalid knots or coordinates

Construction requires at least two matching finite knots, with strictly
increasing x. Logarithmic axes require positive knots. `SetY` validates all
replacement ordinates before mutation. Evaluation rejects nonfinite x, and
nonpositive x with LogX. Check physical versus logarithmic coordinates rather
than silently clipping a bad input.

## LogY fitting produces invalid ordinates

TF1 parameters are physical y, even with LogY. Apply positive bounds to free
ordinate parameters. Direct TF1 writes bypass `SetY` validation; the caller
controls minimizer bounds and the suitability of the model.

## Error-band generation throws

Check fit status, validity, covariance status, parameter identity and the
function range first. Do not replace the error with a zero-width band. A
materially negative or nonfinite propagated variance warrants checking the
fit, parameter conditioning and model. See {doc}`uncertainties`.

## My spline did not change after fitting

Check whether you wrote `auto function = spline.AsTF1(...)`. That creates an
independent TF1. Use `auto &function = ...` to fit the canonical representation.
Editing a graph-owned fitted copy likewise leaves the original spline intact.
