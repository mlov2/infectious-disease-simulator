#include <visualizer/infectious_disease_app.h>

namespace disease {

namespace visualizer {

InfectiousDiseaseApp::InfectiousDiseaseApp() {
  ci::app::setWindowSize((int) kWindowSizeX, (int) kWindowSizeY);
}

void InfectiousDiseaseApp::update() {
  simulator_.Update();
}

void InfectiousDiseaseApp::draw() {
  ci::Color8u background_color(255, 246, 148);  // light yellow
  ci::gl::clear(background_color);

  simulator_.Draw();
}

void InfectiousDiseaseApp::keyDown(ci::app::KeyEvent event) {
  switch (event.getCode()) {
    case ci::app::KeyEvent::KEY_RETURN:
      // TODO: Start breakout
      simulator_.CreatePopulation();
      break;

    case ci::app::KeyEvent::KEY_e:
      // TODO: Change exposure time
      break;

    case ci::app::KeyEvent::KEY_i:
      // TODO: Change infected time
      break;

    case ci::app::KeyEvent::KEY_r:
      // TODO: Change radius of infection
      break;

    case ci::app::KeyEvent::KEY_d:
      // TODO: Change amount of social distance
      break;

    case ci::app::KeyEvent::KEY_DELETE:
      // TODO: End breakout and clear container and histogram
      simulator_.Clear();
      break;
  }
}

}  // namespace visualizer

}  // namespace disease
