#include <core/ideal_gas.h>

#include <catch2/catch.hpp>

using idealgas::IdealGas;
using idealgas::Particle;

TEST_CASE("Create particle", "[create particle]") {
  IdealGas ideal_gas = IdealGas(0, 0, 100, 100, 10);

  SECTION("Create particle when container is empty") {
    ideal_gas.CreateParticle(10, "red");

    vector<Particle> all_particles = ideal_gas.GetInfoForParticles();

    REQUIRE(all_particles.size() == 1);
    REQUIRE(all_particles[0].GetRadius() == 20);
    REQUIRE(all_particles[0].GetMass() == 10);
    REQUIRE(all_particles[0].GetPosition() == vec2(20, 20));
    REQUIRE(all_particles[0].GetVelocity() == vec2(5, 5));
    REQUIRE(all_particles[0].GetSpeed() == Approx(7.071).margin(0.01));
    REQUIRE(all_particles[0].GetColor() == "red");
  }

  SECTION("Create particle when container is not empty") {
    vector<Particle> existing_particles;

    // Create existing particles
    Particle particle;
    particle.SetRadius(20);
    particle.SetMass(10);
    particle.SetPosition(vec2(80, 80));
    particle.SetVelocity(vec2(-7, -9));
    particle.SetSpeed(11.401);

    existing_particles.push_back(particle);
    ideal_gas.SetInfoForParticles(existing_particles);

    // Create a new particle
    ideal_gas.CreateParticle(16, "red");

    // Get all particles
    vector<Particle> all_particles = ideal_gas.GetInfoForParticles();

    REQUIRE(all_particles[0].GetRadius() == 20);
    REQUIRE(all_particles[0].GetMass() == 10);
    REQUIRE(all_particles[0].GetPosition() == vec2(80, 80));
    REQUIRE(all_particles[0].GetVelocity() == vec2(-7, -9));
    REQUIRE(all_particles[0].GetSpeed() == Approx(11.401).margin(0.01));

    REQUIRE(all_particles[1].GetRadius() == 32);
    REQUIRE(all_particles[1].GetMass() == 16);
    REQUIRE(all_particles[1].GetPosition() == vec2(32, 32));
    REQUIRE(all_particles[1].GetVelocity() == vec2(8, 8));
    REQUIRE(all_particles[1].GetSpeed() == Approx(11.314). margin(0.01));
    REQUIRE(all_particles[1].GetColor() == "red");
  }

  SECTION("Particles aren't created if max is reached") {
    for (size_t i = 0; i < 25; i++) {
      ideal_gas.CreateParticle(10, "red");
    }

    REQUIRE(ideal_gas.GetInfoForParticles().size() == 10);
  }
}

TEST_CASE("Particle position updates after 1 frame (no collision)  (same mass)",
          "[position][one frame][no collision][same mass]") {
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
    vector<Particle> updated_particles = ideal_gas.GetInfoForParticles();

    REQUIRE(updated_particles[0].GetPosition() == vec2(20.0, 20.0));
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
    vector<Particle> updated_particles = ideal_gas.GetInfoForParticles();

    // Particle 1
    REQUIRE(updated_particles[0].GetPosition() == vec2(20.0, 20.0));
    REQUIRE(updated_particles[0].GetVelocity() == vec2(5.0, 5.0));

    // Particle 2
    REQUIRE(updated_particles[1].GetPosition() == vec2(50.0, 36.0));
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
    vector<Particle> updated_particles = ideal_gas.GetInfoForParticles();

    // Particle 1
    REQUIRE(updated_particles[0].GetPosition() == vec2(20.0, 20.0));
    REQUIRE(updated_particles[0].GetVelocity() == vec2(5.0, 5.0));

    // Particle 2
    REQUIRE(updated_particles[1].GetPosition() == vec2(50.0, 36.0));
    REQUIRE(updated_particles[1].GetVelocity() == vec2(-5.0, 6.0));

    // Particle 3
    REQUIRE(updated_particles[2].GetPosition() == vec2(62.3, 83.4));
    REQUIRE(updated_particles[2].GetVelocity() == vec2(-7.7, 3.4));
  }
}

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

