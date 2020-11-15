//
// Created by Megan Lov on 11/8/20.
//
#include "core/histogram.h"

#include <catch2/catch.hpp>

using idealgas::Histogram;
using idealgas::IdealGas;

TEST_CASE("Check particles get sorted") {
  Histogram histogram;
  Particle particle;

  SECTION("One mass type") {
    vector<Particle> all_particles;

    for (size_t i = 0; i < 3; i++) {
      particle.SetMass(10);
      particle.SetSpeed(i);
      all_particles.push_back(particle);
    }

    histogram.SortParticles(all_particles);

    map<double, vector<Particle>> actual_sorted_particles = histogram.GetSortedParticles();

    REQUIRE(histogram.GetSortedParticles().size() == 1);
    REQUIRE(actual_sorted_particles[10].size() == 3);
    REQUIRE(histogram.GetMaxSpeed() == 2);
  }

  SECTION("Two mass types") {
    vector<Particle> all_particles;

    for (size_t i = 0; i < 3; i++) {
      particle.SetMass(10);
      particle.SetSpeed(i);
      all_particles.push_back(particle);
    }

    particle.SetMass(15);
    particle.SetSpeed(7);
    all_particles.push_back(particle);

    histogram.SortParticles(all_particles);

    map<double, vector<Particle>> actual_sorted_particles = histogram.GetSortedParticles();

    REQUIRE(histogram.GetSortedParticles().size() == 2);
    REQUIRE(actual_sorted_particles[10].size() == 3);
    REQUIRE(actual_sorted_particles[15].size() == 1);
    REQUIRE(histogram.GetMaxSpeed() == 7);
  }
}

TEST_CASE("Check particles get updated") {
  Histogram histogram;
  Particle particle;

  vector<Particle> existing_particles;

  for (size_t i = 0; i < 3; i++) {
    particle.SetMass(10);
    particle.SetSpeed(i);
    existing_particles.push_back(particle);
  }

  particle.SetMass(15);
  particle.SetSpeed(7);
  existing_particles.push_back(particle);

  histogram.SortParticles(existing_particles);

  vector<Particle> new_particles;

  for (size_t i = 0; i < 3; i++) {
    particle.SetMass(5);
    particle.SetSpeed(i);
    new_particles.push_back(particle);
  }

  histogram.UpdateParticles(new_particles);

  map<double, vector<Particle>> actual_sorted_particles = histogram.GetSortedParticles();

  REQUIRE(histogram.GetSortedParticles().size() == 1);
  REQUIRE(actual_sorted_particles[5].size() == 3);
  REQUIRE(actual_sorted_particles[10].size() == 0);
  REQUIRE(actual_sorted_particles[15].size() == 0);
  REQUIRE(histogram.GetMaxSpeed() == 2);
}

TEST_CASE("Check particles get sorted into bins") {
  Histogram histogram;
  Particle particle;

  SECTION("One particle") {
    vector<Particle> all_particles;

    particle.SetMass(10);
    particle.SetSpeed(5);
    all_particles.push_back(particle);

    // Group by mass
    histogram.SortParticles(all_particles);
    map<double, vector<Particle>> actual_sorted_particles = histogram.GetSortedParticles();

    REQUIRE(actual_sorted_particles.size() == 1);
    REQUIRE(actual_sorted_particles[10].size() == 1);
    REQUIRE(histogram.GetMaxSpeed() == 5);

    // Sort into bins
    vector<vector<Particle>> sorted_into_bins = histogram.SortIntoBins(actual_sorted_particles[10]);

    REQUIRE(sorted_into_bins[0].size() == 0);  // [0, 1.0]
    REQUIRE(sorted_into_bins[1].size() == 0);  // [1.0, 2.0]
    REQUIRE(sorted_into_bins[2].size() == 0);  // [2.0, 3.0]
    REQUIRE(sorted_into_bins[3].size() == 0);  // [3.0, 4.0]
    REQUIRE(sorted_into_bins[4].size() == 1);  // [4.0, 5.0]
  }

  SECTION("Multiple particles") {
    vector<Particle> all_particles;

    for (size_t i = 0; i < 3; i++) {
      particle.SetMass(10);
      particle.SetSpeed(i);
      all_particles.push_back(particle);
    }

    // Group by mass
    histogram.SortParticles(all_particles);
    map<double, vector<Particle>> actual_sorted_particles = histogram.GetSortedParticles();

    REQUIRE(actual_sorted_particles.size() == 1);
    REQUIRE(actual_sorted_particles[10].size() == 3);
    REQUIRE(histogram.GetMaxSpeed() == 2);

    // Sort into bins
    vector<vector<Particle>> sorted_into_bins = histogram.SortIntoBins(actual_sorted_particles[10]);

    REQUIRE(sorted_into_bins[0].size() == 1);  // [0, 0.4]
    REQUIRE(sorted_into_bins[1].size() == 0);  // [0.4, 0.8]
    REQUIRE(sorted_into_bins[2].size() == 1);  // [0.8, 1.2]
    REQUIRE(sorted_into_bins[3].size() == 0);  // [1.2, 1.6]
    REQUIRE(sorted_into_bins[4].size() == 1);  // [1.6, 2.0]
  }

  SECTION("Multiple particles with boundary speeds") {
    vector<Particle> all_particles;

    particle.SetMass(10);
    particle.SetSpeed(5);
    all_particles.push_back(particle);

    for (size_t i = 0; i < 2; i++) {
      particle.SetMass(10);
      particle.SetSpeed(3);
      all_particles.push_back(particle);
    }

    particle.SetMass(10);
    particle.SetSpeed(1);
    all_particles.push_back(particle);

    // Group by mass
    histogram.SortParticles(all_particles);
    map<double, vector<Particle>> actual_sorted_particles = histogram.GetSortedParticles();

    REQUIRE(actual_sorted_particles.size() == 1);
    REQUIRE(actual_sorted_particles[10].size() == 4);
    REQUIRE(histogram.GetMaxSpeed() == 5);

    // Sort into bins
    vector<vector<Particle>> sorted_into_bins = histogram.SortIntoBins(actual_sorted_particles[10]);

    REQUIRE(sorted_into_bins[0].size() == 1);  // [0, 1.0]
    REQUIRE(sorted_into_bins[1].size() == 0);  // [1.0, 2.0]
    REQUIRE(sorted_into_bins[2].size() == 2);  // [2.0, 3.0]
    REQUIRE(sorted_into_bins[3].size() == 0);  // [3.0, 4.0]
    REQUIRE(sorted_into_bins[4].size() == 1);  // [4.0, 5.0]
  }
}

/*
TEST_CASE("Check histogram background's coordinates are correct") {
  vector<Particle> particles;
  Histogram histogram = Histogram(particles, 10, 250, vec2(300, 50));

  double left_boundary = 380;  // 350 + 30
  vector<vec2> corners = histogram.DrawHistogramBackground(left_boundary, 50);

  REQUIRE(corners[0] == vec2(380, 50));
  REQUIRE(corners[1] == vec2(630, 300));  // 250 + 380
}
*/