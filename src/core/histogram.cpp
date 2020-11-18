//
// Created by Megan Lov on 11/8/20.
//
#include "core/histogram.h"

namespace disease {

Histogram::Histogram(const vector<Disease::Person>& people,
                     const vec2& container_top_right_corner) {
  container_top_right_corner_ = container_top_right_corner;
  time_elapsed_since_outbreak_ = 0;

  SortPopulation(people);
}

const map<Status, vector<Disease::Person>>& Histogram::GetSortedPopulation() const {
  return population_sorted_by_status_;
}

void Histogram::SortPopulation(const vector<Disease::Person>& population) {
  population_sorted_by_status_.clear();

  for (const Disease::Person& person : population) {
    population_sorted_by_status_[person.status].push_back(person);
  }

  upper_bound_for_y_ = population.size();
}

void Histogram::Update(const vector<Disease::Person>& updated_population, size_t time_passed) {
  SortPopulation(updated_population);
  time_elapsed_since_outbreak_ = time_passed;
  cumulative_info_of_population_.push_back(population_sorted_by_status_);
}

void Histogram::DrawHistogram() const {
  // Draws the background of histogram
  double left_boundary_of_histogram = container_top_right_corner_.x + kSpacingFromContainer;
  DrawHistogramBackground(left_boundary_of_histogram, container_top_right_corner_.y);

  // Draws the bins of histogram
  DrawHistogramBins(left_boundary_of_histogram, container_top_right_corner_.y);
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

void Histogram::DrawHistogramBins(double left_boundary_of_histogram,
                                  double histogram_top_left_corner_y) const {
  double x_increment = kHistogramGraphDimension / time_elapsed_since_outbreak_;
  double y_increment = kHistogramGraphDimension / upper_bound_for_y_;

  double current_left_side_bin_x = left_boundary_of_histogram;

  // Loop through vector; each element represents one frame, which is one bin of the histogram
  for (const map<Status, vector<Disease::Person>>& info_for_frame : cumulative_info_of_population_) {
    if (info_for_frame.count(Status::kInfectious) != 0) {
      vec2 infectious_bin_top_left =
          vec2(current_left_side_bin_x,histogram_top_left_corner_y + kHistogramGraphDimension -
                     (info_for_frame.at(Status::kInfectious).size() * y_increment));
      current_left_side_bin_x += x_increment;
      vec2 infectious_bin_bottom_right =
          vec2(current_left_side_bin_x,histogram_top_left_corner_y + kHistogramGraphDimension);

      ci::Rectf bin_box(infectious_bin_top_left, infectious_bin_bottom_right);
      ci::gl::color(ci::Color("red"));
      ci::gl::drawSolidRect(bin_box);
    }

    if (info_for_frame.count(Status::kRemoved) != 0) {
      vec2 removed_bin_top_left =
          vec2(current_left_side_bin_x,histogram_top_left_corner_y);
      current_left_side_bin_x += x_increment;
      vec2 removed_bin_bottom_right =
          vec2(current_left_side_bin_x,histogram_top_left_corner_y +
                                       (info_for_frame.at(Status::kRemoved).size() * y_increment));

      ci::Rectf bin_box(removed_bin_top_left, removed_bin_bottom_right);
      ci::gl::color(ci::Color("gray"));
      ci::gl::drawSolidRect(bin_box);
    }
  }
}

}  // namespace disease
