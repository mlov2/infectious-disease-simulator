//
// Created by Megan Lov on 11/8/20.
//
#include "core/histogram.h"

namespace idealgas {

Histogram::Histogram(const vector<Particle>& particles,
                     double max_number_of_particles, double container_height,
                     const vec2& container_top_right_corner) {
  max_speed_ = 0;
  upper_bound_for_y_ = max_number_of_particles;

  container_height_ = container_height;
  container_top_right_corner_ = container_top_right_corner;
  double total_spacing_between_histograms = (kHistogramLimit - 1) * kSpacingBetweenHistograms;
  histogram_graph_dimension_ = (container_height - total_spacing_between_histograms) / kHistogramLimit;

  SortParticles(particles);
}

const map<double, vector<Particle>>& Histogram::GetSortedParticles() const {
  return particles_sorted_by_mass_;
}

double Histogram::GetMaxSpeed() const {
  return max_speed_;
}

void Histogram::SortParticles(const vector<Particle> &particles) {
  particles_sorted_by_mass_.clear();
  max_speed_ = 0;

  for (const Particle& particle: particles) {
    particles_sorted_by_mass_[particle.GetMass()].push_back(particle);

    if (particle.GetSpeed() > max_speed_) {
      max_speed_ = particle.GetSpeed();
    }
  }
}

void Histogram::UpdateParticles(const vector<Particle>& updated_particles) {
  SortParticles(updated_particles);
}

void Histogram::DrawHistograms() const {
  size_t num_of_masses = particles_sorted_by_mass_.size();

  if (num_of_masses > kHistogramLimit) {
    num_of_masses = kHistogramLimit;
  }

  double histogram_top_left_corner_y = container_top_right_corner_.y;
  // double bin_top_left_y;
  for (auto it = particles_sorted_by_mass_.begin(); it != particles_sorted_by_mass_.end(); it++) {
    //double mass = it -> first;
    vector<Particle> particles = it -> second;

    vector<vector<Particle>> bins_with_particles = SortIntoBins(particles);

    // Draws the background of histogram
    double left_boundary_of_histogram = container_top_right_corner_.x + kSpacingFromContainer;
    DrawHistogramBackground(left_boundary_of_histogram, histogram_top_left_corner_y);

    // Draw bins
    DrawHistogramBins(bins_with_particles, left_boundary_of_histogram, histogram_top_left_corner_y);

    // Draw labels
    DrawHistogramLabels(particles, left_boundary_of_histogram, histogram_top_left_corner_y);

    histogram_top_left_corner_y += (histogram_graph_dimension_ + kSpacingBetweenHistograms);
  }
}

vector<vector<Particle>> Histogram::SortIntoBins(const vector<Particle>& vector_for_mass) const {
  vector<vector<Particle>> particles_sorted_into_bins;

  double speed_per_bin = max_speed_ / kNumOfBins;

  double bin_lower_bound = 0;
  for (double i = speed_per_bin; i <= max_speed_; i += speed_per_bin) {
    vector<Particle> particles_in_bin;

    double epsilon = 0.001;
    for (const Particle& particle : vector_for_mass) {
      if (particle.GetSpeed() == 0 && bin_lower_bound == 0) {
        particles_in_bin.push_back(particle);
      } else if (((particle.GetSpeed() - bin_lower_bound) > 0)
           && ((particle.GetSpeed() - i) < 0 || (abs(particle.GetSpeed() - i) < epsilon))) {
        particles_in_bin.push_back(particle);
      }
    }

    particles_sorted_into_bins.push_back(particles_in_bin);
    bin_lower_bound += speed_per_bin;
  }

  return particles_sorted_into_bins;
}

vector<vec2> Histogram::DrawHistogramBackground(double left_boundary_of_histogram,
                                                double histogram_top_left_corner_y) const {
  vec2 pixel_top_left = vec2(left_boundary_of_histogram, histogram_top_left_corner_y);
  vec2 pixel_bottom_right =
      pixel_top_left + vec2(histogram_graph_dimension_, histogram_graph_dimension_);
  ci::Rectf pixel_bounding_box(pixel_top_left, pixel_bottom_right);

  ci::gl::color(ci::Color("black"));
  ci::gl::drawSolidRect(pixel_bounding_box);

  vector<vec2> corner_positions;
  corner_positions.push_back(pixel_top_left);
  corner_positions.push_back(pixel_bottom_right);

  return corner_positions;
}

void Histogram::DrawHistogramBins(vector<vector<Particle>> bins_with_particles,
                                  double left_boundary_of_histogram,
                                  double histogram_top_left_corner_y) const {
  double y_increment = histogram_graph_dimension_ / upper_bound_for_y_;
  double x_increment = 0;
  for (const vector<Particle>& bin : bins_with_particles) {
    vec2 bin_top_left = vec2(left_boundary_of_histogram + x_increment,
                             histogram_top_left_corner_y + histogram_graph_dimension_ - (bin.size() * y_increment));
    x_increment += histogram_graph_dimension_ / kNumOfBins;
    vec2 bin_bottom_right = vec2(left_boundary_of_histogram + x_increment,
                                 histogram_top_left_corner_y + histogram_graph_dimension_);
    ci::Rectf bin_box(bin_top_left, bin_bottom_right);

    //std::string color = bin[0].GetColor();
    ci::gl::color(ci::Color("gray"));
    ci::gl::drawSolidRect(bin_box);
  }
}

void Histogram::DrawHistogramLabels(vector<Particle> particles,
                                    double left_boundary_of_histogram,
                                    double histogram_top_left_corner_y) const {
  // Label title
  double x_centered_color_label = (left_boundary_of_histogram + (left_boundary_of_histogram + histogram_graph_dimension_)) /2;
  double y_centered_color_label = histogram_top_left_corner_y - kLabelSpacingFromHistogram;
  ci::gl::drawStringCentered(
      "Particle of mass: " + std::to_string((int) particles[0].GetMass()),
      glm::vec2(x_centered_color_label, y_centered_color_label), ci::Color("black"));

  // Label axes
  double x_centered_x_axis_label = (left_boundary_of_histogram + (left_boundary_of_histogram + histogram_graph_dimension_)) /2;
  double y_centered_x_axis_label = histogram_top_left_corner_y + histogram_graph_dimension_ + kLabelSpacingFromHistogram;
  ci::gl::drawStringCentered(
      "Speed",
      glm::vec2(x_centered_x_axis_label, y_centered_x_axis_label), ci::Color("black"));

  double x_centered_y_axis_label = (container_top_right_corner_.x + left_boundary_of_histogram) / 2;
  double y_centered_y_axis_label = (histogram_top_left_corner_y + (histogram_top_left_corner_y + histogram_graph_dimension_)) / 2;
  ci::gl::drawStringCentered(
      "Num of particles",
      glm::vec2(x_centered_y_axis_label, y_centered_y_axis_label), ci::Color("black"));

  // Label bounds of axes
  ci::gl::drawString(std::to_string(max_speed_),
                     vec2(left_boundary_of_histogram + histogram_graph_dimension_ + kLabelSpacingFromHistogram,
                          histogram_top_left_corner_y + histogram_graph_dimension_), ci::Color("black"));

  ci::gl::drawStringCentered("0",
                             vec2(left_boundary_of_histogram - kLabelSpacingFromHistogram,
                                  histogram_top_left_corner_y + histogram_graph_dimension_), ci::Color("black"));

  ci::gl::drawStringCentered(std::to_string((int) upper_bound_for_y_),
                             vec2(left_boundary_of_histogram - kLabelSpacingFromHistogram,
                                  histogram_top_left_corner_y), ci::Color("black"));
}

}
