#include "core/infectious_disease.h"

namespace disease {

Disease::Disease(double left_margin, double top_margin,
                 double container_height, double container_width) {
  left_wall_ = left_margin;
  top_wall_ = top_margin;
  bottom_wall_ = top_wall_ + container_height;
  right_wall_ = left_wall_ + container_width;

  exposure_time_to_be_infected_ = kExposureTimeToBeInfected;
  infected_time_to_be_removed_ = kInfectedTimeToBeRemoved;
}

Disease::Disease(double left_margin, double top_margin,
                 double container_height, double container_width,
                 size_t exposure_time, size_t infected_time) {
  left_wall_ = left_margin;
  top_wall_ = top_margin;
  bottom_wall_ = top_wall_ + container_height;
  right_wall_ = left_wall_ + container_width;

  exposure_time_to_be_infected_ = exposure_time;
  infected_time_to_be_removed_ = infected_time;
}

void Disease::SetPopulation(const vector<Disease::Person>& population_to_set_to) {
  population_ = population_to_set_to;
}

const vector<Disease::Person>& Disease::GetPopulation() {
  return population_;
}

void Disease::CreatePopulation() {
  // Add people to population if there isn't anybody in the population
  if (population_.size() == 0) {
    for (size_t i = 0; i < kSusceptiblePopulation; i++) {
      population_.push_back(CreatePerson());
    }
    population_.push_back(CreatePatientZero());
  }
}

Disease::Person Disease::CreatePerson() {
  Disease::Person new_person;

  new_person.radius = kRadius;

  new_person.position = vec2(ci::randFloat(left_wall_, right_wall_),
                             ci::randFloat(top_wall_, bottom_wall_));

  new_person.velocity = vec2(ci::randFloat(-1,1), ci::randFloat(-1,1));
  new_person.status = Status::kSusceptible;
  new_person.color = vec3(0,0,1);
  new_person.continuous_exposure_time = 0;
  new_person.time_infected = 0;
  new_person.has_been_exposed_in_frame = false;

  return new_person;
}

Disease::Person Disease::CreatePatientZero() {
  Disease::Person infected_person = CreatePerson();

  infected_person.status = Status::kInfectious;
  infected_person.color = vec3(1,0,0);

  return infected_person;
}

void Disease::UpdateParticles() {
  ResetExposureInFrame();

  for (size_t current = 0; current < population_.size(); current++) {
    // Update Status
    population_[current] = UpdatePersonStatus(population_[current], current);

    // Check for wall collisions
    CheckForWallCollisions(current);

    vec2 updated_position = population_[current].position +
        population_[current].velocity;
    population_[current].position = (KeepWithinContainer(updated_position, population_[current].radius));
  }
}

void Disease::ResetExposureInFrame() {
  for (size_t current = 0; current < population_.size(); current++) {
    population_[current].has_been_exposed_in_frame = false;
  }
}

Disease::Person Disease::UpdatePersonStatus(const Person& current_person, size_t current_index) {
  Person patient = current_person;

  if (patient.status == Status::kSusceptible) {
    // Update the susceptible person's exposure time
    patient = UpdateExposureTime(current_person, current_index);

    if (patient.continuous_exposure_time == exposure_time_to_be_infected_) {
      patient.status = Status::kInfectious;
      patient.color = vec3(1, 0, 0);
      patient.continuous_exposure_time = 0;
    }
  } else if (patient.status == Status::kInfectious) {
    ExposeOthers(current_person, current_index);

    patient.time_infected++;
    if (patient.time_infected == infected_time_to_be_removed_) {
      patient.status = Status::kRemoved;
      patient.color = vec3(0.5, 0.5, 0.5);
      patient.time_infected = 0;
    }
  }

  return patient;
}

Disease::Person Disease::UpdateExposureTime(const Disease::Person& current_person, size_t current_index) {
  Disease::Person patient = current_person;

  // Check if the current particle has already been
  // infected by a particle that's been updated already
  if (patient.has_been_exposed_in_frame) {
    patient.continuous_exposure_time++;
  } else if (WithinInfectionRadiusOfOthers(patient, current_index)) {
    // Check if the current particle will get
    // infected by particles that aren't updated yet
    patient.continuous_exposure_time++;
  } else {
    patient.continuous_exposure_time = 0;
  }

  return patient;
}

bool Disease::WithinInfectionRadiusOfOthers(const Disease::Person& current_person, size_t current_index) const {
  for (size_t other = current_index + 1; other < population_.size(); other++) {
    Disease::Person other_person = population_[other];

    if (other_person.status == Status::kInfectious) {
      if (WithinOneInfectionRadius(current_person, other_person)) {
        return true;
      }
    }
  }

  return false;
}

void Disease::ExposeOthers(const Disease::Person& current_person, size_t current_index) {
  for (size_t other = current_index + 1; other < population_.size(); other++) {
    if (population_[other].status == Status::kSusceptible) {
      if (WithinOneInfectionRadius(current_person, population_[other])) {
        population_[other].has_been_exposed_in_frame = true;
      }
    }
  }
}

bool Disease::WithinOneInfectionRadius(const Disease::Person& current_person, const Disease::Person& other_person) const {
  // Calculate distance between center of particles
  double position_x_val_difference = current_person.position.x - other_person.position.x;
  double position_y_val_difference = current_person.position.y - other_person.position.y;
  double sum_of_squared_differences = (position_x_val_difference * position_x_val_difference) +
                                      (position_y_val_difference * position_y_val_difference);
  double distance_between_centers = sqrt(sum_of_squared_differences);

  return (distance_between_centers <= (current_person.radius + other_person.radius + kInfectionRadius));
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

bool Disease::HasCollidedWithWall(const Disease::Person& current_particle,
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

bool Disease::IsMovingTowardsWall(const Disease::Person& current_particle,
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