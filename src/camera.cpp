#include "camera.h"
#include "vec3f.h"

void Camera::move() {

}

void Camera::rotate() {

}

// getters
Vec3f Camera::pos() const { return position; }
Vec3f Camera::rot() const { return rotation; }

// setters
void Camera::set_pos(Vec3f pos) { position = pos; }
void Camera::set_rot(Vec3f rot) { rotation = rot; }