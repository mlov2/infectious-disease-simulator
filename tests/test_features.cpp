//
// Created by Megan Lov on 12/8/20.
//
#include <core/infectious_disease.h>

#include <catch2/catch.hpp>

using disease::Disease;
using disease::Status;

TEST_CASE("Check person status updates") {
  Disease disease = Disease(0, 0, 100, 100, vec2(150, 0), vec2(250, 100),
                            vec2(45, 45), vec2(55, 55),
                            25, 500, false, true, false,
                            false, false, false);
  Disease::Person person;

  SECTION("Current status is susceptible") {
    SECTION("Person exposed") {
      SECTION("Exposure time is at (max - 1) -> Status changes to symptomatic") {
        vector<Disease::Person> all_particles;

        // Particle 1
        person.radius = 10;
        person.position = vec2(15, 15);
        person.velocity = vec2(5, 5);
        person.status = disease::Status::kSymptomatic;
        person.color = vec3(1,0,0);
        person.continuous_exposure_time = 0;
        person.time_infected = 0;
        person.has_been_exposed_in_frame = false;
        person.is_quarantined = false;
        person.is_social_distancing = false;
        person.is_going_to_central_location = false;
        person.is_at_central_location = false;
        all_particles.push_back(person);

        // Particle 2
        person.radius = 10;
        person.position = vec2(15, 20);
        person.velocity = vec2(-5, 6);
        person.status = disease::Status::kSusceptible;
        person.color = vec3(0,0,1);
        person.continuous_exposure_time = 24;
        person.time_infected = 0;
        person.has_been_exposed_in_frame = false;
        person.is_quarantined = false;
        person.is_social_distancing = false;
        person.is_going_to_central_location = false;
        person.is_at_central_location = false;
        all_particles.push_back(person);

        disease.SetPopulation(all_particles);
        disease.UpdateParticles();
        vector<Disease::Person> updated_particles = disease.GetPopulation();

        // Particle 1
        REQUIRE(updated_particles[0].position == vec2(20.0, 20.0));
        REQUIRE(updated_particles[0].velocity == vec2(5.0, 5.0));
        REQUIRE(updated_particles[0].status == disease::Status::kSymptomatic);
        REQUIRE(updated_particles[0].color == vec3(1, 0, 0));
        REQUIRE(updated_particles[0].continuous_exposure_time == 0);
        REQUIRE(updated_particles[0].time_infected == 1);
        REQUIRE(updated_particles[0].is_quarantined == false);
        REQUIRE(updated_particles[0].is_social_distancing == false);
        REQUIRE(updated_particles[0].positions_of_people_in_bubble.empty());

        // Particle 2
        REQUIRE(updated_particles[1].position == vec2(10.0, 26.0));
        REQUIRE(updated_particles[1].velocity == vec2(-5.0, 6.0));
        REQUIRE(updated_particles[1].status == disease::Status::kSymptomatic);
        REQUIRE(updated_particles[1].color == vec3(1, 0, 0));
        REQUIRE(updated_particles[1].continuous_exposure_time == 0);
        REQUIRE(updated_particles[1].time_infected == 0);
        REQUIRE(updated_particles[1].is_quarantined == false);
        REQUIRE(updated_particles[1].is_social_distancing == false);
        REQUIRE(updated_particles[1].positions_of_people_in_bubble.empty());
      }

      SECTION("Exposure time is at (max - 1) -> Status changes to asymptomatic") {
        Disease disease1 = Disease(0, 0, 100, 100, vec2(150, 0), vec2(250, 100),
                                   vec2(45, 45), vec2(55, 55),
                                   25, 500, false, false, false,
                                   false, false, false);
        vector<Disease::Person> all_particles;

        // Particle 1
        person.radius = 10;
        person.position = vec2(15, 15);
        person.velocity = vec2(5, 5);
        person.status = disease::Status::kAsymptomatic;
        person.color = vec3(1,1,0);
        person.continuous_exposure_time = 0;
        person.time_infected = 0;
        person.has_been_exposed_in_frame = false;
        person.is_quarantined = false;
        person.is_social_distancing = false;
        person.is_going_to_central_location = false;
        person.is_at_central_location = false;
        all_particles.push_back(person);

        // Particle 2
        person.radius = 10;
        person.position = vec2(15, 20);
        person.velocity = vec2(-5, 6);
        person.status = disease::Status::kSusceptible;
        person.color = vec3(0,0,1);
        person.continuous_exposure_time = 24;
        person.time_infected = 0;
        person.has_been_exposed_in_frame = false;
        person.is_quarantined = false;
        person.is_social_distancing = false;
        person.is_going_to_central_location = false;
        person.is_at_central_location = false;
        all_particles.push_back(person);

        disease1.SetPopulation(all_particles);
        disease1.UpdateParticles();
        vector<Disease::Person> updated_particles = disease1.GetPopulation();

        // Particle 1
        REQUIRE(updated_particles[0].position == vec2(20.0, 20.0));
        REQUIRE(updated_particles[0].velocity == vec2(5.0, 5.0));
        REQUIRE(updated_particles[0].status == disease::Status::kAsymptomatic);
        REQUIRE(updated_particles[0].color == vec3(1, 1, 0));
        REQUIRE(updated_particles[0].continuous_exposure_time == 0);
        REQUIRE(updated_particles[0].time_infected == 1);
        REQUIRE(updated_particles[0].is_quarantined == false);
        REQUIRE(updated_particles[0].is_social_distancing == false);
        REQUIRE(updated_particles[0].positions_of_people_in_bubble.empty());

        // Particle 2
        REQUIRE(updated_particles[1].position == vec2(10.0, 26.0));
        REQUIRE(updated_particles[1].velocity == vec2(-5.0, 6.0));
        REQUIRE(updated_particles[1].status == disease::Status::kAsymptomatic);
        REQUIRE(updated_particles[1].color == vec3(1, 1, 0));
        REQUIRE(updated_particles[1].continuous_exposure_time == 0);
        REQUIRE(updated_particles[1].time_infected == 0);
        REQUIRE(updated_particles[1].is_quarantined == false);
        REQUIRE(updated_particles[1].is_social_distancing == false);
        REQUIRE(updated_particles[1].positions_of_people_in_bubble.empty());
      }

      SECTION("Exposure time is not at (max - 1)") {
        vector<Disease::Person> all_particles;

        // Particle 1
        person.radius = 10;
        person.position = vec2(15, 15);
        person.velocity = vec2(5, 5);
        person.status = disease::Status::kSymptomatic;
        person.color = vec3(1,0,0);
        person.continuous_exposure_time = 0;
        person.time_infected = 0;
        person.has_been_exposed_in_frame = false;
        person.is_quarantined = false;
        person.is_social_distancing = false;
        person.is_going_to_central_location = false;
        person.is_at_central_location = false;
        all_particles.push_back(person);

        // Particle 2
        person.radius = 10;
        person.position = vec2(15, 20);
        person.velocity = vec2(-5, 6);
        person.status = disease::Status::kSusceptible;
        person.color = vec3(0,0,1);
        person.continuous_exposure_time = 3;
        person.time_infected = 0;
        person.has_been_exposed_in_frame = false;
        person.is_quarantined = false;
        person.is_social_distancing = false;
        person.is_going_to_central_location = false;
        person.is_at_central_location = false;
        all_particles.push_back(person);

        disease.SetPopulation(all_particles);
        disease.UpdateParticles();
        vector<Disease::Person> updated_particles = disease.GetPopulation();

        // Particle 1
        REQUIRE(updated_particles[0].position == vec2(20.0, 20.0));
        REQUIRE(updated_particles[0].velocity == vec2(5.0, 5.0));
        REQUIRE(updated_particles[0].status == disease::Status::kSymptomatic);
        REQUIRE(updated_particles[0].color == vec3(1, 0, 0));
        REQUIRE(updated_particles[0].continuous_exposure_time == 0);
        REQUIRE(updated_particles[0].time_infected == 1);
        REQUIRE(updated_particles[0].is_quarantined == false);
        REQUIRE(updated_particles[0].is_social_distancing == false);
        REQUIRE(updated_particles[0].positions_of_people_in_bubble.empty());

        // Particle 2
        REQUIRE(updated_particles[1].position == vec2(10.0, 26.0));
        REQUIRE(updated_particles[1].velocity == vec2(-5.0, 6.0));
        REQUIRE(updated_particles[1].status == disease::Status::kSusceptible);
        REQUIRE(updated_particles[1].color == vec3(0, 0, 1));
        REQUIRE(updated_particles[1].continuous_exposure_time == 4);
        REQUIRE(updated_particles[1].time_infected == 0);
        REQUIRE(updated_particles[1].is_quarantined == false);
        REQUIRE(updated_particles[1].is_social_distancing == false);
        REQUIRE(updated_particles[1].positions_of_people_in_bubble.empty());
      }
    }

    SECTION("Person not exposed") {
      SECTION("Exposure time is at (max - 1)") {
        vector<Disease::Person> all_particles;

        // Particle 1
        person.radius = 10;
        person.position = vec2(15, 15);
        person.velocity = vec2(5, 5);
        person.status = disease::Status::kSymptomatic;
        person.color = vec3(1,0,0);
        person.continuous_exposure_time = 0;
        person.time_infected = 0;
        person.has_been_exposed_in_frame = false;
        person.is_quarantined = false;
        person.is_social_distancing = false;
        person.is_going_to_central_location = false;
        person.is_at_central_location = false;
        all_particles.push_back(person);

        // Particle 2
        person.radius = 10;
        person.position = vec2(60, 15);
        person.velocity = vec2(-5, 6);
        person.status = disease::Status::kSusceptible;
        person.color = vec3(0,0,1);
        person.continuous_exposure_time = 24;
        person.time_infected = 0;
        person.has_been_exposed_in_frame = false;
        person.is_quarantined = false;
        person.is_social_distancing = false;
        person.is_going_to_central_location = false;
        person.is_at_central_location = false;
        all_particles.push_back(person);

        disease.SetPopulation(all_particles);
        disease.UpdateParticles();
        vector<Disease::Person> updated_particles = disease.GetPopulation();

        // Particle 1
        REQUIRE(updated_particles[0].position == vec2(20.0, 20.0));
        REQUIRE(updated_particles[0].velocity == vec2(5.0, 5.0));
        REQUIRE(updated_particles[0].status == disease::Status::kSymptomatic);
        REQUIRE(updated_particles[0].color == vec3(1, 0, 0));
        REQUIRE(updated_particles[0].continuous_exposure_time == 0);
        REQUIRE(updated_particles[0].time_infected == 1);
        REQUIRE(updated_particles[0].is_quarantined == false);
        REQUIRE(updated_particles[0].is_social_distancing == false);
        REQUIRE(updated_particles[0].positions_of_people_in_bubble.empty());

        // Particle 2
        REQUIRE(updated_particles[1].position == vec2(55.0, 21.0));
        REQUIRE(updated_particles[1].velocity == vec2(-5.0, 6.0));
        REQUIRE(updated_particles[1].status == disease::Status::kSusceptible);
        REQUIRE(updated_particles[1].color == vec3(0, 0, 1));
        REQUIRE(updated_particles[1].continuous_exposure_time == 0);
        REQUIRE(updated_particles[1].time_infected == 0);
        REQUIRE(updated_particles[1].is_quarantined == false);
        REQUIRE(updated_particles[1].is_social_distancing == false);
        REQUIRE(updated_particles[1].positions_of_people_in_bubble.empty());
      }

      SECTION("Exposure time is not at (max - 1)") {
        vector<Disease::Person> all_particles;

        // Particle 1
        person.radius = 10;
        person.position = vec2(15, 15);
        person.velocity = vec2(5, 5);
        person.status = disease::Status::kSymptomatic;
        person.color = vec3(1,0,0);
        person.continuous_exposure_time = 0;
        person.time_infected = 0;
        person.has_been_exposed_in_frame = false;
        person.is_quarantined = false;
        person.is_social_distancing = false;
        person.is_going_to_central_location = false;
        person.is_at_central_location = false;
        all_particles.push_back(person);

        // Particle 2
        person.radius = 10;
        person.position = vec2(60, 15);
        person.velocity = vec2(-5, 6);
        person.status = disease::Status::kSusceptible;
        person.color = vec3(0,0,1);
        person.continuous_exposure_time = 2;
        person.time_infected = 0;
        person.has_been_exposed_in_frame = false;
        person.is_quarantined = false;
        person.is_social_distancing = false;
        person.is_going_to_central_location = false;
        person.is_at_central_location = false;
        all_particles.push_back(person);

        disease.SetPopulation(all_particles);
        disease.UpdateParticles();
        vector<Disease::Person> updated_particles = disease.GetPopulation();

        // Particle 1
        REQUIRE(updated_particles[0].position == vec2(20.0, 20.0));
        REQUIRE(updated_particles[0].velocity == vec2(5.0, 5.0));
        REQUIRE(updated_particles[0].status == disease::Status::kSymptomatic);
        REQUIRE(updated_particles[0].color == vec3(1, 0, 0));
        REQUIRE(updated_particles[0].continuous_exposure_time == 0);
        REQUIRE(updated_particles[0].time_infected == 1);
        REQUIRE(updated_particles[0].is_quarantined == false);
        REQUIRE(updated_particles[0].is_social_distancing == false);
        REQUIRE(updated_particles[0].positions_of_people_in_bubble.empty());

        // Particle 2
        REQUIRE(updated_particles[1].position == vec2(55.0, 21.0));
        REQUIRE(updated_particles[1].velocity == vec2(-5.0, 6.0));
        REQUIRE(updated_particles[1].status == disease::Status::kSusceptible);
        REQUIRE(updated_particles[1].color == vec3(0, 0, 1));
        REQUIRE(updated_particles[1].continuous_exposure_time == 0);
        REQUIRE(updated_particles[1].time_infected == 0);
        REQUIRE(updated_particles[1].is_quarantined == false);
        REQUIRE(updated_particles[1].is_social_distancing == false);
        REQUIRE(updated_particles[1].positions_of_people_in_bubble.empty());
      }
    }
  }

  SECTION("Current status is symptomatic") {
    SECTION("Person exposed") {
      SECTION("Time infected is at (max - 1) -> Status changes to removed") {
        vector<Disease::Person> all_particles;

        // Particle 1
        person.radius = 10;
        person.position = vec2(15, 15);
        person.velocity = vec2(5, 5);
        person.status = disease::Status::kSymptomatic;
        person.color = vec3(1,0,0);
        person.continuous_exposure_time = 0;
        person.time_infected = 0;
        person.has_been_exposed_in_frame = false;
        person.is_quarantined = false;
        person.is_social_distancing = false;
        person.is_going_to_central_location = false;
        person.is_at_central_location = false;
        all_particles.push_back(person);

        // Particle 2
        person.radius = 10;
        person.position = vec2(15, 20);
        person.velocity = vec2(-5, 6);
        person.status = disease::Status::kSymptomatic;
        person.color = vec3(1,0,0);
        person.continuous_exposure_time = 0;
        person.time_infected = 499;
        person.has_been_exposed_in_frame = false;
        person.is_quarantined = false;
        person.is_social_distancing = false;
        person.is_going_to_central_location = false;
        person.is_at_central_location = false;
        all_particles.push_back(person);

        disease.SetPopulation(all_particles);
        disease.UpdateParticles();
        vector<Disease::Person> updated_particles = disease.GetPopulation();

        // Particle 1
        REQUIRE(updated_particles[0].position == vec2(20.0, 20.0));
        REQUIRE(updated_particles[0].velocity == vec2(5.0, 5.0));
        REQUIRE(updated_particles[0].status == disease::Status::kSymptomatic);
        REQUIRE(updated_particles[0].color == vec3(1, 0, 0));
        REQUIRE(updated_particles[0].continuous_exposure_time == 0);
        REQUIRE(updated_particles[0].time_infected == 1);
        REQUIRE(updated_particles[0].is_quarantined == false);
        REQUIRE(updated_particles[0].is_social_distancing == false);
        REQUIRE(updated_particles[0].positions_of_people_in_bubble.empty());

        // Particle 2
        REQUIRE(updated_particles[1].position == vec2(10.0, 26.0));
        REQUIRE(updated_particles[1].velocity == vec2(-5.0, 6.0));
        REQUIRE(updated_particles[1].status == disease::Status::kRemoved);
        REQUIRE(updated_particles[1].color == vec3(0.5, 0.5, 0.5));
        REQUIRE(updated_particles[1].continuous_exposure_time == 0);
        REQUIRE(updated_particles[1].time_infected == 0);
        REQUIRE(updated_particles[1].is_quarantined == false);
        REQUIRE(updated_particles[1].is_social_distancing == false);
        REQUIRE(updated_particles[1].positions_of_people_in_bubble.empty());
      }

      SECTION("Time infected is not at (max - 1)") {
        vector<Disease::Person> all_particles;

        // Particle 1
        person.radius = 10;
        person.position = vec2(15, 15);
        person.velocity = vec2(5, 5);
        person.status = disease::Status::kSymptomatic;
        person.color = vec3(1,0,0);
        person.continuous_exposure_time = 0;
        person.time_infected = 0;
        person.has_been_exposed_in_frame = false;
        person.is_quarantined = false;
        person.is_social_distancing = false;
        person.is_going_to_central_location = false;
        person.is_at_central_location = false;
        all_particles.push_back(person);

        // Particle 2
        person.radius = 10;
        person.position = vec2(15, 20);
        person.velocity = vec2(-5, 6);
        person.status = disease::Status::kSymptomatic;
        person.color = vec3(1,0,0);
        person.continuous_exposure_time = 0;
        person.time_infected = 10;
        person.has_been_exposed_in_frame = false;
        person.is_quarantined = false;
        person.is_social_distancing = false;
        person.is_going_to_central_location = false;
        person.is_at_central_location = false;
        all_particles.push_back(person);

        disease.SetPopulation(all_particles);
        disease.UpdateParticles();
        vector<Disease::Person> updated_particles = disease.GetPopulation();

        // Particle 1
        REQUIRE(updated_particles[0].position == vec2(20.0, 20.0));
        REQUIRE(updated_particles[0].velocity == vec2(5.0, 5.0));
        REQUIRE(updated_particles[0].status == disease::Status::kSymptomatic);
        REQUIRE(updated_particles[0].color == vec3(1, 0, 0));
        REQUIRE(updated_particles[0].continuous_exposure_time == 0);
        REQUIRE(updated_particles[0].time_infected == 1);
        REQUIRE(updated_particles[0].is_quarantined == false);
        REQUIRE(updated_particles[0].is_social_distancing == false);
        REQUIRE(updated_particles[0].positions_of_people_in_bubble.empty());

        // Particle 2
        REQUIRE(updated_particles[1].position == vec2(10.0, 26.0));
        REQUIRE(updated_particles[1].velocity == vec2(-5.0, 6.0));
        REQUIRE(updated_particles[1].status == disease::Status::kSymptomatic);
        REQUIRE(updated_particles[1].color == vec3(1, 0, 0));
        REQUIRE(updated_particles[1].continuous_exposure_time == 0);
        REQUIRE(updated_particles[1].time_infected == 11);
        REQUIRE(updated_particles[1].is_quarantined == false);
        REQUIRE(updated_particles[1].is_social_distancing == false);
        REQUIRE(updated_particles[1].positions_of_people_in_bubble.empty());
      }
    }

    SECTION("Person not exposed") {
      SECTION("Time infected is at (max - 1)") {
        vector<Disease::Person> all_particles;

        // Particle 1
        person.radius = 10;
        person.position = vec2(15, 15);
        person.velocity = vec2(5, 5);
        person.status = disease::Status::kSymptomatic;
        person.color = vec3(1,0,0);
        person.continuous_exposure_time = 0;
        person.time_infected = 0;
        person.has_been_exposed_in_frame = false;
        person.is_quarantined = false;
        person.is_social_distancing = false;
        person.is_going_to_central_location = false;
        person.is_at_central_location = false;
        all_particles.push_back(person);

        // Particle 2
        person.radius = 10;
        person.position = vec2(60, 15);
        person.velocity = vec2(-5, 6);
        person.status = disease::Status::kSymptomatic;
        person.color = vec3(1,0,0);
        person.continuous_exposure_time = 0;
        person.time_infected = 499;
        person.has_been_exposed_in_frame = false;
        person.is_quarantined = false;
        person.is_social_distancing = false;
        person.is_going_to_central_location = false;
        person.is_at_central_location = false;
        all_particles.push_back(person);

        disease.SetPopulation(all_particles);
        disease.UpdateParticles();
        vector<Disease::Person> updated_particles = disease.GetPopulation();

        // Particle 1
        REQUIRE(updated_particles[0].position == vec2(20.0, 20.0));
        REQUIRE(updated_particles[0].velocity == vec2(5.0, 5.0));
        REQUIRE(updated_particles[0].status == disease::Status::kSymptomatic);
        REQUIRE(updated_particles[0].color == vec3(1, 0, 0));
        REQUIRE(updated_particles[0].continuous_exposure_time == 0);
        REQUIRE(updated_particles[0].time_infected == 1);
        REQUIRE(updated_particles[0].is_quarantined == false);
        REQUIRE(updated_particles[0].is_social_distancing == false);
        REQUIRE(updated_particles[0].positions_of_people_in_bubble.empty());

        // Particle 2
        REQUIRE(updated_particles[1].position == vec2(55.0, 21.0));
        REQUIRE(updated_particles[1].velocity == vec2(-5.0, 6.0));
        REQUIRE(updated_particles[1].status == disease::Status::kRemoved);
        REQUIRE(updated_particles[1].color == vec3(0.5, 0.5, 0.5));
        REQUIRE(updated_particles[1].continuous_exposure_time == 0);
        REQUIRE(updated_particles[1].time_infected == 0);
        REQUIRE(updated_particles[1].is_quarantined == false);
        REQUIRE(updated_particles[1].is_social_distancing == false);
        REQUIRE(updated_particles[1].positions_of_people_in_bubble.empty());
      }

      SECTION("Time infected is not at (max - 1)") {
        vector<Disease::Person> all_particles;

        // Particle 1
        person.radius = 10;
        person.position = vec2(15, 15);
        person.velocity = vec2(5, 5);
        person.status = disease::Status::kSymptomatic;
        person.color = vec3(1,0,0);
        person.continuous_exposure_time = 0;
        person.time_infected = 0;
        person.has_been_exposed_in_frame = false;
        person.is_quarantined = false;
        person.is_social_distancing = false;
        person.is_going_to_central_location = false;
        person.is_at_central_location = false;
        all_particles.push_back(person);

        // Particle 2
        person.radius = 10;
        person.position = vec2(60, 15);
        person.velocity = vec2(-5, 6);
        person.status = disease::Status::kSymptomatic;
        person.color = vec3(1,0,0);
        person.continuous_exposure_time = 0;
        person.time_infected = 10;
        person.has_been_exposed_in_frame = false;
        person.is_quarantined = false;
        person.is_social_distancing = false;
        person.is_going_to_central_location = false;
        person.is_at_central_location = false;
        all_particles.push_back(person);

        disease.SetPopulation(all_particles);
        disease.UpdateParticles();
        vector<Disease::Person> updated_particles = disease.GetPopulation();

        // Particle 1
        REQUIRE(updated_particles[0].position == vec2(20.0, 20.0));
        REQUIRE(updated_particles[0].velocity == vec2(5.0, 5.0));
        REQUIRE(updated_particles[0].status == disease::Status::kSymptomatic);
        REQUIRE(updated_particles[0].color == vec3(1, 0, 0));
        REQUIRE(updated_particles[0].continuous_exposure_time == 0);
        REQUIRE(updated_particles[0].time_infected == 1);
        REQUIRE(updated_particles[0].is_quarantined == false);
        REQUIRE(updated_particles[0].is_social_distancing == false);
        REQUIRE(updated_particles[0].positions_of_people_in_bubble.empty());

        // Particle 2
        REQUIRE(updated_particles[1].position == vec2(55.0, 21.0));
        REQUIRE(updated_particles[1].velocity == vec2(-5.0, 6.0));
        REQUIRE(updated_particles[1].status == disease::Status::kSymptomatic);
        REQUIRE(updated_particles[1].color == vec3(1, 0, 0));
        REQUIRE(updated_particles[1].continuous_exposure_time == 0);
        REQUIRE(updated_particles[1].time_infected == 11);
        REQUIRE(updated_particles[1].is_quarantined == false);
        REQUIRE(updated_particles[1].is_social_distancing == false);
        REQUIRE(updated_particles[1].positions_of_people_in_bubble.empty());
      }
    }
  }

  SECTION("Current status is asymptomatic") {
    SECTION("Person exposed") {
      SECTION("Time infected is at (max - 1) -> Status changes to removed") {
        vector<Disease::Person> all_particles;

        // Particle 1
        person.radius = 10;
        person.position = vec2(15, 15);
        person.velocity = vec2(5, 5);
        person.status = disease::Status::kAsymptomatic;
        person.color = vec3(1,1,0);
        person.continuous_exposure_time = 0;
        person.time_infected = 0;
        person.has_been_exposed_in_frame = false;
        person.is_quarantined = false;
        person.is_social_distancing = false;
        person.is_going_to_central_location = false;
        person.is_at_central_location = false;
        all_particles.push_back(person);

        // Particle 2
        person.radius = 10;
        person.position = vec2(15, 20);
        person.velocity = vec2(-5, 6);
        person.status = disease::Status::kAsymptomatic;
        person.color = vec3(1,1,0);
        person.continuous_exposure_time = 0;
        person.time_infected = 499;
        person.has_been_exposed_in_frame = false;
        person.is_quarantined = false;
        person.is_social_distancing = false;
        person.is_going_to_central_location = false;
        person.is_at_central_location = false;
        all_particles.push_back(person);

        disease.SetPopulation(all_particles);
        disease.UpdateParticles();
        vector<Disease::Person> updated_particles = disease.GetPopulation();

        // Particle 1
        REQUIRE(updated_particles[0].position == vec2(20.0, 20.0));
        REQUIRE(updated_particles[0].velocity == vec2(5.0, 5.0));
        REQUIRE(updated_particles[0].status == disease::Status::kAsymptomatic);
        REQUIRE(updated_particles[0].color == vec3(1, 1, 0));
        REQUIRE(updated_particles[0].continuous_exposure_time == 0);
        REQUIRE(updated_particles[0].time_infected == 1);
        REQUIRE(updated_particles[0].is_quarantined == false);
        REQUIRE(updated_particles[0].is_social_distancing == false);
        REQUIRE(updated_particles[0].positions_of_people_in_bubble.empty());

        // Particle 2
        REQUIRE(updated_particles[1].position == vec2(10.0, 26.0));
        REQUIRE(updated_particles[1].velocity == vec2(-5.0, 6.0));
        REQUIRE(updated_particles[1].status == disease::Status::kRemoved);
        REQUIRE(updated_particles[1].color == vec3(0.5, 0.5, 0.5));
        REQUIRE(updated_particles[1].continuous_exposure_time == 0);
        REQUIRE(updated_particles[1].time_infected == 0);
        REQUIRE(updated_particles[1].is_quarantined == false);
        REQUIRE(updated_particles[1].is_social_distancing == false);
        REQUIRE(updated_particles[1].positions_of_people_in_bubble.empty());
      }

      SECTION("Time infected is not at (max - 1)") {
        vector<Disease::Person> all_particles;

        // Particle 1
        person.radius = 10;
        person.position = vec2(15, 15);
        person.velocity = vec2(5, 5);
        person.status = disease::Status::kAsymptomatic;
        person.color = vec3(1,1,0);
        person.continuous_exposure_time = 0;
        person.time_infected = 0;
        person.has_been_exposed_in_frame = false;
        person.is_quarantined = false;
        person.is_social_distancing = false;
        person.is_going_to_central_location = false;
        person.is_at_central_location = false;
        all_particles.push_back(person);

        // Particle 2
        person.radius = 10;
        person.position = vec2(15, 20);
        person.velocity = vec2(-5, 6);
        person.status = disease::Status::kAsymptomatic;
        person.color = vec3(1,1,0);
        person.continuous_exposure_time = 0;
        person.time_infected = 10;
        person.has_been_exposed_in_frame = false;
        person.is_quarantined = false;
        person.is_social_distancing = false;
        person.is_going_to_central_location = false;
        person.is_at_central_location = false;
        all_particles.push_back(person);

        disease.SetPopulation(all_particles);
        disease.UpdateParticles();
        vector<Disease::Person> updated_particles = disease.GetPopulation();

        // Particle 1
        REQUIRE(updated_particles[0].position == vec2(20.0, 20.0));
        REQUIRE(updated_particles[0].velocity == vec2(5.0, 5.0));
        REQUIRE(updated_particles[0].status == disease::Status::kAsymptomatic);
        REQUIRE(updated_particles[0].color == vec3(1, 1, 0));
        REQUIRE(updated_particles[0].continuous_exposure_time == 0);
        REQUIRE(updated_particles[0].time_infected == 1);
        REQUIRE(updated_particles[0].is_quarantined == false);
        REQUIRE(updated_particles[0].is_social_distancing == false);
        REQUIRE(updated_particles[0].positions_of_people_in_bubble.empty());

        // Particle 2
        REQUIRE(updated_particles[1].position == vec2(10.0, 26.0));
        REQUIRE(updated_particles[1].velocity == vec2(-5.0, 6.0));
        REQUIRE(updated_particles[1].status == disease::Status::kAsymptomatic);
        REQUIRE(updated_particles[1].color == vec3(1, 1, 0));
        REQUIRE(updated_particles[1].continuous_exposure_time == 0);
        REQUIRE(updated_particles[1].time_infected == 11);
        REQUIRE(updated_particles[1].is_quarantined == false);
        REQUIRE(updated_particles[1].is_social_distancing == false);
        REQUIRE(updated_particles[1].positions_of_people_in_bubble.empty());
      }
    }

    SECTION("Person not exposed") {
      SECTION("Time infected is at (max - 1)") {
        vector<Disease::Person> all_particles;

        // Particle 1
        person.radius = 10;
        person.position = vec2(15, 15);
        person.velocity = vec2(5, 5);
        person.status = disease::Status::kAsymptomatic;
        person.color = vec3(1,1,0);
        person.continuous_exposure_time = 0;
        person.time_infected = 0;
        person.has_been_exposed_in_frame = false;
        person.is_quarantined = false;
        person.is_social_distancing = false;
        person.is_going_to_central_location = false;
        person.is_at_central_location = false;
        all_particles.push_back(person);

        // Particle 2
        person.radius = 10;
        person.position = vec2(60, 15);
        person.velocity = vec2(-5, 6);
        person.status = disease::Status::kAsymptomatic;
        person.color = vec3(1,1,0);
        person.continuous_exposure_time = 0;
        person.time_infected = 499;
        person.has_been_exposed_in_frame = false;
        person.is_quarantined = false;
        person.is_social_distancing = false;
        person.is_going_to_central_location = false;
        person.is_at_central_location = false;
        all_particles.push_back(person);

        disease.SetPopulation(all_particles);
        disease.UpdateParticles();
        vector<Disease::Person> updated_particles = disease.GetPopulation();

        // Particle 1
        REQUIRE(updated_particles[0].position == vec2(20.0, 20.0));
        REQUIRE(updated_particles[0].velocity == vec2(5.0, 5.0));
        REQUIRE(updated_particles[0].status == disease::Status::kAsymptomatic);
        REQUIRE(updated_particles[0].color == vec3(1, 1, 0));
        REQUIRE(updated_particles[0].continuous_exposure_time == 0);
        REQUIRE(updated_particles[0].time_infected == 1);
        REQUIRE(updated_particles[0].is_quarantined == false);
        REQUIRE(updated_particles[0].is_social_distancing == false);
        REQUIRE(updated_particles[0].positions_of_people_in_bubble.empty());

        // Particle 2
        REQUIRE(updated_particles[1].position == vec2(55.0, 21.0));
        REQUIRE(updated_particles[1].velocity == vec2(-5.0, 6.0));
        REQUIRE(updated_particles[1].status == disease::Status::kRemoved);
        REQUIRE(updated_particles[1].color == vec3(0.5, 0.5, 0.5));
        REQUIRE(updated_particles[1].continuous_exposure_time == 0);
        REQUIRE(updated_particles[1].time_infected == 0);
        REQUIRE(updated_particles[1].is_quarantined == false);
        REQUIRE(updated_particles[1].is_social_distancing == false);
        REQUIRE(updated_particles[1].positions_of_people_in_bubble.empty());
      }

      SECTION("Time infected is not at (max - 1)") {
        vector<Disease::Person> all_particles;

        // Particle 1
        person.radius = 10;
        person.position = vec2(15, 15);
        person.velocity = vec2(5, 5);
        person.status = disease::Status::kAsymptomatic;
        person.color = vec3(1,1,0);
        person.continuous_exposure_time = 0;
        person.time_infected = 0;
        person.has_been_exposed_in_frame = false;
        person.is_quarantined = false;
        person.is_social_distancing = false;
        person.is_going_to_central_location = false;
        person.is_at_central_location = false;
        all_particles.push_back(person);

        // Particle 2
        person.radius = 10;
        person.position = vec2(60, 15);
        person.velocity = vec2(-5, 6);
        person.status = disease::Status::kAsymptomatic;
        person.color = vec3(1,1,0);
        person.continuous_exposure_time = 0;
        person.time_infected = 10;
        person.has_been_exposed_in_frame = false;
        person.is_quarantined = false;
        person.is_social_distancing = false;
        person.is_going_to_central_location = false;
        person.is_at_central_location = false;
        all_particles.push_back(person);

        disease.SetPopulation(all_particles);
        disease.UpdateParticles();
        vector<Disease::Person> updated_particles = disease.GetPopulation();

        // Particle 1
        REQUIRE(updated_particles[0].position == vec2(20.0, 20.0));
        REQUIRE(updated_particles[0].velocity == vec2(5.0, 5.0));
        REQUIRE(updated_particles[0].status == disease::Status::kAsymptomatic);
        REQUIRE(updated_particles[0].color == vec3(1, 1, 0));
        REQUIRE(updated_particles[0].continuous_exposure_time == 0);
        REQUIRE(updated_particles[0].time_infected == 1);
        REQUIRE(updated_particles[0].is_quarantined == false);
        REQUIRE(updated_particles[0].is_social_distancing == false);
        REQUIRE(updated_particles[0].positions_of_people_in_bubble.empty());

        // Particle 2
        REQUIRE(updated_particles[1].position == vec2(55.0, 21.0));
        REQUIRE(updated_particles[1].velocity == vec2(-5.0, 6.0));
        REQUIRE(updated_particles[1].status == disease::Status::kAsymptomatic);
        REQUIRE(updated_particles[1].color == vec3(1, 1, 0));
        REQUIRE(updated_particles[1].continuous_exposure_time == 0);
        REQUIRE(updated_particles[1].time_infected == 11);
        REQUIRE(updated_particles[1].is_quarantined == false);
        REQUIRE(updated_particles[1].is_social_distancing == false);
        REQUIRE(updated_particles[1].positions_of_people_in_bubble.empty());
      }
    }
  }

  SECTION("Current status is removed") {
    SECTION("Person exposed") {
      vector<Disease::Person> all_particles;

      // Particle 1
      person.radius = 10;
      person.position = vec2(15, 15);
      person.velocity = vec2(5, 5);
      person.status = disease::Status::kSymptomatic;
      person.color = vec3(1,0,0);
      person.continuous_exposure_time = 0;
      person.time_infected = 0;
      person.has_been_exposed_in_frame = false;
      person.is_quarantined = false;
      person.is_social_distancing = false;
      person.is_going_to_central_location = false;
      person.is_at_central_location = false;
      all_particles.push_back(person);

      // Particle 2
      person.radius = 10;
      person.position = vec2(15, 20);
      person.velocity = vec2(-5, 6);
      person.status = disease::Status::kRemoved;
      person.color = vec3(0.5,0.5,0.5);
      person.continuous_exposure_time = 0;
      person.time_infected = 0;
      person.has_been_exposed_in_frame = false;
      person.is_quarantined = false;
      person.is_social_distancing = false;
      person.is_going_to_central_location = false;
      person.is_at_central_location = false;
      all_particles.push_back(person);

      disease.SetPopulation(all_particles);
      disease.UpdateParticles();
      vector<Disease::Person> updated_particles = disease.GetPopulation();

      // Particle 1
      REQUIRE(updated_particles[0].position == vec2(20.0, 20.0));
      REQUIRE(updated_particles[0].velocity == vec2(5.0, 5.0));
      REQUIRE(updated_particles[0].status == disease::Status::kSymptomatic);
      REQUIRE(updated_particles[0].color == vec3(1, 0, 0));
      REQUIRE(updated_particles[0].continuous_exposure_time == 0);
      REQUIRE(updated_particles[0].time_infected == 1);
      REQUIRE(updated_particles[0].is_quarantined == false);
      REQUIRE(updated_particles[0].is_social_distancing == false);
      REQUIRE(updated_particles[0].positions_of_people_in_bubble.empty());

      // Particle 2
      REQUIRE(updated_particles[1].position == vec2(10.0, 26.0));
      REQUIRE(updated_particles[1].velocity == vec2(-5.0, 6.0));
      REQUIRE(updated_particles[1].status == disease::Status::kRemoved);
      REQUIRE(updated_particles[1].color == vec3(0.5, 0.5, 0.5));
      REQUIRE(updated_particles[1].continuous_exposure_time == 0);
      REQUIRE(updated_particles[1].time_infected == 0);
      REQUIRE(updated_particles[1].is_quarantined == false);
      REQUIRE(updated_particles[1].is_social_distancing == false);
      REQUIRE(updated_particles[1].positions_of_people_in_bubble.empty());
    }

    SECTION("Person not exposed") {
      vector<Disease::Person> all_particles;

      // Particle 1
      person.radius = 10;
      person.position = vec2(15, 15);
      person.velocity = vec2(5, 5);
      person.status = disease::Status::kSymptomatic;
      person.color = vec3(1,0,0);
      person.continuous_exposure_time = 0;
      person.time_infected = 0;
      person.has_been_exposed_in_frame = false;
      person.is_quarantined = false;
      person.is_social_distancing = false;
      person.is_going_to_central_location = false;
      person.is_at_central_location = false;
      all_particles.push_back(person);

      // Particle 2
      person.radius = 10;
      person.position = vec2(60, 15);
      person.velocity = vec2(-5, 6);
      person.status = disease::Status::kRemoved;
      person.color = vec3(0.5,0.5,0.5);
      person.continuous_exposure_time = 0;
      person.time_infected = 0;
      person.has_been_exposed_in_frame = false;
      person.is_quarantined = false;
      person.is_social_distancing = false;
      person.is_going_to_central_location = false;
      person.is_at_central_location = false;
      all_particles.push_back(person);

      disease.SetPopulation(all_particles);
      disease.UpdateParticles();
      vector<Disease::Person> updated_particles = disease.GetPopulation();

      // Particle 1
      REQUIRE(updated_particles[0].position == vec2(20.0, 20.0));
      REQUIRE(updated_particles[0].velocity == vec2(5.0, 5.0));
      REQUIRE(updated_particles[0].status == disease::Status::kSymptomatic);
      REQUIRE(updated_particles[0].color == vec3(1, 0, 0));
      REQUIRE(updated_particles[0].continuous_exposure_time == 0);
      REQUIRE(updated_particles[0].time_infected == 1);
      REQUIRE(updated_particles[0].is_quarantined == false);
      REQUIRE(updated_particles[0].is_social_distancing == false);
      REQUIRE(updated_particles[0].positions_of_people_in_bubble.empty());

      // Particle 2
      REQUIRE(updated_particles[1].position == vec2(55.0, 21.0));
      REQUIRE(updated_particles[1].velocity == vec2(-5.0, 6.0));
      REQUIRE(updated_particles[1].status == disease::Status::kRemoved);
      REQUIRE(updated_particles[1].color == vec3(0.5, 0.5, 0.5));
      REQUIRE(updated_particles[1].continuous_exposure_time == 0);
      REQUIRE(updated_particles[1].time_infected == 0);
      REQUIRE(updated_particles[1].is_quarantined == false);
      REQUIRE(updated_particles[1].is_social_distancing == false);
      REQUIRE(updated_particles[1].positions_of_people_in_bubble.empty());
    }
  }
}

