//
// Created by Megan Lov on 11/8/20.
//
#include "core/histogram.h"

#include <catch2/catch.hpp>

using disease::Disease;
using disease::Histogram;
using disease::Status;

TEST_CASE("Check people get sorted according to health status") {
  Histogram histogram;
  Disease::Person person;

  SECTION("One status type (susceptible)") {
    vector<Disease::Person> all_particles;

    for (size_t i = 0; i < 3; i++) {
      person.status = Status::kSusceptible;
      person.color = vec3(0,0,1);
      all_particles.push_back(person);
    }

    histogram.SortPopulation(all_particles);

    map<Status, vector<Disease::Person>> actual_sorted_people = histogram.GetSortedPopulation();

    REQUIRE(histogram.GetSortedPopulation().size() == 1);
    REQUIRE(actual_sorted_people[Status::kSusceptible].size() == 3);
  }

  SECTION("Two status types (susceptible and infectious)") {
    vector<Disease::Person> all_particles;

    for (size_t i = 0; i < 3; i++) {
      person.status = Status::kSusceptible;
      person.color = vec3(0,0,1);
      all_particles.push_back(person);
    }

    person.status = Status::kInfectious;
    person.color = vec3(1,0,0);
    all_particles.push_back(person);

    histogram.SortPopulation(all_particles);

    map<Status, vector<Disease::Person>> actual_sorted_people = histogram.GetSortedPopulation();

    REQUIRE(histogram.GetSortedPopulation().size() == 2);
    REQUIRE(actual_sorted_people[Status::kSusceptible].size() == 3);
    REQUIRE(actual_sorted_people[Status::kInfectious].size() == 1);
  }

  SECTION("Two status types (susceptible and infectious), unordered") {
    vector<Disease::Person> all_particles;

    person.status = Status::kInfectious;
    person.color = vec3(1,0,0);
    all_particles.push_back(person);

    for (size_t i = 0; i < 3; i++) {
      person.status = Status::kSusceptible;
      person.color = vec3(0,0,1);
      all_particles.push_back(person);
    }

    person.status = Status::kInfectious;
    person.color = vec3(1,0,0);
    all_particles.push_back(person);

    histogram.SortPopulation(all_particles);

    map<Status, vector<Disease::Person>> actual_sorted_people = histogram.GetSortedPopulation();

    REQUIRE(histogram.GetSortedPopulation().size() == 2);
    REQUIRE(actual_sorted_people[Status::kSusceptible].size() == 3);
    REQUIRE(actual_sorted_people[Status::kInfectious].size() == 2);
  }
}