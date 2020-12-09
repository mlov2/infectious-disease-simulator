#include "core/infectious_disease.h"

namespace disease {

Disease::Disease(double left_margin, double top_margin,
                 double container_height, double container_width,
                 const vec2& quarantine_top_left, const vec2& quarantine_bottom_right,
                 const vec2& location_top_left, const vec2& location_bottom_right) {
  left_wall_ = left_margin;
  top_wall_ = top_margin;
  bottom_wall_ = top_wall_ + container_height;
  right_wall_ = left_wall_ + container_width;

  quarantine_left_wall_ = quarantine_top_left.x;
  quarantine_top_wall_ = quarantine_top_left.y;
  quarantine_right_wall_ = quarantine_bottom_right.x;
  quarantine_bottom_wall_ = quarantine_bottom_right.y;

  location_left_wall_ = location_top_left.x;
  location_top_wall_ = location_top_left.y;
  location_right_wall_ = location_bottom_right.x;
  location_bottom_wall_ = location_bottom_right.y;

  should_quarantine_ = false;
  exposure_time_to_be_infected_ = kExposureTimeToBeInfected;
  infected_time_to_be_removed_ = kInfectedTimeToBeRemoved;
  percent_performing_social_distance_ = 0;
  radius_of_infection_ = kInfectionRadius;
  have_central_location_ = false;

  is_infection_determination_random_ = true;
  is_symptomatic_ = true;
  is_new_distancing_velocity_random_ = true;
  is_going_to_loc_random_ = true;
  is_leaving_loc_random_ = true;
  is_below_threshold_ = true;
}

Disease::Disease(double left_margin, double top_margin,
                 double container_height, double container_width,
                 const vec2& quarantine_top_left, const vec2& quarantine_bottom_right,
                 const vec2& location_top_left, const vec2& location_bottom_right,
                 size_t exposure_time, size_t infected_time,
                 bool is_infection_determination_random, bool is_symptomatic,
                 bool is_new_distancing_velocity_random, bool is_going_to_loc_random,
                 bool is_leaving_loc_random, bool is_below_threshold) {
  left_wall_ = left_margin;
  top_wall_ = top_margin;
  bottom_wall_ = top_wall_ + container_height;
  right_wall_ = left_wall_ + container_width;

  quarantine_left_wall_ = quarantine_top_left.x;
  quarantine_top_wall_ = quarantine_top_left.y;
  quarantine_right_wall_ = quarantine_bottom_right.x;
  quarantine_bottom_wall_ = quarantine_bottom_right.y;

  location_left_wall_ = location_top_left.x;
  location_top_wall_ = location_top_left.y;
  location_right_wall_ = location_bottom_right.x;
  location_bottom_wall_ = location_bottom_right.y;

  should_quarantine_ = false;
  exposure_time_to_be_infected_ = exposure_time;
  infected_time_to_be_removed_ = infected_time;
  percent_performing_social_distance_ = 0;
  radius_of_infection_ = kInfectionRadius;
  have_central_location_ = false;

  is_infection_determination_random_ = is_infection_determination_random;
  is_symptomatic_ = is_symptomatic;
  is_new_distancing_velocity_random_ = is_new_distancing_velocity_random;
  is_going_to_loc_random_ = is_going_to_loc_random;
  is_leaving_loc_random_ = is_leaving_loc_random;
  is_below_threshold_ = is_below_threshold;
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

void Disease::SetHaveCentralLocation(bool have_central_location) {
  have_central_location_ = have_central_location;
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

bool Disease::GetHaveCentralLocation() const {
  return have_central_location_;
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

size_t Disease::GetAmountOfSocialDistance() const {
  return kAmountOfSocialDistance;
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

    // Determine people social distancing
    double social_distancing_percentage = double(percent_performing_social_distance_) / kOneHundred;
    for (size_t person = 0; person < size_t(social_distancing_percentage * population_.size()); person++) {
      population_[person].is_social_distancing = true;
    }
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
  new_person.is_social_distancing = false;
  new_person.is_going_to_central_location = false;
  new_person.is_at_central_location = false;

  return new_person;
}

Disease::Person Disease::CreatePatientZero() {
  Disease::Person infected_person = CreatePerson();

  infected_person.status = Status::kSymptomatic;
  infected_person.color = vec3(1,0,0);

  return infected_person;
}

void Disease::UpdateParticles() {
  ResetFrame();

  for (size_t current = 0; current < population_.size(); current++) {
    // Update Status
    population_[current] = UpdatePersonStatus(population_[current], current);

    // TODO: Move this chunk of code to a separate function
    if (have_central_location_ && !population_[current].is_quarantined) {
      if (population_[current].is_at_central_location) {
        // Determine if the person leaves
        double probability = ci::randFloat(0,1);
        if (!is_leaving_loc_random_) {
          if (is_below_threshold_) {
            probability = kProbabilityOfLeavingLocation;
          } else {
            probability = 1 - kProbabilityOfLeavingLocation;
          }
        }

        if (probability <= kProbabilityOfLeavingLocation) {
          population_[current].is_at_central_location = false;
          population_[current].is_going_to_central_location = false;
        }
      } else if (population_[current].is_going_to_central_location) {
        // Move person to central location--wouldn't use if I
        // were to visually show the particle moving there
        double new_x_position = ci::randFloat(location_left_wall_, location_right_wall_);
        double new_y_position = ci::randFloat(location_top_wall_, location_bottom_wall_);
        population_[current].position = vec2(new_x_position, new_y_position);

        // Check if person is at location yet
        if (population_[current].position.x >= location_left_wall_ &&
            population_[current].position.x <= location_right_wall_ &&
            population_[current].position.y >= location_top_wall_ &&
            population_[current].position.y <= location_bottom_wall_) {
          population_[current].is_going_to_central_location = false;
          population_[current].is_at_central_location = true;
        }
      } else {
        double probability = ci::randFloat(0,1);
        if (!is_going_to_loc_random_) {
          if (is_below_threshold_) {
            probability = kProbabilityOfGoingToLocation;
          } else {
            probability = 1 - kProbabilityOfGoingToLocation;
          }
        }

        if (probability <= kProbabilityOfGoingToLocation) {
          population_[current].is_going_to_central_location = true;

          // TODO: Visualize the particle moving to the new location instead of
          //  immediately moving it there--put that code here
        }
      }
    }

    // Check for wall collisions
    if (population_[current].is_quarantined) {
      if (should_quarantine_) {
        // Check for collision with quarantine box walls
        CheckForWallCollisions(current, quarantine_left_wall_, quarantine_top_wall_,
                               quarantine_right_wall_, quarantine_bottom_wall_, false);
      }
    } else if (population_[current].is_at_central_location) {
      // Check for collision with inside of central location walls
      if (have_central_location_) {
        CheckForWallCollisions(current, location_left_wall_, location_top_wall_,
                               location_right_wall_, location_bottom_wall_, false);
      }
    } else {
      // Check for collision with container walls
      CheckForWallCollisions(current, left_wall_, top_wall_, right_wall_, bottom_wall_, false);

      if (have_central_location_) {
        // Check for collision with outside of central location walls
        CheckForWallCollisions(current, location_right_wall_, location_bottom_wall_,
                               location_left_wall_, location_top_wall_, true);
      }
    }

    // Check if the person should be quarantined
    if (ShouldBeQuarantined(population_[current])) {
      if (should_quarantine_ && !population_[current].is_going_to_central_location) {
        population_[current] = QuarantinePerson(population_[current]);
        population_[current].is_at_central_location = false;
      }
    } else {
      // Update position
      UpdatePosition(current);
    }
  }
}

void Disease::ResetFrame() {
  for (size_t current = 0; current < population_.size(); current++) {
    population_[current].has_been_exposed_in_frame = false;
    population_[current].positions_of_people_in_bubble.clear();
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
                                     double right_bound, double bottom_bound,
                                     bool is_outside_collision) {
  if (HasCollidedWithWall(population_[current], top_bound, true, true,
                          left_bound, right_bound, is_outside_collision) ||
      HasCollidedWithWall(population_[current], bottom_bound, true, false,
                          left_bound, right_bound, is_outside_collision)) {
    vec2 new_velocity = vec2(population_[current].velocity.x,
                             -population_[current].velocity.y);
    population_[current].velocity = new_velocity;
  }

  if (HasCollidedWithWall(population_[current], left_bound, false, true,
                          top_bound, bottom_bound, is_outside_collision) ||
      HasCollidedWithWall(population_[current], right_bound, false, false,
                          top_bound, bottom_bound, is_outside_collision)) {
    vec2 new_velocity = vec2(-population_[current].velocity.x,
                             population_[current].velocity.y);
    population_[current].velocity = new_velocity;
  }
}

bool Disease::HasCollidedWithWall(const Disease::Person& current_particle,
                                  double wall_boundary,
                                  bool is_horizontal_wall, bool is_lower_bound,
                                  double perpendicular_lower_bound,
                                  double perpendicular_upper_bound,
                                  bool is_outside_collision) const {
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
    if (IsMovingTowardsWall(current_particle, wall_position,
                            is_horizontal_wall, is_lower_bound,
                            perpendicular_lower_bound,
                            perpendicular_upper_bound,
                            is_outside_collision)) {
      return true;
    }
  }
  return false;
}

bool Disease::IsMovingTowardsWall(const Disease::Person& current_particle,
                                  const vec2& wall_position, bool is_horizontal,
                                  bool is_lower_bound, double perpendicular_lower_bound,
                                  double perpendicular_upper_bound, bool is_outside_collision) const {
  vec2 velocity_difference = current_particle.velocity;
  vec2 position_difference = current_particle.position - wall_position;

  // Check if moving towards each other
  if (dot(velocity_difference, position_difference) < 0) {
    if (is_outside_collision && !current_particle.is_going_to_central_location) {
      if (IsMovingTowardsWallOnOutside(current_particle, wall_position,
                                       is_lower_bound, is_horizontal,
                                       perpendicular_lower_bound,
                                       perpendicular_upper_bound,
                                       is_outside_collision,
                                       velocity_difference)) {
        return true;
      }
    } else {
      return true;
    }
  }
  return false;
}

bool Disease::IsMovingTowardsWallOnOutside(const Disease::Person& current_particle, const vec2& wall_position,
                                  bool is_lower_bound, bool is_horizontal,
                                  double perpendicular_lower_bound,
                                  double perpendicular_upper_bound, bool is_outside_collision,
                                  const vec2& velocity_difference) const {
  // Check it's moving towards the proper side
  if (is_lower_bound) {
    if (is_horizontal && velocity_difference.y < 0 &&
        current_particle.position.x > perpendicular_upper_bound &&
        current_particle.position.x < perpendicular_lower_bound) {
      return true;
    } else if (!is_horizontal && velocity_difference.x < 0 &&
               current_particle.position.y > perpendicular_upper_bound &&
               current_particle.position.y < perpendicular_lower_bound) {
      return true;
    }
  } else {
    if (is_horizontal && velocity_difference.y > 0 &&
        current_particle.position.x > perpendicular_upper_bound &&
        current_particle.position.x < perpendicular_lower_bound) {
      return true;
    } else if (!is_horizontal && velocity_difference.x > 0 &&
               current_particle.position.y > perpendicular_upper_bound &&
               current_particle.position.y < perpendicular_lower_bound) {
      return true;
    }
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

void Disease::UpdatePosition(size_t current_index) {
  if (population_[current_index].is_quarantined) {
    if (should_quarantine_) {
      vec2 updated_position = population_[current_index].position +
                              population_[current_index].velocity;
      population_[current_index].position =
          KeepWithinContainer(updated_position, population_[current_index].radius,
                              quarantine_left_wall_, quarantine_top_wall_,
                              quarantine_right_wall_, quarantine_bottom_wall_);
    }
  } else {
    SocialDistance(current_index);

    vec2 updated_position = population_[current_index].position +
                            population_[current_index].velocity;
    if (population_[current_index].is_at_central_location) {
      population_[current_index].position =
          KeepWithinContainer(updated_position, population_[current_index].radius,
                              location_left_wall_, location_top_wall_,
                              location_right_wall_, location_bottom_wall_);
    } else {
      population_[current_index].position =
          KeepWithinContainer(updated_position, population_[current_index].radius,
                              left_wall_, top_wall_, right_wall_, bottom_wall_);
    }
  }
}

void Disease::SocialDistance(size_t current_index) {
  if (population_[current_index].is_social_distancing) {

    // Find all the people who are within the bubble
    for (size_t other_index = current_index + 1; other_index < population_.size(); other_index++) {
      if (WithinDistancingBubble(population_[current_index], population_[other_index])) {
        // Save the position of the person within the bubble
        SavePositionRelativeToCurrentPerson(current_index, other_index);

        // Check if the current particle needs to be added to the other person's save list
        if (population_[other_index].is_social_distancing) {
          SavePositionRelativeToCurrentPerson(other_index, current_index);
        }
      }
    }

    // Determine the direction the person will have to move
    // in to continue practicing social distancing
    UpdateVelocity(current_index);
  }
}

bool Disease::WithinDistancingBubble(const Disease::Person& current_person, const Disease::Person& other_person) const {
  // Calculate distance between center of particles
  double position_x_val_difference = current_person.position.x - other_person.position.x;
  double position_y_val_difference = current_person.position.y - other_person.position.y;
  double sum_of_squared_differences = (position_x_val_difference * position_x_val_difference) +
                                      (position_y_val_difference * position_y_val_difference);
  double distance_between_centers = sqrt(sum_of_squared_differences);

  return (distance_between_centers <= (current_person.radius + other_person.radius + kAmountOfSocialDistance));
}

void Disease::SavePositionRelativeToCurrentPerson(size_t current_index, size_t other_index) {
  if (population_[other_index].position.x > population_[current_index].position.x) {
    population_[current_index].positions_of_people_in_bubble["right"] += 1;
  } else if (population_[other_index].position.x < population_[current_index].position.x) {
    population_[current_index].positions_of_people_in_bubble["left"] += 1;
  }

  if (population_[other_index].position.y > population_[current_index].position.y) {
    population_[current_index].positions_of_people_in_bubble["down"] += 1;
  } else if (population_[other_index].position.y < population_[current_index].position.y) {
    population_[current_index].positions_of_people_in_bubble["up"] += 1;
  }
}

void Disease::UpdateVelocity(size_t current_index) {
  int x_sign = 1;
  int y_sign = 1;

  size_t num_people_above_current_particle = population_[current_index].positions_of_people_in_bubble["up"];
  size_t num_people_below_current_particle = population_[current_index].positions_of_people_in_bubble["down"];
  size_t num_people_left_current_particle = population_[current_index].positions_of_people_in_bubble["left"];
  size_t num_people_right_current_particle = population_[current_index].positions_of_people_in_bubble["right"];

  if (num_people_above_current_particle < num_people_below_current_particle) {
    y_sign = -1;
  }
  if (num_people_left_current_particle < num_people_right_current_particle) {
    x_sign = -1;
  }

  if (num_people_above_current_particle != num_people_below_current_particle) {
    if (is_new_distancing_velocity_random_) {
      population_[current_index].velocity.y = ci::randFloat(0, 1);
    } else {
      population_[current_index].velocity.y = abs(population_[current_index].velocity.y);
    }
  }
  if (num_people_left_current_particle != num_people_right_current_particle) {
    if (is_new_distancing_velocity_random_) {
      population_[current_index].velocity.x = ci::randFloat(0, 1);
    } else {
      population_[current_index].velocity.x = abs(population_[current_index].velocity.x);
    }
  }

  population_[current_index].velocity.x = population_[current_index].velocity.x * x_sign;
  population_[current_index].velocity.y = population_[current_index].velocity.y * y_sign;
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