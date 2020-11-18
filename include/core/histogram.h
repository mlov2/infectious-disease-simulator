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
  const double kHistogramGraphDimension = 200;  // length and width of histogram graph
  //const size_t kLabelSpacingFromHistogram = 8;
  const size_t kSpacingFromContainer = 125;

  // the key is a Status representing the health status
  // the value is a vector representing the people with the specified health status
  map<Status, vector<Disease::Person>> population_sorted_by_status_;

  double upper_bound_for_y_;  // i.e. the highest label value for y axis
  double container_height_;
  vec2 container_top_right_corner_;

  /*
   * Draws the background of the histogram (i.e. the graph).
   *
   * @param left_boundary_of_histogram The left boundary of the histogram
   * @param top_left_corner_y The y value of the top left corner of the histogram
   * @return A vector holding the vec2 values of the top left and bottom right
   *     corners of the histogram, in that order
   */
  vector<vec2> DrawHistogramBackground(double left_boundary_of_histogram,
                                       double histogram_top_left_corner_y) const;

 public:
  Histogram() = default;
  Histogram(const vector<Disease::Person>& people, double container_height,
            const vec2& container_top_right_corner);

  const map<Status, vector<Disease::Person>>& GetSortedPopulation() const;

  /*
   * Sorts all the people according to their health status.
   *
   * @param particles The vector of people to sort
   */
  void SortPopulation(const vector<Disease::Person>& population);

  /*
   * Updates the information of everyone in the population.
   *
   * @param updated_population The updated population
   */
  void UpdatePopulation(const vector<Disease::Person>& updated_population);

  /*
   * Draws the histogram.
   */
  void DrawHistogram() const;
};

}  // namespace disease