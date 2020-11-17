#include <visualizer/infectious_disease_app.h>

namespace disease {

namespace visualizer {

InfectiousDiseaseApp::InfectiousDiseaseApp() {
  ci::app::setWindowSize((int) kWindowSizeX, (int) kWindowSizeY);
}

void InfectiousDiseaseApp::update() {
  sketchpad_.Update();
}

void InfectiousDiseaseApp::draw() {
  ci::Color8u background_color(255, 246, 148);  // light yellow
  ci::gl::clear(background_color);

  sketchpad_.Draw();
}

}  // namespace visualizer

}  // namespace disease
