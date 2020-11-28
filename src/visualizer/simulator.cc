#include <visualizer/simulator.h>

namespace disease {

namespace visualizer {

using glm::vec2;

Simulator::Simulator() : histogram_(disease_.GetPopulation(),
                                   vec2(kLeftContainerMargin, kTopContainerMargin) +
                                   vec2(kContainerWidth, 0)) {
  disease_ = Disease(kLeftContainerMargin, kTopContainerMargin, kContainerHeight, kContainerWidth);
  time_passed_ = 0;
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

  // Draw the container and particles
  DrawContainer();
  DrawParticles();

  // Draw the histograms
  if (particles_info.size() != 0) {
    histogram_.DrawHistogram();
  }
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

void Simulator::CreatePopulation() {
  disease_.CreatePopulation();
}

}  // namespace visualizer

}  // namespace disease
