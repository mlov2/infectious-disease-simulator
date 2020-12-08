#include <core/infectious_disease.h>

#include <catch2/catch.hpp>

using disease::Disease;
using disease::Status;

TEST_CASE("Create population", "[create population]") {
  SECTION("Create population when container is empty") {
    Disease disease = Disease(0, 0, 100, 100, vec2(150, 0), vec2(250, 100));

    disease.CreatePopulation();

    vector<Disease::Person> all_particles = disease.GetPopulation();
    REQUIRE(all_particles.size() == 201);

    // Susceptible people created
    for (size_t i = 0; i < all_particles.size() - 1; i++) {
      REQUIRE(all_particles[i].radius == 10);
      REQUIRE(all_particles[i].position.x >= 0);
      REQUIRE(all_particles[i].position.x <= 100);
      REQUIRE(all_particles[i].position.y >= 0);
      REQUIRE(all_particles[i].position.y <= 100);
      REQUIRE(all_particles[i].velocity.x >= -1);
      REQUIRE(all_particles[i].velocity.x <= 1);
      REQUIRE(all_particles[i].velocity.y >= -1);
      REQUIRE(all_particles[i].velocity.y <= 1);
      REQUIRE(all_particles[i].status == disease::Status::kSusceptible);
      REQUIRE(all_particles[i].color == vec3(0, 0, 1));
      REQUIRE(all_particles[i].continuous_exposure_time == 0);
      REQUIRE(all_particles[i].time_infected == 0);
      REQUIRE(all_particles[i].has_been_exposed_in_frame == false);
      REQUIRE(all_particles[i].is_quarantined == false);
      REQUIRE(all_particles[i].is_social_distancing == false);
      REQUIRE(all_particles[i].positions_of_people_in_bubble.empty());
    }

    // Patient zero created
    REQUIRE(all_particles[all_particles.size() - 1].radius == 10);
    REQUIRE(all_particles[all_particles.size() - 1].position.x >= 0);
    REQUIRE(all_particles[all_particles.size() - 1].position.x <= 100);
    REQUIRE(all_particles[all_particles.size() - 1].position.y >= 0);
    REQUIRE(all_particles[all_particles.size() - 1].position.y <= 100);
    REQUIRE(all_particles[all_particles.size() - 1].velocity.x >= -1);
    REQUIRE(all_particles[all_particles.size() - 1].velocity.x <= 1);
    REQUIRE(all_particles[all_particles.size() - 1].velocity.y >= -1);
    REQUIRE(all_particles[all_particles.size() - 1].velocity.y <= 1);
    REQUIRE(all_particles[all_particles.size() - 1].status == disease::Status::kSymptomatic);
    REQUIRE(all_particles[all_particles.size() - 1].color == vec3(1, 0, 0));
    REQUIRE(all_particles[all_particles.size() - 1].continuous_exposure_time == 0);
    REQUIRE(all_particles[all_particles.size() - 1].time_infected == 0);
    REQUIRE(all_particles[all_particles.size() - 1].has_been_exposed_in_frame == false);
    REQUIRE(all_particles[all_particles.size() - 1].is_quarantined == false);
    REQUIRE(all_particles[all_particles.size() - 1].is_social_distancing == false);
    REQUIRE(all_particles[all_particles.size() - 1].positions_of_people_in_bubble.empty());
  }

  SECTION("Population isn't created more than once") {
    Disease disease = Disease(0, 0, 100, 100, vec2(150, 0), vec2(250, 100));

    disease.CreatePopulation();
    disease.CreatePopulation();

    vector<Disease::Person> all_particles = disease.GetPopulation();
    REQUIRE(all_particles.size() == 201);

    // Susceptible people created
    for (size_t i = 0; i < all_particles.size() - 1; i++) {
      REQUIRE(all_particles[i].radius == 10);
      REQUIRE(all_particles[i].position.x >= 0);
      REQUIRE(all_particles[i].position.x <= 100);
      REQUIRE(all_particles[i].position.y >= 0);
      REQUIRE(all_particles[i].position.y <= 100);
      REQUIRE(all_particles[i].velocity.x >= -1);
      REQUIRE(all_particles[i].velocity.x <= 1);
      REQUIRE(all_particles[i].velocity.y >= -1);
      REQUIRE(all_particles[i].velocity.y <= 1);
      REQUIRE(all_particles[i].status == disease::Status::kSusceptible);
      REQUIRE(all_particles[i].color == vec3(0, 0, 1));
      REQUIRE(all_particles[i].continuous_exposure_time == 0);
      REQUIRE(all_particles[i].time_infected == 0);
      REQUIRE(all_particles[i].has_been_exposed_in_frame == false);
      REQUIRE(all_particles[i].is_quarantined == false);
      REQUIRE(all_particles[i].is_social_distancing == false);
      REQUIRE(all_particles[i].positions_of_people_in_bubble.empty());
    }

    // Patient zero created
    REQUIRE(all_particles[all_particles.size() - 1].radius == 10);
    REQUIRE(all_particles[all_particles.size() - 1].position.x >= 0);
    REQUIRE(all_particles[all_particles.size() - 1].position.x <= 100);
    REQUIRE(all_particles[all_particles.size() - 1].position.y >= 0);
    REQUIRE(all_particles[all_particles.size() - 1].position.y <= 100);
    REQUIRE(all_particles[all_particles.size() - 1].velocity.x >= -1);
    REQUIRE(all_particles[all_particles.size() - 1].velocity.x <= 1);
    REQUIRE(all_particles[all_particles.size() - 1].velocity.y >= -1);
    REQUIRE(all_particles[all_particles.size() - 1].velocity.y <= 1);
    REQUIRE(all_particles[all_particles.size() - 1].status == disease::Status::kSymptomatic);
    REQUIRE(all_particles[all_particles.size() - 1].color == vec3(1, 0, 0));
    REQUIRE(all_particles[all_particles.size() - 1].continuous_exposure_time == 0);
    REQUIRE(all_particles[all_particles.size() - 1].time_infected == 0);
    REQUIRE(all_particles[all_particles.size() - 1].has_been_exposed_in_frame == false);
    REQUIRE(all_particles[all_particles.size() - 1].is_quarantined == false);
    REQUIRE(all_particles[all_particles.size() - 1].is_social_distancing == false);
    REQUIRE(all_particles[all_particles.size() - 1].positions_of_people_in_bubble.empty());
  }
}

