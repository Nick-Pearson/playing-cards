#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <glm.hpp>

struct Transform
{
  Transform();

  glm::mat4 GetMatrix() const { return matrix; }

  inline void SetPosition(const glm::vec3& newPosition) { position = newPosition; UpdateMatrix(); }
  inline void SetRotation(const glm::vec3& newRotation) { rotation = newRotation; UpdateMatrix(); }
  inline void SetScale(const glm::vec3& newScale) { scale = newScale; UpdateMatrix(); }

private:
  void UpdateMatrix();

  glm::vec3 position;
  glm::vec3 rotation;
  glm::vec3 scale;

  glm::mat4 matrix;
};

#endif
