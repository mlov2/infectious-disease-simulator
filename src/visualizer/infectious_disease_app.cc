#include <visualizer/infectious_disease_app.h>

namespace disease {

namespace visualizer {

InfectiousDiseaseApp::InfectiousDiseaseApp() {
  ci::app::setWindowSize(int(kWindowSizeX), int(kWindowSizeY));
}

void InfectiousDiseaseApp::update() {
  simulator_.Update();
}

void InfectiousDiseaseApp::draw() {
  ci::Color8u background_color(255, 246, 148);  // light yellow
  ci::gl::clear(background_color);

  simulator_.Draw();

  if (simulator_.GetParticlesInfo().size() != 0) {
    cinder::gl::drawStringCentered(
        "Press 'Delete' to end the simulation.",
        glm::vec2((kWindowSizeX + simulator_.GetRightMargin()) / 2, simulator_.GetTopMargin() / 2),
        ci::Color("black"));
  } else {
    cinder::gl::drawStringCentered(
        "Press 'Enter' to begin the simulation.",
        glm::vec2((kWindowSizeX + simulator_.GetRightMargin()) / 2, simulator_.GetYLocForEnterInstructions()),
        ci::Color("black"));
  }
}

void InfectiousDiseaseApp::keyDown(ci::app::KeyEvent event) {
  switch (event.getCode()) {
    case ci::app::KeyEvent::KEY_RETURN:
      simulator_.CreatePopulation();
      break;

    case ci::app::KeyEvent::KEY_q:
      simulator_.ChangeFeature(FeatureChangeKey::kQuarantine);
      break;

    case ci::app::KeyEvent::KEY_e:
      simulator_.ChangeFeature(FeatureChangeKey::kExposureTime);
      break;

    case ci::app::KeyEvent::KEY_i:
      simulator_.ChangeFeature(FeatureChangeKey::kInfectedTime);
      break;

    case ci::app::KeyEvent::KEY_r:
      simulator_.ChangeFeature(FeatureChangeKey::kInfectionRadius);
      break;

    case ci::app::KeyEvent::KEY_d:
      simulator_.ChangeFeature(FeatureChangeKey::kSocialDistance);
      break;

    case ci::app::KeyEvent::KEY_c:
      simulator_.ChangeFeature(FeatureChangeKey::kCentralLocation);
      break;

    case ci::app::KeyEvent::KEY_UP:
      simulator_.ChangeFeatureValue(true);
      break;

    case ci::app::KeyEvent::KEY_DOWN:
      simulator_.ChangeFeatureValue(false);
      break;

    case ci::app::KeyEvent::KEY_DELETE:
      // End breakout and clear container and histogram
      simulator_.Clear();
      break;
  }
}

}  // namespace visualizer

}  // namespace disease
