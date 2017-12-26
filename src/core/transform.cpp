#include "transform.h"

#include <gtc/matrix_transform.hpp>

Transform::Transform()
{
  position = glm::vec3(0.0f, 0.0f, 0.0f);
  rotation = glm::vec3(0.0f, 0.0f, 0.0f);
  scale = glm::vec3(1.0f, 1.0f, 1.0f);
  UpdateMatrix();
}

void Transform::UpdateMatrix()
{
  matrix = glm::mat4();
  matrix = glm::translate(matrix, position);
  matrix = glm::rotate(matrix, rotation[0], glm::vec3(1.0f, 0.0f, 0.0f));
  matrix = glm::rotate(matrix, rotation[1], glm::vec3(0.0f, 1.0f, 0.0f));
  matrix = glm::rotate(matrix, rotation[2], glm::vec3(0.0f, 0.0f, 1.0f));
  matrix = glm::scale(matrix, scale);
}
