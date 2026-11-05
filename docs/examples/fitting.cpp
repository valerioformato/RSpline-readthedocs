#include <TFitResult.h>
#include <TGraphErrors.h>
#include <cmath>
#include <memory>
#include <rspline/Spline3.h>
#include <vector>

int main() {
  using namespace RSpline;
  const auto options = SplineOptions::LogX | SplineOptions::LogY | SplineOptions::NonMonotonic;
  const std::vector<double> x{1., 4., 16.};
  Spline3 truth(x, std::vector<double>{1., 2., 1.5}, options);
  TGraphErrors data;
  for (int i = 0; i < 49; ++i) {
    const double position = std::pow(16., i / 48.);
    data.SetPoint(i, position, truth.Eval(position) + .005 * std::sin(i));
    data.SetPointError(i, 0., .05);
  }

  std::unique_ptr<TF1> clone;
  {
    Spline3 spline(x, std::vector<double>{1.1, 1.9, 1.6}, options);
    auto &function = spline.AsTF1("positive_fit", 1., 16.);
    // Native LogY fit parameters are physical y values: keep them positive.
    // These bounds suit this illustrative dataset; choose bounds for your model.
    for (size_t i = 0; i < spline.NKnots(); ++i)
      function.SetParLimits(i, .01, 100.);
    auto result = data.Fit(&function, "SQN0");
    if (!result.Get() || int(result) != 0 || !result->IsValid() || result->CovMatrixStatus() != 3)
      return 1;
    const auto band = spline.FitErrorBand(function, *result);
    if (band.GetN() == 0 || band.GetErrorY(0) <= 0.)
      return 2;

    if (std::abs(spline.YKnots()[0] - function.GetParameter(0)) > 1.e-12)
      return 3;
    clone.reset(static_cast<TF1 *>(function.Clone("fit_copy")));
  }
  // The owning clone remains parameterized after the source spline is destroyed.
  clone->SetParameter(0, 1.2);
  return std::abs(clone->Eval(1.) - 1.2) < 1.e-9 ? 0 : 4;
}