TEST_CASE("Person info updates after 1 frame (no collision)",
          "[one frame][no collision]") {
  Disease disease = Disease(0, 0, 100, 100, vec2(150, 0), vec2(250, 100));
  Disease::Person person;

  SECTION("No particles") {
    disease.UpdateParticles();

    vector<Disease::Person> updated_particles = disease.GetPopulation();

    REQUIRE(updated_particles.empty() == true);
  }

  SECTION("One particle") {
    vector<Disease::Person> all_particles;

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

    all_particles.push_back(person);

    disease.SetPopulation(all_particles);
    disease.UpdateParticles();
    vector<Disease::Person> updated_particles = disease.GetPopulation();

    REQUIRE(updated_particles[0].position == vec2(20.0, 20.0));
    REQUIRE(updated_particles[0].velocity == vec2(5, 5));
    REQUIRE(updated_particles[0].status == disease::Status::kSymptomatic);
    REQUIRE(updated_particles[0].color == vec3(1, 0, 0));
    REQUIRE(updated_particles[0].continuous_exposure_time == 0);
    REQUIRE(updated_particles[0].time_infected == 1);
    REQUIRE(updated_particles[0].is_quarantined == false);
    REQUIRE(updated_particles[0].is_social_distancing == false);
    REQUIRE(updated_particles[0].positions_of_people_in_bubble.empty());
  }

  SECTION("Two particles") {
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
    all_particles.push_back(person);

    // Particle 2
    person.radius = 10;
    person.position = vec2(55, 30);
    person.velocity = vec2(-5, 6);
    person.status = disease::Status::kSusceptible;
    person.color = vec3(0,0,1);
    person.continuous_exposure_time = 0;
    person.time_infected = 0;
    person.has_been_exposed_in_frame = false;
    person.is_quarantined = false;
    person.is_social_distancing = false;
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
    REQUIRE(updated_particles[1].position == vec2(50.0, 36.0));
    REQUIRE(updated_particles[1].velocity == vec2(-5.0, 6.0));
    REQUIRE(updated_particles[1].status == disease::Status::kSusceptible);
    REQUIRE(updated_particles[1].color == vec3(0, 0, 1));
    REQUIRE(updated_particles[1].continuous_exposure_time == 0);
    REQUIRE(updated_particles[1].time_infected == 0);
    REQUIRE(updated_particles[1].is_quarantined == false);
    REQUIRE(updated_particles[1].is_social_distancing == false);
    REQUIRE(updated_particles[1].positions_of_people_in_bubble.empty());
  }

  SECTION("Three particles") {
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
    all_particles.push_back(person);

    // Particle 2
    person.radius = 10;
    person.position = vec2(55, 30);
    person.velocity = vec2(-5, 6);
    person.status = disease::Status::kSusceptible;
    person.color = vec3(0,0,1);
    person.continuous_exposure_time = 0;
    person.time_infected = 0;
    person.has_been_exposed_in_frame = false;
    person.is_quarantined = false;
    person.is_social_distancing = false;
    all_particles.push_back(person);

    // Particle 3
    person.radius = 10;
    person.position = vec2(70, 80);
    person.velocity = vec2(-7.7, 3.4);
    person.status = disease::Status::kSusceptible;
    person.color = vec3(0,0,1);
    person.continuous_exposure_time = 0;
    person.time_infected = 0;
    person.has_been_exposed_in_frame = false;
    person.is_quarantined = false;
    person.is_social_distancing = false;
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
    REQUIRE(updated_particles[1].position == vec2(50.0, 36.0));
    REQUIRE(updated_particles[1].velocity == vec2(-5.0, 6.0));
    REQUIRE(updated_particles[1].status == disease::Status::kSusceptible);
    REQUIRE(updated_particles[1].color == vec3(0, 0, 1));
    REQUIRE(updated_particles[1].continuous_exposure_time == 0);
    REQUIRE(updated_particles[1].time_infected == 0);
    REQUIRE(updated_particles[1].is_quarantined == false);
    REQUIRE(updated_particles[1].is_social_distancing == false);
    REQUIRE(updated_particles[1].positions_of_people_in_bubble.empty());

    // Particle 3
    REQUIRE(updated_particles[2].position == vec2(62.3, 83.4));
    REQUIRE(updated_particles[2].velocity == vec2(-7.7, 3.4));
    REQUIRE(updated_particles[2].status == disease::Status::kSusceptible);
    REQUIRE(updated_particles[2].color == vec3(0, 0, 1));
    REQUIRE(updated_particles[2].continuous_exposure_time == 0);
    REQUIRE(updated_particles[2].time_infected == 0);
    REQUIRE(updated_particles[2].is_quarantined == false);
    REQUIRE(updated_particles[2].is_social_distancing == false);
    REQUIRE(updated_particles[2].positions_of_people_in_bubble.empty());
  }
}