TEST_CASE("Check infected people get quarantined") {
  Disease disease = Disease(0, 0, 100, 100, vec2(150, 0), vec2(250, 100),
                            vec2(45, 45), vec2(55, 55),
                            25, 500, false, true, false,
                            false, false, false);
  Disease::Person person;

  disease.SetShouldQuarantine(true);

  SECTION("Infection time is exactly the time needed to be put into quarantine") {
    vector<Disease::Person> all_particles;

    // Particle 1
    person.radius = 10;
    person.position = vec2(15, 15);
    person.velocity = vec2(5, 5);
    person.status = disease::Status::kSymptomatic;
    person.color = vec3(1,0,0);
    person.continuous_exposure_time = 0;
    person.time_infected = 0;
    person.has_been_exposed_in_frame = false;
    person.is_quarantined = false;
    person.is_social_distancing = false;
    person.is_going_to_central_location = false;
    person.is_at_central_location = false;
    all_particles.push_back(person);

    // Particle 2
    person.radius = 10;
    person.position = vec2(60, 15);
    person.velocity = vec2(-5, 6);
    person.status = disease::Status::kSymptomatic;
    person.color = vec3(1,0,0);
    person.continuous_exposure_time = 0;
    person.time_infected = 69;
    person.has_been_exposed_in_frame = false;
    person.is_quarantined = false;
    person.is_social_distancing = false;
    person.is_going_to_central_location = false;
    person.is_at_central_location = false;
    all_particles.push_back(person);

    disease.SetPopulation(all_particles);
    disease.UpdateParticles();
    vector<Disease::Person> updated_particles = disease.GetPopulation();

    // Particle 1
    REQUIRE(updated_particles[0].position == vec2(20.0, 20.0));
    REQUIRE(updated_particles[0].velocity == vec2(5.0, 5.0));
    REQUIRE(updated_particles[0].status == disease::Status::kSymptomatic);
    REQUIRE(updated_particles[0].color == vec3(1, 0, 0));
    REQUIRE(updated_particles[0].continuous_exposure_time == 0);
    REQUIRE(updated_particles[0].time_infected == 1);
    REQUIRE(updated_particles[0].is_quarantined == false);
    REQUIRE(updated_particles[0].is_social_distancing == false);
    REQUIRE(updated_particles[0].positions_of_people_in_bubble.empty());

    // Particle 2
    REQUIRE(updated_particles[1].position.x >= 150);
    REQUIRE(updated_particles[1].position.x <= 250);
    REQUIRE(updated_particles[1].position.y >= 0);
    REQUIRE(updated_particles[1].position.y <= 100);
    REQUIRE(updated_particles[1].velocity == vec2(-5.0, 6.0));
    REQUIRE(updated_particles[1].status == disease::Status::kSymptomatic);
    REQUIRE(updated_particles[1].color == vec3(1, 0, 0));
    REQUIRE(updated_particles[1].continuous_exposure_time == 0);
    REQUIRE(updated_particles[1].time_infected == 70);
    REQUIRE(updated_particles[1].is_quarantined == true);
    REQUIRE(updated_particles[1].is_social_distancing == false);
    REQUIRE(updated_particles[1].positions_of_people_in_bubble.empty());
  }

  SECTION("Infection time is over the time needed to be put into quarantine") {
    vector<Disease::Person> all_particles;

    // Particle 1
    person.radius = 10;
    person.position = vec2(15, 15);
    person.velocity = vec2(5, 5);
    person.status = disease::Status::kSymptomatic;
    person.color = vec3(1,0,0);
    person.continuous_exposure_time = 0;
    person.time_infected = 0;
    person.has_been_exposed_in_frame = false;
    person.is_quarantined = false;
    person.is_social_distancing = false;
    person.is_going_to_central_location = false;
    person.is_at_central_location = false;
    all_particles.push_back(person);

    // Particle 2
    person.radius = 10;
    person.position = vec2(60, 15);
    person.velocity = vec2(-5, 6);
    person.status = disease::Status::kSymptomatic;
    person.color = vec3(1,0,0);
    person.continuous_exposure_time = 0;
    person.time_infected = 489;
    person.has_been_exposed_in_frame = false;
    person.is_quarantined = false;
    person.is_social_distancing = false;
    person.is_going_to_central_location = false;
    person.is_at_central_location = false;
    all_particles.push_back(person);

    disease.SetPopulation(all_particles);
    disease.UpdateParticles();
    vector<Disease::Person> updated_particles = disease.GetPopulation();

    // Particle 1
    REQUIRE(updated_particles[0].position == vec2(20.0, 20.0));
    REQUIRE(updated_particles[0].velocity == vec2(5.0, 5.0));
    REQUIRE(updated_particles[0].status == disease::Status::kSymptomatic);
    REQUIRE(updated_particles[0].color == vec3(1, 0, 0));
    REQUIRE(updated_particles[0].continuous_exposure_time == 0);
    REQUIRE(updated_particles[0].time_infected == 1);
    REQUIRE(updated_particles[0].is_quarantined == false);
    REQUIRE(updated_particles[0].is_social_distancing == false);
    REQUIRE(updated_particles[0].positions_of_people_in_bubble.empty());

    // Particle 2
    REQUIRE(updated_particles[1].position.x >= 150);
    REQUIRE(updated_particles[1].position.x <= 250);
    REQUIRE(updated_particles[1].position.y >= 0);
    REQUIRE(updated_particles[1].position.y <= 100);
    REQUIRE(updated_particles[1].velocity == vec2(-5.0, 6.0));
    REQUIRE(updated_particles[1].status == disease::Status::kSymptomatic);
    REQUIRE(updated_particles[1].color == vec3(1, 0, 0));
    REQUIRE(updated_particles[1].continuous_exposure_time == 0);
    REQUIRE(updated_particles[1].time_infected == 490);
    REQUIRE(updated_particles[1].is_quarantined == true);
    REQUIRE(updated_particles[1].is_social_distancing == false);
    REQUIRE(updated_particles[1].positions_of_people_in_bubble.empty());
  }
}

