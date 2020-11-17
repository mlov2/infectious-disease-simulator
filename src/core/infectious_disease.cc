#include "core/infectious_disease.h"

namespace disease {

Disease::Disease(double left_margin, double top_margin,
                 double container_height, double container_width,
                 bool should_create_population) {
  left_wall_ = left_margin;
  top_wall_ = top_margin;
  bottom_wall_ = top_wall_ + container_height;
  right_wall_ = left_wall_ + container_width;

  if (should_create_population) {
    // Add people to population
    for (size_t i = 0; i < kPopulationSize; i++) {
      population_.push_back(CreatePerson());
    }
    population_.push_back(CreatePatientZero());
  }
}

void Disease::SetPopulation(const vector<Disease::Person>& population_to_set_to) {
  population_ = population_to_set_to;
}

const vector<Disease::Person>& Disease::GetPopulation() {
  return population_;
}

Disease::Person Disease::CreatePerson() {
  Disease::Person new_person;

  new_person.radius = kRadius;

  int x_position = rand() % int(right_wall_) + int(left_wall_);
  int y_position = rand() % int(bottom_wall_) + int(top_wall_);
  new_person.position = vec2(x_position, y_position);

  new_person.velocity = GenerateVelocity();
  new_person.status = Status::kSusceptible;
  new_person.color = vec3(0,0,1);
  new_person.continuous_exposure_time = 0;
  new_person.time_infected = 0;

  return new_person;
}

vec2 Disease::GenerateVelocity() {
  int x_velocity = rand() % kAddToMinVelComponent + kMinVelComponent;
  int y_velocity = rand() % kAddToMinVelComponent + kMinVelComponent;
  while (x_velocity == 0 || y_velocity == 0) {
    x_velocity = rand() % kAddToMinVelComponent + kMinVelComponent;
    y_velocity = rand() % kAddToMinVelComponent + kMinVelComponent;
  }
  int scale_x_velocity_numerator = rand() % kMaxScaleForVelNumerator + 1;
  int scale_y_velocity_numerator = rand() % kMaxScaleForVelNumerator + 1;

  return vec2(double(x_velocity) * double(scale_x_velocity_numerator) / kScaleDenominatorVel,
              double(y_velocity) * double(scale_y_velocity_numerator) / kScaleDenominatorVel);
}

Disease::Person Disease::CreatePatientZero() {
  Disease::Person infected_person = CreatePerson();

  infected_person.status = Status::kInfectious;
  infected_person.color = vec3(1,0,0);

  return infected_person;
}

void Disease::UpdateParticles() {
  for (size_t current = 0; current < population_.size(); current++) {
    // Check for wall collisions
    CheckForWallCollisions(current);

    vec2 updated_position = population_[current].position +
        population_[current].velocity;
    population_[current].position = (KeepWithinContainer(updated_position, population_[current].radius));

  }
}

void Disease::CheckForWallCollisions(size_t current) {
  if (HasCollidedWithWall(population_[current],
                          top_wall_, true) ||
      HasCollidedWithWall(population_[current],
                          bottom_wall_, true)) {
    vec2 new_velocity = vec2(population_[current].velocity.x,
                             -population_[current].velocity.y);
    population_[current].velocity = new_velocity;
  }

  if (HasCollidedWithWall(population_[current],
                          left_wall_, false) ||
      HasCollidedWithWall(population_[current],
                          right_wall_, false)) {
    vec2 new_velocity = vec2(-population_[current].velocity.x,
                             population_[current].velocity.y);
    population_[current].velocity = new_velocity;
  }
}

bool Disease::HasCollidedWithWall(const Person& current_particle,
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

bool Disease::IsMovingTowardsWall(const Person& current_particle,
                                   const vec2& wall_position) const {
  vec2 velocity_difference = current_particle.velocity;
  vec2 position_difference = current_particle.position - wall_position;

  if (dot(velocity_difference, position_difference) < 0) {
    return true;
  }
  return false;
}

vec2 Disease::KeepWithinContainer(const vec2& updated_position, double current_particle_radius) {
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