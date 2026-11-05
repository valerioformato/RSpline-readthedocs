#include <cmath>
#include <rspline/Spline3.h>
#include <vector>

int main() {
  using namespace RSpline;
  Spline3 spline(std::vector<double>{1., 10., 100.}, std::vector<double>{2., 20., 200.},
                 SplineOptions::LogX | SplineOptions::LogY | SplineOptions::NonMonotonic);
  // A transformed slope of 1 means y is proportional to x.
  spline.SetExtrapolation(SplineExtrapolationRange::Below, SplineExtrapolationType::LinearFree, 1.);
  spline.SetExtrapolation(SplineExtrapolationRange::Above, SplineExtrapolationType::LinearFree, 1.);
  if (std::abs(spline.Eval(5.) - 10.) > 1.e-10 || std::abs(spline.Eval(200.) - 400.) > 1.e-9)
    return 1;

  auto &linked = spline.AsTF1("power_law", .5, 200.);
  TF1 independent = linked;
  linked.SetParameter(1, 25.);
  if (std::abs(spline.Eval(10.) - 25.) > 1.e-10 || std::abs(independent.Eval(10.) - 20.) > 1.e-10)
    return 2;
  const auto coefficients = spline.Coefficients();
  return coefficients[0].size() == spline.NKnots() ? 0 : 3;
}
