#pragma once

#include "cinder/gl/gl.h"
#include "core/histogram.h"
#include "core/infectious_disease.h"

using disease::Disease;

namespace disease {

enum class FeatureChangeKey {
  kQuarantine,       // 1
  kExposureTime,     // 2
  kInfectedTime,     // 3
  kSocialDistance,   // 4
  kInfectionRadius,  // 5
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
  void ChangeFeatureValue(bool is_key_up);  // TODO: Write tests for this function

  const vector<Disease::Person>& GetParticlesInfo();

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
};

}  // namespace visualizer

}  // namespace disease