TEST_CASE("Check social distancing") {
  Disease disease = Disease(0, 0, 100, 100, vec2(150, 0), vec2(250, 100),
                            vec2(45, 45), vec2(55, 55),
                            25, 500, false, true, false,
                            false, false, false);
  Disease::Person person;

  SECTION("Check percent performing social distancing works") {
    SECTION("0 percent social distancing") {
      disease.SetPercentPerformingSocialDistance(0);
      disease.CreatePopulation();
      vector<Disease::Person> population = disease.GetPopulation();

      size_t num_social_distancing = 0;
      for (const Disease::Person& p : population) {
        if (p.is_social_distancing) {
          num_social_distancing += 1;
        }
      }

      REQUIRE(num_social_distancing == 0);
    }

    SECTION("50 percent social distancing") {
      disease.SetPercentPerformingSocialDistance(50);
      disease.CreatePopulation();
      vector<Disease::Person> population = disease.GetPopulation();

      size_t num_social_distancing = 0;
      for (const Disease::Person& p : population) {
        if (p.is_social_distancing) {
          num_social_distancing += 1;
        }
      }

      REQUIRE(num_social_distancing == 100);
    }

    SECTION("100 percent social distancing") {
      disease.SetPercentPerformingSocialDistance(100);
      disease.CreatePopulation();
      vector<Disease::Person> population = disease.GetPopulation();

      size_t num_social_distancing = 0;
      for (const Disease::Person& p : population) {
        if (p.is_social_distancing) {
          num_social_distancing += 1;
        }
      }

      REQUIRE(num_social_distancing == 201);
    }
  }

  SECTION("W/ social distancing") {
    SECTION("W/ quarantine--no social distancing occurs even if they practice it") {
      disease.SetShouldQuarantine(true);

      vector<Disease::Person> all_particles;

      disease.SetPercentPerformingSocialDistance(100);

      // Particle 1
      person.radius = 10;
      person.position = vec2(175, 75);
      person.velocity = vec2(-5, 6);
      person.status = disease::Status::kSymptomatic;
      person.color = vec3(1,0,0);
      person.continuous_exposure_time = 0;
      person.time_infected = 69;
      person.has_been_exposed_in_frame = false;
      person.is_quarantined = true;
      person.is_social_distancing = true;
      person.is_going_to_central_location = false;
      person.is_at_central_location = false;
      all_particles.push_back(person);

      // Particle 2
      person.radius = 10;
      person.position = vec2(175, 55);
      person.velocity = vec2(-5, 6);
      person.status = disease::Status::kSymptomatic;
      person.color = vec3(1,0,0);
      person.continuous_exposure_time = 0;
      person.time_infected = 69;
      person.has_been_exposed_in_frame = false;
      person.is_quarantined = true;
      person.is_social_distancing = true;
      person.is_going_to_central_location = false;
      person.is_at_central_location = false;
      all_particles.push_back(person);

      disease.SetPopulation(all_particles);
      disease.UpdateParticles();
      vector<Disease::Person> updated_particles = disease.GetPopulation();

      // Particle 1
      REQUIRE(updated_particles[0].position == vec2(170, 81));
      REQUIRE(updated_particles[0].velocity == vec2(-5.0, 6.0));
      REQUIRE(updated_particles[0].status == disease::Status::kSymptomatic);
      REQUIRE(updated_particles[0].color == vec3(1, 0, 0));
      REQUIRE(updated_particles[0].continuous_exposure_time == 0);
      REQUIRE(updated_particles[0].time_infected == 70);
      REQUIRE(updated_particles[0].is_quarantined == true);
      REQUIRE(updated_particles[0].is_social_distancing == true);
      REQUIRE(updated_particles[0].positions_of_people_in_bubble.empty());

      // Particle 2
      REQUIRE(updated_particles[1].position == vec2(170, 61));
      REQUIRE(updated_particles[1].velocity == vec2(-5.0, 6.0));
      REQUIRE(updated_particles[1].status == disease::Status::kSymptomatic);
      REQUIRE(updated_particles[1].color == vec3(1, 0, 0));
      REQUIRE(updated_particles[1].continuous_exposure_time == 0);
      REQUIRE(updated_particles[1].time_infected == 70);
      REQUIRE(updated_particles[1].is_quarantined == true);
      REQUIRE(updated_particles[1].is_social_distancing == true);
      REQUIRE(updated_particles[1].positions_of_people_in_bubble.empty());
    }

    SECTION("W/o quarantine") {
      SECTION("Two particles") {
        SECTION("Both particles are social distancing") {
          vector<Disease::Person> all_particles;

          disease.SetPercentPerformingSocialDistance(100);

          // Particle 1
          person.radius = 10;
          person.position = vec2(75, 75);
          person.velocity = vec2(-5, 6);
          person.status = disease::Status::kSusceptible;
          person.color = vec3(0, 0, 1);
          person.continuous_exposure_time = 0;
          person.time_infected = 0;
          person.has_been_exposed_in_frame = false;
          person.is_quarantined = false;
          person.is_social_distancing = true;
          person.is_going_to_central_location = false;
          person.is_at_central_location = false;
          all_particles.push_back(person);

          // Particle 2
          person.radius = 10;
          person.position = vec2(75, 55);
          person.velocity = vec2(-5, 6);
          person.status = disease::Status::kSymptomatic;
          person.color = vec3(1, 0, 0);
          person.continuous_exposure_time = 0;
          person.time_infected = 69;
          person.has_been_exposed_in_frame = false;
          person.is_quarantined = false;
          person.is_social_distancing = true;
          person.is_going_to_central_location = false;
          person.is_at_central_location = false;
          all_particles.push_back(person);

          disease.SetPopulation(all_particles);
          disease.UpdateParticles();
          vector<Disease::Person> updated_particles = disease.GetPopulation();

          // Particle 1
          REQUIRE(updated_particles[0].position == vec2(70, 81));
          REQUIRE(updated_particles[0].velocity == vec2(-5.0, 6.0));
          REQUIRE(updated_particles[0].status == disease::Status::kSusceptible);
          REQUIRE(updated_particles[0].color == vec3(0, 0, 1));
          REQUIRE(updated_particles[0].continuous_exposure_time == 1);
          REQUIRE(updated_particles[0].time_infected == 0);
          REQUIRE(updated_particles[0].is_quarantined == false);
          REQUIRE(updated_particles[0].is_social_distancing == true);
          REQUIRE(updated_particles[0].positions_of_people_in_bubble["left"] == 0);
          REQUIRE(updated_particles[0].positions_of_people_in_bubble["right"] == 0);
          REQUIRE(updated_particles[0].positions_of_people_in_bubble["up"] == 1);
          REQUIRE(updated_particles[0].positions_of_people_in_bubble["down"] == 0);

          // Particle 2
          REQUIRE(updated_particles[1].position == vec2(70, 49));
          REQUIRE(updated_particles[1].velocity == vec2(-5.0, -6.0));
          REQUIRE(updated_particles[1].status == disease::Status::kSymptomatic);
          REQUIRE(updated_particles[1].color == vec3(1, 0, 0));
          REQUIRE(updated_particles[1].continuous_exposure_time == 0);
          REQUIRE(updated_particles[1].time_infected == 70);
          REQUIRE(updated_particles[1].is_quarantined == false);
          REQUIRE(updated_particles[1].is_social_distancing == true);
          REQUIRE(updated_particles[1].positions_of_people_in_bubble["left"] == 0);
          REQUIRE(updated_particles[1].positions_of_people_in_bubble["right"] == 0);
          REQUIRE(updated_particles[1].positions_of_people_in_bubble["up"] == 0);
          REQUIRE(updated_particles[1].positions_of_people_in_bubble["down"] == 1);
        }

        SECTION("One of two particles are social distancing") {
          vector<Disease::Person> all_particles;

          disease.SetPercentPerformingSocialDistance(100);

          // Particle 1
          person.radius = 10;
          person.position = vec2(75, 75);
          person.velocity = vec2(-5, 6);
          person.status = disease::Status::kSusceptible;
          person.color = vec3(0, 0, 1);
          person.continuous_exposure_time = 0;
          person.time_infected = 0;
          person.has_been_exposed_in_frame = false;
          person.is_quarantined = false;
          person.is_social_distancing = true;
          person.is_going_to_central_location = false;
          person.is_at_central_location = false;
          all_particles.push_back(person);

          // Particle 2
          person.radius = 10;
          person.position = vec2(75, 55);
          person.velocity = vec2(-5, 6);
          person.status = disease::Status::kSymptomatic;
          person.color = vec3(1, 0, 0);
          person.continuous_exposure_time = 0;
          person.time_infected = 69;
          person.has_been_exposed_in_frame = false;
          person.is_quarantined = false;
          person.is_social_distancing = false;
          person.is_going_to_central_location = false;
          person.is_at_central_location = false;
          all_particles.push_back(person);

          disease.SetPopulation(all_particles);
          disease.UpdateParticles();
          vector<Disease::Person> updated_particles = disease.GetPopulation();

          // Particle 1
          REQUIRE(updated_particles[0].position == vec2(70, 81));
          REQUIRE(updated_particles[0].velocity == vec2(-5.0, 6.0));
          REQUIRE(updated_particles[0].status == disease::Status::kSusceptible);
          REQUIRE(updated_particles[0].color == vec3(0, 0, 1));
          REQUIRE(updated_particles[0].continuous_exposure_time == 1);
          REQUIRE(updated_particles[0].time_infected == 0);
          REQUIRE(updated_particles[0].is_quarantined == false);
          REQUIRE(updated_particles[0].is_social_distancing == true);
          REQUIRE(updated_particles[0].positions_of_people_in_bubble["left"] == 0);
          REQUIRE(updated_particles[0].positions_of_people_in_bubble["right"] == 0);
          REQUIRE(updated_particles[0].positions_of_people_in_bubble["up"] == 1);
          REQUIRE(updated_particles[0].positions_of_people_in_bubble["down"] == 0);

          // Particle 2
          REQUIRE(updated_particles[1].position == vec2(70, 61));
          REQUIRE(updated_particles[1].velocity == vec2(-5.0, 6.0));
          REQUIRE(updated_particles[1].status == disease::Status::kSymptomatic);
          REQUIRE(updated_particles[1].color == vec3(1, 0, 0));
          REQUIRE(updated_particles[1].continuous_exposure_time == 0);
          REQUIRE(updated_particles[1].time_infected == 70);
          REQUIRE(updated_particles[1].is_quarantined == false);
          REQUIRE(updated_particles[1].is_social_distancing == false);
          REQUIRE(updated_particles[1].positions_of_people_in_bubble.empty());
        }
      }

      SECTION("Three particles") {
        SECTION("All particles are social distancing") {
          vector<Disease::Person> all_particles;

          disease.SetPercentPerformingSocialDistance(100);

          // Particle 1
          person.radius = 10;
          person.position = vec2(75, 75);
          person.velocity = vec2(-5, 6);
          person.status = disease::Status::kSusceptible;
          person.color = vec3(0, 0, 1);
          person.continuous_exposure_time = 0;
          person.time_infected = 0;
          person.has_been_exposed_in_frame = false;
          person.is_quarantined = false;
          person.is_social_distancing = true;
          person.is_going_to_central_location = false;
          person.is_at_central_location = false;
          all_particles.push_back(person);

          // Particle 2
          person.radius = 10;
          person.position = vec2(75, 55);
          person.velocity = vec2(-5, 6);
          person.status = disease::Status::kSymptomatic;
          person.color = vec3(1, 0, 0);
          person.continuous_exposure_time = 0;
          person.time_infected = 69;
          person.has_been_exposed_in_frame = false;
          person.is_quarantined = false;
          person.is_social_distancing = true;
          person.is_going_to_central_location = false;
          person.is_at_central_location = false;
          all_particles.push_back(person);

          // Particle 3
          person.radius = 10;
          person.position = vec2(55, 55);
          person.velocity = vec2(-5, 6);
          person.status = disease::Status::kSymptomatic;
          person.color = vec3(1, 0, 0);
          person.continuous_exposure_time = 0;
          person.time_infected = 69;
          person.has_been_exposed_in_frame = false;
          person.is_quarantined = false;
          person.is_social_distancing = true;
          person.is_going_to_central_location = false;
          person.is_at_central_location = false;
          all_particles.push_back(person);

          disease.SetPopulation(all_particles);
          disease.UpdateParticles();
          vector<Disease::Person> updated_particles = disease.GetPopulation();

          // Particle 1
          REQUIRE(updated_particles[0].position == vec2(70, 81));
          REQUIRE(updated_particles[0].velocity == vec2(-5.0, 6.0));
          REQUIRE(updated_particles[0].status == disease::Status::kSusceptible);
          REQUIRE(updated_particles[0].color == vec3(0, 0, 1));
          REQUIRE(updated_particles[0].continuous_exposure_time == 1);
          REQUIRE(updated_particles[0].time_infected == 0);
          REQUIRE(updated_particles[0].is_quarantined == false);
          REQUIRE(updated_particles[0].is_social_distancing == true);
          REQUIRE(updated_particles[0].positions_of_people_in_bubble["left"] == 0);
          REQUIRE(updated_particles[0].positions_of_people_in_bubble["right"] == 0);
          REQUIRE(updated_particles[0].positions_of_people_in_bubble["up"] == 1);
          REQUIRE(updated_particles[0].positions_of_people_in_bubble["down"] == 0);

          // Particle 2
          REQUIRE(updated_particles[1].position == vec2(80, 49));
          REQUIRE(updated_particles[1].velocity == vec2(5.0, -6.0));
          REQUIRE(updated_particles[1].status == disease::Status::kSymptomatic);
          REQUIRE(updated_particles[1].color == vec3(1, 0, 0));
          REQUIRE(updated_particles[1].continuous_exposure_time == 0);
          REQUIRE(updated_particles[1].time_infected == 70);
          REQUIRE(updated_particles[1].is_quarantined == false);
          REQUIRE(updated_particles[1].is_social_distancing == true);
          REQUIRE(updated_particles[1].positions_of_people_in_bubble["left"] == 1);
          REQUIRE(updated_particles[1].positions_of_people_in_bubble["right"] == 0);
          REQUIRE(updated_particles[1].positions_of_people_in_bubble["up"] == 0);
          REQUIRE(updated_particles[1].positions_of_people_in_bubble["down"] == 1);

          // Particle 3
          REQUIRE(updated_particles[2].position == vec2(50, 61));
          REQUIRE(updated_particles[2].velocity == vec2(-5.0, 6.0));
          REQUIRE(updated_particles[2].status == disease::Status::kSymptomatic);
          REQUIRE(updated_particles[2].color == vec3(1, 0, 0));
          REQUIRE(updated_particles[2].continuous_exposure_time == 0);
          REQUIRE(updated_particles[2].time_infected == 70);
          REQUIRE(updated_particles[2].is_quarantined == false);
          REQUIRE(updated_particles[2].is_social_distancing == true);
          REQUIRE(updated_particles[2].positions_of_people_in_bubble["left"] == 0);
          REQUIRE(updated_particles[2].positions_of_people_in_bubble["right"] == 1);
          REQUIRE(updated_particles[2].positions_of_people_in_bubble["up"] == 0);
          REQUIRE(updated_particles[2].positions_of_people_in_bubble["down"] == 0);
        }

        SECTION("One of three particles are social distancing") {
          vector<Disease::Person> all_particles;

          disease.SetPercentPerformingSocialDistance(100);

          // Particle 1
          person.radius = 10;
          person.position = vec2(75, 75);
          person.velocity = vec2(-5, 6);
          person.status = disease::Status::kSusceptible;
          person.color = vec3(0, 0, 1);
          person.continuous_exposure_time = 0;
          person.time_infected = 0;
          person.has_been_exposed_in_frame = false;
          person.is_quarantined = false;
          person.is_social_distancing = true;
          person.is_going_to_central_location = false;
          person.is_at_central_location = false;
          all_particles.push_back(person);

          // Particle 2
          person.radius = 10;
          person.position = vec2(75, 55);
          person.velocity = vec2(-5, 6);
          person.status = disease::Status::kSymptomatic;
          person.color = vec3(1, 0, 0);
          person.continuous_exposure_time = 0;
          person.time_infected = 69;
          person.has_been_exposed_in_frame = false;
          person.is_quarantined = false;
          person.is_social_distancing = true;
          person.is_going_to_central_location = false;
          person.is_at_central_location = false;
          all_particles.push_back(person);

          // Particle 3
          person.radius = 10;
          person.position = vec2(55, 55);
          person.velocity = vec2(-5, 6);
          person.status = disease::Status::kSymptomatic;
          person.color = vec3(1, 0, 0);
          person.continuous_exposure_time = 0;
          person.time_infected = 69;
          person.has_been_exposed_in_frame = false;
          person.is_quarantined = false;
          person.is_social_distancing = false;
          person.is_going_to_central_location = false;
          person.is_at_central_location = false;
          all_particles.push_back(person);

          disease.SetPopulation(all_particles);
          disease.UpdateParticles();
          vector<Disease::Person> updated_particles = disease.GetPopulation();

          // Particle 1
          REQUIRE(updated_particles[0].position == vec2(70, 81));
          REQUIRE(updated_particles[0].velocity == vec2(-5.0, 6.0));
          REQUIRE(updated_particles[0].status == disease::Status::kSusceptible);
          REQUIRE(updated_particles[0].color == vec3(0, 0, 1));
          REQUIRE(updated_particles[0].continuous_exposure_time == 1);
          REQUIRE(updated_particles[0].time_infected == 0);
          REQUIRE(updated_particles[0].is_quarantined == false);
          REQUIRE(updated_particles[0].is_social_distancing == true);
          REQUIRE(updated_particles[0].positions_of_people_in_bubble["left"] == 0);
          REQUIRE(updated_particles[0].positions_of_people_in_bubble["right"] == 0);
          REQUIRE(updated_particles[0].positions_of_people_in_bubble["up"] == 1);
          REQUIRE(updated_particles[0].positions_of_people_in_bubble["down"] == 0);

          // Particle 2
          REQUIRE(updated_particles[1].position == vec2(80, 49));
          REQUIRE(updated_particles[1].velocity == vec2(5.0, -6.0));
          REQUIRE(updated_particles[1].status == disease::Status::kSymptomatic);
          REQUIRE(updated_particles[1].color == vec3(1, 0, 0));
          REQUIRE(updated_particles[1].continuous_exposure_time == 0);
          REQUIRE(updated_particles[1].time_infected == 70);
          REQUIRE(updated_particles[1].is_quarantined == false);
          REQUIRE(updated_particles[1].is_social_distancing == true);
          REQUIRE(updated_particles[1].positions_of_people_in_bubble["left"] == 1);
          REQUIRE(updated_particles[1].positions_of_people_in_bubble["right"] == 0);
          REQUIRE(updated_particles[1].positions_of_people_in_bubble["up"] == 0);
          REQUIRE(updated_particles[1].positions_of_people_in_bubble["down"] == 1);

          // Particle 3
          REQUIRE(updated_particles[2].position == vec2(50, 61));
          REQUIRE(updated_particles[2].velocity == vec2(-5.0, 6.0));
          REQUIRE(updated_particles[2].status == disease::Status::kSymptomatic);
          REQUIRE(updated_particles[2].color == vec3(1, 0, 0));
          REQUIRE(updated_particles[2].continuous_exposure_time == 0);
          REQUIRE(updated_particles[2].time_infected == 70);
          REQUIRE(updated_particles[2].is_quarantined == false);
          REQUIRE(updated_particles[2].is_social_distancing == false);
          REQUIRE(updated_particles[2].positions_of_people_in_bubble.empty());
        }

        SECTION("Two of three particles are social distancing") {
          vector<Disease::Person> all_particles;

          disease.SetPercentPerformingSocialDistance(100);

          // Particle 1
          person.radius = 10;
          person.position = vec2(75, 75);
          person.velocity = vec2(-5, 6);
          person.status = disease::Status::kSusceptible;
          person.color = vec3(0, 0, 1);
          person.continuous_exposure_time = 0;
          person.time_infected = 0;
          person.has_been_exposed_in_frame = false;
          person.is_quarantined = false;
          person.is_social_distancing = true;
          person.is_going_to_central_location = false;
          person.is_at_central_location = false;
          all_particles.push_back(person);

          // Particle 2
          person.radius = 10;
          person.position = vec2(75, 55);
          person.velocity = vec2(-5, 6);
          person.status = disease::Status::kSymptomatic;
          person.color = vec3(1, 0, 0);
          person.continuous_exposure_time = 0;
          person.time_infected = 69;
          person.has_been_exposed_in_frame = false;
          person.is_quarantined = false;
          person.is_social_distancing = false;
          person.is_going_to_central_location = false;
          person.is_at_central_location = false;
          all_particles.push_back(person);

          // Particle 3
          person.radius = 10;
          person.position = vec2(55, 55);
          person.velocity = vec2(-5, 6);
          person.status = disease::Status::kSymptomatic;
          person.color = vec3(1, 0, 0);
          person.continuous_exposure_time = 0;
          person.time_infected = 69;
          person.has_been_exposed_in_frame = false;
          person.is_quarantined = false;
          person.is_social_distancing = false;
          person.is_going_to_central_location = false;
          person.is_at_central_location = false;
          all_particles.push_back(person);

          disease.SetPopulation(all_particles);
          disease.UpdateParticles();
          vector<Disease::Person> updated_particles = disease.GetPopulation();

          // Particle 1
          REQUIRE(updated_particles[0].position == vec2(70, 81));
          REQUIRE(updated_particles[0].velocity == vec2(-5.0, 6.0));
          REQUIRE(updated_particles[0].status == disease::Status::kSusceptible);
          REQUIRE(updated_particles[0].color == vec3(0, 0, 1));
          REQUIRE(updated_particles[0].continuous_exposure_time == 1);
          REQUIRE(updated_particles[0].time_infected == 0);
          REQUIRE(updated_particles[0].is_quarantined == false);
          REQUIRE(updated_particles[0].is_social_distancing == true);
          REQUIRE(updated_particles[0].positions_of_people_in_bubble["left"] == 0);
          REQUIRE(updated_particles[0].positions_of_people_in_bubble["right"] == 0);
          REQUIRE(updated_particles[0].positions_of_people_in_bubble["up"] == 1);
          REQUIRE(updated_particles[0].positions_of_people_in_bubble["down"] == 0);

          // Particle 2
          REQUIRE(updated_particles[1].position == vec2(70, 61));
          REQUIRE(updated_particles[1].velocity == vec2(-5.0, 6.0));
          REQUIRE(updated_particles[1].status == disease::Status::kSymptomatic);
          REQUIRE(updated_particles[1].color == vec3(1, 0, 0));
          REQUIRE(updated_particles[1].continuous_exposure_time == 0);
          REQUIRE(updated_particles[1].time_infected == 70);
          REQUIRE(updated_particles[1].is_quarantined == false);
          REQUIRE(updated_particles[1].is_social_distancing == false);
          REQUIRE(updated_particles[1].positions_of_people_in_bubble.empty());

          // Particle 3
          REQUIRE(updated_particles[2].position == vec2(50, 61));
          REQUIRE(updated_particles[2].velocity == vec2(-5.0, 6.0));
          REQUIRE(updated_particles[2].status == disease::Status::kSymptomatic);
          REQUIRE(updated_particles[2].color == vec3(1, 0, 0));
          REQUIRE(updated_particles[2].continuous_exposure_time == 0);
          REQUIRE(updated_particles[2].time_infected == 70);
          REQUIRE(updated_particles[2].is_quarantined == false);
          REQUIRE(updated_particles[2].is_social_distancing == false);
          REQUIRE(updated_particles[2].positions_of_people_in_bubble.empty());
        }
      }
    }
  }
}

