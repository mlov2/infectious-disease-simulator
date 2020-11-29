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

  SECTION("Two status types (susceptible and symptomatic)") {
    vector<Disease::Person> all_particles;

    for (size_t i = 0; i < 3; i++) {
      person.status = Status::kSusceptible;
      person.color = vec3(0,0,1);
      all_particles.push_back(person);
    }

    person.status = Status::kSymptomatic;
    person.color = vec3(1,0,0);
    all_particles.push_back(person);

    histogram.SortPopulation(all_particles);

    map<Status, vector<Disease::Person>> actual_sorted_people = histogram.GetSortedPopulation();

    REQUIRE(histogram.GetSortedPopulation().size() == 2);
    REQUIRE(actual_sorted_people[Status::kSusceptible].size() == 3);
    REQUIRE(actual_sorted_people[Status::kSymptomatic].size() == 1);
  }

  SECTION("Two status types (susceptible and symptomatic), unordered") {
    vector<Disease::Person> all_particles;

    person.status = Status::kSymptomatic;
    person.color = vec3(1,0,0);
    all_particles.push_back(person);

    for (size_t i = 0; i < 3; i++) {
      person.status = Status::kSusceptible;
      person.color = vec3(0,0,1);
      all_particles.push_back(person);
    }

    person.status = Status::kSymptomatic;
    person.color = vec3(1,0,0);
    all_particles.push_back(person);

    histogram.SortPopulation(all_particles);

    map<Status, vector<Disease::Person>> actual_sorted_people = histogram.GetSortedPopulation();

    REQUIRE(histogram.GetSortedPopulation().size() == 2);
    REQUIRE(actual_sorted_people[Status::kSusceptible].size() == 3);
    REQUIRE(actual_sorted_people[Status::kSymptomatic].size() == 2);
  }

  SECTION("Three status types (susceptible, symptomatic, asymptomatic)") {
    vector<Disease::Person> all_particles;

    person.status = Status::kSymptomatic;
    person.color = vec3(1,0,0);
    all_particles.push_back(person);

    for (size_t i = 0; i < 3; i++) {
      person.status = Status::kSusceptible;
      person.color = vec3(0,0,1);
      all_particles.push_back(person);
    }

    person.status = Status::kAsymptomatic;
    person.color = vec3(1,1,0);
    all_particles.push_back(person);

    histogram.SortPopulation(all_particles);

    map<Status, vector<Disease::Person>> actual_sorted_people = histogram.GetSortedPopulation();

    REQUIRE(histogram.GetSortedPopulation().size() == 3);
    REQUIRE(actual_sorted_people[Status::kSusceptible].size() == 3);
    REQUIRE(actual_sorted_people[Status::kSymptomatic].size() == 1);
    REQUIRE(actual_sorted_people[Status::kAsymptomatic].size() == 1);
  }
}

TEST_CASE("Check population get updated") {
  SECTION("Info gets updated properly when population size and time elapsed isn't 0") {
    SECTION("Population has an infectious person") {
      Histogram histogram;
      Disease::Person person;

      vector<Disease::Person> existing_people;

      for (size_t i = 0; i < 3; i++) {
        person.status = Status::kSusceptible;
        person.color = vec3(0,0,1);
        existing_people.push_back(person);
      }

      person.status = Status::kSymptomatic;
      person.color = vec3(1,0,0);
      existing_people.push_back(person);

      histogram.SortPopulation(existing_people);

      vector<Disease::Person> updated_people;

      person.status = Status::kSusceptible;
      person.color = vec3(0,0,1);
      updated_people.push_back(person);

      for (size_t i = 0; i < 2; i++) {
        person.status = Status::kSymptomatic;
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
      REQUIRE(actual_sorted_people[Status::kSymptomatic].size() == 2);
      REQUIRE(actual_sorted_people[Status::kRemoved].size() == 1);
      REQUIRE(histogram.GetCumulativeInfoOfPopulation().size() == 1);
      REQUIRE(histogram.GetTimeElapsedSinceOutbreak() == 10);
    }

    SECTION("Population doesn't have an infectious person") {
      Histogram histogram;
      Disease::Person person;

      vector<Disease::Person> existing_people;

      person.status = Status::kSusceptible;
      person.color = vec3(0,0,1);
      existing_people.push_back(person);

      for (size_t i = 0; i < 3; i++) {
        person.status = Status::kRemoved;
        person.color = vec3(0.5,0.5,0.5);
        existing_people.push_back(person);
      }

      histogram.SortPopulation(existing_people);

      map<Status, vector<Disease::Person>> sorted_people = histogram.GetSortedPopulation();

      REQUIRE(sorted_people.size() == 2);
      REQUIRE(sorted_people[Status::kSusceptible].size() == 1);
      REQUIRE(sorted_people[Status::kRemoved].size() == 3);
      REQUIRE(histogram.GetCumulativeInfoOfPopulation().size() == 0);
      REQUIRE(histogram.GetTimeElapsedSinceOutbreak() == Approx(0.0).margin(0.01));

      vector<Disease::Person> updated_people;

      person.status = Status::kSusceptible;
      person.color = vec3(0,0,1);
      updated_people.push_back(person);

      for (size_t i = 0; i < 3; i++) {
        person.status = Status::kRemoved;
        person.color = vec3(0.5,0.5,0.5);
        updated_people.push_back(person);
      }

      histogram.Update(updated_people, 10);

      map<Status, vector<Disease::Person>> actual_sorted_people = histogram.GetSortedPopulation();

      REQUIRE(actual_sorted_people.size() == 4);
      REQUIRE(actual_sorted_people[Status::kSusceptible].size() == 1);
      REQUIRE(actual_sorted_people[Status::kRemoved].size() == 3);
      REQUIRE(histogram.GetCumulativeInfoOfPopulation().size() == 0);
      REQUIRE(histogram.GetTimeElapsedSinceOutbreak() == Approx(0.0).margin(0.01));
    }
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

    person.status = Status::kSymptomatic;
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