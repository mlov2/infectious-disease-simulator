#include <visualizer/sketchpad.h>

namespace disease {

namespace visualizer {

using glm::vec2;

Sketchpad::Sketchpad() {
  ideal_gas = IdealGas(kLeftContainerMargin, kTopContainerMargin, kContainerHeight, kContainerWidth, kMaxNumParticles);
}

void Sketchpad::Update() {
  ideal_gas.UpdateParticles();
  particles_info = ideal_gas.GetInfoForParticles();
  //histogram_.UpdateParticles(particles_info);
}

void Sketchpad::Draw() const {
  // Draws the container
  vec2 pixel_top_left = vec2(kLeftContainerMargin, kTopContainerMargin);
  vec2 pixel_bottom_right =
      pixel_top_left + vec2(kContainerWidth, kContainerHeight);
  ci::Rectf pixel_bounding_box(pixel_top_left, pixel_bottom_right);

  ci::gl::color(ci::Color("black"));
  ci::gl::drawSolidRect(pixel_bounding_box);

  if (!particles_info.empty()) {
    for (IdealGas::Person particle : particles_info) {
      // Draws the particles
      // Figured out how to color a particle from:
      // https://libcinder.org/docs/guides/opengl/part1.html
      ci::gl::color(ci::Color(particle.color.x, particle.color.y, particle.color.z));

      vec2 center = particle.position;
      ci::gl::drawSolidCircle(center, particle.radius);
    }
  }

  // Draws the histograms
  //histogram_.DrawHistograms();
}

void Sketchpad::Clear() {
  particles_info.clear();
  ideal_gas.SetInfoForParticles(particles_info);
}

double Sketchpad::GetTopMargin() {
  return kTopContainerMargin;
}

double Sketchpad::GetRedParticleMass() {
  return kRedParticleMass;
}

double Sketchpad::GetBlueParticleMass() {
  return kBlueParticleMass;
}

double Sketchpad::GetGreenParticleMass() {
  return kGreenParticleMass;
}

void Sketchpad::CreateOneParticle(double mass, const std::string& color) {
  ideal_gas.CreateParticle(mass, color);
}

const vector<IdealGas::Person>& Sketchpad::GetParticlesInfo() {
  return particles_info;
}

size_t Sketchpad::GetMaxNumParticles() {
  return kMaxNumParticles;
}


}  // namespace visualizer

}  // namespace disease
