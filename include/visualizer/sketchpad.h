#pragma once

#include "cinder/gl/gl.h"
#include "core/histogram.h"
#include "core/ideal_gas.h"

using disease::IdealGas;

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

  const vector<IdealGas::Person>& GetParticlesInfo();

  double GetTopMargin();

 private:
  // Container info
  const double kTopContainerMargin = 50;
  const double kLeftContainerMargin = 25;
  const double kContainerHeight = 580;
  const double kContainerWidth = 550;

  IdealGas ideal_gas;
  //Histogram histogram_;
  vector<IdealGas::Person> particles_info;
};

}  // namespace visualizer

}  // namespace disease
