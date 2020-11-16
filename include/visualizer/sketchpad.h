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

  /**
   * Deletes all of the particles in the sketchpad.
   */
  void Clear();

  /**
   * Creates one particle inside the container.
   *
   * @param mass The mass of the particle to create
   * @param color The color of the particle to create
   */
  void CreateOneParticle(double mass, const string& color);

  const vector<Particle>& GetParticlesInfo();
  size_t GetMaxNumParticles();

  double GetTopMargin();
  double GetRedParticleMass();
  double GetBlueParticleMass();
  double GetGreenParticleMass();

 private:
  // Container info
  const double kTopContainerMargin = 50;
  const double kLeftContainerMargin = 25;
  const double kContainerHeight = 580;
  const double kContainerWidth = 550;

  // Particle info
  const double kRedParticleMass = 10;
  const double kBlueParticleMass = 5;
  const double kGreenParticleMass = 15;

  const size_t kMaxNumParticles = 20;

  // Histogram info
  //const double kSpacingBetweenHistograms = 20;
  //const size_t kNumHistograms = 3;

  IdealGas ideal_gas;
  Histogram histogram_;
  vector<Particle> particles_info;
};

}  // namespace visualizer

}  // namespace disease
