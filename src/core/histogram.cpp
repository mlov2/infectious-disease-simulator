//
// Created by Megan Lov on 11/8/20.
//
#include "core/histogram.h"

namespace disease {

Histogram::Histogram(const vector<Disease::Person>& people,
                     const vec2& container_top_right_corner) {
  container_top_right_corner_ = container_top_right_corner;
  time_elapsed_since_outbreak_ = 0;

  bottom_most_boundary_of_histogram_ = container_top_right_corner.y + kHistogramGraphDimension +
                                       kLabelSpacingFromHistogramTimes2 + kLabelSpacingFromHistogram;
  x_coordinate_of_status_stat_labels_ = container_top_right_corner_.x +
      kSpacingFromContainer + kHistogramGraphDimension +
      kLabelSpacingFromHistogramTimes2 + kLabelSpacingFromHistogramTimes2;

  SortPopulation(people);
}

const map<Status, vector<Disease::Person>>& Histogram::GetSortedPopulation() const {
  return population_sorted_by_status_;
}

double Histogram::GetTimeElapsedSinceOutbreak() const {
  return time_elapsed_since_outbreak_;
}

const vector<map<Status, vector<Disease::Person>>>& Histogram::GetCumulativeInfoOfPopulation() const {
  return cumulative_info_of_population_;
}

size_t Histogram::GetBottomMostBoundaryOfHistogram() const {
  return bottom_most_boundary_of_histogram_;
}

size_t Histogram::GetXCoordinateOfStatusStatLabels() const {
  return x_coordinate_of_status_stat_labels_;
}

size_t Histogram::GetYCoordinateOfLastStatusStatLabel() const {
  return container_top_right_corner_.y + kLabelSpacingFromHistogram +
      (kNumOfStatuses - 1) * kLabelSpacingFromHistogramTimes2;
}

void Histogram::SortPopulation(const vector<Disease::Person>& population) {
  population_sorted_by_status_.clear();

  // Sort population by status
  for (const Disease::Person& person : population) {
    population_sorted_by_status_[person.status].push_back(person);
  }

  upper_bound_for_y_ = population.size();
}

void Histogram::Update(const vector<Disease::Person>& updated_population, size_t time_passed) {
  SortPopulation(updated_population);

  if (population_sorted_by_status_.size() == 0) {
    time_elapsed_since_outbreak_ = time_passed;
    cumulative_info_of_population_.clear();
  } else if (population_sorted_by_status_[Status::kSymptomatic].size() != 0 ||
             population_sorted_by_status_[Status::kAsymptomatic].size() != 0) {
    time_elapsed_since_outbreak_ = time_passed;
    cumulative_info_of_population_.push_back(population_sorted_by_status_);
  }
}

void Histogram::DrawHistogram() const {
  // Draws the background of histogram
  double left_boundary_of_histogram = container_top_right_corner_.x + kSpacingFromContainer;
  DrawHistogramBackground(left_boundary_of_histogram, container_top_right_corner_.y);

  // Draws the bins of histogram
  DrawHistogramBins(left_boundary_of_histogram, container_top_right_corner_.y);

  // Draws the labels of histogram
  DrawHistogramLabels(left_boundary_of_histogram, container_top_right_corner_.y);
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
    if (info_for_frame.count(Status::kSymptomatic) != 0) {
      DrawStatusBin(current_left_side_bin_x,
                    histogram_top_left_corner_y + kHistogramGraphDimension -
                    (info_for_frame.at(Status::kSymptomatic).size() * y_increment),
                    current_left_side_bin_x + x_increment,
                    histogram_top_left_corner_y + kHistogramGraphDimension,
                    info_for_frame.at(Status::kSymptomatic).front().color);
    }

    if (info_for_frame.count(Status::kAsymptomatic) != 0) {
      double bin_top_left_y = histogram_top_left_corner_y + kHistogramGraphDimension -
                              (info_for_frame.at(Status::kSymptomatic).size() * y_increment) -
                              (info_for_frame.at(Status::kAsymptomatic).size() * y_increment);
      double bin_bottom_right_y = histogram_top_left_corner_y + kHistogramGraphDimension -
                                  (info_for_frame.at(Status::kSymptomatic).size() * y_increment);

      DrawStatusBin(current_left_side_bin_x,bin_top_left_y,
                    current_left_side_bin_x + x_increment, bin_bottom_right_y,
                    info_for_frame.at(Status::kAsymptomatic).front().color);
    }

    if (info_for_frame.count(Status::kRemoved) != 0) {
      DrawStatusBin(current_left_side_bin_x, histogram_top_left_corner_y,
                    current_left_side_bin_x + x_increment,
                    histogram_top_left_corner_y +
                    (info_for_frame.at(Status::kRemoved).size() * y_increment),
                    info_for_frame.at(Status::kRemoved).front().color);
    }

    current_left_side_bin_x += x_increment;
  }
}

void Histogram::DrawStatusBin(double bin_top_left_x, double bin_top_left_y,
                               double bin_bottom_right_x, double bin_bottom_right_y,
                               const vec3& color) const {
  vec2 removed_bin_top_left =
      vec2(bin_top_left_x, bin_top_left_y);
  vec2 removed_bin_bottom_right =
      vec2(bin_bottom_right_x, bin_bottom_right_y);

  ci::Rectf bin_box(removed_bin_top_left, removed_bin_bottom_right);
  ci::gl::color(ci::Color(color.x, color.y, color.z));
  ci::gl::drawSolidRect(bin_box);
}

