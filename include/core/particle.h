//
// Created by Megan Lov on 11/8/20.
//
#pragma once

#include "cinder/gl/gl.h"

using glm::vec2;
using std::string;

namespace disease {

class Particle {
 private:
  double radius_;
  double mass_;
  vec2 position_;
  vec2 velocity_;
  double speed_;
  string color_;

 public:
  Particle() = default;
  Particle(double radius, double mass, const vec2& position, const vec2& velocity, double speed);
  Particle(double radius, double mass, const vec2& position, const vec2& velocity, double speed, const string& color);

  double GetRadius() const;
  double GetMass() const;
  const vec2& GetPosition() const;
  const vec2& GetVelocity() const;
  double GetSpeed() const;
  const string& GetColor() const;

  void SetRadius(double radius);
  void SetMass(double mass);
  void SetPosition(const vec2& position);
  void SetVelocity(const vec2& velocity);
  void SetSpeed(const double speed);
  void SetColor(const string& color);
};

}  // namespace disease
