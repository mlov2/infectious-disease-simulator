#pragma once

#include "cinder/gl/gl.h"
#include "core/histogram.h"
#include "core/infectious_disease.h"

using disease::Disease;

namespace disease {

enum class FeatureChangeKey {
  kQuarantine,       // 0
  kExposureTime,     // 1
  kInfectedTime,     // 2
  kSocialDistance,   // 3
  kInfectionRadius,  // 4
  kCentralLocation,  // 5
};

namespace visualizer {

/*
 * A simulator which will be displayed in the Cinder application.
 */
class Simulator {
 public:
  /*
   * Creates a simulator.
   */
  Simulator();

  /*
   * Updates particles' info.
   */
  void Update();

  /*
   * Displays the current state of the sketchpad in the Cinder application.
   */
  void Draw() const;

  /*
   * Deletes all the people in the population.
   */
  void Clear();

  /*
   * Creates the population.
   */
  void CreatePopulation();

  /*
   * Changes the specified feature.
   */
  void ChangeFeature(FeatureChangeKey feature_to_change);

  /*
   * Changes the value of the feature that is currently being changed.
   *
   * @param is_key_up A bool representing if the up key was pressed
   */
  void ChangeFeatureValue(bool is_key_up);

  const vector<Disease::Person>& GetParticlesInfo();
  size_t GetTimePassed() const;
  FeatureChangeKey GetFeatureCurrentlyChanging() const;
  Disease GetDiseaseClass() const;

  /*
   * Changes the feature being changed from enum class type to a string.
   *
   * @return A string that holds the feature name
   */
  std::string GetFeatureBeingChanged() const;

  double GetTopMargin();

 private:
  // Container info
  const double kTopContainerMargin = 50;
  const double kLeftContainerMargin = 25;
  const double kContainerHeight = 580;
  const double kContainerWidth = 550;
  //const size_t kUpdatesPerSecond = 50;

  // Quarantine box info
  const double kSpacesFromContainer = 20;
  const double kQuarantineBoxWidth = 675;
  double quarantine_box_top_left_x_;
  double quarantine_box_top_left_y_;
  double quarantine_box_bottom_right_x_;
  double quarantine_box_bottom_right_y_;

  const double kInitialYLocForFeatureStats = 100;
  const double kInitialYLocForGeneralInstructionsMultiplier = 3;

  Disease disease_;
  Histogram histogram_;
  vector<Disease::Person> particles_info;
  size_t time_passed_;
  FeatureChangeKey feature_currently_being_changed_;
  const size_t kIncrementOrDecrementBy = 5;

  /*
   * Draws the container.
   */
  void DrawContainer() const;

  /*
   * Draws the particles.
   */
  void DrawParticles() const;

  /*
   * Draws the quarantine box.
   */
  void DrawQuarantineBox() const;

  /*
   * Draws the instructions on how to change the value of features.
   */
  void DrawFeatureChangeInstructions() const;

  /*
   * Draws the feature stat labels to display to user.
   *
   * - quarantine
   * - exposed time
   * - infected time
   * - amount of social distance
   * - radius of infection
   */
  void DrawFeatureLabels() const;

  /*
   * Draws a message that will be displayed to the user if the feature
   * they are currently changes reaches its min or max value.
   *
   * @param y_location A double representing the y_coordinate of the
   *     location the string will be drawn
   */
  void DrawConstraintsMessage(double y_location) const;
};

}  // namespace visualizer

}  // namespace disease
