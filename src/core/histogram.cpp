//
// Created by Megan Lov on 11/8/20.
//
#include "core/histogram.h"

namespace disease {

Histogram::Histogram(const vector<Disease::Person>& people, double container_height,
                     const vec2& container_top_right_corner) {
  upper_bound_for_y_ = people.size();

  container_height_ = container_height;
  container_top_right_corner_ = container_top_right_corner;
}

const map<Status, vector<Disease::Person>>& Histogram::GetSortedPopulation() const {
  return population_sorted_by_status_;
}

void Histogram::SortPopulation(const vector<Disease::Person>& population) {
  population_sorted_by_status_.clear();

  for (const Disease::Person& person : population) {
    population_sorted_by_status_[person.status].push_back(person);
  }
}

void Histogram::UpdatePopulation(const vector<Disease::Person>& updated_population) {
  SortPopulation(updated_population);
}

void Histogram::DrawHistogram() const {
  // Draws the background of histogram
  double left_boundary_of_histogram = container_top_right_corner_.x + kSpacingFromContainer;
  DrawHistogramBackground(left_boundary_of_histogram, container_top_right_corner_.y);
}

vector<vec2> Histogram::DrawHistogramBackground(double left_boundary_of_histogram,
                                                double histogram_top_left_corner_y) const {
  vec2 pixel_top_left = vec2(left_boundary_of_histogram, histogram_top_left_corner_y);
  vec2 pixel_bottom_right =
      pixel_top_left + vec2(kHistogramGraphDimension, kHistogramGraphDimension);
  ci::Rectf pixel_bounding_box(pixel_top_left, pixel_bottom_right);

  ci::gl::color(ci::Color("blue"));
  ci::gl::drawSolidRect(pixel_bounding_box);

  vector<vec2> corner_positions;
  corner_positions.push_back(pixel_top_left);
  corner_positions.push_back(pixel_bottom_right);

  return corner_positions;
}

}  // namespace disease
