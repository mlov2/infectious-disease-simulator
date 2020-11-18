//
// Created by Megan Lov on 11/8/20.
//
#include "core/histogram.h"

namespace disease {

Histogram::Histogram(const vector<Disease::Person>& particles,
                     double max_number_of_particles, double container_height,
                     const vec2& container_top_right_corner) {
  upper_bound_for_y_ = max_number_of_particles;

  container_height_ = container_height;
  container_top_right_corner_ = container_top_right_corner;
  double total_spacing_between_histograms = (kHistogramLimit - 1) * kSpacingBetweenHistograms;
  histogram_graph_dimension_ = (container_height - total_spacing_between_histograms) / kHistogramLimit;
}

const map<Status, vector<Disease::Person>>& Histogram::GetSortedPopulation() const {
  return population_sorted_by_status_;
}

}  // namespace disease
