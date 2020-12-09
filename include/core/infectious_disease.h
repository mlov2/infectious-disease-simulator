#pragma once

#include "cinder/gl/gl.h"
#include "cinder/Rand.h"
#include <cmath>
#include <string>
#include <vector>

using glm::vec2;
using glm::vec3;
using std::map;
using std::string;
using std::vector;

namespace disease {

/*
 * Represents the health status of a person.
 */
enum class Status {
  kSusceptible,
  kSymptomatic,  // person is infectious with this status
  kAsymptomatic,  // person is infectious with this status
  kRemoved,
};

/*
 * Holds info on people in the population and their changes
 * in health status and movement.
 */
class Disease {
 public:
  /*
   * Holds the info pertaining to a single person in the population.
   *
   * radius: the radius of the particle representing the person
   * position: the position of the particle representing the person
   * velocity: the velocity of the particle representing the person
   * status: the health status of the person
   * color: the color of the particle representing the person
   * continuous_exposure_time: the time the person has been exposed to an
   *     infected person continuously (used when status is susceptible)
   * time_infected: the total amount of time the person has been infected
   *     (used when status is infectious)
   * has_been_exposed_in_frame: represents if the person (if status is
   *     susceptible) has been exposed to an infected person within the
   *     current frame
   * is_quarantined: represents if the person is in quarantine
   * is_social_distancing: represents if the person is social distancing
   * positions_of_people_in_bubble: stores the count of people within social
   *     distancing bubble (i.e. above, below, right, left)
   * is_going_to_central_location: represents if the person is going to the
   *     central location
   * at_central_location: represents if the person is at the central location
   */
  struct Person {
      double radius;
      vec2 position;
      vec2 velocity;
      Status status;
      vec3 color;
      size_t continuous_exposure_time;
      size_t time_infected;
      bool has_been_exposed_in_frame;
      bool is_quarantined;
      bool is_social_distancing;
      map<string, size_t> positions_of_people_in_bubble;
      bool is_going_to_central_location;
      bool is_at_central_location;
  };

  Disease() = default;
  Disease(double left_margin, double top_margin,
          double container_height, double container_width,
          const vec2& quarantine_top_left, const vec2& quarantine_bottom_right,
          const vec2& location_top_left, const vec2& location_bottom_right);
  Disease(double left_margin, double top_margin,
          double container_height, double container_width,
          const vec2& quarantine_top_left, const vec2& quarantine_bottom_right,
          size_t exposure_time, size_t infected_time,
          bool is_infection_determination_random, bool is_symptomatic,
          bool is_new_distancing_velocity_random);  // used for testing

  void SetPopulation(const vector<Person>& population_to_set_to);
  void SetShouldQuarantine(bool should_quarantine);
  void SetExposureTime(size_t exposure_time);
  void SetInfectedTime(size_t infected_time);
  void SetPercentPerformingSocialDistance(size_t percent_performing_social_distance);
  void SetRadiusOfInfection(size_t radius_of_infection);
  void SetHaveCentralLocation(bool have_central_location);

  const vector<Person>& GetPopulation();
  bool GetShouldQuarantineValue() const;
  size_t GetExposureTime() const;
  size_t GetInfectedTime() const;
  size_t GetPercentPerformingSocialDistance() const;
  size_t GetRadiusOfInfection() const;
  bool GetHaveCentralLocation() const;

  size_t GetMinimumExposureTime() const;
  size_t GetMaximumExposureTime() const;
  size_t GetMinimumInfectedTime() const;
  size_t GetMaximumInfectedTime() const;
  size_t GetAmountOfSocialDistance() const;
  size_t GetMinimumSocialDistancePercentage() const;
  size_t GetMaximumSocialDistancePercentage() const;
  size_t GetMinimumInfectionRadius() const;
  size_t GetMaximumInfectionRadius() const;

  /*
   * Create a population where all but one is susceptible to the disease (the
   * single person is patient zero).
   */
  void CreatePopulation();

  /*
   * Updates the information of all particles in the container,
   * specifically the velocity, speed, and position.
   */
  void UpdateParticles();

 private:
  // ================
  // Person constants
  // ================
  constexpr static double kRadius = 10;