TEST_CASE("Check wall collisions w/ central location") {
  Disease disease = Disease(0, 0, 100, 100, vec2(150, 0), vec2(250, 100),
                            vec2(45, 45), vec2(55, 55),
                            25, 500, false, true, false,
                            false, false, false);
  Disease::Person person;
  disease.SetHaveCentralLocation(true);

  SECTION("Wall collisions on inside") {
    SECTION("Particles who are at the location should collide with walls") {
      vector<Disease::Person> all_particles;

      person.radius = 2;
      person.position = vec2(47, 50);
      person.velocity = vec2(-0.5, 0.6);
      person.status = disease::Status::kSusceptible;
      person.color = vec3(0, 0, 1);
      person.continuous_exposure_time = 0;
      person.time_infected = 0;
      person.has_been_exposed_in_frame = false;
      person.is_quarantined = false;
      person.is_social_distancing = false;
      person.is_going_to_central_location = false;
      person.is_at_central_location = true;
      all_particles.push_back(person);

      disease.SetPopulation(all_particles);
      disease.UpdateParticles();
      vector<Disease::Person> updated_particles = disease.GetPopulation();

      REQUIRE(updated_particles[0].position == vec2(47.5, 50.6));
      REQUIRE(updated_particles[0].velocity == vec2(0.5, 0.6));
      REQUIRE(updated_particles[0].status == disease::Status::kSusceptible);
      REQUIRE(updated_particles[0].color == vec3(0, 0, 1));
      REQUIRE(updated_particles[0].continuous_exposure_time == 0);
      REQUIRE(updated_particles[0].time_infected == 0);
      REQUIRE(updated_particles[0].is_quarantined == false);
      REQUIRE(updated_particles[0].is_social_distancing == false);
      REQUIRE(updated_particles[0].positions_of_people_in_bubble.empty());
      REQUIRE(updated_particles[0].is_going_to_central_location == false);
      REQUIRE(updated_particles[0].is_at_central_location == true);
    }

    SECTION("Particles who are going to the location should not collide"
            "with walls") {
      // TODO: Figure out if it's possible to test this based on current implementation
    }

    SECTION("Particles who don't have anything to do with the location"
            "should not collide with walls") {
      vector<Disease::Person> all_particles;

      person.radius = 2;
      person.position = vec2(47, 50);
      person.velocity = vec2(-0.5, 0.6);
      person.status = disease::Status::kSusceptible;
      person.color = vec3(0, 0, 1);
      person.continuous_exposure_time = 0;
      person.time_infected = 0;
      person.has_been_exposed_in_frame = false;
      person.is_quarantined = false;
      person.is_social_distancing = false;
      person.is_going_to_central_location = false;
      person.is_at_central_location = false;
      all_particles.push_back(person);

      disease.SetPopulation(all_particles);
      disease.UpdateParticles();
      vector<Disease::Person> updated_particles = disease.GetPopulation();

      REQUIRE(updated_particles[0].position == vec2(46.5, 50.6));
      REQUIRE(updated_particles[0].velocity == vec2(-0.5, 0.6));
      REQUIRE(updated_particles[0].status == disease::Status::kSusceptible);
      REQUIRE(updated_particles[0].color == vec3(0, 0, 1));
      REQUIRE(updated_particles[0].continuous_exposure_time == 0);
      REQUIRE(updated_particles[0].time_infected == 0);
      REQUIRE(updated_particles[0].is_quarantined == false);
      REQUIRE(updated_particles[0].is_social_distancing == false);
      REQUIRE(updated_particles[0].positions_of_people_in_bubble.empty());
      REQUIRE(updated_particles[0].is_going_to_central_location == false);
      REQUIRE(updated_particles[0].is_at_central_location == false);
    }
  }

  SECTION("Wall collisions on outside") {
    SECTION("Particles who are not within the location should collide with outside walls") {
      person.radius = 2;
      person.status = disease::Status::kSusceptible;
      person.color = vec3(0, 0, 1);
      person.continuous_exposure_time = 0;
      person.time_infected = 0;
      person.has_been_exposed_in_frame = false;
      person.is_quarantined = false;
      person.is_social_distancing = false;
      person.is_going_to_central_location = false;
      person.is_at_central_location = false;

      SECTION("Left wall") {
        vector<Disease::Person> all_particles;
        person.position = vec2(43, 50);
        person.velocity = vec2(0.5, 0.6);
        all_particles.push_back(person);

        disease.SetPopulation(all_particles);
        disease.UpdateParticles();
        vector<Disease::Person> updated_particles = disease.GetPopulation();

        REQUIRE(updated_particles[0].position == vec2(42.5, 50.6));
        REQUIRE(updated_particles[0].velocity == vec2(-0.5, 0.6));
        REQUIRE(updated_particles[0].status == disease::Status::kSusceptible);
        REQUIRE(updated_particles[0].color == vec3(0, 0, 1));
        REQUIRE(updated_particles[0].continuous_exposure_time == 0);
        REQUIRE(updated_particles[0].time_infected == 0);
        REQUIRE(updated_particles[0].is_quarantined == false);
        REQUIRE(updated_particles[0].is_social_distancing == false);
        REQUIRE(updated_particles[0].positions_of_people_in_bubble.empty());
        REQUIRE(updated_particles[0].is_going_to_central_location == false);
        REQUIRE(updated_particles[0].is_at_central_location == false);
      }

      SECTION("Top wall") {
        vector<Disease::Person> all_particles;
        person.position = vec2(50, 43);
        person.velocity = vec2(0.5, 0.6);
        all_particles.push_back(person);

        disease.SetPopulation(all_particles);
        disease.UpdateParticles();
        vector<Disease::Person> updated_particles = disease.GetPopulation();

        REQUIRE(updated_particles[0].position == vec2(50.5, 42.4));
        REQUIRE(updated_particles[0].velocity == vec2(0.5, -0.6));
        REQUIRE(updated_particles[0].status == disease::Status::kSusceptible);
        REQUIRE(updated_particles[0].color == vec3(0, 0, 1));
        REQUIRE(updated_particles[0].continuous_exposure_time == 0);
        REQUIRE(updated_particles[0].time_infected == 0);
        REQUIRE(updated_particles[0].is_quarantined == false);
        REQUIRE(updated_particles[0].is_social_distancing == false);
        REQUIRE(updated_particles[0].positions_of_people_in_bubble.empty());
        REQUIRE(updated_particles[0].is_going_to_central_location == false);
        REQUIRE(updated_particles[0].is_at_central_location == false);
      }

      SECTION("Right wall") {
        vector<Disease::Person> all_particles;
        person.position = vec2(57, 50);
        person.velocity = vec2(-0.5, 0.6);
        all_particles.push_back(person);

        disease.SetPopulation(all_particles);
        disease.UpdateParticles();
        vector<Disease::Person> updated_particles = disease.GetPopulation();

        REQUIRE(updated_particles[0].position == vec2(57.5, 50.6));
        REQUIRE(updated_particles[0].velocity == vec2(0.5, 0.6));
        REQUIRE(updated_particles[0].status == disease::Status::kSusceptible);
        REQUIRE(updated_particles[0].color == vec3(0, 0, 1));
        REQUIRE(updated_particles[0].continuous_exposure_time == 0);
        REQUIRE(updated_particles[0].time_infected == 0);
        REQUIRE(updated_particles[0].is_quarantined == false);
        REQUIRE(updated_particles[0].is_social_distancing == false);
        REQUIRE(updated_particles[0].positions_of_people_in_bubble.empty());
        REQUIRE(updated_particles[0].is_going_to_central_location == false);
        REQUIRE(updated_particles[0].is_at_central_location == false);
      }

      SECTION("Bottom wall") {
        vector<Disease::Person> all_particles;
        person.position = vec2(50, 57);
        person.velocity = vec2(0.5, -0.6);
        all_particles.push_back(person);

        disease.SetPopulation(all_particles);
        disease.UpdateParticles();
        vector<Disease::Person> updated_particles = disease.GetPopulation();

        REQUIRE(updated_particles[0].position == vec2(50.5, 57.6));
        REQUIRE(updated_particles[0].velocity == vec2(0.5, 0.6));
        REQUIRE(updated_particles[0].status == disease::Status::kSusceptible);
        REQUIRE(updated_particles[0].color == vec3(0, 0, 1));
        REQUIRE(updated_particles[0].continuous_exposure_time == 0);
        REQUIRE(updated_particles[0].time_infected == 0);
        REQUIRE(updated_particles[0].is_quarantined == false);
        REQUIRE(updated_particles[0].is_social_distancing == false);
        REQUIRE(updated_particles[0].positions_of_people_in_bubble.empty());
        REQUIRE(updated_particles[0].is_going_to_central_location == false);
        REQUIRE(updated_particles[0].is_at_central_location == false);
      }
    }

    // NOTE: The following section will fail if the visualization of particles moving to location is not implemented
    SECTION("Particles who are going to the location should not collide with outside walls") {
      person.radius = 2;
      person.status = disease::Status::kSusceptible;
      person.color = vec3(0, 0, 1);
      person.continuous_exposure_time = 0;
      person.time_infected = 0;
      person.has_been_exposed_in_frame = false;
      person.is_quarantined = false;
      person.is_social_distancing = false;
      person.is_going_to_central_location = true;
      person.is_at_central_location = false;

      SECTION("Left wall") {
        vector<Disease::Person> all_particles;
        person.position = vec2(43, 50);
        person.velocity = vec2(0.5, 0.6);
        all_particles.push_back(person);

        disease.SetPopulation(all_particles);
        disease.UpdateParticles();
        vector<Disease::Person> updated_particles = disease.GetPopulation();

        REQUIRE(updated_particles[0].position == vec2(43.5, 50.6));
        REQUIRE(updated_particles[0].velocity == vec2(0.5, 0.6));
        REQUIRE(updated_particles[0].status == disease::Status::kSusceptible);
        REQUIRE(updated_particles[0].color == vec3(0, 0, 1));
        REQUIRE(updated_particles[0].continuous_exposure_time == 0);
        REQUIRE(updated_particles[0].time_infected == 0);
        REQUIRE(updated_particles[0].is_quarantined == false);
        REQUIRE(updated_particles[0].is_social_distancing == false);
        REQUIRE(updated_particles[0].positions_of_people_in_bubble.empty());
        REQUIRE(updated_particles[0].is_going_to_central_location == true);
        REQUIRE(updated_particles[0].is_at_central_location == false);
      }

      SECTION("Top wall") {
        vector<Disease::Person> all_particles;
        person.position = vec2(50, 43);
        person.velocity = vec2(0.5, 0.6);
        all_particles.push_back(person);

        disease.SetPopulation(all_particles);
        disease.UpdateParticles();
        vector<Disease::Person> updated_particles = disease.GetPopulation();

        REQUIRE(updated_particles[0].position == vec2(50.5, 43.6));
        REQUIRE(updated_particles[0].velocity == vec2(0.5, 0.6));
        REQUIRE(updated_particles[0].status == disease::Status::kSusceptible);
        REQUIRE(updated_particles[0].color == vec3(0, 0, 1));
        REQUIRE(updated_particles[0].continuous_exposure_time == 0);
        REQUIRE(updated_particles[0].time_infected == 0);
        REQUIRE(updated_particles[0].is_quarantined == false);
        REQUIRE(updated_particles[0].is_social_distancing == false);
        REQUIRE(updated_particles[0].positions_of_people_in_bubble.empty());
        REQUIRE(updated_particles[0].is_going_to_central_location == true);
        REQUIRE(updated_particles[0].is_at_central_location == false);
      }

      SECTION("Right wall") {
        vector<Disease::Person> all_particles;
        person.position = vec2(57, 50);
        person.velocity = vec2(-0.5, 0.6);
        all_particles.push_back(person);

        disease.SetPopulation(all_particles);
        disease.UpdateParticles();
        vector<Disease::Person> updated_particles = disease.GetPopulation();

        REQUIRE(updated_particles[0].position == vec2(56.5, 50.6));
        REQUIRE(updated_particles[0].velocity == vec2(-0.5, 0.6));
        REQUIRE(updated_particles[0].status == disease::Status::kSusceptible);
        REQUIRE(updated_particles[0].color == vec3(0, 0, 1));
        REQUIRE(updated_particles[0].continuous_exposure_time == 0);
        REQUIRE(updated_particles[0].time_infected == 0);
        REQUIRE(updated_particles[0].is_quarantined == false);
        REQUIRE(updated_particles[0].is_social_distancing == false);
        REQUIRE(updated_particles[0].positions_of_people_in_bubble.empty());
        REQUIRE(updated_particles[0].is_going_to_central_location == true);
        REQUIRE(updated_particles[0].is_at_central_location == false);
      }

      SECTION("Bottom wall") {
        vector<Disease::Person> all_particles;
        person.position = vec2(50, 57);
        person.velocity = vec2(0.5, -0.6);
        all_particles.push_back(person);

        disease.SetPopulation(all_particles);
        disease.UpdateParticles();
        vector<Disease::Person> updated_particles = disease.GetPopulation();

        REQUIRE(updated_particles[0].position == vec2(50.5, 56.4));
        REQUIRE(updated_particles[0].velocity == vec2(0.5, -0.6));
        REQUIRE(updated_particles[0].status == disease::Status::kSusceptible);
        REQUIRE(updated_particles[0].color == vec3(0, 0, 1));
        REQUIRE(updated_particles[0].continuous_exposure_time == 0);
        REQUIRE(updated_particles[0].time_infected == 0);
        REQUIRE(updated_particles[0].is_quarantined == false);
        REQUIRE(updated_particles[0].is_social_distancing == false);
        REQUIRE(updated_particles[0].positions_of_people_in_bubble.empty());
        REQUIRE(updated_particles[0].is_going_to_central_location == true);
        REQUIRE(updated_particles[0].is_at_central_location == false);
      }
    }

    SECTION("Particles who are not near the location should not collide with outside of location walls") {
      SECTION("Left wall") {

      }

      SECTION("Top wall") {

      }

      SECTION("Right wall") {

      }

      SECTION("Bottom wall") {

      }
    }
  }
}

