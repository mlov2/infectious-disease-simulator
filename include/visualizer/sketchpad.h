#pragma once

#include "cinder/gl/gl.h"
#include "core/histogram.h"
#include "core/infectious_disease.h"

using disease::Disease;

namespace disease {

namespace visualizer {

/**
 * A sketchpad which will be displayed in the Cinder application.
 */
class Sketchpad {
 public:
  /**
   * Creates a sketchpad.
   */
  Sketchpad();

  /**
   * Updates particles' info.
   */
  void Update();

  /**
   * Displays the current state of the sketchpad in the Cinder application.
   */
  void Draw() const;

  const vector<Disease::Person>& GetParticlesInfo();

  double GetTopMargin();

 private:
  // Container info
  const double kTopContainerMargin = 50;
  const double kLeftContainerMargin = 25;
  const double kContainerHeight = 580;
  const double kContainerWidth = 550;

  Disease disease;
  //Histogram histogram_;
  vector<Disease::Person> particles_info;
};

}  // namespace visualizer

}  // namespace disease
