#pragma once

#include "cinder/gl/gl.h"
#include <cmath>
#include <string>
#include <vector>

using glm::vec2;
using glm::vec3;
using std::string;
using std::vector;

namespace disease {

enum class Status {
  kSusceptible,
  kInfectious,
  kRemoved,
};

class Disease {
 public:
  struct Person {
      double radius;
      vec2 position;
      vec2 velocity;
      Status status;
      vec3 color;
      size_t continuous_exposure_time;
      size_t time_infected;
  };

  Disease() = default;
  Disease(double left_margin, double top_margin,
          double container_height, double container_width,
          bool should_create_population);

  void SetPopulation(const vector<Person>& population_to_set_to);
  const vector<Person>& GetPopulation();

  /*
   * Updates the information of all particles in the container,
   * specifically the velocity, speed, and position.
   */
  void UpdateParticles();

 private:
  // ================
  // Person constants
  // ================
  double kRadius = 10;
  int kMinVelComponent = -1;
  int kAddToMinVelComponent = 2;
  double kScaleDenominatorVel = 10.0;
  int kMaxScaleForVelNumerator = 9;

  size_t kPopulationSize = 200;

  // ===================
  // Sketchpad variables
  // ===================
  double left_wall_;
  double top_wall_;
  double bottom_wall_;
  double right_wall_;

  /*
   * Holds all the particles, each representing a person.
   */
  vector<Person> population_;

  /*
   * Creates a susceptible person with their info initialized.
   *
   * @return The person with their info initialized as a susceptible person
   */
  Person CreatePerson();

  /*
   * Generates a random velocity.
   *
   * @return A vec2 representing the generated particle velocity
   */
  vec2 GenerateVelocity();

  /*
   * Creates a person who is infected.
   *
   * @return The person with their info initialized as an infected person
   */
  Person CreatePatientZero();

  /*
   * Checks for wall collisions with the current particle.
   *
   * @param current The index of the current particle
   */
  void CheckForWallCollisions(size_t current);

  /*
   * Checks if the current particle has collided with a specific wall.
   *
   * @param particle the current Particle to check for a collision
   * @param wall_boundary the wall to check for a collision with
   * @param is_horizontal_wall a bool representing if the wall being checked
   *     is a horizontal wall
   * @return a bool representing if the current particle has collided with
   *     the wall
   */
  bool HasCollidedWithWall(const Person& current_particle, double wall_boundary, bool is_horizontal_wall) const;

  /*
   * Checks if the current particle is moving towards a wall.
   *
   * @param current_particle The current particle to check
   * @param wall_position The position of the wall where the current particle
   *      would be touching
   * @return A bool representing if the current particle is moving towards
   *     the wall
   */
  bool IsMovingTowardsWall(const Person& current_particle, const vec2& wall_position) const;





  /*
   * Adjusts the updated position so that the particle will still be within the
   * container walls when the position is updated.
   *
   * @param updated_position A vec2 of the current particle's updated position
   * @param current_particle_radius A double of the current particle's radius
   * @return A vec2 representing the updated_position within the container bounds
   */
  vec2 KeepWithinContainer(const vec2& updated_position, double current_particle_radius);
};

}  // namespace disease