  // ==================
  // Stats as constants
  // ==================
  constexpr static double kOneHundred = 100;
  const static size_t kSusceptiblePopulation = 200;
  const static size_t kExposureTimeToBeInfected = 25;
  const static size_t kMinimumExposureTime = 5;
  const static size_t kMaximumExposureTime = 50;
  const static size_t kInfectedTimeToBeRemoved = 500;
  const static size_t kMinimumInfectedTime = 250;
  const static size_t kMaximumInfectedTime = 750;
  const static size_t kAmountOfSocialDistance = 5;
  const static size_t kMinimumSocialDistancePercentage = 0;
  const static size_t kMaximumSocialDistancePercentage = 100;
  const static size_t kInfectionRadius = 10;
  const static size_t kMinimumInfectionRadius = 5;
  const static size_t kMaximumInfectionRadius = 45;
  const static size_t kTimeToBeDetectedForQuarantine = 70;
  constexpr static double kProbabilityOfBeingAsymptomatic = 0.2;
  constexpr static double kProbabilityOfBeingSymptomatic = 0.8;

  // ==================
  // Stats as variables
  // ==================
  bool should_quarantine_;
  size_t exposure_time_to_be_infected_;
  size_t infected_time_to_be_removed_;
  size_t percent_performing_social_distance_;
  size_t radius_of_infection_;
  bool have_central_location_;

  bool is_infection_determination_random_;
  bool is_symptomatic_;
  bool is_new_distancing_velocity_random_;

  // ===================
  // Container variables
  // ===================
  double left_wall_;
  double top_wall_;
  double bottom_wall_;
  double right_wall_;

  // ========================
  // Quarantine box variables
  // ========================
  double quarantine_left_wall_;
  double quarantine_top_wall_;
  double quarantine_bottom_wall_;
  double quarantine_right_wall_;

  // ==========================
  // Central location variables
  // ==========================
  double location_left_wall_;
  double location_right_wall_;
  double location_top_wall_;
  double location_bottom_wall_;
  constexpr static double kProbabilityOfLeavingLocation = 0.005;
  constexpr static double kProbabilityOfGoingToLocation = 0.0005;

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
   * Creates a person who is infected.
   *
   * @return The person with their info initialized as an infected person
   */
  Person CreatePatientZero();

  /*
   * Resets each person's has_been_exposed_in_frame status to false and
   * clears positions_of_people_in_bubble.
   */
  void ResetFrame();

  /*
   * Updates the person's status based on the current stats for the person (i.e.
   * exposure time if currently susceptible or infected time if currently infected).
   *
   * @param current_person The current person's status to update
   * @param current_index The index of the current person in the population vector
   * @return The person with their status updated
   */
  Person UpdatePersonStatus(const Person& current_person, size_t current_index);

  /*
   * Updates the exposure time for a susceptible person.
   *
   * @param current_person The current person's exposure time to update
   * @param current_index The index of the current person in the population vector
   * @return The person with their exposure time updated
   */
  Person UpdateExposureTime(const Person& current_person, size_t current_index);

  /*
   * Checks if the current person is within the radius of infected people.
   *
   * @param current_person The current person to check
   * @param current_index The index of the current person in the population vector
   * @return A bool representing if the current person is within the radius
   *     of an infected person
   */
  bool WithinInfectionRadiusOfOthers(const Person& current_person, size_t current_index) const;

  /*
   * Determines whether the susceptible person becomes an infected person who is now
   * symptomatic or asymptomatic.
   *
   * @param current_person The current person to determine the infectious status for
   * @return The person with the chosen infection status
   */
  Person DetermineInfectionStatus(const Person& current_person) const;

  /*
   * Makes the current infected person expose the disease to those who are susceptible.
   *
   * @param current_person The current person who is infected
   * @param current_index The index of the current person in the population vector
   */
  void ExposeOthers(const Person& current_person, size_t current_index);

  /*
   * Checks if the current person is within the radius of the specified infected person.
   *
   * @param current_person The current person to check
   * @param other_person The person to check if the current person is within their infection radius
   * @return A bool representing if the current person is within the radius
   *     of an infected person
   */
  bool WithinOneInfectionRadius(const Person& current_person, const Person& other_person) const;

