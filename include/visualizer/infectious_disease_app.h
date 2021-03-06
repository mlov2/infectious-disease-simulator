#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "simulator.h"

namespace disease {

namespace visualizer {

/*
 * Displays a simulator to the user.
 */
class InfectiousDiseaseApp : public ci::app::App {
 public:
  InfectiousDiseaseApp();

  void update() override;
  void draw() override;
  void keyDown(ci::app::KeyEvent event) override;

  const double kWindowSizeY = 650;
  const double kWindowSizeX = 1300;

 private:
  Simulator simulator_;
};

}  // namespace visualizer

}  // namespace disease
