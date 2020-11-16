#include <visualizer/ideal_gas_app.h>

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

  if (sketchpad_.GetParticlesInfo().size() != sketchpad_.GetMaxNumParticles()) {
    ci::gl::drawStringCentered(
        "Press Delete to empty the container. Press r to add a red particle. "
        "Press b to add a blue particle. Press g to add a green particle.",
        glm::vec2(kWindowSizeX / 2, sketchpad_.GetTopMargin() / 2), ci::Color("black"));
  } else {
    ci::gl::drawStringCentered(
        "Press Delete to empty the container. You may not add anymore particles because you've reached the maximum number.",
        glm::vec2(kWindowSizeX / 2, sketchpad_.GetTopMargin() / 2), ci::Color("black"));
  }
}

void NaiveBayesApp::keyDown(ci::app::KeyEvent event) {
  switch (event.getCode()) {
    case ci::app::KeyEvent::KEY_r:
      sketchpad_.CreateOneParticle(sketchpad_.GetRedParticleMass(), "red");
      break;

    case ci::app::KeyEvent::KEY_b:
      sketchpad_.CreateOneParticle(sketchpad_.GetBlueParticleMass(), "blue");
      break;

    case ci::app::KeyEvent::KEY_g:
      sketchpad_.CreateOneParticle(sketchpad_.GetGreenParticleMass(), "green");
      break;

    case ci::app::KeyEvent::KEY_DELETE:
      std::cout << "about to clear" << std::endl;
      sketchpad_.Clear();
      std::cout << "cleared" << std::endl;
      break;
  }
}

}  // namespace visualizer

}  // namespace idealgas
