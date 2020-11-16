#include "core/ideal_gas.h"

namespace disease {

IdealGas::IdealGas(double left_margin, double top_margin,
                   double container_height, double container_width,
                   size_t max_num_particles) {
  left_wall_ = left_margin;
  top_wall_ = top_margin;
  bottom_wall_ = top_wall_ + container_height;
  right_wall_ = left_wall_ + container_width;
  max_num_particles_ = max_num_particles;
}

void IdealGas::SetInfoForParticles(const vector<Particle>& particles_to_set_to) {
  info_for_particles_ = particles_to_set_to;
}

const vector<Particle>& IdealGas::GetInfoForParticles() {
  return info_for_particles_;
}

void IdealGas::CreateParticle(double mass, const string& color) {
  if (info_for_particles_.size() != max_num_particles_) {
    Particle new_particle;

    new_particle.SetRadius(mass * 2);
    new_particle.SetMass(mass);
    new_particle.SetPosition(vec2(left_wall_, top_wall_) +
                            vec2(new_particle.GetRadius(), new_particle.GetRadius()));
    new_particle.SetVelocity(vec2(new_particle.GetRadius() / 4, new_particle.GetRadius() /4));
    new_particle.SetSpeed(length(new_particle.GetVelocity()));
    new_particle.SetColor(color);

    info_for_particles_.push_back(new_particle);
  }
}

void IdealGas::UpdateParticles() {
  for (size_t current = 0; current < info_for_particles_.size(); current++) {
    // Check for wall collisions
    if (HasCollidedWithWall(info_for_particles_[current],
                            top_wall_, true) ||
        HasCollidedWithWall(info_for_particles_[current],
                            bottom_wall_, true)) {
      vec2 new_velocity = vec2(info_for_particles_[current].GetVelocity().x,
                               -info_for_particles_[current].GetVelocity().y);
      info_for_particles_[current].SetVelocity(new_velocity);
    }

    if (HasCollidedWithWall(info_for_particles_[current],
                            left_wall_, false) ||
        HasCollidedWithWall(info_for_particles_[current],
                            right_wall_, false)) {
      vec2 new_velocity = vec2(-info_for_particles_[current].GetVelocity().x,
                               info_for_particles_[current].GetVelocity().y);
      info_for_particles_[current].SetVelocity(new_velocity);
    }

    // Check for particle collisions
    for (size_t other = current + 1; other < info_for_particles_.size(); other++) {
      if (HasCollidedWithParticle(info_for_particles_[current],
                                  info_for_particles_[other])) {
        // Get the new velocities
        vec2 current_particle_new_velocity = CalculateVelocitiesAfterParticleCollision(
            info_for_particles_[current], info_for_particles_[other]);
        vec2 other_particle_new_velocity = CalculateVelocitiesAfterParticleCollision(
            info_for_particles_[other], info_for_particles_[current]);

        // Set the new velocities
        info_for_particles_[current].SetVelocity(current_particle_new_velocity);
        info_for_particles_[other].SetVelocity(other_particle_new_velocity);
      }
    }

    vec2 updated_position = info_for_particles_[current].GetPosition() +
        info_for_particles_[current].GetVelocity();
    info_for_particles_[current].SetPosition(KeepWithinContainer(updated_position, info_for_particles_[current].GetRadius()));
        ;

    info_for_particles_[current].SetSpeed(length(info_for_particles_[current].GetVelocity()));
  }
}

bool IdealGas::HasCollidedWithWall(const Particle& current_particle,
                                   double wall_boundary,
                                   bool is_horizontal_wall) const {
  double particle_position_component_different = current_particle.GetPosition().x;
  if (is_horizontal_wall) {
    particle_position_component_different = current_particle.GetPosition().y;
  }

  // Checks if the particle and wall are touching
  if (abs(particle_position_component_different - wall_boundary) <= current_particle.GetRadius()) {
    vec2 wall_position = vec2(wall_boundary, current_particle.GetPosition().y);
    if (is_horizontal_wall) {
      wall_position = vec2(current_particle.GetPosition().x, wall_boundary);
    }

    // Checks if the particle is moving towards the wall
    if (IsMovingTowardsWall(current_particle, wall_position)) {
      return true;
    }
  }
  return false;
}

bool IdealGas::IsMovingTowardsWall(const Particle& current_particle,
                                   const vec2& wall_position) const {
  vec2 velocity_difference = current_particle.GetVelocity();
  vec2 position_difference = current_particle.GetPosition() - wall_position;

  if (dot(velocity_difference, position_difference) < 0) {
    return true;
  }
  return false;
}

bool IdealGas::HasCollidedWithParticle(const Particle& current_particle,
                                       const Particle& other_particle) const {
  // Check if the particles are touching
  if (AreParticlesTouching(current_particle, other_particle)) {
    // Check if the particles are moving towards each other
    if (IsMovingTowardsParticle(current_particle, other_particle)) {
      return true;
    }
  }

  return false;
}

bool IdealGas::AreParticlesTouching(const Particle& current_particle,
                                    const Particle& other_particle) const {
  // Calculate distance between center of particles
  double position_x_val_difference = current_particle.GetPosition().x - other_particle.GetPosition().x;
  double position_y_val_difference = current_particle.GetPosition().y - other_particle.GetPosition().y;
  double sum_of_squared_differences = (position_x_val_difference * position_x_val_difference) +
                                      (position_y_val_difference * position_y_val_difference);
  double distance_between_centers = sqrt(sum_of_squared_differences);

  return (distance_between_centers <= (current_particle.GetRadius() + other_particle.GetRadius()));
}

bool IdealGas::IsMovingTowardsParticle(const Particle& current_particle,
                               const Particle& other_particle) const {
  vec2 velocity_difference = current_particle.GetVelocity() - other_particle.GetVelocity();
  vec2 position_difference = current_particle.GetPosition() - other_particle.GetPosition();

  if (dot(velocity_difference, position_difference) < 0) {
    return true;
  }
  return false;
}

vec2 IdealGas::CalculateVelocitiesAfterParticleCollision(const Particle& particle_one,
                                                         const Particle& particle_two) {
  vec2 velocity_difference = particle_one.GetVelocity() - particle_two.GetVelocity();
  vec2 position_difference = particle_one.GetPosition() - particle_two.GetPosition();

  double mass_component_numerator = 2 * particle_two.GetMass();
  double mass_component_denominator = particle_one.GetMass() + particle_two.GetMass();
  double scale_numerator = dot(velocity_difference, position_difference) *
      mass_component_numerator;
  double scale_denominator = length(position_difference) * length(position_difference) *
      mass_component_denominator;
  double scale = scale_numerator / scale_denominator;

  // Scale the position difference vector
  position_difference.x *= scale;
  position_difference.y *= scale;

  // Calculate the new velocities for particle
  return particle_one.GetVelocity() - position_difference;
}

vec2 IdealGas::KeepWithinContainer(const vec2& updated_position, double current_particle_radius) {
  vec2 updated_position_within_container = updated_position;
  if (updated_position.x + current_particle_radius > right_wall_) {
    updated_position_within_container.x = right_wall_ - current_particle_radius;
  } else if (updated_position.x - current_particle_radius < left_wall_) {
    updated_position_within_container.x = left_wall_ + current_particle_radius;
  }

  if (updated_position.y + current_particle_radius > bottom_wall_) {
    updated_position_within_container.y = bottom_wall_ - current_particle_radius;
  } else if (updated_position.y - current_particle_radius < top_wall_) {
    updated_position_within_container.y = top_wall_ + current_particle_radius;
  }

  return updated_position_within_container;
}

}  // namespace disease