#include "core/infectious_disease.h"

namespace disease {

Disease::Disease(double left_margin, double top_margin,
                 double container_height, double container_width,
                 const vec2& quarantine_top_left, const vec2& quarantine_bottom_right) {
  left_wall_ = left_margin;
  top_wall_ = top_margin;
  bottom_wall_ = top_wall_ + container_height;
  right_wall_ = left_wall_ + container_width;

  quarantine_left_wall_ = quarantine_top_left.x;
  quarantine_top_wall_ = quarantine_top_left.y;
  quarantine_right_wall_ = quarantine_bottom_right.x;
  quarantine_bottom_wall_ = quarantine_bottom_right.y;

  should_quarantine_ = true;
  exposure_time_to_be_infected_ = kExposureTimeToBeInfected;
  infected_time_to_be_removed_ = kInfectedTimeToBeRemoved;
  percent_performing_social_distance_ = 0;
  radius_of_infection_ = kInfectionRadius;
  is_infection_determination_random_ = true;
  is_symptomatic_ = true;
}

Disease::Disease(double left_margin, double top_margin,
                 double container_height, double container_width,
                 const vec2& quarantine_top_left, const vec2& quarantine_bottom_right,
                 size_t exposure_time, size_t infected_time,
                 bool is_infection_determination_random, bool is_symptomatic) {
  left_wall_ = left_margin;
  top_wall_ = top_margin;
  bottom_wall_ = top_wall_ + container_height;
  right_wall_ = left_wall_ + container_width;

  quarantine_left_wall_ = quarantine_top_left.x;
  quarantine_top_wall_ = quarantine_top_left.y;
  quarantine_right_wall_ = quarantine_bottom_right.x;
  quarantine_bottom_wall_ = quarantine_bottom_right.y;

  should_quarantine_ = true;
  exposure_time_to_be_infected_ = exposure_time;
  infected_time_to_be_removed_ = infected_time;
  percent_performing_social_distance_ = 0;
  radius_of_infection_ = kInfectionRadius;
  is_infection_determination_random_ = is_infection_determination_random;
  is_symptomatic_ = is_symptomatic;
}

void Disease::SetPopulation(const vector<Disease::Person>& population_to_set_to) {
  population_ = population_to_set_to;
}

void Disease::SetShouldQuarantine(bool should_quarantine) {
  should_quarantine_ = should_quarantine;
}
void Disease::SetExposureTime(size_t exposure_time) {
  exposure_time_to_be_infected_ = exposure_time;
}

void Disease::SetInfectedTime(size_t infected_time) {
  infected_time_to_be_removed_ = infected_time;
}

void Disease::SetPercentPerformingSocialDistance(size_t percent_performing_social_distance) {
  percent_performing_social_distance_ = percent_performing_social_distance;
}

void Disease::SetRadiusOfInfection(size_t radius_of_infection) {
  radius_of_infection_ = radius_of_infection;
}

const vector<Disease::Person>& Disease::GetPopulation() {
  return population_;
}

bool Disease::GetShouldQuarantineValue() const {
  return should_quarantine_;
}

size_t Disease::GetExposureTime() const {
  return exposure_time_to_be_infected_;
}

size_t Disease::GetInfectedTime() const {
  return infected_time_to_be_removed_;
}

size_t Disease::GetPercentPerformingSocialDistance() const {
  return percent_performing_social_distance_;
}

size_t Disease::GetRadiusOfInfection() const {
  return radius_of_infection_;
}

size_t Disease::GetMinimumExposureTime() const {
  return kMinimumExposureTime;
}

size_t Disease::GetMaximumExposureTime() const {
  return kMaximumExposureTime;
}

size_t Disease::GetMinimumInfectedTime() const {
  return kMinimumInfectedTime;
}

size_t Disease::GetMaximumInfectedTime() const {
  return kMaximumInfectedTime;
}

size_t Disease::GetMinimumSocialDistancePercentage() const {
  return kMinimumSocialDistancePercentage;
}

size_t Disease::GetMaximumSocialDistancePercentage() const {
  return kMaximumSocialDistancePercentage;
}

size_t Disease::GetMinimumInfectionRadius() const {
  return kMinimumInfectionRadius;
}

size_t Disease::GetMaximumInfectionRadius() const {
  return kMaximumInfectionRadius;
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
  new_person.is_quarantined = false;

  return new_person;
}

Disease::Person Disease::CreatePatientZero() {
  Disease::Person infected_person = CreatePerson();

  infected_person.status = Status::kSymptomatic;
  infected_person.color = vec3(1,0,0);

  return infected_person;
}

void Disease::UpdateParticles() {
  ResetExposureInFrame();

  for (size_t current = 0; current < population_.size(); current++) {
    // Update Status
    population_[current] = UpdatePersonStatus(population_[current], current);

    // Check for wall collisions
    if (population_[current].is_quarantined) {
      if (should_quarantine_) {
        CheckForWallCollisions(current, quarantine_left_wall_, quarantine_top_wall_,
                               quarantine_right_wall_, quarantine_bottom_wall_);
      }
    } else {
      CheckForWallCollisions(current, left_wall_, top_wall_, right_wall_, bottom_wall_);
    }

    // Check if the person should be quarantined
    if (ShouldBeQuarantined(population_[current])) {
      if (should_quarantine_) {
        population_[current] = QuarantinePerson(population_[current]);
      }
    } else {
      // Update position
      UpdatePosition(current);
    }
  }
}

void Disease::ResetExposureInFrame() {
  for (size_t current = 0; current < population_.size(); current++) {
    population_[current].has_been_exposed_in_frame = false;
  }
}

void Disease::UpdatePosition(size_t current_index) {
  vec2 updated_position = population_[current_index].position +
                          population_[current_index].velocity;

  if (population_[current_index].is_quarantined) {
    if (should_quarantine_) {
      population_[current_index].position =
          KeepWithinContainer(updated_position, population_[current_index].radius,
                              quarantine_left_wall_, quarantine_top_wall_,
                              quarantine_right_wall_, quarantine_bottom_wall_);
    }
  } else {
    population_[current_index].position =
        KeepWithinContainer(updated_position, population_[current_index].radius,
                            left_wall_, top_wall_, right_wall_, bottom_wall_);
  }
}

Disease::Person Disease::UpdatePersonStatus(const Person& current_person, size_t current_index) {
  Person patient = current_person;

  if (patient.status == Status::kSusceptible) {
    // Update the susceptible person's exposure time
    patient = UpdateExposureTime(current_person, current_index);

    if (patient.continuous_exposure_time == exposure_time_to_be_infected_) {
      patient = DetermineInfectionStatus(current_person);
      patient.continuous_exposure_time = 0;
    }
  } else if (patient.status == Status::kSymptomatic || patient.status == Status::kAsymptomatic) {
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

bool Disease::WithinInfectionRadiusOfOthers(const Disease::Person& current_person,
                                            size_t current_index) const {
  for (size_t other = current_index + 1; other < population_.size(); other++) {
    Disease::Person other_person = population_[other];

    if (other_person.status == Status::kSymptomatic ||
        other_person.status == Status::kAsymptomatic) {
      if (WithinOneInfectionRadius(current_person, other_person)) {
        return true;
      }
    }
  }

  return false;
}

Disease::Person Disease::DetermineInfectionStatus(const Person& current_person) const {
  Person patient = current_person;

  double value_to_determine_infection_status = ci::randFloat(0,1);
  if (!is_infection_determination_random_) {
    if (is_symptomatic_) {
      value_to_determine_infection_status = kProbabilityOfBeingSymptomatic;
    } else {
      value_to_determine_infection_status = kProbabilityOfBeingAsymptomatic;
    }
  }

  if (value_to_determine_infection_status <= kProbabilityOfBeingAsymptomatic) {
    patient.status = Status::kAsymptomatic;
    patient.color = vec3(1, 1, 0);
  } else {
    patient.status = Status::kSymptomatic;
    patient.color = vec3(1, 0, 0);
  }

  return patient;
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

void Disease::CheckForWallCollisions(size_t current, double left_bound, double top_bound,
                                     double right_bound, double bottom_bound) {
  if (HasCollidedWithWall(population_[current],
                          top_bound, true) ||
      HasCollidedWithWall(population_[current],
                          bottom_bound, true)) {
    vec2 new_velocity = vec2(population_[current].velocity.x,
                             -population_[current].velocity.y);
    population_[current].velocity = new_velocity;
  }

  if (HasCollidedWithWall(population_[current],
                          left_bound, false) ||
      HasCollidedWithWall(population_[current],
                          right_bound, false)) {
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

bool Disease::ShouldBeQuarantined(const Disease::Person& current_person) const {
  return (current_person.status == Status::kSymptomatic &&
      current_person.time_infected >= kTimeToBeDetectedForQuarantine &&
      !current_person.is_quarantined && should_quarantine_);
}

Disease::Person Disease::QuarantinePerson(const Disease::Person& current_person) {
  Person infected_person = current_person;

  infected_person.position = vec2(ci::randFloat(quarantine_left_wall_, quarantine_right_wall_),
                             ci::randFloat(quarantine_top_wall_, quarantine_bottom_wall_));
  infected_person.is_quarantined = true;

  return infected_person;
}

vec2 Disease::KeepWithinContainer(const vec2& updated_position, double current_particle_radius,
                                  double left_bound, double top_bound,
                                  double right_bound, double bottom_bound) {
  vec2 updated_position_within_container = updated_position;
  if (updated_position.x + current_particle_radius > right_bound) {
    updated_position_within_container.x = right_bound - current_particle_radius;
  } else if (updated_position.x - current_particle_radius < left_bound) {
    updated_position_within_container.x = left_bound + current_particle_radius;
  }

  if (updated_position.y + current_particle_radius > bottom_bound) {
    updated_position_within_container.y = bottom_bound - current_particle_radius;
  } else if (updated_position.y - current_particle_radius < top_bound) {
    updated_position_within_container.y = top_bound + current_particle_radius;
  }

  return updated_position_within_container;
}

}  // namespace disease