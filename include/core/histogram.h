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
  const size_t kNumOfStatuses = 4;

  // ================================
  // Constants for drawing histograms
  // ================================
  const double kHistogramGraphDimension = 300;  // length and width of histogram graph
  const size_t kLabelSpacingFromHistogram = 10;
  const size_t kLabelSpacingFromHistogramTimes2 = 20;
  const size_t kSpacingFromContainer = 125;

  double upper_bound_for_y_;  // i.e. the highest label value for y axis
  vec2 container_top_right_corner_;
  double time_elapsed_since_outbreak_;

  // Info regarding placement of histogram stuff
  size_t bottom_most_boundary_of_histogram_;
  size_t x_coordinate_of_status_stat_labels_;

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

  /*
   * Draws the bins of the histogram.
   *
   * @param left_boundary_of_histogram The left boundary of the histogram
   * @param top_left_corner_y The y value of the top left corner of the histogram
   */
  void DrawHistogramBins(double left_boundary_of_histogram,
                         double histogram_top_left_corner_y) const;

  /*
   * Draws a bin for a specific health status.
   *
   * @param bin_top_left_x A double of the x coordinate of the top left corner
   *     of the bin
   * @param bin_top_left_y A double of the y coordinate of the top left corner
   *     of the bin
   * @param bin_bottom_right_x A double of the x coordinate of the bottom
   *     right corner of the bin
   * @param bin_bottom_right_y A double of the y coordinate of the bottom
   *     right corner of the bin
   * @param color A vec3 of the color of the health status
   */
  void DrawStatusBin(double bin_top_left_x, double bin_top_left_y,
                     double bin_bottom_right_x, double bin_bottom_right_y,
                     const vec3& color) const;

  /*
   * Draws the labels of the histogram for the axes and title.
   *
   * @param left_boundary_of_histogram The left boundary of the histogram
   * @param top_left_corner_y The y value of the top left corner of the histogram
   */
  void DrawHistogramLabels(double left_boundary_of_histogram,
                           double histogram_top_left_corner_y) const;

  /*
   * Draws the axes labels of the histogram.
   *
   * @param left_boundary_of_histogram The left boundary of the histogram
   * @param top_left_corner_y The y value of the top left corner of the histogram
   */
  void DrawAxesLabels(double left_boundary_of_histogram,
                      double histogram_top_left_corner_y) const;

  /*
   * Draws the labels of the axes bounds.
   *
   * @param left_boundary_of_histogram The left boundary of the histogram
   * @param top_left_corner_y The y value of the top left corner of the histogram
   */
  void DrawBoundsLabels(double left_boundary_of_histogram,
                        double histogram_top_left_corner_y) const;

  /*
   * Draws the status statistics of the population.
   *
   * @param left_boundary_of_histogram The left boundary of the histogram
   */
  void DrawStatusStatistics(double left_boundary_of_histogram) const;

 public:
  Histogram() = default;
  Histogram(const vector<Disease::Person>& people,
            const vec2& container_top_right_corner);

  const map<Status, vector<Disease::Person>>& GetSortedPopulation() const;
  const vector<map<Status, vector<Disease::Person>>>& GetCumulativeInfoOfPopulation() const;
  double GetTimeElapsedSinceOutbreak() const;
  size_t GetBottomMostBoundaryOfHistogram() const;  // i.e. y coordinate below the x axis label
  size_t GetXCoordinateOfStatusStatLabels() const;
  size_t GetYCoordinateOfLastStatusStatLabel() const;

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