#include <visualizer/simulator.h>

namespace disease {

namespace visualizer {

using glm::vec2;

Simulator::Simulator() : histogram_(disease_.GetPopulation(),
                                   vec2(kLeftContainerMargin, kTopContainerMargin) +
                                   vec2(kContainerWidth, 0)) {
  quarantine_box_top_left_x_ = kLeftContainerMargin + kContainerWidth + kSpacesFromContainer;
  quarantine_box_top_left_y_ = histogram_.GetBottomMostBoundaryOfHistogram() + kSpacesFromContainer;
  quarantine_box_bottom_right_x_ = quarantine_box_top_left_x_ + kQuarantineBoxWidth;
  quarantine_box_bottom_right_y_ = kTopContainerMargin + kContainerHeight;

  disease_ = Disease(kLeftContainerMargin, kTopContainerMargin, kContainerHeight, kContainerWidth,
                     vec2(quarantine_box_top_left_x_, quarantine_box_top_left_y_),
                     vec2(quarantine_box_bottom_right_x_, quarantine_box_bottom_right_y_));
  time_passed_ = 0;
  feature_currently_being_changed_ = FeatureChangeKey::kQuarantine;
}

void Simulator::Update() {
  disease_.UpdateParticles();
  particles_info = disease_.GetPopulation();
  if (particles_info.size() != 0) {
    time_passed_++;
  }
  histogram_.Update(particles_info, time_passed_);
}

void Simulator::Draw() const {
  ci::gl::drawStringCentered(
      "Time elapsed: " + std::to_string(time_passed_),
      glm::vec2((2*kLeftContainerMargin + kContainerWidth) / 2, kTopContainerMargin / 2), ci::Color("black"));

  // Draw the container
  DrawContainer();

  // Draw the histograms
  if (particles_info.size() != 0) {
    histogram_.DrawHistogram();
    DrawQuarantineBox();
  }

  // Draw the particles
  DrawParticles();

  DrawFeatureChangeInstructions();
  DrawFeatureLabels();
}

void Simulator::DrawContainer() const {
  vec2 pixel_top_left = vec2(kLeftContainerMargin, kTopContainerMargin);
  vec2 pixel_bottom_right =
      pixel_top_left + vec2(kContainerWidth, kContainerHeight);
  ci::Rectf pixel_bounding_box(pixel_top_left, pixel_bottom_right);

  ci::gl::color(ci::Color("black"));
  ci::gl::drawSolidRect(pixel_bounding_box);
}

void Simulator::DrawParticles() const {
  if (!particles_info.empty()) {
    for (Disease::Person particle : particles_info) {
      // Draws the particles
      // Figured out how to color a particle from:
      // https://libcinder.org/docs/guides/opengl/part1.html
      ci::gl::color(ci::Color(particle.color.x, particle.color.y, particle.color.z));

      vec2 center = particle.position;
      ci::gl::drawSolidCircle(center, particle.radius);
    }
  }
}

void Simulator::DrawQuarantineBox() const {
  if (disease_.GetShouldQuarantineValue()) {
    if (!particles_info.empty()) {
      vec2 pixel_top_left = vec2(quarantine_box_top_left_x_, quarantine_box_top_left_y_);
      vec2 pixel_bottom_right = vec2(quarantine_box_bottom_right_x_, quarantine_box_bottom_right_y_);
      ci::Rectf pixel_bounding_box(pixel_top_left, pixel_bottom_right);

      ci::gl::color(ci::Color("black"));
      ci::gl::drawSolidRect(pixel_bounding_box);
    }
  }
}

void Simulator::DrawFeatureChangeInstructions() const {
  if (particles_info.empty()) {
    double x_location = kLeftContainerMargin + kContainerWidth + kSpacesFromContainer;
    double y_location = histogram_.GetYCoordinateOfLastStatusStatLabel() + kInitialYLocForFeatureStats;

    // General instructions
    double general_instructions_y_location = y_location - kInitialYLocForGeneralInstructionsMultiplier *
        kSpacesFromContainer;
    ci::gl::drawString(
        "You are currently changing: ",  // TODO: add a to_string that will show what's being changed
        glm::vec2(x_location, general_instructions_y_location), ci::Color("black"));

    general_instructions_y_location += kSpacesFromContainer;
    ci::gl::drawString(
        "To change the value, press the arrow up or arrow down key",
        glm::vec2(x_location, general_instructions_y_location), ci::Color("black"));

    // Specific instructions
    ci::gl::drawString(
        "To change if population should quarantine when infected, press 'q'",
        glm::vec2(x_location, y_location), ci::Color("black"));

    y_location += kSpacesFromContainer;
    ci::gl::drawString(
        "To change the exposure time, press 'e'",
        glm::vec2(x_location, y_location), ci::Color("black"));

    y_location += kSpacesFromContainer;
    ci::gl::drawString(
        "To change the infected time, press 'i'",
        glm::vec2(x_location, y_location), ci::Color("black"));

    y_location += kSpacesFromContainer;
    ci::gl::drawString(
        "To change the amount of social distance, press 'd'",
        glm::vec2(x_location, y_location), ci::Color("black"));

    y_location += kSpacesFromContainer;
    ci::gl::drawString(
        "To change the radius of infection, press 'r'",
        glm::vec2(x_location, y_location), ci::Color("black"));
  }
}

void Simulator::DrawFeatureLabels() const {
  double x_location = histogram_.GetXCoordinateOfStatusStatLabels();
  double y_location = histogram_.GetYCoordinateOfLastStatusStatLabel() + kInitialYLocForFeatureStats;

  ci::gl::drawString(
      "FEATURE STATS",
      glm::vec2(x_location, y_location - kSpacesFromContainer), ci::Color("black"));

  std::string quarantine = "No";
  if (disease_.GetShouldQuarantineValue()) {
    quarantine = "Yes";
  }
  ci::gl::drawString(
      "Should quarantine? " + quarantine,
      glm::vec2(x_location, y_location), ci::Color("black"));

  y_location += kSpacesFromContainer;
  ci::gl::drawString(
      "Exposure time: " + std::to_string(disease_.GetExposureTime()),
      glm::vec2(x_location, y_location), ci::Color("black"));

  y_location += kSpacesFromContainer;
  ci::gl::drawString(
      "Infected time: " + std::to_string(disease_.GetInfectedTime()),
      glm::vec2(x_location, y_location), ci::Color("black"));

  y_location += kSpacesFromContainer;
  ci::gl::drawString(
      "Amount of social distance: " + std::to_string(disease_.GetAmountOfSocialDistance()),
      glm::vec2(x_location, y_location), ci::Color("black"));

  y_location += kSpacesFromContainer;
  ci::gl::drawString(
      "Radius of infection: " + std::to_string(disease_.GetRadiusOfInfection()),
      glm::vec2(x_location, y_location), ci::Color("black"));
}

void Simulator::CreatePopulation() {
  disease_.CreatePopulation();
}

void Simulator::ChangeFeature(FeatureChangeKey feature_to_change) {
  feature_currently_being_changed_ = feature_to_change;
}

void Simulator::ChangeFeatureValue(bool is_key_up) {
  if (particles_info.empty()) {
    switch (int(feature_currently_being_changed_)) {
      case 1:  // kQuarantine
        // TODO: User getters and setters from Disease class to change the value
        break;

      case 2:  // kExposureTime
        break;

      case 3:  // kInfectedTime
        break;

      case 4:  // kSocialDistance
        break;

      case 5:  // kInfectionRadius
        break;
    }
  }
}

void Simulator::Clear() {
  time_passed_ = 0;
  particles_info.clear();
  disease_.SetPopulation(particles_info);
}

double Simulator::GetTopMargin() {
  return kTopContainerMargin;
}

const vector<Disease::Person>& Simulator::GetParticlesInfo() {
  return particles_info;
}

}  // namespace visualizer

}  // namespace disease
