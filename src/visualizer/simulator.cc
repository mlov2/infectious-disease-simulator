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

  if (disease_.GetPercentPerformingSocialDistance() != 0 &&
      disease_.GetRadiusOfInfection() < disease_.GetAmountOfSocialDistance() + kIncrementOrDecrementBy) {
    disease_.SetRadiusOfInfection(disease_.GetAmountOfSocialDistance() + kIncrementOrDecrementBy);
  }
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
    DrawConstraintsMessage(general_instructions_y_location);

    ci::gl::drawString(
        "You are currently changing: " + GetFeatureBeingChanged(),
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
        "To change the percent of population social distancing, press 'd'",
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
      "Percent of population social distancing: " +
      std::to_string(disease_.GetPercentPerformingSocialDistance()) + "%",
      glm::vec2(x_location, y_location), ci::Color("black"));

  y_location += kSpacesFromContainer;
  ci::gl::drawString(
      "Radius of infection: " + std::to_string(disease_.GetRadiusOfInfection()),
      glm::vec2(x_location, y_location), ci::Color("black"));
}

void Simulator::DrawConstraintsMessage(double y_location) const {
  double x_location = histogram_.GetXCoordinateOfStatusStatLabels();

  switch (int(feature_currently_being_changed_)) {
    case 1:
      if (disease_.GetExposureTime() >= disease_.GetMaximumExposureTime()) {
        ci::gl::drawString(GetFeatureBeingChanged() + " is at its max value",
                           glm::vec2(x_location, y_location), ci::Color("red"));
      } else if (disease_.GetExposureTime() <= disease_.GetMinimumExposureTime()) {
        ci::gl::drawString(GetFeatureBeingChanged() + " is at its min value",
                           glm::vec2(x_location, y_location), ci::Color("red"));
      }
      break;

    case 2:
      if (disease_.GetInfectedTime() >= disease_.GetMaximumInfectedTime()) {
        ci::gl::drawString(GetFeatureBeingChanged() + " is at its max value",
                           glm::vec2(x_location, y_location), ci::Color("red"));
      } else if (disease_.GetInfectedTime() <= disease_.GetMinimumInfectedTime()) {
        ci::gl::drawString(GetFeatureBeingChanged() + " is at its min value",
                           glm::vec2(x_location, y_location), ci::Color("red"));
      }
      break;

    case 3:
      if (disease_.GetPercentPerformingSocialDistance() >= disease_.GetMaximumSocialDistancePercentage()) {
        ci::gl::drawString(GetFeatureBeingChanged() + " is at its max value",
                           glm::vec2(x_location, y_location), ci::Color("red"));
      } else if (disease_.GetPercentPerformingSocialDistance() <= disease_.GetMinimumSocialDistancePercentage()) {
        ci::gl::drawString(GetFeatureBeingChanged() + " is at its min value",
                           glm::vec2(x_location, y_location), ci::Color("red"));
      }
      break;

    case 4:
      if (disease_.GetRadiusOfInfection() >= disease_.GetMaximumInfectionRadius()) {
        ci::gl::drawString(GetFeatureBeingChanged() + " is at its max value",
                           glm::vec2(x_location, y_location), ci::Color("red"));
      } else if (disease_.GetRadiusOfInfection() <= disease_.GetMinimumInfectionRadius()) {
        ci::gl::drawString(GetFeatureBeingChanged() + " is at its min value",
                           glm::vec2(x_location, y_location), ci::Color("red"));
      } else if (disease_.GetRadiusOfInfection() <= (disease_.GetAmountOfSocialDistance() +
          kIncrementOrDecrementBy) &&
          disease_.GetPercentPerformingSocialDistance() != 0) {
        ci::gl::drawString(GetFeatureBeingChanged() + " is at its min value",
                           glm::vec2(x_location, y_location), ci::Color("red"));
        ci::gl::drawString("when social distance is on",
                           glm::vec2(x_location, y_location + kSpacesFromContainer),
                           ci::Color("red"));
      }
      break;
  }
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
      case 0:  // kQuarantine
        if (disease_.GetShouldQuarantineValue()) {
          disease_.SetShouldQuarantine(false);
        } else {
          disease_.SetShouldQuarantine(true);
        }
        break;

      case 1:  // kExposureTime
        if (is_key_up) {
          if (disease_.GetExposureTime() < disease_.GetMaximumExposureTime()) {
            disease_.SetExposureTime(disease_.GetExposureTime() + kIncrementOrDecrementBy);
          }
        } else {
          if (disease_.GetExposureTime() > disease_.GetMinimumExposureTime()) {
            disease_.SetExposureTime(disease_.GetExposureTime() - kIncrementOrDecrementBy);
          }
        }
        break;

      case 2:  // kInfectedTime
        if (is_key_up) {
          if (disease_.GetInfectedTime() < disease_.GetMaximumInfectedTime()) {
            disease_.SetInfectedTime(disease_.GetInfectedTime() + kIncrementOrDecrementBy);
          }
        } else {
          if (disease_.GetInfectedTime() > disease_.GetMinimumInfectedTime()) {
            disease_.SetInfectedTime(disease_.GetInfectedTime() - kIncrementOrDecrementBy);
          }
        }
        break;

      case 3:  // kSocialDistance
        if (is_key_up) {
          if (disease_.GetPercentPerformingSocialDistance() < disease_.GetMaximumSocialDistancePercentage()) {
            disease_.SetPercentPerformingSocialDistance(
                disease_.GetPercentPerformingSocialDistance() + kIncrementOrDecrementBy);
          }
        } else {
          if (disease_.GetPercentPerformingSocialDistance() > disease_.GetMinimumSocialDistancePercentage()) {
            disease_.SetPercentPerformingSocialDistance(
                disease_.GetPercentPerformingSocialDistance() - kIncrementOrDecrementBy);
          }
        }
        break;

      case 4:  // kInfectionRadius
        if (is_key_up) {
          if (disease_.GetRadiusOfInfection() < disease_.GetMaximumInfectionRadius()) {
            disease_.SetRadiusOfInfection(disease_.GetRadiusOfInfection() + kIncrementOrDecrementBy);
          }
        } else {
          if (disease_.GetPercentPerformingSocialDistance() != 0) {
            if ((disease_.GetRadiusOfInfection() > disease_.GetMinimumInfectionRadius()) &&
                (disease_.GetRadiusOfInfection() > disease_.GetAmountOfSocialDistance() + kIncrementOrDecrementBy)) {
              disease_.SetRadiusOfInfection(disease_.GetRadiusOfInfection() - kIncrementOrDecrementBy);
            }
          } else {
            if (disease_.GetRadiusOfInfection() > disease_.GetMinimumInfectionRadius()) {
              disease_.SetRadiusOfInfection(disease_.GetRadiusOfInfection() - kIncrementOrDecrementBy);
            }
          }
        }
        break;
    }
  }
}

void Simulator::Clear() {
  time_passed_ = 0;
  particles_info.clear();
  disease_.SetPopulation(particles_info);
}

std::string Simulator::GetFeatureBeingChanged() const {
  std::string feature_being_changed;

  switch (int(feature_currently_being_changed_)) {
    case 0:
      feature_being_changed = "'Should Quarantine'";
      break;

    case 1:
      feature_being_changed = "'Exposed Time'";
      break;

    case 2:
      feature_being_changed = "'Infected Time'";
      break;

    case 3:
      feature_being_changed = "'Percent Social Distancing'";
      break;

    case 4:
      feature_being_changed = "'Radius of Infection'";
      break;
  }

  return feature_being_changed;
}

const vector<Disease::Person>& Simulator::GetParticlesInfo() {
  return particles_info;
}

size_t Simulator::GetTimePassed() const {
  return time_passed_;
}

FeatureChangeKey Simulator::GetFeatureCurrentlyChanging() const {
  return feature_currently_being_changed_;
}

Disease Simulator::GetDiseaseClass() const {
  return disease_;
}

double Simulator::GetTopMargin() {
  return kTopContainerMargin;
}

}  // namespace visualizer

}  // namespace disease
