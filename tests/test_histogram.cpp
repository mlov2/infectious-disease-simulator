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

TEST_CASE("Check population get updated") {
  SECTION("Info gets updated properly when population size and time elapsed isn't 0") {
    Histogram histogram;
    Disease::Person person;

    vector<Disease::Person> existing_people;

    for (size_t i = 0; i < 3; i++) {
      person.status = Status::kSusceptible;
      person.color = vec3(0,0,1);
      existing_people.push_back(person);
    }

    person.status = Status::kInfectious;
    person.color = vec3(1,0,0);
    existing_people.push_back(person);

    histogram.SortPopulation(existing_people);

    vector<Disease::Person> updated_people;

    person.status = Status::kSusceptible;
    person.color = vec3(0,0,1);
    updated_people.push_back(person);

    for (size_t i = 0; i < 2; i++) {
      person.status = Status::kInfectious;
      person.color = vec3(1,0,0);
      updated_people.push_back(person);
    }

    person.status = Status::kRemoved;
    person.color = vec3(0.5,0.5,0.5);
    updated_people.push_back(person);

    histogram.Update(updated_people, 10);

    map<Status, vector<Disease::Person>> actual_sorted_people = histogram.GetSortedPopulation();

    REQUIRE(actual_sorted_people.size() == 3);
    REQUIRE(actual_sorted_people[Status::kSusceptible].size() == 1);
    REQUIRE(actual_sorted_people[Status::kInfectious].size() == 2);
    REQUIRE(actual_sorted_people[Status::kRemoved].size() == 1);
    REQUIRE(histogram.GetCumulativeInfoOfPopulation().size() == 1);
    REQUIRE(histogram.GetTimeElapsedSinceOutbreak() == 10);
  }

  SECTION("Info gets updated properly when population size and time elapsed is 0") {
    Histogram histogram;
    Disease::Person person;

    vector<Disease::Person> existing_people;

    for (size_t i = 0; i < 3; i++) {
      person.status = Status::kSusceptible;
      person.color = vec3(0,0,1);
      existing_people.push_back(person);
    }

    person.status = Status::kInfectious;
    person.color = vec3(1,0,0);
    existing_people.push_back(person);

    histogram.SortPopulation(existing_people);

    vector<Disease::Person> updated_people;
    REQUIRE(updated_people.size() == 0);

    histogram.Update(updated_people, 0);

    map<Status, vector<Disease::Person>> actual_sorted_people = histogram.GetSortedPopulation();

    REQUIRE(actual_sorted_people.size() == 0);
    REQUIRE(histogram.GetCumulativeInfoOfPopulation().size() == 0);
    REQUIRE(histogram.GetTimeElapsedSinceOutbreak() == 0);
  }
}