  /*
   * Checks for wall collisions with the current particle.
   *
   * @param current The index of the current particle
   * @param left_bound The left bound of the container
   * @param top_bound The top bound of the container
   * @param right_bound The right bound of the container
   * @param bottom_bound The bottom bound of the container
   */
  void CheckForWallCollisions(size_t current, double left_bound, double top_bound,
                              double right_bound, double bottom_bound,
                              bool is_outside_collision);

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
  bool HasCollidedWithWall(const Person& current_particle, double wall_boundary,
                           bool is_horizontal_wall, bool is_lower_bound,
                           double perpendicular_lower_bound,
                           double perpendicular_upper_bound,
                           bool is_outside_collision) const;

  /*
   * Checks if the current particle is moving towards a wall from the outside.
   *
   * @param current_particle The current particle to check
   * @param wall_position The position of the wall where the current particle
   *      would be touching
   * @return A bool representing if the current particle is moving towards
   *     the wall
   */
  bool IsMovingTowardsWallOnOutside(const Person& current_particle, const vec2& wall_position,
                                    bool is_lower_bound, bool is_horizontal,
                                    double perpendicular_lower_bound,
                                    double perpendicular_upper_bound, bool is_outside_collision,
                                    const vec2& velocity_difference) const;

  /*
   * Checks if the current particle is moving towards a wall.
   *
   * @param current_particle The current particle to check
   * @param wall_position The position of the wall where the current particle
   *      would be touching
   * @return A bool representing if the current particle is moving towards
   *     the wall
   */
  bool IsMovingTowardsWall(const Person& current_particle, const vec2& wall_position,
                           bool is_lower_bound, bool is_horizontal,
                           double perpendicular_lower_bound,
                           double perpendicular_upper_bound, bool is_outside_collision) const;

  /*
   * Determines if the current person should be quarantined based on their statistics.
   *
   * @param current_person The current person to check
   * @return A bool representing if the current person should be quarantined
   */
  bool ShouldBeQuarantined(const Person& current_person) const;

  /*
   * Moves the current person to the quarantine box.
   *
   * @param current_person The current person to put in quarantine
   * @return A Person representing the current person with updated info
   */
  Person QuarantinePerson(const Person& current_person);

  /*
   * Updates the current person's position.
   *
   * @param current_index The index of the current person in the population vector
   */
  void UpdatePosition(size_t current_index);

  /*
   * Determines how the current person, if performing social distancing, will social
   * distance.
   *
   * @param current_index The index of the current person in the population vector
   */
  void SocialDistance(size_t current_index);

  /*
   * Determines whether a person is within the current person's social distancing bubble.
   *
   * @param current_person The current Person who is performing social distancing
   * @param other_person The Person to check
   * @return A bool representing if the other person is within the current person's social
   *     distancing bubble
   */
  bool WithinDistancingBubble(const Disease::Person& current_person, const Disease::Person& other_person) const;



  /*
   * Saves the other person's position relative to the current person's.
   *
   * @param current_index The index of the current person in the population vector
   * @param other_index The index of the other person in the population vector
   */
  void SavePositionRelativeToCurrentPerson(size_t current_index, size_t other_index);

  /*
   * Updates the current person's velocity based on who's within their
   * social distancing bubble.
   *
   * @param current_index The index of the current person in the population vector
   */
  void UpdateVelocity(size_t current_index);

  /*
   * Adjusts the updated position so that the particle will still be within the
   * container walls when the position is updated.
   *
   * @param updated_position A vec2 of the current particle's updated position
   * @param current_particle_radius A double of the current particle's radius
   * @param left_bound The left bound of the container
   * @param top_bound The top bound of the container
   * @param right_bound The right bound of the container
   * @param bottom_bound The bottom bound of the container
   * @return A vec2 representing the updated_position within the container bounds
   */
  vec2 KeepWithinContainer(const vec2& updated_position, double current_particle_radius,
                           double left_bound, double top_bound,
                           double right_bound, double bottom_bound);
};

}  // namespace disease