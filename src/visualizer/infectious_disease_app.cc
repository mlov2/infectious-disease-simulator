#include <visualizer/infectious_disease_app.h>

namespace disease {

namespace visualizer {

NaiveBayesApp::NaiveBayesApp() {
  ci::app::setWindowSize((int) kWindowSizeX, (int) kWindowSizeY);
}

void NaiveBayesApp::update() {
  sketchpad_.Update();
}

void NaiveBayesApp::draw() {
  ci::Color8u background_color(255, 246, 148);  // light yellow
  ci::gl::clear(background_color);

  sketchpad_.Draw();
}

}  // namespace visualizer

}  // namespace disease