TEST_CASE("Person info updates after 2 frames (no collision)",
          "[two frames][no collision]") {
  Disease disease = Disease(0, 0, 100, 100, vec2(150, 0), vec2(250, 100));
  Disease::Person person;

  SECTION("No particles") {
    disease.UpdateParticles();

    vector<Disease::Person> updated_particles = disease.GetPopulation();

    REQUIRE(updated_particles.empty() == true);
  }

  SECTION("One particle") {
    vector<Disease::Person> all_particles;

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
    all_particles.push_back(person);

    disease.SetPopulation(all_particles);
    disease.UpdateParticles();
    disease.UpdateParticles();
    vector<Disease::Person> updated_particles = disease.GetPopulation();

    REQUIRE(updated_particles[0].position == vec2(25.0, 25.0));
    REQUIRE(updated_particles[0].velocity == vec2(5, 5));
    REQUIRE(updated_particles[0].status == disease::Status::kSymptomatic);
    REQUIRE(updated_particles[0].color == vec3(1, 0, 0));
    REQUIRE(updated_particles[0].continuous_exposure_time == 0);
    REQUIRE(updated_particles[0].time_infected == 2);
    REQUIRE(updated_particles[0].is_quarantined == false);
    REQUIRE(updated_particles[0].is_social_distancing == false);
    REQUIRE(updated_particles[0].positions_of_people_in_bubble.empty());
  }

  SECTION("Two particles") {
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
    all_particles.push_back(person);

    // Particle 2
    person.radius = 10;
    person.position = vec2(55, 30);
    person.velocity = vec2(-5, 6);
    person.status = disease::Status::kSusceptible;
    person.color = vec3(0,0,1);
    person.continuous_exposure_time = 0;
    person.time_infected = 0;
    person.has_been_exposed_in_frame = false;
    person.is_quarantined = false;
    person.is_social_distancing = false;
    all_particles.push_back(person);

    disease.SetPopulation(all_particles);
    disease.UpdateParticles();
    disease.UpdateParticles();
    vector<Disease::Person> updated_particles = disease.GetPopulation();

    // Particle 1
    REQUIRE(updated_particles[0].position == vec2(25.0, 25.0));
    REQUIRE(updated_particles[0].velocity == vec2(5, 5));
    REQUIRE(updated_particles[0].status == disease::Status::kSymptomatic);
    REQUIRE(updated_particles[0].color == vec3(1, 0, 0));
    REQUIRE(updated_particles[0].continuous_exposure_time == 0);
    REQUIRE(updated_particles[0].time_infected == 2);
    REQUIRE(updated_particles[0].is_quarantined == false);
    REQUIRE(updated_particles[0].is_social_distancing == false);
    REQUIRE(updated_particles[0].positions_of_people_in_bubble.empty());

    // Particle 2
    REQUIRE(updated_particles[1].position == vec2(45.0, 42.0));
    REQUIRE(updated_particles[1].velocity == vec2(-5, 6));
    REQUIRE(updated_particles[1].status == disease::Status::kSusceptible);
    REQUIRE(updated_particles[1].color == vec3(0, 0, 1));
    REQUIRE(updated_particles[1].continuous_exposure_time == 0);
    REQUIRE(updated_particles[1].time_infected == 0);
    REQUIRE(updated_particles[1].is_quarantined == false);
    REQUIRE(updated_particles[1].is_social_distancing == false);
    REQUIRE(updated_particles[1].positions_of_people_in_bubble.empty());
  }

  SECTION("Three particles") {
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
    all_particles.push_back(person);

    // Particle 2
    person.radius = 10;
    person.position = vec2(55, 30);
    person.velocity = vec2(-5, 6);
    person.status = disease::Status::kSusceptible;
    person.color = vec3(0,0,1);
    person.continuous_exposure_time = 0;
    person.time_infected = 0;
    person.has_been_exposed_in_frame = false;
    person.is_quarantined = false;
    person.is_social_distancing = false;
    all_particles.push_back(person);

    // Particle 3
    person.radius = 10;
    person.position = vec2(70, 80);
    person.velocity = vec2(-7.7, 3.4);
    person.status = disease::Status::kSusceptible;
    person.color = vec3(0,0,1);
    person.continuous_exposure_time = 0;
    person.time_infected = 0;
    person.has_been_exposed_in_frame = false;
    person.is_quarantined = false;
    person.is_social_distancing = false;
    all_particles.push_back(person);

    disease.SetPopulation(all_particles);
    disease.UpdateParticles();
    disease.UpdateParticles();
    vector<Disease::Person> updated_particles = disease.GetPopulation();

    // Particle 1
    REQUIRE(updated_particles[0].position == vec2(25.0, 25.0));
    REQUIRE(updated_particles[0].velocity == vec2(5, 5));
    REQUIRE(updated_particles[0].status == disease::Status::kSymptomatic);
    REQUIRE(updated_particles[0].color == vec3(1, 0, 0));
    REQUIRE(updated_particles[0].continuous_exposure_time == 0);
    REQUIRE(updated_particles[0].time_infected == 2);
    REQUIRE(updated_particles[0].is_quarantined == false);
    REQUIRE(updated_particles[0].is_social_distancing == false);
    REQUIRE(updated_particles[0].positions_of_people_in_bubble.empty());

    // Particle 2
    REQUIRE(updated_particles[1].position == vec2(45.0, 42.0));
    REQUIRE(updated_particles[1].velocity == vec2(-5, 6));
    REQUIRE(updated_particles[1].status == disease::Status::kSusceptible);
    REQUIRE(updated_particles[1].color == vec3(0, 0, 1));
    REQUIRE(updated_particles[1].continuous_exposure_time == 0);
    REQUIRE(updated_particles[1].time_infected == 0);
    REQUIRE(updated_particles[1].is_quarantined == false);
    REQUIRE(updated_particles[1].is_social_distancing == false);
    REQUIRE(updated_particles[1].positions_of_people_in_bubble.empty());

    // Particle 3
    REQUIRE(updated_particles[2].position == vec2(54.6, 86.8));
    REQUIRE(updated_particles[2].velocity == vec2(-7.7, 3.4));
    REQUIRE(updated_particles[2].status == disease::Status::kSusceptible);
    REQUIRE(updated_particles[2].color == vec3(0, 0, 1));
    REQUIRE(updated_particles[2].continuous_exposure_time == 0);
    REQUIRE(updated_particles[2].time_infected == 0);
    REQUIRE(updated_particles[2].is_quarantined == false);
    REQUIRE(updated_particles[2].is_social_distancing == false);
    REQUIRE(updated_particles[2].positions_of_people_in_bubble.empty());
  }
}