TEST_CASE("Check particle updates properly w/ a central location") {
  Disease disease = Disease(0, 0, 100, 100, vec2(150, 0), vec2(250, 100),
                            vec2(45, 45), vec2(55, 55),
                            25, 500, false, true, false,
                            false, false, false);
  disease.SetHaveCentralLocation(true);
  Disease::Person person;

  SECTION("Person meets threshold") {
    Disease disease1 = Disease(0, 0, 100, 100, vec2(150, 0), vec2(250, 100),
                              vec2(45, 45), vec2(55, 55),
                              25, 500, false, true, false,
                              false, false, true);
    disease1.SetHaveCentralLocation(true);

    SECTION("Person is currently not going or at location") {
      // Person should go to location

    }

    SECTION("Person is currently at location") {
      // Person should leave location
    }
  }

  SECTION("Person doesn't meet threshold") {
    SECTION("Person is currently not going or at location") {
      // Person shouldn't go to location

    }

    SECTION("Person is currently at location") {
      // Person shouldn't leave location
    }
  }

  SECTION("Person is currently going to location") {
    // Person should be at location
    vector<Disease::Person> all_particles;

    person.radius = 2;
    person.position = vec2(65, 70);
    person.velocity = vec2(-0.5, 0.6);
    person.status = disease::Status::kSusceptible;
    person.color = vec3(0, 0, 1);
    person.continuous_exposure_time = 0;
    person.time_infected = 0;
    person.has_been_exposed_in_frame = false;
    person.is_quarantined = false;
    person.is_social_distancing = false;
    person.is_going_to_central_location = true;
    person.is_at_central_location = false;
    all_particles.push_back(person);

    disease.SetPopulation(all_particles);
    disease.UpdateParticles();
    vector<Disease::Person> updated_particles = disease.GetPopulation();

    REQUIRE(updated_particles[0].position.x >= 45);
    REQUIRE(updated_particles[0].position.x <= 55);
    REQUIRE(updated_particles[0].position.y >= 45);
    REQUIRE(updated_particles[0].position.y <= 55);
    REQUIRE(updated_particles[0].velocity == vec2(-0.5, 0.6));
    REQUIRE(updated_particles[0].status == disease::Status::kSusceptible);
    REQUIRE(updated_particles[0].color == vec3(0, 0, 1));
    REQUIRE(updated_particles[0].continuous_exposure_time == 0);
    REQUIRE(updated_particles[0].time_infected == 0);
    REQUIRE(updated_particles[0].is_quarantined == false);
    REQUIRE(updated_particles[0].is_social_distancing == false);
    REQUIRE(updated_particles[0].positions_of_people_in_bubble.empty());
    REQUIRE(updated_particles[0].is_going_to_central_location == false);
    REQUIRE(updated_particles[0].is_at_central_location == true);
  }

  SECTION("Person is in quarantine--going to and at central location should be false") {

  }

  SECTION("Person social distances while at central location") {

  }
}