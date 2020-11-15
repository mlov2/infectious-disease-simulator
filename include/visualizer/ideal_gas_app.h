#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "sketchpad.h"

namespace idealgas {

namespace visualizer {

/**
 * Allows a user to add particles to a container and delete them.
 */
class NaiveBayesApp : public ci::app::App {
 public:
  NaiveBayesApp();

  void update() override;
  void draw() override;
  void keyDown(ci::app::KeyEvent event) override;

  const double kWindowSizeY = 650;
  const double kWindowSizeX = 1000;

 private:
  Sketchpad sketchpad_;
};

}  // namespace visualizer

}  // namespace idealgas
