#pragma once

namespace timing {

/// simple helper to provide time in seconds represented as doubles.
double tic();

/// Compute ellapsed time from t0.
double toc(double t0);

}  // namespace timing
