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
  const double kHistogramGraphDimension = 400;  // length and width of histogram graph
  //const size_t kLabelSpacingFromHistogram = 8;
  const size_t kSpacingFromContainer = 125;
  //const size_t kUpdatesPerSecond = 50;

  double upper_bound_for_y_;  // i.e. the highest label value for y axis
  vec2 container_top_right_corner_;
  size_t time_elapsed_since_outbreak_;

  // the key is a Status representing the health status
  // the value is a vector representing the people with the specified health status
  map<Status, vector<Disease::Person>> population_sorted_by_status_;

  // Contains info of sorted particles for every frame
  vector<map<Status, vector<Disease::Person>>> cumulative_info_of_population_;

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
  Histogram(const vector<Disease::Person>& people,
            const vec2& container_top_right_corner);

  const map<Status, vector<Disease::Person>>& GetSortedPopulation() const;

  /*
   * Sorts all the people according to their health status.
   *
   * @param particles The vector of people to sort
   */
  void SortPopulation(const vector<Disease::Person>& population);

  /*
   * Updates the information of everyone in the population and
   * of the time passed.
   *
   * @param updated_population The updated population
   * @param time_passed The time elapsed since outbreak started
   */
  void Update(const vector<Disease::Person>& updated_population, size_t time_passed);

  /*
   * Draws the histogram.
   */
  void DrawHistogram() const;
};

}  // namespace disease