TEST_CASE("Person info updates after collision with wall",
          "[one frame][collision][wall]") {
  Disease disease = Disease(0, 0, 100, 100, vec2(150, 0), vec2(250, 100));
  Disease::Person person;

  SECTION("One particle") {
    SECTION("One particle collides with right wall") {
      vector<Disease::Person> all_particles;

      person.radius = 10;
      person.position = vec2(90, 30);
      person.velocity = vec2(5, 7);
      person.status = disease::Status::kSymptomatic;
      person.color = vec3(1,0,0);
      person.continuous_exposure_time = 0;
      person.time_infected = 0;
      person.has_been_exposed_in_frame = false;
      person.is_quarantined = false;
      person.is_social_distancing = false;
      all_particles.push_back(person);

      disease.SetPopulation(all_particles);
      disease.UpdateParticles();
      vector<Disease::Person> updated_particles = disease.GetPopulation();

      REQUIRE(updated_particles[0].position == vec2(85.0, 37.0));
      REQUIRE(updated_particles[0].velocity == vec2(-5.0, 7.0));
      REQUIRE(updated_particles[0].status == disease::Status::kSymptomatic);
      REQUIRE(updated_particles[0].color == vec3(1, 0, 0));
      REQUIRE(updated_particles[0].continuous_exposure_time == 0);
      REQUIRE(updated_particles[0].time_infected == 1);
      REQUIRE(updated_particles[0].is_quarantined == false);
      REQUIRE(updated_particles[0].is_social_distancing == false);
      REQUIRE(updated_particles[0].positions_of_people_in_bubble.empty());
    }

    SECTION("One particle collides with bottom wall") {
      vector<Disease::Person> all_particles;

      person.radius = 10;
      person.position = vec2(30, 90);
      person.velocity = vec2(5, 7);
      person.status = disease::Status::kSymptomatic;
      person.color = vec3(1,0,0);
      person.continuous_exposure_time = 0;
      person.time_infected = 0;
      person.has_been_exposed_in_frame = false;
      person.is_quarantined = false;
      person.is_social_distancing = false;
      all_particles.push_back(person);

      disease.SetPopulation(all_particles);
      disease.UpdateParticles();
      vector<Disease::Person> updated_particles = disease.GetPopulation();

      REQUIRE(updated_particles[0].position == vec2(35.0, 83.0));
      REQUIRE(updated_particles[0].velocity == vec2(5.0, -7.0));
      REQUIRE(updated_particles[0].status == disease::Status::kSymptomatic);
      REQUIRE(updated_particles[0].color == vec3(1, 0, 0));
      REQUIRE(updated_particles[0].continuous_exposure_time == 0);
      REQUIRE(updated_particles[0].time_infected == 1);
      REQUIRE(updated_particles[0].is_quarantined == false);
      REQUIRE(updated_particles[0].is_social_distancing == false);
      REQUIRE(updated_particles[0].positions_of_people_in_bubble.empty());
    }

    SECTION("One particle collides with left wall") {
      vector<Disease::Person> all_particles;

      person.radius = 10;
      person.position = vec2(10, 30);
      person.velocity = vec2(-5, -7);
      person.status = disease::Status::kSymptomatic;
      person.color = vec3(1,0,0);
      person.continuous_exposure_time = 0;
      person.time_infected = 0;
      person.has_been_exposed_in_frame = false;
      person.is_quarantined = false;
      person.is_social_distancing = false;
      all_particles.push_back(person);

      disease.SetPopulation(all_particles);
      disease.UpdateParticles();
      vector<Disease::Person> updated_particles = disease.GetPopulation();

      REQUIRE(updated_particles[0].position == vec2(15.0, 23.0));
      REQUIRE(updated_particles[0].velocity == vec2(5.0, -7.0));
      REQUIRE(updated_particles[0].status == disease::Status::kSymptomatic);
      REQUIRE(updated_particles[0].color == vec3(1, 0, 0));
      REQUIRE(updated_particles[0].continuous_exposure_time == 0);
      REQUIRE(updated_particles[0].time_infected == 1);
      REQUIRE(updated_particles[0].is_social_distancing == false);
      REQUIRE(updated_particles[0].positions_of_people_in_bubble.empty());
    }

    SECTION("One particle collides with top wall") {
      vector<Disease::Person> all_particles;

      person.radius = 10;
      person.position = vec2(30, 10);
      person.velocity = vec2(5, -7);
      person.status = disease::Status::kSymptomatic;
      person.color = vec3(1,0,0);
      person.continuous_exposure_time = 0;
      person.time_infected = 0;
      person.has_been_exposed_in_frame = false;
      person.is_quarantined = false;
      person.is_social_distancing = false;
      all_particles.push_back(person);

      disease.SetPopulation(all_particles);
      disease.UpdateParticles();
      vector<Disease::Person> updated_particles = disease.GetPopulation();

      REQUIRE(updated_particles[0].position == vec2(35.0, 17.0));
      REQUIRE(updated_particles[0].velocity == vec2(5.0, 7.0));
      REQUIRE(updated_particles[0].status == disease::Status::kSymptomatic);
      REQUIRE(updated_particles[0].color == vec3(1, 0, 0));
      REQUIRE(updated_particles[0].continuous_exposure_time == 0);
      REQUIRE(updated_particles[0].time_infected == 1);
      REQUIRE(updated_particles[0].is_quarantined == false);
      REQUIRE(updated_particles[0].is_social_distancing == false);
      REQUIRE(updated_particles[0].positions_of_people_in_bubble.empty());
    }

    SECTION("One particle collides with two walls at once") {
      vector<Disease::Person> all_particles;

      person.radius = 10;
      person.position = vec2(90, 90);
      person.velocity = vec2(5, 7);
      person.status = disease::Status::kSymptomatic;
      person.color = vec3(1,0,0);
      person.continuous_exposure_time = 0;
      person.time_infected = 0;
      person.has_been_exposed_in_frame = false;
      person.is_quarantined = false;
      person.is_social_distancing = false;
      all_particles.push_back(person);

      disease.SetPopulation(all_particles);
      disease.UpdateParticles();
      vector<Disease::Person> updated_particles = disease.GetPopulation();

      REQUIRE(updated_particles[0].position == vec2(85.0, 83.0));
      REQUIRE(updated_particles[0].velocity == vec2(-5.0, -7.0));
      REQUIRE(updated_particles[0].status == disease::Status::kSymptomatic);
      REQUIRE(updated_particles[0].color == vec3(1, 0, 0));
      REQUIRE(updated_particles[0].continuous_exposure_time == 0);
      REQUIRE(updated_particles[0].time_infected == 1);
      REQUIRE(updated_particles[0].is_quarantined == false);
      REQUIRE(updated_particles[0].is_social_distancing == false);
      REQUIRE(updated_particles[0].positions_of_people_in_bubble.empty());
    }
  }

  SECTION("Two particles") {
    SECTION("Two particles collide with a wall in a frame") {
      vector<Disease::Person> all_particles;

      // Particle 1 collides with top wall
      person.radius = 10;
      person.position = vec2(30, 10);
      person.velocity = vec2(5, -7);
      person.status = disease::Status::kSymptomatic;
      person.color = vec3(1,0,0);
      person.continuous_exposure_time = 0;
      person.time_infected = 0;
      person.has_been_exposed_in_frame = false;
      person.is_quarantined = false;
      person.is_social_distancing = false;
      all_particles.push_back(person);

      // Particle 2 collides with bottom wall
      person.radius = 10;
      person.position = vec2(30, 90);
      person.velocity = vec2(5, 7);
      person.status = disease::Status::kSusceptible;
      person.color = vec3(0,0,1);
      person.continuous_exposure_time = 0;
      person.time_infected = 0;
      person.has_been_exposed_in_frame = false;
      person.is_quarantined = false;
      person.is_social_distancing = false;
      all_particles.push_back(person);

      disease.SetPopulation(all_particles);
      disease.UpdateParticles();
      vector<Disease::Person> updated_particles = disease.GetPopulation();

      // Particle 1
      REQUIRE(updated_particles[0].position == vec2(35.0, 17.0));
      REQUIRE(updated_particles[0].velocity == vec2(5.0, 7.0));
      REQUIRE(updated_particles[0].status == disease::Status::kSymptomatic);
      REQUIRE(updated_particles[0].color == vec3(1, 0, 0));
      REQUIRE(updated_particles[0].continuous_exposure_time == 0);
      REQUIRE(updated_particles[0].time_infected == 1);
      REQUIRE(updated_particles[0].is_quarantined == false);
      REQUIRE(updated_particles[0].is_social_distancing == false);
      REQUIRE(updated_particles[0].positions_of_people_in_bubble.empty());

      // Particle 2
      REQUIRE(updated_particles[1].position == vec2(35.0, 83.0));
      REQUIRE(updated_particles[1].velocity == vec2(5.0, -7.0));
      REQUIRE(updated_particles[1].status == disease::Status::kSusceptible);
      REQUIRE(updated_particles[1].color == vec3(0, 0, 1));
      REQUIRE(updated_particles[1].continuous_exposure_time == 0);
      REQUIRE(updated_particles[1].time_infected == 0);
      REQUIRE(updated_particles[1].is_quarantined == false);
      REQUIRE(updated_particles[1].is_social_distancing == false);
      REQUIRE(updated_particles[1].positions_of_people_in_bubble.empty());
    }

    SECTION("One of two particles collide with a wall in a frame") {
      vector<Disease::Person> all_particles;

      // Particle 1 collides with top wall
      person.radius = 10;
      person.position = vec2(30, 10);
      person.velocity = vec2(5, -7);
      person.status = disease::Status::kSymptomatic;
      person.color = vec3(1,0,0);
      person.continuous_exposure_time = 0;
      person.time_infected = 0;
      person.has_been_exposed_in_frame = false;
      person.is_quarantined = false;
      person.is_social_distancing = false;
      all_particles.push_back(person);

      // Particle 2 doesn't collide with anything
      person.radius = 10;
      person.position = vec2(30, 50);
      person.velocity = vec2(5, 7);
      person.status = disease::Status::kSymptomatic;
      person.color = vec3(1,0,0);
      person.continuous_exposure_time = 0;
      person.time_infected = 0;
      person.has_been_exposed_in_frame = false;
      person.is_quarantined = false;
      person.is_social_distancing = false;
      all_particles.push_back(person);

      disease.SetPopulation(all_particles);
      disease.UpdateParticles();
      vector<Disease::Person> updated_particles = disease.GetPopulation();

      // Particle 1
      REQUIRE(updated_particles[0].position == vec2(35.0, 17.0));
      REQUIRE(updated_particles[0].velocity == vec2(5.0, 7.0));
      REQUIRE(updated_particles[0].status == disease::Status::kSymptomatic);
      REQUIRE(updated_particles[0].color == vec3(1, 0, 0));
      REQUIRE(updated_particles[0].continuous_exposure_time == 0);
      REQUIRE(updated_particles[0].time_infected == 1);
      REQUIRE(updated_particles[0].is_quarantined == false);
      REQUIRE(updated_particles[0].is_social_distancing == false);
      REQUIRE(updated_particles[0].positions_of_people_in_bubble.empty());

      // Particle 2
      REQUIRE(updated_particles[1].position == vec2(35.0, 57.0));
      REQUIRE(updated_particles[1].velocity == vec2(5.0, 7.0));
      REQUIRE(updated_particles[1].status == disease::Status::kSymptomatic);
      REQUIRE(updated_particles[1].color == vec3(1, 0, 0));
      REQUIRE(updated_particles[1].continuous_exposure_time == 0);
      REQUIRE(updated_particles[1].time_infected == 1);
      REQUIRE(updated_particles[1].is_quarantined == false);
      REQUIRE(updated_particles[1].is_social_distancing == false);
      REQUIRE(updated_particles[1].positions_of_people_in_bubble.empty());
    }
  }
}

