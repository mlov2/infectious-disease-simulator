//
// Created by Megan Lov on 11/8/20.
//
#include "core/particle.h"

namespace disease {

Particle::Particle(double radius, double mass, const vec2& position, const vec2& velocity, double speed) {
  radius_ = radius;
  mass_ = mass;
  position_ = position;
  velocity_ = velocity;
  speed_ = speed;
}

Particle::Particle(double radius, double mass, const vec2& position, const vec2& velocity, double speed, const string& color) {
  radius_ = radius;
  mass_ = mass;
  position_ = position;
  velocity_ = velocity;
  speed_ = speed;
  color_ = color;
}

double Particle::GetRadius() const {
  return radius_;
}

double Particle::GetMass() const {
  return mass_;
}

const vec2& Particle::GetPosition() const {
  return position_;
}
const vec2& Particle::GetVelocity() const {
  return velocity_;
}
double Particle::GetSpeed() const {
  return speed_;
}

const string& Particle::GetColor() const {
  return color_;
}

void Particle::SetRadius(double radius) {
  radius_ = radius;
}

void Particle::SetMass(double mass) {
  mass_ = mass;
}

void Particle::SetPosition(const vec2& position) {
  position_ = position;
}

void Particle::SetVelocity(const vec2& velocity) {
  velocity_ = velocity;
}

void Particle::SetSpeed(const double speed) {
  speed_ = speed;
}

void Particle::SetColor(const string& color) {
  color_ = color;
}

}