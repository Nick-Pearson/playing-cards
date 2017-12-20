#ifndef RENDERABLE_H
#define RENDERABLE_H

#include "shadermanager.h"

#include <vector>

class Renderable
{

public:

  Renderable() {}
  virtual ~Renderable() {}

  // force the mesh buffer to update
  void UpdateBuffers();

  int GetVAO() const { return m_VAO; }
  virtual Shader GetShader() const { return Shader::STD; }

protected:

  // returns the mesh data for this object
  virtual void GetMeshData(std::vector<float>& outVerticies, std::vector<unsigned int>& outIndicies) const = 0;

private:

  void GenerateBuffers();

  unsigned int m_VAO = -1;
  unsigned int m_VBO = -1;
  unsigned int m_EBO = -1;
  bool m_IsValid = false;
};

#endif