TEST_CASE("Particle touches wall but isn't colliding (i.e. moving towards)",
          "[no collision][wall][touching]") {
  Disease disease = Disease(0, 0, 100, 100, vec2(150, 0), vec2(250, 100));
  Disease::Person person;

  SECTION("One particle") {
    SECTION("One particle touches but doesn't collide with right wall") {
      vector<Disease::Person> all_particles;

      person.radius = 10;
      person.position = vec2(90, 30);
      person.velocity = vec2(-5, 7);
      person.status = disease::Status::kSymptomatic;
      person.color = vec3(1,0,0);
      person.continuous_exposure_time = 0;
      person.time_infected = 0;
      person.has_been_exposed_in_frame = false;
      person.is_quarantined = false;
      person.is_social_distancing = false;
      all_particles.push_back(person);

      disease.SetPopulation(all_particles);
      disease.UpdateParticles();
      vector<Disease::Person> updated_particles = disease.GetPopulation();

      REQUIRE(updated_particles[0].position == vec2(85.0, 37.0));
      REQUIRE(updated_particles[0].velocity == vec2(-5.0, 7.0));
      REQUIRE(updated_particles[0].status == disease::Status::kSymptomatic);
      REQUIRE(updated_particles[0].color == vec3(1, 0, 0));
      REQUIRE(updated_particles[0].continuous_exposure_time == 0);
      REQUIRE(updated_particles[0].time_infected == 1);
      REQUIRE(updated_particles[0].is_quarantined == false);
      REQUIRE(updated_particles[0].is_social_distancing == false);
      REQUIRE(updated_particles[0].positions_of_people_in_bubble.empty());
    }

    SECTION("One particle touches but doesn't collide with bottom wall") {
      vector<Disease::Person> all_particles;

      person.radius = 10;
      person.position = vec2(30, 90);
      person.velocity = vec2(5, -7);
      person.status = disease::Status::kSymptomatic;
      person.color = vec3(1,0,0);
      person.continuous_exposure_time = 0;
      person.time_infected = 0;
      person.has_been_exposed_in_frame = false;
      person.is_quarantined = false;
      person.is_social_distancing = false;
      all_particles.push_back(person);

      disease.SetPopulation(all_particles);
      disease.UpdateParticles();
      vector<Disease::Person> updated_particles = disease.GetPopulation();

      REQUIRE(updated_particles[0].position == vec2(35.0, 83.0));
      REQUIRE(updated_particles[0].velocity == vec2(5.0, -7.0));
      REQUIRE(updated_particles[0].status == disease::Status::kSymptomatic);
      REQUIRE(updated_particles[0].color == vec3(1, 0, 0));
      REQUIRE(updated_particles[0].continuous_exposure_time == 0);
      REQUIRE(updated_particles[0].time_infected == 1);
      REQUIRE(updated_particles[0].is_quarantined == false);
      REQUIRE(updated_particles[0].is_social_distancing == false);
      REQUIRE(updated_particles[0].positions_of_people_in_bubble.empty());
    }

    SECTION("One particle touches but doesn't collide with left wall") {
      vector<Disease::Person> all_particles;

      person.radius = 10;
      person.position = vec2(10, 30);
      person.velocity = vec2(5, -7);
      person.status = disease::Status::kSymptomatic;
      person.color = vec3(1,0,0);
      person.continuous_exposure_time = 0;
      person.time_infected = 0;
      person.has_been_exposed_in_frame = false;
      person.is_quarantined = false;
      person.is_social_distancing = false;
      all_particles.push_back(person);

      disease.SetPopulation(all_particles);
      disease.UpdateParticles();
      vector<Disease::Person> updated_particles = disease.GetPopulation();

      REQUIRE(updated_particles[0].position == vec2(15.0, 23.0));
      REQUIRE(updated_particles[0].velocity == vec2(5.0, -7.0));
      REQUIRE(updated_particles[0].status == disease::Status::kSymptomatic);
      REQUIRE(updated_particles[0].color == vec3(1, 0, 0));
      REQUIRE(updated_particles[0].continuous_exposure_time == 0);
      REQUIRE(updated_particles[0].time_infected == 1);
      REQUIRE(updated_particles[0].is_quarantined == false);
      REQUIRE(updated_particles[0].is_social_distancing == false);
      REQUIRE(updated_particles[0].positions_of_people_in_bubble.empty());
    }

    SECTION("One particle touches but doesn't collide with top wall") {
      vector<Disease::Person> all_particles;

      person.radius = 10;
      person.position = vec2(30, 10);
      person.velocity = vec2(5, 7);
      person.status = disease::Status::kSymptomatic;
      person.color = vec3(1,0,0);
      person.continuous_exposure_time = 0;
      person.time_infected = 0;
      person.has_been_exposed_in_frame = false;
      person.is_quarantined = false;
      person.is_social_distancing = false;
      all_particles.push_back(person);

      disease.SetPopulation(all_particles);
      disease.UpdateParticles();
      vector<Disease::Person> updated_particles = disease.GetPopulation();

      REQUIRE(updated_particles[0].position == vec2(35.0, 17.0));
      REQUIRE(updated_particles[0].velocity == vec2(5.0, 7.0));
      REQUIRE(updated_particles[0].status == disease::Status::kSymptomatic);
      REQUIRE(updated_particles[0].color == vec3(1, 0, 0));
      REQUIRE(updated_particles[0].continuous_exposure_time == 0);
      REQUIRE(updated_particles[0].time_infected == 1);
      REQUIRE(updated_particles[0].is_quarantined == false);
      REQUIRE(updated_particles[0].is_social_distancing == false);
      REQUIRE(updated_particles[0].positions_of_people_in_bubble.empty());
    }

    SECTION("One particle touches but doesn't collide with two walls at once") {
      vector<Disease::Person> all_particles;

      person.radius = 10;
      person.position = vec2(90, 90);
      person.velocity = vec2(-5, -7);
      person.status = disease::Status::kSymptomatic;
      person.color = vec3(1,0,0);
      person.continuous_exposure_time = 0;
      person.time_infected = 0;
      person.has_been_exposed_in_frame = false;
      person.is_quarantined = false;
      person.is_social_distancing = false;
      all_particles.push_back(person);

      disease.SetPopulation(all_particles);
      disease.UpdateParticles();
      vector<Disease::Person> updated_particles = disease.GetPopulation();

      REQUIRE(updated_particles[0].position == vec2(85.0, 83.0));
      REQUIRE(updated_particles[0].velocity == vec2(-5.0, -7.0));
      REQUIRE(updated_particles[0].status == disease::Status::kSymptomatic);
      REQUIRE(updated_particles[0].color == vec3(1, 0, 0));
      REQUIRE(updated_particles[0].continuous_exposure_time == 0);
      REQUIRE(updated_particles[0].time_infected == 1);
      REQUIRE(updated_particles[0].is_quarantined == false);
      REQUIRE(updated_particles[0].is_social_distancing == false);
      REQUIRE(updated_particles[0].positions_of_people_in_bubble.empty());
    }
  }

  SECTION("Two particles") {
    SECTION("Two particles touches but doesn't collide with a wall in a frame") {
      vector<Disease::Person> all_particles;

      // Particle 1 touches but doesn't collide with top wall
      person.radius = 10;
      person.position = vec2(30, 10);
      person.velocity = vec2(5, 7);
      person.status = disease::Status::kSymptomatic;
      person.color = vec3(1,0,0);
      person.continuous_exposure_time = 0;
      person.time_infected = 0;
      person.has_been_exposed_in_frame = false;
      person.is_quarantined = false;
      person.is_social_distancing = false;
      all_particles.push_back(person);

      // Particle 2 touches but doesn't collide with bottom wall
      person.radius = 10;
      person.position = vec2(30, 90);
      person.velocity = vec2(5, -7);
      person.status = disease::Status::kSusceptible;
      person.color = vec3(0,0,1);
      person.continuous_exposure_time = 0;
      person.time_infected = 0;
      person.has_been_exposed_in_frame = false;
      person.is_quarantined = false;
      person.is_social_distancing = false;
      all_particles.push_back(person);

      disease.SetPopulation(all_particles);
      disease.UpdateParticles();
      vector<Disease::Person> updated_particles = disease.GetPopulation();

      // Particle 1
      REQUIRE(updated_particles[0].position == vec2(35.0, 17.0));
      REQUIRE(updated_particles[0].velocity == vec2(5.0, 7.0));
      REQUIRE(updated_particles[0].status == disease::Status::kSymptomatic);
      REQUIRE(updated_particles[0].color == vec3(1, 0, 0));
      REQUIRE(updated_particles[0].continuous_exposure_time == 0);
      REQUIRE(updated_particles[0].time_infected == 1);
      REQUIRE(updated_particles[0].is_quarantined == false);
      REQUIRE(updated_particles[0].is_social_distancing == false);
      REQUIRE(updated_particles[0].positions_of_people_in_bubble.empty());

      // Particle 2
      REQUIRE(updated_particles[1].position == vec2(35.0, 83.0));
      REQUIRE(updated_particles[1].velocity == vec2(5.0, -7.0));
      REQUIRE(updated_particles[1].status == disease::Status::kSusceptible);
      REQUIRE(updated_particles[1].color == vec3(0, 0, 1));
      REQUIRE(updated_particles[1].continuous_exposure_time == 0);
      REQUIRE(updated_particles[1].time_infected == 0);
      REQUIRE(updated_particles[1].is_quarantined == false);
      REQUIRE(updated_particles[1].is_social_distancing == false);
      REQUIRE(updated_particles[1].positions_of_people_in_bubble.empty());
    }

    SECTION("One of two particles touches but doesn't collide with a wall in a frame") {
      vector<Disease::Person> all_particles;

      // Particle 1 touches but doesn't collide with top wall
      person.radius = 10;
      person.position = vec2(30, 10);
      person.velocity = vec2(5, 7);
      person.status = disease::Status::kSymptomatic;
      person.color = vec3(1,0,0);
      person.continuous_exposure_time = 0;
      person.time_infected = 0;
      person.has_been_exposed_in_frame = false;
      person.is_quarantined = false;
      person.is_social_distancing = false;
      all_particles.push_back(person);

      // Particle 2 doesn't collide with anything
      person.radius = 10;
      person.position = vec2(30, 50);
      person.velocity = vec2(5, 7);
      person.status = disease::Status::kSymptomatic;
      person.color = vec3(1,0,0);
      person.continuous_exposure_time = 0;
      person.time_infected = 0;
      person.has_been_exposed_in_frame = false;
      person.is_quarantined = false;
      person.is_social_distancing = false;
      all_particles.push_back(person);

      disease.SetPopulation(all_particles);
      disease.UpdateParticles();
      vector<Disease::Person> updated_particles = disease.GetPopulation();

      // Particle 1
      REQUIRE(updated_particles[0].position == vec2(35.0, 17.0));
      REQUIRE(updated_particles[0].velocity == vec2(5.0, 7.0));
      REQUIRE(updated_particles[0].status == disease::Status::kSymptomatic);
      REQUIRE(updated_particles[0].color == vec3(1, 0, 0));
      REQUIRE(updated_particles[0].continuous_exposure_time == 0);
      REQUIRE(updated_particles[0].time_infected == 1);
      REQUIRE(updated_particles[0].is_quarantined == false);
      REQUIRE(updated_particles[0].is_social_distancing == false);
      REQUIRE(updated_particles[0].positions_of_people_in_bubble.empty());

      // Particle 2
      REQUIRE(updated_particles[1].position == vec2(35.0, 57.0));
      REQUIRE(updated_particles[1].velocity == vec2(5.0, 7.0));
      REQUIRE(updated_particles[1].status == disease::Status::kSymptomatic);
      REQUIRE(updated_particles[1].color == vec3(1, 0, 0));
      REQUIRE(updated_particles[1].continuous_exposure_time == 0);
      REQUIRE(updated_particles[1].time_infected == 1);
      REQUIRE(updated_particles[1].is_quarantined == false);
      REQUIRE(updated_particles[1].is_social_distancing == false);
      REQUIRE(updated_particles[1].positions_of_people_in_bubble.empty());
    }
  }
}

TEST_CASE("Check person status updates") {
  Disease disease = Disease(0, 0, 100, 100, vec2(150, 0), vec2(250, 100),
                            25, 500, false, true, false);
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
                                   25, 500, false, false, false);
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
                            25, 500, false, true, false);
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
                            25, 500, false, true, false);
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