void Histogram::DrawHistogramLabels(double left_boundary_of_histogram,
                                    double histogram_top_left_corner_y) const {
  // Label title
  double x_centered_color_label = (left_boundary_of_histogram + (left_boundary_of_histogram + kHistogramGraphDimension)) /2;
  double y_centered_color_label = histogram_top_left_corner_y - kLabelSpacingFromHistogram;
  ci::gl::drawStringCentered(
      "Population Status Over Time",
      glm::vec2(x_centered_color_label, y_centered_color_label), ci::Color("black"));

  // Label axes
  DrawAxesLabels(left_boundary_of_histogram, histogram_top_left_corner_y);

  // Label bounds of axes
  DrawBoundsLabels(left_boundary_of_histogram, histogram_top_left_corner_y);

  DrawStatusStatistics();
}

void Histogram::DrawAxesLabels(double left_boundary_of_histogram,
                               double histogram_top_left_corner_y) const {
  double x_centered_x_axis_label = (left_boundary_of_histogram + (left_boundary_of_histogram + kHistogramGraphDimension)) /2;
  double y_centered_x_axis_label = histogram_top_left_corner_y + kHistogramGraphDimension +
      kLabelSpacingFromHistogramTimes2 + kLabelSpacingFromHistogram;
  ci::gl::drawStringCentered(
      "Time Since Outbreak",
      glm::vec2(x_centered_x_axis_label, y_centered_x_axis_label), ci::Color("black"));

  double x_centered_y_axis_label = (container_top_right_corner_.x + left_boundary_of_histogram) / 2;
  double y_centered_y_axis_label = (histogram_top_left_corner_y + (histogram_top_left_corner_y + kHistogramGraphDimension)) / 2;
  ci::gl::drawStringCentered(
      "Num of people",
      glm::vec2(x_centered_y_axis_label, y_centered_y_axis_label), ci::Color("black"));
}

void Histogram::DrawBoundsLabels(double left_boundary_of_histogram,
                                 double histogram_top_left_corner_y) const {
  ci::gl::drawString(std::to_string(int(time_elapsed_since_outbreak_)),
                     vec2(left_boundary_of_histogram + kHistogramGraphDimension + kLabelSpacingFromHistogram,
                          histogram_top_left_corner_y + kHistogramGraphDimension), ci::Color("black"));

  ci::gl::drawString(std::to_string(int(time_elapsed_since_outbreak_ / 2)),
                     vec2(left_boundary_of_histogram + kHistogramGraphDimension / 2,
                          histogram_top_left_corner_y + kHistogramGraphDimension + kLabelSpacingFromHistogram),
                     ci::Color("black"));

  ci::gl::drawStringCentered("0",
                             vec2(left_boundary_of_histogram - kLabelSpacingFromHistogram,
                                  histogram_top_left_corner_y + kHistogramGraphDimension), ci::Color("black"));

  ci::gl::drawStringCentered(std::to_string(int(upper_bound_for_y_)),
                             vec2(left_boundary_of_histogram - kLabelSpacingFromHistogram,
                                  histogram_top_left_corner_y), ci::Color("black"));
}

void Histogram::DrawStatusStatistics() const {
  size_t num_susceptible = 0;
  size_t num_symptomatic = 0;
  size_t num_asymptomatic = 0;
  size_t num_removed = 0;

  if (population_sorted_by_status_.count(Status::kSusceptible) != 0) {
    num_susceptible = population_sorted_by_status_.at(Status::kSusceptible).size();
  }
  if (population_sorted_by_status_.count(Status::kSymptomatic) != 0) {
    num_symptomatic = population_sorted_by_status_.at(Status::kSymptomatic).size();
  }
  if (population_sorted_by_status_.count(Status::kAsymptomatic) != 0) {
    num_asymptomatic = population_sorted_by_status_.at(Status::kAsymptomatic).size();
  }
  if (population_sorted_by_status_.count(Status::kRemoved) != 0) {
    num_removed = population_sorted_by_status_.at(Status::kRemoved).size();
  }

  size_t label_spacing_y = container_top_right_corner_.y + kLabelSpacingFromHistogram;
  ci::gl::drawString("Number of People Susceptible: " + std::to_string(num_susceptible),
                    vec2(x_coordinate_of_status_stat_labels_, label_spacing_y), ci::Color("blue"));

  label_spacing_y += kLabelSpacingFromHistogramTimes2;
  ci::gl::drawString("Number of People Symptomatic: " + std::to_string(num_symptomatic),
                     vec2(x_coordinate_of_status_stat_labels_, label_spacing_y), ci::Color("red"));

  label_spacing_y += kLabelSpacingFromHistogramTimes2;
  ci::gl::drawString("Number of People Asymptomatic: " + std::to_string(num_asymptomatic),
                     vec2(x_coordinate_of_status_stat_labels_, label_spacing_y), ci::Color("black"));

  label_spacing_y += kLabelSpacingFromHistogramTimes2;
  ci::gl::drawString("Number of People Removed: " + std::to_string(num_removed),
                     vec2(x_coordinate_of_status_stat_labels_, label_spacing_y),ci::Color("gray"));
}

}  // namespace disease
