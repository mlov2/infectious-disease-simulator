#pragma once

#include "cinder/gl/gl.h"
#include "core/histogram.h"
#include "core/infectious_disease.h"

using disease::Disease;

namespace disease {

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

  Disease disease_;
  Histogram histogram_;
  vector<Disease::Person> particles_info;
  size_t time_passed_;

  /*
   * Draws the container.
   */
  void DrawContainer() const;

  /*
   * Draws the particles.
   */
  void DrawParticles() const;
};

}  // namespace visualizer

}  // namespace disease
