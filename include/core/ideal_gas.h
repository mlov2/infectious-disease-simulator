#pragma once

#include "cinder/gl/gl.h"
#include "core/particle.h"
#include <cmath>
#include <string>
#include <vector>

using glm::vec2;
using std::string;
using std::vector;
using disease::Particle;

namespace disease {

class IdealGas {
 public:
  IdealGas() = default;
  IdealGas(double left_margin, double top_margin,
           double container_height, double container_width,
           size_t max_num_particles);

  void SetInfoForParticles(const vector<Particle>& particles_to_set_to);
  const vector<Particle>& GetInfoForParticles();

  /*
   * Creates a particle with the specified mass.
   *
   * @param mass The mass the new particle should have
   * @param color The color the new particle should have
   */
  void CreateParticle(double mass, const string& color);

  /*
   * Updates the information of all particles in the container,
   * specifically the velocity, speed, and position.
   */
  void UpdateParticles();

 private:
  Particle particle;

  // ===================
  // Sketchpad variables
  // ===================
  double left_wall_;
  double top_wall_;
  double bottom_wall_;
  double right_wall_;
  size_t max_num_particles_;

  /*
   * Holds all the particles.
   */
  vector<Particle> info_for_particles_;

  /*
   * Checks if the current particle has collided with a wall.
   *
   * @param particle the current Particle to check for a collision
   * @param wall_boundary the wall to check for a collision with
   * @param is_horizontal_wall a bool representing if the wall being checked
   *     is a horizontal wall
   * @return a bool representing if the current particle has collided with
   *     the wall
   */
  bool HasCollidedWithWall(const Particle& current_particle, double wall_boundary, bool is_horizontal_wall) const;

  /*
   * Checks if the current particle is moving towards a wall.
   *
   * @param current_particle The current particle to check
   * @param wall_position The position of the wall where the current particle
   *      would be touching
   * @return A bool representing if the current particle is moving towards
   *     the wall
   */
  bool IsMovingTowardsWall(const Particle& current_particle, const vec2& wall_position) const;

  /*
   * Checks if the current particle has collided with another particle.
   *
   * @param current_particle The current Particle to check for a collision
   * @param other_particle The Particle to check a collision with
   * @return A bool representing if the current particle has collided with
   *     another particle
   */
  bool HasCollidedWithParticle(const Particle& current_particle,
                               const Particle& other_particle) const;

  /*
   * Checks if the given particles are touching.
   *
   * @param current_particle The current particle
   * @param other_particle The particle to check
   * @return A bool representing if the two particles are touching
   */
  bool AreParticlesTouching(const Particle& current_particle, const Particle& other_particle) const;

  /*
   * Checks if the current particle is moving towards the other particle.
   *
   * @param current_particle The current particle to check
   * @param other_particle The other particle to check
   * @return A bool representing if the two particles are moving towards
   *     each other
   */
  bool IsMovingTowardsParticle(const Particle& current_particle,
                               const Particle& other_particle) const;

  /*
   * Calculates the new velocity of a particle after it has collided with
   * another particle.
   *
   * @param particle_one The current Particle that's moving
   * @param particle_two The other particle the current Particle has
   *     collided with
   * @return a vec2 representing the new velocity of particle 1
   */
  vec2 CalculateVelocitiesAfterParticleCollision(const Particle& particle_one, const Particle& particle_two);

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