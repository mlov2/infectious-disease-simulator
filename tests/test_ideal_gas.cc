#include <core/ideal_gas.h>

#include <catch2/catch.hpp>

using disease::IdealGas;

/*TEST_CASE("Create particle", "[create particle]") {
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