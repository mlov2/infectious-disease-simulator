#include <core/infectious_disease.h>

#include <catch2/catch.hpp>

using disease::Disease;
using disease::Status;

TEST_CASE("Create population", "[create population]") {
  Disease disease = Disease(0, 0, 100, 100, true);

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
  REQUIRE(all_particles[all_particles.size() - 1].status == disease::Status::kInfectious);
  REQUIRE(all_particles[all_particles.size() - 1].color == vec3(1, 0, 0));
  REQUIRE(all_particles[all_particles.size() - 1].continuous_exposure_time == 0);
  REQUIRE(all_particles[all_particles.size() - 1].time_infected == 0);
}

TEST_CASE("Person info updates after 1 frame (no collision)",
          "[one frame][no collision]") {
  Disease disease = Disease(0, 0, 100, 100, false);
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
    person.status = disease::Status::kSusceptible;
    person.color = vec3(0,0,1);
    person.continuous_exposure_time = 0;
    person.time_infected = 0;
    all_particles.push_back(person);

    disease.SetPopulation(all_particles);
    disease.UpdateParticles();
    vector<Disease::Person> updated_particles = disease.GetPopulation();

    REQUIRE(updated_particles[0].position == vec2(20.0, 20.0));
    REQUIRE(updated_particles[0].velocity == vec2(5, 5));
  }

  SECTION("Two particles") {
    vector<Disease::Person> all_particles;

    // Particle 1
    person.radius = 10;
    person.position = vec2(15, 15);
    person.velocity = vec2(5, 5);
    person.status = disease::Status::kSusceptible;
    person.color = vec3(0,0,1);
    person.continuous_exposure_time = 0;
    person.time_infected = 0;
    all_particles.push_back(person);

    // Particle 2
    person.radius = 10;
    person.position = vec2(55, 30);
    person.velocity = vec2(-5, 6);
    person.status = disease::Status::kSusceptible;
    person.color = vec3(0,0,1);
    person.continuous_exposure_time = 0;
    person.time_infected = 0;
    all_particles.push_back(person);

    disease.SetPopulation(all_particles);
    disease.UpdateParticles();
    vector<Disease::Person> updated_particles = disease.GetPopulation();

    // Particle 1
    REQUIRE(updated_particles[0].position == vec2(20.0, 20.0));
    REQUIRE(updated_particles[0].velocity == vec2(5.0, 5.0));

    // Particle 2
    REQUIRE(updated_particles[1].position == vec2(50.0, 36.0));
    REQUIRE(updated_particles[1].velocity == vec2(-5.0, 6.0));
  }

  SECTION("Three particles") {
    vector<Disease::Person> all_particles;

    // Particle 1
    person.radius = 10;
    person.position = vec2(15, 15);
    person.velocity = vec2(5, 5);
    person.status = disease::Status::kSusceptible;
    person.color = vec3(0,0,1);
    person.continuous_exposure_time = 0;
    person.time_infected = 0;
    all_particles.push_back(person);

    // Particle 2
    person.radius = 10;
    person.position = vec2(55, 30);
    person.velocity = vec2(-5, 6);
    person.status = disease::Status::kSusceptible;
    person.color = vec3(0,0,1);
    person.continuous_exposure_time = 0;
    person.time_infected = 0;
    all_particles.push_back(person);

    // Particle 3
    person.radius = 10;
    person.position = vec2(70, 80);
    person.velocity = vec2(-7.7, 3.4);
    person.status = disease::Status::kSusceptible;
    person.color = vec3(0,0,1);
    person.continuous_exposure_time = 0;
    person.time_infected = 0;
    all_particles.push_back(person);

    disease.SetPopulation(all_particles);
    disease.UpdateParticles();
    vector<Disease::Person> updated_particles = disease.GetPopulation();

    // Particle 1
    REQUIRE(updated_particles[0].position == vec2(20.0, 20.0));
    REQUIRE(updated_particles[0].velocity == vec2(5.0, 5.0));

    // Particle 2
    REQUIRE(updated_particles[1].position == vec2(50.0, 36.0));
    REQUIRE(updated_particles[1].velocity == vec2(-5.0, 6.0));

    // Particle 3
    REQUIRE(updated_particles[2].position == vec2(62.3, 83.4));
    REQUIRE(updated_particles[2].velocity == vec2(-7.7, 3.4));
  }
}
/*
TEST_CASE("Particle position updates after 2 frames (no collision) (same mass)",
          "[position][two frames][no collision][same mass]") {
  IdealGas ideal_gas = IdealGas(0, 0, 100, 100, 10);
  Particle particle;

  SECTION("No particles") {
    ideal_gas.UpdateParticles();

    vector<Particle> updated_particles = ideal_gas.GetInfoForParticles();

    REQUIRE(updated_particles.empty() == true);
  }

  SECTION("One particle") {
    vector<Particle> all_particles;

    particle.SetRadius(10);
    particle.SetMass(5);
    particle.SetPosition(glm::vec2(15.0, 15.0));
    particle.SetVelocity(glm::vec2(5, 5));
    all_particles.push_back(particle);

    ideal_gas.SetInfoForParticles(all_particles);
    ideal_gas.UpdateParticles();
    ideal_gas.UpdateParticles();
    vector<Particle> updated_particles = ideal_gas.GetInfoForParticles();

    REQUIRE(updated_particles[0].GetPosition() == vec2(25.0, 25.0));
    REQUIRE(updated_particles[0].GetVelocity() == vec2(5, 5));
  }

  SECTION("Two particles") {
    vector<Particle> all_particles;

    // Particle 1
    particle.SetRadius(10);
    particle.SetMass(5);
    particle.SetPosition(glm::vec2(15.0, 15.0));
    particle.SetVelocity(glm::vec2(5.0, 5.0));
    all_particles.push_back(particle);

    // Particle 2
    particle.SetRadius(10);
    particle.SetMass(5);
    particle.SetPosition(vec2(55.0, 30.0));
    particle.SetVelocity(vec2(-5.0, 6.0));
    all_particles.push_back(particle);

    ideal_gas.SetInfoForParticles(all_particles);
    ideal_gas.UpdateParticles();
    ideal_gas.UpdateParticles();
    vector<Particle> updated_particles = ideal_gas.GetInfoForParticles();

    // Particle 1
    REQUIRE(updated_particles[0].GetPosition() == vec2(25.0, 25.0));
    REQUIRE(updated_particles[0].GetVelocity() == vec2(5.0, 5.0));

    // Particle 2
    REQUIRE(updated_particles[1].GetPosition() == vec2(45.0, 42.0));
    REQUIRE(updated_particles[1].GetVelocity() == vec2(-5.0, 6.0));
  }

  SECTION("Three particles") {
    vector<Particle> all_particles;

    // Particle 1
    particle.SetRadius(10);
    particle.SetMass(5);
    particle.SetPosition(glm::vec2(15.0, 15.0));
    particle.SetVelocity(glm::vec2(5.0, 5.0));
    all_particles.push_back(particle);

    // Particle 2
    particle.SetRadius(10);
    particle.SetMass(5);
    particle.SetPosition(vec2(55.0, 30.0));
    particle.SetVelocity(vec2(-5.0, 6.0));
    all_particles.push_back(particle);

    // Particle 3
    particle.SetRadius(10);
    particle.SetMass(5);
    particle.SetPosition(vec2(70.0, 80.0));
    particle.SetVelocity(vec2(-7.7, 3.4));
    all_particles.push_back(particle);

    ideal_gas.SetInfoForParticles(all_particles);
    ideal_gas.UpdateParticles();
    ideal_gas.UpdateParticles();
    vector<Particle> updated_particles = ideal_gas.GetInfoForParticles();

    // Particle 1
    REQUIRE(updated_particles[0].GetPosition() == vec2(25.0, 25.0));
    REQUIRE(updated_particles[0].GetVelocity() == vec2(5.0, 5.0));

    // Particle 2
    REQUIRE(updated_particles[1].GetPosition() == vec2(45.0, 42.0));
    REQUIRE(updated_particles[1].GetVelocity() == vec2(-5.0, 6.0));

    // Particle 3
    REQUIRE(updated_particles[2].GetPosition() == vec2(54.6, 86.8));
    REQUIRE(updated_particles[2].GetVelocity() == vec2(-7.7, 3.4));
  }
}

TEST_CASE("Particle position updates after collision with wall (same mass)",
          "[position][one frame][collision][wall][same mass]") {
  IdealGas ideal_gas = IdealGas(0, 0, 100, 100, 10);
  Particle particle;

  SECTION("One particle") {
    SECTION("One particle collides with right wall") {
      vector<Particle> all_particles;

      particle.SetRadius(10);
      particle.SetMass(5);
      particle.SetPosition(glm::vec2(90.0, 30.0));
      particle.SetVelocity(glm::vec2(5, 7));
      all_particles.push_back(particle);

      ideal_gas.SetInfoForParticles(all_particles);
      ideal_gas.UpdateParticles();
      vector<Particle> updated_particles = ideal_gas.GetInfoForParticles();

      REQUIRE(updated_particles[0].GetPosition() == vec2(85.0, 37.0));
      REQUIRE(updated_particles[0].GetVelocity() == vec2(-5.0, 7.0));
    }

    SECTION("One particle collides with bottom wall") {
      vector<Particle> all_particles;

      particle.SetRadius(10);
      particle.SetMass(5);
      particle.SetPosition(glm::vec2(30.0, 90.0));
      particle.SetVelocity(glm::vec2(5, 7));
      all_particles.push_back(particle);

      ideal_gas.SetInfoForParticles(all_particles);
      ideal_gas.UpdateParticles();
      vector<Particle> updated_particles = ideal_gas.GetInfoForParticles();

      REQUIRE(updated_particles[0].GetPosition() == vec2(35.0, 83.0));
      REQUIRE(updated_particles[0].GetVelocity() == vec2(5.0, -7.0));
    }

    SECTION("One particle collides with left wall") {
      vector<Particle> all_particles;

      particle.SetRadius(10);
      particle.SetMass(5);
      particle.SetPosition(glm::vec2(10.0, 30.0));
      particle.SetVelocity(glm::vec2(-5, -7));
      all_particles.push_back(particle);

      ideal_gas.SetInfoForParticles(all_particles);
      ideal_gas.UpdateParticles();
      vector<Particle> updated_particles = ideal_gas.GetInfoForParticles();

      REQUIRE(updated_particles[0].GetPosition() == vec2(15.0, 23.0));
      REQUIRE(updated_particles[0].GetVelocity() == vec2(5.0, -7.0));
    }

    SECTION("One particle collides with top wall") {
      vector<Particle> all_particles;

      particle.SetRadius(10);
      particle.SetMass(5);
      particle.SetPosition(glm::vec2(30.0, 10.0));
      particle.SetVelocity(glm::vec2(5, -7));
      all_particles.push_back(particle);

      ideal_gas.SetInfoForParticles(all_particles);
      ideal_gas.UpdateParticles();
      vector<Particle> updated_particles = ideal_gas.GetInfoForParticles();

      REQUIRE(updated_particles[0].GetPosition() == vec2(35.0, 17.0));
      REQUIRE(updated_particles[0].GetVelocity() == vec2(5.0, 7.0));
    }

    SECTION("One particle collides with two walls at once") {
      vector<Particle> all_particles;

      particle.SetRadius(10);
      particle.SetMass(5);
      particle.SetPosition(glm::vec2(90.0, 90.0));
      particle.SetVelocity(glm::vec2(5, 7));
      all_particles.push_back(particle);

      ideal_gas.SetInfoForParticles(all_particles);
      ideal_gas.UpdateParticles();
      vector<Particle> updated_particles = ideal_gas.GetInfoForParticles();

      REQUIRE(updated_particles[0].GetPosition() == vec2(85.0, 83.0));
      REQUIRE(updated_particles[0].GetVelocity() == vec2(-5.0, -7.0));
    }
  }

  SECTION("Two particles") {
    SECTION("Two particles collide with a wall in a frame") {
      vector<Particle> all_particles;

      // Particle 1 collides with top wall
      particle.SetRadius(10);
      particle.SetMass(5);
      particle.SetPosition(glm::vec2(30.0, 10.0));
      particle.SetVelocity(glm::vec2(5, -7));
      all_particles.push_back(particle);

      // Particle 2 collides with bottom wall
      particle.SetRadius(10);
      particle.SetMass(5);
      particle.SetPosition(glm::vec2(30.0, 90.0));
      particle.SetVelocity(glm::vec2(5, 7));
      all_particles.push_back(particle);

      ideal_gas.SetInfoForParticles(all_particles);
      ideal_gas.UpdateParticles();
      vector<Particle> updated_particles = ideal_gas.GetInfoForParticles();

      // Particle 1
      REQUIRE(updated_particles[0].GetPosition() == vec2(35.0, 17.0));
      REQUIRE(updated_particles[0].GetVelocity() == vec2(5.0, 7.0));

      // Particle 2
      REQUIRE(updated_particles[1].GetPosition() == vec2(35.0, 83.0));
      REQUIRE(updated_particles[1].GetVelocity() == vec2(5.0, -7.0));
    }

    SECTION("One of two particles collide with a wall in a frame") {
      vector<Particle> all_particles;

      // Particle 1 collides with top wall
      particle.SetRadius(10);
      particle.SetMass(5);
      particle.SetPosition(glm::vec2(30.0, 10.0));
      particle.SetVelocity(glm::vec2(5, -7));
      all_particles.push_back(particle);

      // Particle 2 doesn't collide with anything
      particle.SetRadius(10);
      particle.SetMass(5);
      particle.SetPosition(glm::vec2(30.0, 50.0));
      particle.SetVelocity(glm::vec2(5, 7));
      all_particles.push_back(particle);

      ideal_gas.SetInfoForParticles(all_particles);
      ideal_gas.UpdateParticles();
      vector<Particle> updated_particles = ideal_gas.GetInfoForParticles();

      // Particle 1
      REQUIRE(updated_particles[0].GetPosition() == vec2(35.0, 17.0));
      REQUIRE(updated_particles[0].GetVelocity() == vec2(5.0, 7.0));

      // Particle 2
      REQUIRE(updated_particles[1].GetPosition() == vec2(35.0, 57.0));
      REQUIRE(updated_particles[1].GetVelocity() == vec2(5.0, 7.0));
    }
  }
}

TEST_CASE("Particle touches wall but isn't colliding (i.e. moving towards) (same mass)",
          "[no collision][wall][touching][same mass]") {
  IdealGas ideal_gas = IdealGas(0, 0, 100, 100, 10);

  SECTION("One particle") {
    SECTION("One particle touches but doesn't collide with right wall") {
      vector<Particle> all_particles;

      Particle particle1 = Particle(10, 5, glm::vec2(90.0, 30.0), glm::vec2(-5, 7), 0);
      all_particles.push_back(particle1);

      ideal_gas.SetInfoForParticles(all_particles);
      ideal_gas.UpdateParticles();
      vector<Particle> updated_particles = ideal_gas.GetInfoForParticles();

      REQUIRE(updated_particles[0].GetPosition() == vec2(85.0, 37.0));
      REQUIRE(updated_particles[0].GetVelocity() == vec2(-5.0, 7.0));
    }

    SECTION("One particle touches but doesn't collide with bottom wall") {
      vector<Particle> all_particles;

      Particle particle1 = Particle(10, 5, glm::vec2(30.0, 90.0), glm::vec2(5, -7), 0);
      all_particles.push_back(particle1);

      ideal_gas.SetInfoForParticles(all_particles);
      ideal_gas.UpdateParticles();
      vector<Particle> updated_particles = ideal_gas.GetInfoForParticles();

      REQUIRE(updated_particles[0].GetPosition() == vec2(35.0, 83.0));
      REQUIRE(updated_particles[0].GetVelocity() == vec2(5.0, -7.0));
    }

    SECTION("One particle touches but doesn't collide with left wall") {
      vector<Particle> all_particles;

      Particle particle1 = Particle(10, 5, glm::vec2(10.0, 30.0), glm::vec2(5, -7), 0);
      all_particles.push_back(particle1);

      ideal_gas.SetInfoForParticles(all_particles);
      ideal_gas.UpdateParticles();
      vector<Particle> updated_particles = ideal_gas.GetInfoForParticles();

      REQUIRE(updated_particles[0].GetPosition() == vec2(15.0, 23.0));
      REQUIRE(updated_particles[0].GetVelocity() == vec2(5.0, -7.0));
    }

    SECTION("One particle touches but doesn't collide with top wall") {
      vector<Particle> all_particles;

      Particle particle1 = Particle(10, 5, glm::vec2(30.0, 10.0), glm::vec2(5, 7), 0);
      all_particles.push_back(particle1);

      ideal_gas.SetInfoForParticles(all_particles);
      ideal_gas.UpdateParticles();
      vector<Particle> updated_particles = ideal_gas.GetInfoForParticles();

      REQUIRE(updated_particles[0].GetPosition() == vec2(35.0, 17.0));
      REQUIRE(updated_particles[0].GetVelocity() == vec2(5.0, 7.0));
    }

    SECTION("One particle touches but doesn't collide with two walls at once") {
      vector<Particle> all_particles;

      Particle particle1 = Particle(10, 5, glm::vec2(90.0, 90.0), glm::vec2(-5, -7), 0);
      all_particles.push_back(particle1);

      ideal_gas.SetInfoForParticles(all_particles);
      ideal_gas.UpdateParticles();
      vector<Particle> updated_particles = ideal_gas.GetInfoForParticles();

      REQUIRE(updated_particles[0].GetPosition() == vec2(85.0, 83.0));
      REQUIRE(updated_particles[0].GetVelocity() == vec2(-5.0, -7.0));
    }
  }

  SECTION("Two particles") {
    SECTION("Two particles touches but doesn't collide with a wall in a frame") {
      vector<Particle> all_particles;

      // Particle 1 touches but doesn't collide with top wall
      Particle particle1 = Particle(10, 5, glm::vec2(30.0, 10.0), glm::vec2(5, 7), 0);
      all_particles.push_back(particle1);

      // Particle 2 touches but doesn't collide with bottom wall
      Particle particle2 = Particle(10, 5, glm::vec2(30.0, 90.0), glm::vec2(5, -7), 0);
      all_particles.push_back(particle2);

      ideal_gas.SetInfoForParticles(all_particles);
      ideal_gas.UpdateParticles();
      vector<Particle> updated_particles = ideal_gas.GetInfoForParticles();

      // Particle 1
      REQUIRE(updated_particles[0].GetPosition() == vec2(35.0, 17.0));
      REQUIRE(updated_particles[0].GetVelocity() == vec2(5.0, 7.0));

      // Particle 2
      REQUIRE(updated_particles[1].GetPosition() == vec2(35.0, 83.0));
      REQUIRE(updated_particles[1].GetVelocity() == vec2(5.0, -7.0));
    }

    SECTION("One of two particles touches but doesn't collide with a wall in a frame") {
      vector<Particle> all_particles;

      // Particle 1 touches but doesn't collide with top wall
      Particle particle1 = Particle(10, 5, glm::vec2(30.0, 10.0), glm::vec2(5, 7), 0);
      all_particles.push_back(particle1);

      // Particle 2 doesn't collide with anything
      Particle particle2 = Particle(10, 5, glm::vec2(30.0, 50.0), glm::vec2(5, 7), 0);
      all_particles.push_back(particle2);

      ideal_gas.SetInfoForParticles(all_particles);
      ideal_gas.UpdateParticles();
      vector<Particle> updated_particles = ideal_gas.GetInfoForParticles();

      // Particle 1
      REQUIRE(updated_particles[0].GetPosition() == vec2(35.0, 17.0));
      REQUIRE(updated_particles[0].GetVelocity() == vec2(5.0, 7.0));

      // Particle 2
      REQUIRE(updated_particles[1].GetPosition() == vec2(35.0, 57.0));
      REQUIRE(updated_particles[1].GetVelocity() == vec2(5.0, 7.0));
    }
  }
}*/