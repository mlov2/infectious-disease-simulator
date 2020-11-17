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

void IdealGas::SetInfoForParticles(const vector<IdealGas::Person>& particles_to_set_to) {
  info_for_particles_ = particles_to_set_to;
}

const vector<IdealGas::Person>& IdealGas::GetInfoForParticles() {
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
      vec2 new_velocity = vec2(info_for_particles_[current].velocity.x,
                               -info_for_particles_[current].velocity.y);
      info_for_particles_[current].velocity = new_velocity;
    }

    if (HasCollidedWithWall(info_for_particles_[current],
                            left_wall_, false) ||
        HasCollidedWithWall(info_for_particles_[current],
                            right_wall_, false)) {
      vec2 new_velocity = vec2(-info_for_particles_[current].velocity.x,
                               info_for_particles_[current].velocity.y);
      info_for_particles_[current].velocity = new_velocity;
    }


    vec2 updated_position = info_for_particles_[current].position +
        info_for_particles_[current].velocity;
    info_for_particles_[current].position = (KeepWithinContainer(updated_position, info_for_particles_[current].radius));
  }
}

bool IdealGas::HasCollidedWithWall(const Person& current_particle,
                                   double wall_boundary,
                                   bool is_horizontal_wall) const {
  double particle_position_component_different = current_particle.position.x;
  if (is_horizontal_wall) {
    particle_position_component_different = current_particle.position.y;
  }

  // Checks if the particle and wall are touching
  if (abs(particle_position_component_different - wall_boundary) <= current_particle.radius) {
    vec2 wall_position = vec2(wall_boundary, current_particle.position.y);
    if (is_horizontal_wall) {
      wall_position = vec2(current_particle.position.x, wall_boundary);
    }

    // Checks if the particle is moving towards the wall
    if (IsMovingTowardsWall(current_particle, wall_position)) {
      return true;
    }
  }
  return false;
}

bool IdealGas::IsMovingTowardsWall(const Person& current_particle,
                                   const vec2& wall_position) const {
  vec2 velocity_difference = current_particle.velocity;
  vec2 position_difference = current_particle.position - wall_position;

  if (dot(velocity_difference, position_difference) < 0) {
    return true;
  }
  return false;
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