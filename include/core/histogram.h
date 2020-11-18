//
// Created by Megan Lov on 11/8/20.
//
#pragma once

#include "core/infectious_disease.h"
#include <map>

using std::map;

namespace disease {

/*
 * Holds functionality for generating the histograms that
 * are to be displayed in Cinder app/simulator.
 */
class Histogram {
 private:
  // ================================
  // Constants for drawing histograms
  // ================================
  const size_t kHistogramLimit = 3;
  const double kSpacingBetweenHistograms = 50;
  const size_t kLabelSpacingFromHistogram = 8;
  const size_t kSpacingFromContainer = 125;

  // the key is a Status representing the health status
  // the value is a vector representing the people with the specified health status
  map<Status, vector<Disease::Person>> population_sorted_by_status_;

  double upper_bound_for_y_;  // i.e. the highest label value for y axis
  double histogram_graph_dimension_;  // length and width of histogram graph
  double container_height_;
  vec2 container_top_right_corner_;

 public:
  Histogram() = default;
  Histogram(const vector<Disease::Person>& particles,
            double max_number_of_particles, double container_height,
            const vec2& container_top_right_corner);

  const map<Status, vector<Disease::Person>>& GetSortedPopulation() const;

  /*
   * Sorts all the people according to their health status.
   *
   * @param particles The vector of people to sort
   */
  void SortPopulation(const vector<Disease::Person>& population);
};

}  // namespace disease