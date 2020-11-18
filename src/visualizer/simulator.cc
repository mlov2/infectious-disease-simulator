#include <visualizer/simulator.h>

namespace disease {

namespace visualizer {

using glm::vec2;

Simulator::Simulator() : histogram_(disease_.GetPopulation(), kContainerHeight,
                                   vec2(kLeftContainerMargin, kTopContainerMargin) +
                                   vec2(kContainerWidth, 0)) {
  disease_ = Disease(kLeftContainerMargin, kTopContainerMargin, kContainerHeight, kContainerWidth, true);
}

void Simulator::Update() {
  disease_.UpdateParticles();
  particles_info = disease_.GetPopulation();
  histogram_.UpdatePopulation(particles_info);
}

void Simulator::Draw() const {
  // Draws the container
  vec2 pixel_top_left = vec2(kLeftContainerMargin, kTopContainerMargin);
  vec2 pixel_bottom_right =
      pixel_top_left + vec2(kContainerWidth, kContainerHeight);
  ci::Rectf pixel_bounding_box(pixel_top_left, pixel_bottom_right);

  ci::gl::color(ci::Color("black"));
  ci::gl::drawSolidRect(pixel_bounding_box);

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

  // Draws the histograms
  histogram_.DrawHistogram();
}

double Simulator::GetTopMargin() {
  return kTopContainerMargin;
}

const vector<Disease::Person>& Simulator::GetParticlesInfo() {
  return particles_info;
}

}  // namespace visualizer

}  // namespace disease
