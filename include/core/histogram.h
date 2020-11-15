//
// Created by Megan Lov on 11/8/20.
//
#pragma once

#include "core/ideal_gas.h"

#include <map>
#include <vector>

using std::map;
using std::vector;

namespace idealgas {

class Histogram {
 private:
  const size_t kNumOfBins = 5;
  const size_t kHistogramLimit = 3;
  const double kSpacingBetweenHistograms = 50;
  const size_t kLabelSpacingFromHistogram = 8;
  const size_t kSpacingFromContainer = 125;

  // the key is a double representing mass
  // the value is a vector representing the Particles with the specified mass
  map<double, vector<Particle>> particles_sorted_by_mass_;

  double upper_bound_for_y_;  // i.e. the highest label value for y axis
  double histogram_graph_dimension_;  // length and width of histogram graph
  double container_height_;
  vec2 container_top_right_corner_;

  double max_speed_;  // will be upper bound for x

 public:
  Histogram() = default;
  Histogram(const vector<Particle>& particles,
            double max_number_of_particles, double container_height,
            const vec2& container_top_right_corner);

  const map<double, vector<Particle>>& GetSortedParticles() const;
  double GetMaxSpeed() const;

  /*
   * Sorts all the particles according to mass and finds the max particle speed.
   *
   * @param particles The vector of Particles to sort
   */
  void SortParticles(const vector<Particle>& particles);

  /*
   * Sorts particles of a certain mass into bins according to their particle velocities.
   *
   * @param vector_for_mass A vector that contains all the particles for a particular mass
   * @return a vector containing a vector of Particles representing the all the particles
   *     for a bin.
   */
  vector<vector<Particle>> SortIntoBins(const vector<Particle>& vector_for_mass) const;

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
   * @param bins_with_particles The vector of vector of Particles holding the particles for
   *     each bin of the histogram
   * @param left_boundary_of_histogram The left boundary of the histogram
   * @param top_left_corner_y The y value of the top left corner of the histogram
   * @return A vector holding the vec2 values of the top left and bottom right
   *     corners of the histogram, in that order
   */
  void DrawHistogramBins(vector<vector<Particle>> bins_with_particles,
                         double left_boundary_of_histogram,
                         double histogram_top_left_corner_y) const;

  /*
   * Draws the labels of the histogram for the axes and title.
   *
   * @param particles The vector of particles for a single bin (all of same mass)
   * @param left_boundary_of_histogram The left boundary of the histogram
   * @param top_left_corner_y The y value of the top left corner of the histogram
   */
  void DrawHistogramLabels(vector<Particle> particles,
                           double left_boundary_of_histogram,
                           double histogram_top_left_corner_y) const;

  /*
   * Updates the particle information.
   *
   * @param updated_particles The updated particles
   */
  void UpdateParticles(const vector<Particle>& updated_particles);

  /*
   * Draws the histograms.
   */
  void DrawHistograms() const;
};

}  // namespace idealgas