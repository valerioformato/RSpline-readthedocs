# Covariance uncertainty bands

`FitErrorBand(function,result)` propagates the fitted parameter covariance:

$$
\sigma_y^2(x) = \nabla_p f(x)^\mathsf{T}\,C\,\nabla_p f(x).
$$

The returned `TGraphErrors` contains physical y and one-standard-deviation
covariance errors, with zero x errors. There is no additional reduced-chi-square
normalization. In LogY mode the physical-y function gradient already contains
the inverse-transform Jacobian; applying it again would be incorrect.

## Required fit state

The helper requires a valid status-0 fit and covariance status 3. Approximate or
forced-positive-definite covariance is rejected. Function and result must have
the same number of finite parameters, matching within
`64 * epsilon * max(1, abs(p), abs(p_fit))`, and complete finite covariance with
nonnegative diagonal entries. The caller is responsible for supplying the same
model; equal parameter arrays cannot establish that by themselves.

The requested function range must be finite and increasing, and positive with
LogX. Range portions outside the knots use the configured extrapolation. Points
are sampled at 100 steps per range/knot segment, including the two outer range
endpoints.

Invalid inputs throw `std::invalid_argument`. A failed fit or absent covariance
must not be interpreted as zero uncertainty.

## Rounding and calculation failures

Each ordinate and gradient must be finite. Variance is accumulated in extended
precision. A negative result is clamped to zero only when its magnitude is at
most `64 * epsilon * sum(abs(gradient_i * C_ij * gradient_j))`; epsilon is double
machine precision. More negative variance, nonfinite calculations and an
unrepresentable uncertainty throw `std::runtime_error` identifying the sampled
coordinate. No partially computed band is returned.

A genuine zero uncertainty remains valid, for example where the model depends
only on fixed parameters. This differs from a failed covariance calculation.

## Interpretation

This is a local parameter-covariance approximation. It is not a prediction band
for future observations, a simultaneous confidence region, or a replacement
for evaluating model choice and systematic uncertainties. Asymmetric data
errors do not automatically imply an asymmetric returned band: this interface
returns symmetric covariance errors around the fitted physical prediction.