TEST_CASE("Particle position updates after collision with same mass particle(s)",
          "[position][one frame][collision][particle][same mass]") {
  IdealGas ideal_gas = IdealGas(0, 0, 100, 100, 10);

  SECTION("Two particles") {
    SECTION("Two particles collide") {
      SECTION("Two particles moving in opposite directions collide") {
        vector<Particle> all_particles;

        // Particle 1
        Particle particle1 = Particle(10, 5, glm::vec2(40.0, 50.0), glm::vec2(5.0, 7.0), 0);
        all_particles.push_back(particle1);

        // Particle 2
        Particle particle2 = Particle(10, 5, vec2(50.0, 55.0), vec2(0.0, -5.0), 0);
        all_particles.push_back(particle2);

        ideal_gas.SetInfoForParticles(all_particles);
        ideal_gas.UpdateParticles();
        vector<Particle> updated_particles = ideal_gas.GetInfoForParticles();

        // Particle 1
        REQUIRE(updated_particles[0].GetPosition().x == Approx(36.2).margin(0.01));
        REQUIRE(updated_particles[0].GetPosition().y == Approx(52.6).margin(0.01));
        REQUIRE(updated_particles[0].GetVelocity().x == Approx(-3.8).margin(0.01));
        REQUIRE(updated_particles[0].GetVelocity().y == Approx(2.6).margin(0.01));

        // Particle 2
        REQUIRE(updated_particles[1].GetPosition().x == Approx(58.8).margin(0.01));
        REQUIRE(updated_particles[1].GetPosition().y == Approx(54.4).margin(0.01));
        REQUIRE(updated_particles[1].GetVelocity().x == Approx(8.8).margin(0.01));
        REQUIRE(updated_particles[1].GetVelocity().y == Approx(-0.6).margin(0.01));
      }

      SECTION("Two particles moving in same direction, with the one behind the first"
              "particle having a higher velocity, collide") {
        vector<Particle> all_particles;

        // Particle 1
        Particle particle1 = Particle(10, 5, glm::vec2(40.0, 50.0), glm::vec2(5.0, 7.0), 0);
        all_particles.push_back(particle1);

        // Particle 2
        Particle particle2 = Particle(10, 5, vec2(50.0, 55.0), vec2(0.0, 5.0), 0);
        all_particles.push_back(particle2);

        ideal_gas.SetInfoForParticles(all_particles);
        ideal_gas.UpdateParticles();
        vector<Particle> updated_particles = ideal_gas.GetInfoForParticles();

        // Particle 1
        REQUIRE(updated_particles[0].GetPosition().x == Approx(40.2).margin(0.01));
        REQUIRE(updated_particles[0].GetPosition().y == Approx(54.6).margin(0.01));
        REQUIRE(updated_particles[0].GetVelocity().x == Approx(0.2).margin(0.01));
        REQUIRE(updated_particles[0].GetVelocity().y == Approx(4.6).margin(0.01));

        // Particle 2
        REQUIRE(updated_particles[1].GetPosition().x == Approx(54.8).margin(0.01));
        REQUIRE(updated_particles[1].GetPosition().y == Approx(62.4).margin(0.01));
        REQUIRE(updated_particles[1].GetVelocity().x == Approx(4.8).margin(0.01));
        REQUIRE(updated_particles[1].GetVelocity().y == Approx(7.4).margin(0.01));
      }
    }

    SECTION("Particle collides with a particle and a wall") {
      SECTION("Updated particle position goes past boundary") {
        vector<Particle> all_particles;

        // Particle 1
        Particle particle1 = Particle(10, 5, glm::vec2(30.0, 90.0), glm::vec2(5.0, 5.0), 0);
        all_particles.push_back(particle1);

        // Particle 2
        Particle particle2 = Particle(10, 5, vec2(30.0, 80.0), vec2(0.0, 7.0), 0);
        all_particles.push_back(particle2);

        ideal_gas.SetInfoForParticles(all_particles);
        ideal_gas.UpdateParticles();
        vector<Particle> updated_particles = ideal_gas.GetInfoForParticles();

        // Particle 1
        // Would've been (35.0, 97.0) if not adjusted
        REQUIRE(updated_particles[0].GetPosition().x == Approx(35.0).margin(0.01));
        REQUIRE(updated_particles[0].GetPosition().y == Approx(90.0).margin(0.01));
        REQUIRE(updated_particles[0].GetVelocity().x == Approx(5.0).margin(0.01));
        REQUIRE(updated_particles[0].GetVelocity().y == Approx(7.0).margin(0.01));

        // Particle 2
        REQUIRE(updated_particles[1].GetPosition().x == Approx(30.0).margin(0.01));
        REQUIRE(updated_particles[1].GetPosition().y == Approx(75.0).margin(0.01));
        REQUIRE(updated_particles[1].GetVelocity().x == Approx(0.0).margin(0.01));
        REQUIRE(updated_particles[1].GetVelocity().y == Approx(-5.0).margin(0.01));
      }

      SECTION("Updated particle position is within boundary") { // Isn't actually within boundary
        vector<Particle> all_particles;

        // Particle 1
        Particle particle1 = Particle(10, 5, glm::vec2(30.0, 90.0), glm::vec2(-5.0, 5.0), 0);
        all_particles.push_back(particle1);

        // Particle 2
        Particle particle2 = Particle(10, 5, vec2(25.0, 85.0), vec2(0.0, 7.0), 0);
        all_particles.push_back(particle2);

        ideal_gas.SetInfoForParticles(all_particles);
        ideal_gas.UpdateParticles();
        vector<Particle> updated_particles = ideal_gas.GetInfoForParticles();

        // Particle 1
        REQUIRE(updated_particles[0].GetPosition().x == Approx(33.5).margin(0.01));
        REQUIRE(updated_particles[0].GetPosition().y == Approx(90.0).margin(0.01));
        REQUIRE(updated_particles[0].GetVelocity().x == Approx(3.5).margin(0.01));
        REQUIRE(updated_particles[0].GetVelocity().y == Approx(3.5).margin(0.01));

        // Particle 2
        REQUIRE(updated_particles[1].GetPosition().x == Approx(16.5).margin(0.01));
        REQUIRE(updated_particles[1].GetPosition().y == Approx(83.5).margin(0.01));
        REQUIRE(updated_particles[1].GetVelocity().x == Approx(-8.5).margin(0.01));
        REQUIRE(updated_particles[1].GetVelocity().y == Approx(-1.5).margin(0.01));
      }
    }
  }

  SECTION("Three particles") {
    SECTION("Two particles collide, one particle collides with a wall") {
      vector<Particle> all_particles;

      // Particle 1 collides with Particle 2
      Particle particle1 = Particle(10, 5, glm::vec2(40.0, 50.0), glm::vec2(5.0, 7.0), 0);
      all_particles.push_back(particle1);

      // Particle 2 collides with Particle 1
      Particle particle2 = Particle(10, 5, vec2(50.0, 55.0), vec2(0.0, -5.0), 0);
      all_particles.push_back(particle2);

      // Particle 3 collides with wall
      Particle particle3 = Particle(10, 5, glm::vec2(30.0, 90.0), glm::vec2(5, 7), 0);
      all_particles.push_back(particle3);

      ideal_gas.SetInfoForParticles(all_particles);
      ideal_gas.UpdateParticles();
      vector<Particle> updated_particles = ideal_gas.GetInfoForParticles();

      // Particle 1
      REQUIRE(updated_particles[0].GetPosition().x == Approx(36.2).margin(0.01));
      REQUIRE(updated_particles[0].GetPosition().y == Approx(52.6).margin(0.01));
      REQUIRE(updated_particles[0].GetVelocity().x == Approx(-3.8).margin(0.01));
      REQUIRE(updated_particles[0].GetVelocity().y == Approx(2.6).margin(0.01));

      // Particle 2
      REQUIRE(updated_particles[1].GetPosition().x == Approx(58.8).margin(0.01));
      REQUIRE(updated_particles[1].GetPosition().y == Approx(54.4).margin(0.01));
      REQUIRE(updated_particles[1].GetVelocity().x == Approx(8.8).margin(0.01));
      REQUIRE(updated_particles[1].GetVelocity().y == Approx(-0.6).margin(0.01));

      // Particle 3
      REQUIRE(updated_particles[2].GetPosition().x == Approx(35.0).margin(0.01));
      REQUIRE(updated_particles[2].GetPosition().y == Approx(83.0).margin(0.01));
      REQUIRE(updated_particles[2].GetVelocity().x == Approx(5.0).margin(0.01));
      REQUIRE(updated_particles[2].GetVelocity().y == Approx(-7.0).margin(0.01));
    }

    SECTION("Two particles collide, one particle doesn't collide with anything") {
      vector<Particle> all_particles;

      // Particle 1 collides with Particle 2
      Particle particle1 = Particle(10, 5, glm::vec2(40.0, 50.0), glm::vec2(5.0, 7.0), 0);
      all_particles.push_back(particle1);

      // Particle 2 collides with Particle 1
      Particle particle2 = Particle(10, 5, vec2(50.0, 55.0), vec2(0.0, -5.0), 0);
      all_particles.push_back(particle2);

      // Particle 3 doesn't collide with anything
      Particle particle3 = Particle( 10, 5, vec2(70.0, 80.0), vec2(-7.7, 3.4), 0);
      all_particles.push_back(particle3);

      ideal_gas.SetInfoForParticles(all_particles);
      ideal_gas.UpdateParticles();
      vector<Particle> updated_particles = ideal_gas.GetInfoForParticles();

      // Particle 1
      REQUIRE(updated_particles[0].GetPosition().x == Approx(36.2).margin(0.01));
      REQUIRE(updated_particles[0].GetPosition().y == Approx(52.6).margin(0.01));
      REQUIRE(updated_particles[0].GetVelocity().x == Approx(-3.8).margin(0.01));
      REQUIRE(updated_particles[0].GetVelocity().y == Approx(2.6).margin(0.01));

      // Particle 2
      REQUIRE(updated_particles[1].GetPosition().x == Approx(58.8).margin(0.01));
      REQUIRE(updated_particles[1].GetPosition().y == Approx(54.4).margin(0.01));
      REQUIRE(updated_particles[1].GetVelocity().x == Approx(8.8).margin(0.01));
      REQUIRE(updated_particles[1].GetVelocity().y == Approx(-0.6).margin(0.01));

      // Particle 3
      REQUIRE(updated_particles[2].GetPosition().x == Approx(62.3).margin(0.01));
      REQUIRE(updated_particles[2].GetPosition().y == Approx(83.4).margin(0.01));
      REQUIRE(updated_particles[2].GetVelocity().x == Approx(-7.7).margin(0.01));
      REQUIRE(updated_particles[2].GetVelocity().y == Approx(3.4).margin(0.01));
    }

    SECTION("Particle collides with two particles") {
      vector<Particle> all_particles;

      // Particle 1 collides with Particle 2
      Particle particle1 = Particle(10, 5, glm::vec2(40.0, 50.0), glm::vec2(5.0, 7.0), 0);
      all_particles.push_back(particle1);

      // Particle 2 collides with Particle 1 and 3
      Particle particle2 = Particle(10, 5, vec2(50.0, 65.0), vec2(0.0, 5.0), 0);
      all_particles.push_back(particle2);

      // Particle 3 collides with Particle 2
      Particle particle3 = Particle(10, 5, vec2(38.0, 80.0), vec2(5.0, -7.0), 0);
      all_particles.push_back(particle3);

      ideal_gas.SetInfoForParticles(all_particles);
      ideal_gas.UpdateParticles();
      vector<Particle> updated_particles = ideal_gas.GetInfoForParticles();

      // Particle 1
      REQUIRE(updated_particles[0].GetPosition().x == Approx(42.538).margin(0.01));
      REQUIRE(updated_particles[0].GetPosition().y == Approx(53.308).margin(0.01));
      REQUIRE(updated_particles[0].GetVelocity().x == Approx(2.538).margin(0.01));
      REQUIRE(updated_particles[0].GetVelocity().y == Approx(3.308).margin(0.01));

      // Particle 2
      REQUIRE(updated_particles[1].GetPosition().x == Approx(61.107).margin(0.01));
      REQUIRE(updated_particles[1].GetPosition().y == Approx(62.886).margin(0.01));
      REQUIRE(updated_particles[1].GetVelocity().x == Approx(11.107).margin(0.01));
      REQUIRE(updated_particles[1].GetVelocity().y == Approx(-2.114).margin(0.01));

      // Particle 3
      REQUIRE(updated_particles[2].GetPosition().x == Approx(34.355).margin(0.01));
      REQUIRE(updated_particles[2].GetPosition().y == Approx(83.806).margin(0.01));
      REQUIRE(updated_particles[2].GetVelocity().x == Approx(-3.645).margin(0.01));
      REQUIRE(updated_particles[2].GetVelocity().y == Approx(3.806).margin(0.01));
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
}

TEST_CASE("Particle touches but isn't colliding with same mass particle(s)",
          "[one frame][no collision][particle][same mass]") {
  IdealGas ideal_gas = IdealGas(0, 0, 100, 100, 10);

  SECTION("Two particles") {
    SECTION("Two particles touch but don't collide") {
      SECTION("Two particles moving in opposite directions") {
        vector<Particle> all_particles;

        // Particle 1
        Particle particle1 = Particle(10, 5, glm::vec2(40.0, 50.0), glm::vec2(-5.0, -7.0), 0);
        all_particles.push_back(particle1);

        // Particle 2
        Particle particle2 = Particle(10, 5, vec2(50.0, 55.0), vec2(0.0, 5.0), 0);
        all_particles.push_back(particle2);

        ideal_gas.SetInfoForParticles(all_particles);
        ideal_gas.UpdateParticles();
        vector<Particle> updated_particles = ideal_gas.GetInfoForParticles();

        // Particle 1
        REQUIRE(updated_particles[0].GetPosition().x == Approx(35.0).margin(0.01));
        REQUIRE(updated_particles[0].GetPosition().y == Approx(43.0).margin(0.01));
        REQUIRE(updated_particles[0].GetVelocity().x == Approx(-5.0).margin(0.01));
        REQUIRE(updated_particles[0].GetVelocity().y == Approx(-7.0).margin(0.01));

        // Particle 2
        REQUIRE(updated_particles[1].GetPosition().x == Approx(50.0).margin(0.01));
        REQUIRE(updated_particles[1].GetPosition().y == Approx(60.0).margin(0.01));
        REQUIRE(updated_particles[1].GetVelocity().x == Approx(0.0).margin(0.01));
        REQUIRE(updated_particles[1].GetVelocity().y == Approx(5.0).margin(0.01));
      }

      SECTION("Two particles moving in same direction, with the one behind the first"
              "particle having a smaller velocity, touch but don't collide") {
        vector<Particle> all_particles;

        // Particle 1
        Particle particle1 = Particle(10, 5, glm::vec2(40.0, 50.0), glm::vec2(-5.0, -7.0), 0);
        all_particles.push_back(particle1);

        // Particle 2
        Particle particle2 = Particle(10, 5, vec2(50.0, 55.0), vec2(0.0, -5.0), 0);
        all_particles.push_back(particle2);

        ideal_gas.SetInfoForParticles(all_particles);
        ideal_gas.UpdateParticles();
        vector<Particle> updated_particles = ideal_gas.GetInfoForParticles();

        // Particle 1
        REQUIRE(updated_particles[0].GetPosition().x == Approx(35.0).margin(0.01));
        REQUIRE(updated_particles[0].GetPosition().y == Approx(43.0).margin(0.01));
        REQUIRE(updated_particles[0].GetVelocity().x == Approx(-5.0).margin(0.01));
        REQUIRE(updated_particles[0].GetVelocity().y == Approx(-7.0).margin(0.01));

        // Particle 2
        REQUIRE(updated_particles[1].GetPosition().x == Approx(50.0).margin(0.01));
        REQUIRE(updated_particles[1].GetPosition().y == Approx(50.0).margin(0.01));
        REQUIRE(updated_particles[1].GetVelocity().x == Approx(0.0).margin(0.01));
        REQUIRE(updated_particles[1].GetVelocity().y == Approx(-5.0).margin(0.01));
      }
    }

    SECTION("Particle touches but doesn't collide with a particle and a wall") {
      vector<Particle> all_particles;

      // Particle 1
      Particle particle1 = Particle(10, 5, glm::vec2(30.0, 90.0), glm::vec2(-5.0, -5.0), 0);
      all_particles.push_back(particle1);

      // Particle 2
      Particle particle2 = Particle(10, 5, vec2(30.0, 80.0), vec2(0.0, -7.0), 0);
      all_particles.push_back(particle2);

      ideal_gas.SetInfoForParticles(all_particles);
      ideal_gas.UpdateParticles();
      vector<Particle> updated_particles = ideal_gas.GetInfoForParticles();

      // Particle 1
      REQUIRE(updated_particles[0].GetPosition().x == Approx(25.0).margin(0.01));
      REQUIRE(updated_particles[0].GetPosition().y == Approx(85.0).margin(0.01));
      REQUIRE(updated_particles[0].GetVelocity().x == Approx(-5.0).margin(0.01));
      REQUIRE(updated_particles[0].GetVelocity().y == Approx(-5.0).margin(0.01));

      // Particle 2
      REQUIRE(updated_particles[1].GetPosition().x == Approx(30.0).margin(0.01));
      REQUIRE(updated_particles[1].GetPosition().y == Approx(73.0).margin(0.01));
      REQUIRE(updated_particles[1].GetVelocity().x == Approx(0.0).margin(0.01));
      REQUIRE(updated_particles[1].GetVelocity().y == Approx(-7.0).margin(0.01));
    }
  }

  SECTION("Three particles") {
    SECTION("Two particles touch but don't collide,"
            "one particle touches but doesn't collide with a wall") {
      vector<Particle> all_particles;

      // Particle 1 touches but doesn't collide with Particle 2
      Particle particle1 = Particle(10, 5, glm::vec2(40.0, 50.0), glm::vec2(-5.0, -7.0), 0);
      all_particles.push_back(particle1);

      // Particle 2 touches but doesn't collide with Particle 1
      Particle particle2 = Particle(10, 5, vec2(50.0, 55.0), vec2(0.0, 5.0), 0);
      all_particles.push_back(particle2);

      // Particle 3 touches but doesn't collide with wall
      Particle particle3 = Particle(10, 5, glm::vec2(30.0, 90.0), glm::vec2(5, -7), 0);
      all_particles.push_back(particle3);

      ideal_gas.SetInfoForParticles(all_particles);
      ideal_gas.UpdateParticles();
      vector<Particle> updated_particles = ideal_gas.GetInfoForParticles();

      // Particle 1
      REQUIRE(updated_particles[0].GetPosition().x == Approx(35.0).margin(0.01));
      REQUIRE(updated_particles[0].GetPosition().y == Approx(43.0).margin(0.01));
      REQUIRE(updated_particles[0].GetVelocity().x == Approx(-5.0).margin(0.01));
      REQUIRE(updated_particles[0].GetVelocity().y == Approx(-7.0).margin(0.01));

      // Particle 2
      REQUIRE(updated_particles[1].GetPosition().x == Approx(50.0).margin(0.01));
      REQUIRE(updated_particles[1].GetPosition().y == Approx(60.0).margin(0.01));
      REQUIRE(updated_particles[1].GetVelocity().x == Approx(0.0).margin(0.01));
      REQUIRE(updated_particles[1].GetVelocity().y == Approx(5.0).margin(0.01));

      // Particle 3
      REQUIRE(updated_particles[2].GetPosition().x == Approx(35.0).margin(0.01));
      REQUIRE(updated_particles[2].GetPosition().y == Approx(83.0).margin(0.01));
      REQUIRE(updated_particles[2].GetVelocity().x == Approx(5.0).margin(0.01));
      REQUIRE(updated_particles[2].GetVelocity().y == Approx(-7.0).margin(0.01));
    }

    SECTION("Two particles collide, one particle doesn't collide with anything") {
      vector<Particle> all_particles;

      // Particle 1 collides with Particle 2
      Particle particle1 = Particle(10, 5, glm::vec2(40.0, 50.0), glm::vec2(-5.0, -7.0), 0);
      all_particles.push_back(particle1);

      // Particle 2 collides with Particle 1
      Particle particle2 = Particle(10, 5, vec2(50.0, 55.0), vec2(0.0, 5.0), 0);
      all_particles.push_back(particle2);

      // Particle 3 doesn't collide with anything
      Particle particle3 = Particle(10, 5, vec2(70.0, 80.0), vec2(-7.7, 3.4), 0);
      all_particles.push_back(particle3);

      ideal_gas.SetInfoForParticles(all_particles);
      ideal_gas.UpdateParticles();
      vector<Particle> updated_particles = ideal_gas.GetInfoForParticles();

      // Particle 1
      REQUIRE(updated_particles[0].GetPosition().x == Approx(35.0).margin(0.01));
      REQUIRE(updated_particles[0].GetPosition().y == Approx(43.0).margin(0.01));
      REQUIRE(updated_particles[0].GetVelocity().x == Approx(-5.0).margin(0.01));
      REQUIRE(updated_particles[0].GetVelocity().y == Approx(-7.0).margin(0.01));

      // Particle 2
      REQUIRE(updated_particles[1].GetPosition().x == Approx(50.0).margin(0.01));
      REQUIRE(updated_particles[1].GetPosition().y == Approx(60.0).margin(0.01));
      REQUIRE(updated_particles[1].GetVelocity().x == Approx(0.0).margin(0.01));
      REQUIRE(updated_particles[1].GetVelocity().y == Approx(5.0).margin(0.01));

      // Particle 3
      REQUIRE(updated_particles[2].GetPosition().x == Approx(62.3).margin(0.01));
      REQUIRE(updated_particles[2].GetPosition().y == Approx(83.4).margin(0.01));
      REQUIRE(updated_particles[2].GetVelocity().x == Approx(-7.7).margin(0.01));
      REQUIRE(updated_particles[2].GetVelocity().y == Approx(3.4).margin(0.01));
    }

    SECTION("Particle touches but doesn't collide with two particles") {
      vector<Particle> all_particles;

      // Particle 1 touches but doesn't collide with Particle 2
      Particle particle1 = Particle(10, 5, glm::vec2(40.0, 50.0), glm::vec2(-5.0, -7.0), 0);
      all_particles.push_back(particle1);

      // Particle 2 touches but doesn't collide with Particle 1 and 3
      Particle particle2 = Particle(10, 5, vec2(50.0, 65.0), vec2(0.0, -5.0), 0);
      all_particles.push_back(particle2);

      // Particle 3 touches but doesn't collide with Particle 2
      Particle particle3 = Particle(10, 5, vec2(38.0, 80.0), vec2(-5.0, 7.0), 0);
      all_particles.push_back(particle3);

      ideal_gas.SetInfoForParticles(all_particles);
      ideal_gas.UpdateParticles();
      vector<Particle> updated_particles = ideal_gas.GetInfoForParticles();

      // Particle 1
      REQUIRE(updated_particles[0].GetPosition().x == Approx(35.0).margin(0.01));
      REQUIRE(updated_particles[0].GetPosition().y == Approx(43.0).margin(0.01));
      REQUIRE(updated_particles[0].GetVelocity().x == Approx(-5.0).margin(0.01));
      REQUIRE(updated_particles[0].GetVelocity().y == Approx(-7.0).margin(0.01));

      // Particle 2
      REQUIRE(updated_particles[1].GetPosition().x == Approx(50.0).margin(0.01));
      REQUIRE(updated_particles[1].GetPosition().y == Approx(60.0).margin(0.01));
      REQUIRE(updated_particles[1].GetVelocity().x == Approx(0.0).margin(0.01));
      REQUIRE(updated_particles[1].GetVelocity().y == Approx(-5.0).margin(0.01));

      // Particle 3
      REQUIRE(updated_particles[2].GetPosition().x == Approx(33.0).margin(0.01));
      REQUIRE(updated_particles[2].GetPosition().y == Approx(87.0).margin(0.01));
      REQUIRE(updated_particles[2].GetVelocity().x == Approx(-5.0).margin(0.01));
      REQUIRE(updated_particles[2].GetVelocity().y == Approx(7.0).margin(0.01));
    }
  }
}

TEST_CASE("Check speed gets updated", "[speed][same mass][collision]") {
  IdealGas ideal_gas = IdealGas(0, 0, 100, 100, 10);

  SECTION("Two particles moving in opposite directions collide") {
    vector<Particle> all_particles;

    // Particle 1
    Particle particle1 = Particle(10, 5, glm::vec2(40.0, 50.0), glm::vec2(5.0, 7.0), 8.602);
    all_particles.push_back(particle1);

    // Particle 2
    Particle particle2 = Particle(10, 5, vec2(50.0, 55.0), vec2(0.0, -5.0), 5);
    all_particles.push_back(particle2);

    ideal_gas.SetInfoForParticles(all_particles);
    ideal_gas.UpdateParticles();
    vector<Particle> updated_particles = ideal_gas.GetInfoForParticles();

    // Particle 1
    REQUIRE(updated_particles[0].GetPosition().x == Approx(36.2).margin(0.01));
    REQUIRE(updated_particles[0].GetPosition().y == Approx(52.6).margin(0.01));
    REQUIRE(updated_particles[0].GetVelocity().x == Approx(-3.8).margin(0.01));
    REQUIRE(updated_particles[0].GetVelocity().y == Approx(2.6).margin(0.01));
    REQUIRE(updated_particles[0].GetSpeed() == Approx(4.604).margin(0.01));

    // Particle 2
    REQUIRE(updated_particles[1].GetPosition().x == Approx(58.8).margin(0.01));
    REQUIRE(updated_particles[1].GetPosition().y == Approx(54.4).margin(0.01));
    REQUIRE(updated_particles[1].GetVelocity().x == Approx(8.8).margin(0.01));
    REQUIRE(updated_particles[1].GetVelocity().y == Approx(-0.6).margin(0.01));
    REQUIRE(updated_particles[1].GetSpeed() == Approx(8.820).margin(0.01));
  }
}

TEST_CASE("Particle position updates after 1 frame (no collision) (different mass)",
          "[position][one frame][no collision][different mass]") {
  IdealGas ideal_gas = IdealGas(0, 0, 100, 100, 10);

  SECTION("No particles") {
    ideal_gas.UpdateParticles();

    vector<Particle> updated_particles = ideal_gas.GetInfoForParticles();

    REQUIRE(updated_particles.empty() == true);
  }

  SECTION("One particle") {
    vector<Particle> all_particles;

    Particle particle1 = Particle(10, 5, glm::vec2(15.0, 15.0), glm::vec2(5, 5), 0);
    all_particles.push_back(particle1);

    ideal_gas.SetInfoForParticles(all_particles);
    ideal_gas.UpdateParticles();
    vector<Particle> updated_particles = ideal_gas.GetInfoForParticles();

    REQUIRE(updated_particles[0].GetPosition() == vec2(20.0, 20.0));
    REQUIRE(updated_particles[0].GetVelocity() == vec2(5, 5));
  }

  SECTION("Two particles") {
    vector<Particle> all_particles;

    // Particle 1
    Particle particle1 = Particle(10, 5, glm::vec2(15.0, 15.0), glm::vec2(5.0, 5.0), 0);
    all_particles.push_back(particle1);

    // Particle 2
    Particle particle2 = Particle(16, 8, vec2(55.0, 30.0), vec2(-5.0, 6.0), 0);
    all_particles.push_back(particle2);

    ideal_gas.SetInfoForParticles(all_particles);
    ideal_gas.UpdateParticles();
    vector<Particle> updated_particles = ideal_gas.GetInfoForParticles();

    // Particle 1
    REQUIRE(updated_particles[0].GetPosition() == vec2(20.0, 20.0));
    REQUIRE(updated_particles[0].GetVelocity() == vec2(5.0, 5.0));

    // Particle 2
    REQUIRE(updated_particles[1].GetPosition() == vec2(50.0, 36.0));
    REQUIRE(updated_particles[1].GetVelocity() == vec2(-5.0, 6.0));
  }

  SECTION("Three particles") {
    vector<Particle> all_particles;

    // Particle 1
    Particle particle1 = Particle(10, 5, glm::vec2(15.0, 15.0), glm::vec2(5.0, 5.0), 0);
    all_particles.push_back(particle1);

    // Particle 2
    Particle particle2 = Particle(16, 8, vec2(55.0, 30.0), vec2(-5.0, 6.0), 0);
    all_particles.push_back(particle2);

    // Particle 3
    Particle particle3 = Particle(8, 4, vec2(70.0, 80.0), vec2(-7.7, 3.4), 0);
    all_particles.push_back(particle3);

    ideal_gas.SetInfoForParticles(all_particles);
    ideal_gas.UpdateParticles();
    vector<Particle> updated_particles = ideal_gas.GetInfoForParticles();

    // Particle 1
    REQUIRE(updated_particles[0].GetPosition() == vec2(20.0, 20.0));
    REQUIRE(updated_particles[0].GetVelocity() == vec2(5.0, 5.0));

    // Particle 2
    REQUIRE(updated_particles[1].GetPosition() == vec2(50.0, 36.0));
    REQUIRE(updated_particles[1].GetVelocity() == vec2(-5.0, 6.0));

    // Particle 3
    REQUIRE(updated_particles[2].GetPosition() == vec2(62.3, 83.4));
    REQUIRE(updated_particles[2].GetVelocity() == vec2(-7.7, 3.4));
  }
}

TEST_CASE("Particle position updates after 2 frames (no collision) (different mass)",
          "[position][two frames][no collision][different mass]") {
  IdealGas ideal_gas = IdealGas(0, 0, 100, 100, 10);

  SECTION("No particles") {
    ideal_gas.UpdateParticles();

    vector<Particle> updated_particles = ideal_gas.GetInfoForParticles();

    REQUIRE(updated_particles.empty() == true);
  }

  SECTION("One particle") {
    vector<Particle> all_particles;

    Particle particle1 = Particle(10, 5, glm::vec2(15.0, 15.0), glm::vec2(5, 5), 0);
    all_particles.push_back(particle1);

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
    Particle particle1 = Particle(10, 5, glm::vec2(15.0, 15.0), glm::vec2(0, 5.0), 0);
    all_particles.push_back(particle1);

    // Particle 2
    Particle particle2 = Particle(16, 8, vec2(55.0, 30.0), vec2(0, 2.0), 0);
    all_particles.push_back(particle2);

    ideal_gas.SetInfoForParticles(all_particles);
    ideal_gas.UpdateParticles();
    ideal_gas.UpdateParticles();
    vector<Particle> updated_particles = ideal_gas.GetInfoForParticles();

    // Particle 1
    REQUIRE(updated_particles[0].GetPosition() == vec2(15.0, 25.0));
    REQUIRE(updated_particles[0].GetVelocity() == vec2(0, 5.0));

    // Particle 2
    REQUIRE(updated_particles[1].GetPosition() == vec2(55.0, 34.0));
    REQUIRE(updated_particles[1].GetVelocity() == vec2(0, 2.0));
  }

  SECTION("Three particles") {
    vector<Particle> all_particles;

    // Particle 1
    Particle particle1 = Particle(10, 5, glm::vec2(15.0, 15.0), glm::vec2(0.0, 5.0), 0);
    all_particles.push_back(particle1);

    // Particle 2
    Particle particle2 = Particle(16, 8, vec2(55.0, 30.0), vec2(0, -2.0), 0);
    all_particles.push_back(particle2);

    // Particle 3
    Particle particle3 = Particle(10, 5, vec2(70.0, 80.0), vec2(-7.7, 0), 0);
    all_particles.push_back(particle3);

    ideal_gas.SetInfoForParticles(all_particles);
    ideal_gas.UpdateParticles();
    ideal_gas.UpdateParticles();
    vector<Particle> updated_particles = ideal_gas.GetInfoForParticles();

    // Particle 1
    REQUIRE(updated_particles[0].GetPosition() == vec2(15.0, 25.0));
    REQUIRE(updated_particles[0].GetVelocity() == vec2(0.0, 5.0));

    // Particle 2
    REQUIRE(updated_particles[1].GetPosition() == vec2(55.0, 26.0));
    REQUIRE(updated_particles[1].GetVelocity() == vec2(0.0, -2.0));

    // Particle 3
    REQUIRE(updated_particles[2].GetPosition() == vec2(54.6, 80.0));
    REQUIRE(updated_particles[2].GetVelocity() == vec2(-7.7, 0));
  }
}

TEST_CASE("Particle updates after collision with different mass particle(s)",
          "[one frame][collision][particle][different mass]") {
  IdealGas ideal_gas = IdealGas(0, 0, 100, 100, 10);

  SECTION("Two particles") {
    SECTION("Two particles collide") {
      SECTION("Two particles moving in opposite directions collide") {
        vector<Particle> all_particles;

        // Particle 1
        Particle particle1 = Particle(10, 5, glm::vec2(40.0, 50.0), glm::vec2(5.0, 7.0), 0);
        all_particles.push_back(particle1);

        // Particle 2
        Particle particle2 = Particle(4, 2, vec2(54.0, 50.0), vec2(-1.0, 0.0), 0);
        all_particles.push_back(particle2);

        ideal_gas.SetInfoForParticles(all_particles);
        ideal_gas.UpdateParticles();
        vector<Particle> updated_particles = ideal_gas.GetInfoForParticles();

        // Particle 1
        REQUIRE(updated_particles[0].GetPosition().x == Approx(41.5714).margin(0.01));
        REQUIRE(updated_particles[0].GetPosition().y == Approx(57).margin(0.01));
        REQUIRE(updated_particles[0].GetVelocity().x == Approx(1.5714).margin(0.01));
        REQUIRE(updated_particles[0].GetVelocity().y == Approx(7).margin(0.01));

        // Particle 2
        REQUIRE(updated_particles[1].GetPosition().x == Approx(61.5714).margin(0.01));
        REQUIRE(updated_particles[1].GetPosition().y == Approx(50).margin(0.01));
        REQUIRE(updated_particles[1].GetVelocity().x == Approx(7.5714).margin(0.01));
        REQUIRE(updated_particles[1].GetVelocity().y == Approx(0).margin(0.01));
      }

      SECTION("Two particles moving in same direction, with the one behind the first"
              "particle having a higher velocity, collide") {
        vector<Particle> all_particles;

        // Particle 1
        Particle particle1 = Particle(10, 5, glm::vec2(40.0, 50.0), glm::vec2(7.0, 0.0), 0);
        all_particles.push_back(particle1);

        // Particle 2
        Particle particle2 = Particle(4, 2, vec2(54.0, 50.0), vec2(2.0, 0.0), 0);
        all_particles.push_back(particle2);

        ideal_gas.SetInfoForParticles(all_particles);
        ideal_gas.UpdateParticles();
        vector<Particle> updated_particles = ideal_gas.GetInfoForParticles();

        // Particle 1
        REQUIRE(updated_particles[0].GetPosition().x == Approx(44.1429).margin(0.01));
        REQUIRE(updated_particles[0].GetPosition().y == Approx(50.0).margin(0.01));
        REQUIRE(updated_particles[0].GetVelocity().x == Approx(4.1429).margin(0.01));
        REQUIRE(updated_particles[0].GetVelocity().y == Approx(0.0).margin(0.01));

        // Particle 2
        REQUIRE(updated_particles[1].GetPosition().x == Approx(63.1429).margin(0.01));
        REQUIRE(updated_particles[1].GetPosition().y == Approx(50.0).margin(0.01));
        REQUIRE(updated_particles[1].GetVelocity().x == Approx(9.1429).margin(0.01));
        REQUIRE(updated_particles[1].GetVelocity().y == Approx(0.0).margin(0.01));
      }
    }

    SECTION("Particle collides with a particle and a wall") {
      SECTION("Updated particle position stays within boundary") {
        vector<Particle> all_particles;

        // Particle 1
        Particle particle1 = Particle(10, 5, glm::vec2(30.0, 84.0), glm::vec2(5.0, 5.0), 0);
        all_particles.push_back(particle1);

        // Particle 2
        Particle particle2 = Particle(4, 2, vec2(30.0, 96.0), vec2(0.0, 3.0), 0);
        all_particles.push_back(particle2);

        ideal_gas.SetInfoForParticles(all_particles);
        ideal_gas.UpdateParticles();
        vector<Particle> updated_particles = ideal_gas.GetInfoForParticles();

        // Particle 1
        REQUIRE(updated_particles[0].GetPosition().x == Approx(35.0).margin(0.01));
        REQUIRE(updated_particles[0].GetPosition().y == Approx(87.8571).margin(0.01));
        REQUIRE(updated_particles[0].GetVelocity().x == Approx(5.0).margin(0.01));
        REQUIRE(updated_particles[0].GetVelocity().y == Approx(3.8571).margin(0.01));

        // Particle 2
        REQUIRE(updated_particles[1].GetPosition().x == Approx(30).margin(0.01));
        REQUIRE(updated_particles[1].GetPosition().y == Approx(90.1429).margin(0.01));
        REQUIRE(updated_particles[1].GetVelocity().x == Approx(0).margin(0.01));
        REQUIRE(updated_particles[1].GetVelocity().y == Approx(-5.8571).margin(0.01));
      }
    }
  }

  SECTION("Three particles") {
    SECTION("Two particles collide, one particle collides with a wall") {
      vector<Particle> all_particles;

      // Particle 1 collides with Particle 2
      Particle particle1 = Particle(10, 5, glm::vec2(40.0, 50.0), glm::vec2(5.0, 7.0), 0);
      all_particles.push_back(particle1);

      // Particle 2 collides with Particle 1
      Particle particle2 = Particle(4, 2, vec2(54.0, 50.0), vec2(-1.0, 0.0), 0);
      all_particles.push_back(particle2);

      // Particle 3 collides with wall
      Particle particle3 = Particle(10, 5, glm::vec2(30.0, 90.0), glm::vec2(5, 7), 0);
      all_particles.push_back(particle3);

      ideal_gas.SetInfoForParticles(all_particles);
      ideal_gas.UpdateParticles();
      vector<Particle> updated_particles = ideal_gas.GetInfoForParticles();

      // Particle 1
      REQUIRE(updated_particles[0].GetPosition().x == Approx(41.5714).margin(0.01));
      REQUIRE(updated_particles[0].GetPosition().y == Approx(57).margin(0.01));
      REQUIRE(updated_particles[0].GetVelocity().x == Approx(1.5714).margin(0.01));
      REQUIRE(updated_particles[0].GetVelocity().y == Approx(7).margin(0.01));

      // Particle 2
      REQUIRE(updated_particles[1].GetPosition().x == Approx(61.5714).margin(0.01));
      REQUIRE(updated_particles[1].GetPosition().y == Approx(50).margin(0.01));
      REQUIRE(updated_particles[1].GetVelocity().x == Approx(7.5714).margin(0.01));
      REQUIRE(updated_particles[1].GetVelocity().y == Approx(0).margin(0.01));

      // Particle 3
      REQUIRE(updated_particles[2].GetPosition().x == Approx(35.0).margin(0.01));
      REQUIRE(updated_particles[2].GetPosition().y == Approx(83.0).margin(0.01));
      REQUIRE(updated_particles[2].GetVelocity().x == Approx(5.0).margin(0.01));
      REQUIRE(updated_particles[2].GetVelocity().y == Approx(-7.0).margin(0.01));
    }

    SECTION("Two particles collide, one particle doesn't collide with anything") {
      vector<Particle> all_particles;

      // Particle 1 collides with Particle 2
      Particle particle1 = Particle(10, 5, glm::vec2(40.0, 50.0), glm::vec2(5.0, 7.0), 0);
      all_particles.push_back(particle1);

      // Particle 2 collides with Particle 1
      Particle particle2 = Particle(4, 2, vec2(54.0, 50.0), vec2(-1.0, 0.0), 0);
      all_particles.push_back(particle2);

      // Particle 3 doesn't collide with anything
      Particle particle3 = Particle(10, 5, vec2(70.0, 80.0), vec2(-7.7, 3.4), 0);
      all_particles.push_back(particle3);

      ideal_gas.SetInfoForParticles(all_particles);
      ideal_gas.UpdateParticles();
      vector<Particle> updated_particles = ideal_gas.GetInfoForParticles();

      // Particle 1
      REQUIRE(updated_particles[0].GetPosition().x == Approx(41.5714).margin(0.01));
      REQUIRE(updated_particles[0].GetPosition().y == Approx(57).margin(0.01));
      REQUIRE(updated_particles[0].GetVelocity().x == Approx(1.5714).margin(0.01));
      REQUIRE(updated_particles[0].GetVelocity().y == Approx(7).margin(0.01));

      // Particle 2
      REQUIRE(updated_particles[1].GetPosition().x == Approx(61.5714).margin(0.01));
      REQUIRE(updated_particles[1].GetPosition().y == Approx(50).margin(0.01));
      REQUIRE(updated_particles[1].GetVelocity().x == Approx(7.5714).margin(0.01));
      REQUIRE(updated_particles[1].GetVelocity().y == Approx(0).margin(0.01));

      // Particle 3
      REQUIRE(updated_particles[2].GetPosition().x == Approx(62.3).margin(0.01));
      REQUIRE(updated_particles[2].GetPosition().y == Approx(83.4).margin(0.01));
      REQUIRE(updated_particles[2].GetVelocity().x == Approx(-7.7).margin(0.01));
      REQUIRE(updated_particles[2].GetVelocity().y == Approx(3.4).margin(0.01));
    }

    SECTION("Particle collides with two particles") {
      vector<Particle> all_particles;

      // Particle 1 collides with Particle 2
      Particle particle1 = Particle(10, 5, glm::vec2(40.0, 50.0), glm::vec2(5.0, 7.0), 0);
      all_particles.push_back(particle1);

      // Particle 2 collides with Particle 1 and 3
      Particle particle2 = Particle(4, 2, vec2(54.0, 50.0), vec2(-1.0, 0.0), 0);
      all_particles.push_back(particle2);

      // Particle 3 collides with Particle 2
      Particle particle3 = Particle(10, 5, vec2(54.0, 40.0), vec2(0, 4.0), 0);
      all_particles.push_back(particle3);

      ideal_gas.SetInfoForParticles(all_particles);
      ideal_gas.UpdateParticles();
      vector<Particle> updated_particles = ideal_gas.GetInfoForParticles();

      // Particle 1
      REQUIRE(updated_particles[0].GetPosition().x == Approx(41.5714).margin(0.01));
      REQUIRE(updated_particles[0].GetPosition().y == Approx(57).margin(0.01));
      REQUIRE(updated_particles[0].GetVelocity().x == Approx(1.5714).margin(0.01));
      REQUIRE(updated_particles[0].GetVelocity().y == Approx(7).margin(0.01));

      // Particle 2
      REQUIRE(updated_particles[1].GetPosition().x == Approx(61.5714).margin(0.01));
      REQUIRE(updated_particles[1].GetPosition().y == Approx(55.7143).margin(0.01));
      REQUIRE(updated_particles[1].GetVelocity().x == Approx(7.5714).margin(0.01));
      REQUIRE(updated_particles[1].GetVelocity().y == Approx(5.7143).margin(0.01));

      // Particle 3
      REQUIRE(updated_particles[2].GetPosition().x == Approx(54).margin(0.01));
      REQUIRE(updated_particles[2].GetPosition().y == Approx(41.7143).margin(0.01));
      REQUIRE(updated_particles[2].GetVelocity().x == Approx(0).margin(0.01));
      REQUIRE(updated_particles[2].GetVelocity().y == Approx(1.7143).margin(0.01));
    }
  }
}