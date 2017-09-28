#include "plot.h"

#include "particle.h"
#include "vector3d.h"
#include "fields.h"
#include "propagator.h"
#include "plane3d.h"

#include<vector>
#include<iostream>

class TwoFields: public FieldDescriptor {
public:
  TwoFields(const Vector3D& strength1, const Vector3D& strength2): strength1(strength1), strength2(strength2) {}
  /**
   * In this example, if x is less or equal to 80, strength1 is returned, otherwise strength2
   */
  Vector3D getStrength(const Vector3D &location) const override {
    if (location.x <= 80) {
      return strength1;
    } else {
      return strength2;
    }
  }
private:
  Vector3D strength1;
  Vector3D strength2;
};

int main () {
  // initiate the particle
  Vector3D momentum(0.5, 0.5, 0.5);
  Vector3D location(1, 1, 1);
  Particle particle(0, 1, 1, 0.5, location, momentum);

  // initiate the magnetic field
  Vector3D fieldStrength1(-0.1, -0.1, 0);
  Vector3D fieldStrength2(0.1,0.1, 0);
  TwoFields field(fieldStrength1, fieldStrength2);

  // propagate the particle through the field
  Propagator propagator(field);
  std::vector<Vector3D> points = propagator.getPoints(particle, 400);
  plot("Two Homogeneous Fields Example", points);
}
