#ifndef DeSerializingOperators_H
#define DeSerializingOperators_H

#include "ResourceTypes.h"

// forward declaration
enum class MaterialType;
struct QuaternionTransform;
struct Animation;

std::ifstream& operator>>(std::ifstream& inputFile, size_t& t);
std::ifstream& operator>>(std::ifstream& inputFile, int& t);
std::ifstream& operator>>(std::ifstream& inputFile, unsigned& t);
std::ifstream& operator>>(std::ifstream& inputFile, float& t);
std::ifstream& operator>>(std::ifstream& inputFile, glm::vec2& vec);
std::ifstream& operator>>(std::ifstream& inputFile, glm::vec3& vec);
std::ifstream& operator>>(std::ifstream& inputFile, glm::vec4& vec);
std::ifstream& operator>>(std::ifstream& inputFile, MaterialType& type);
std::ifstream& operator>>(std::ifstream& inputFile, std::wstring maps[static_cast<size_t>(MapType::Count)]);
std::ifstream& operator>>(std::ifstream& inputFile, QuaternionTransform&);
std::ifstream& operator>>(std::ifstream& inputFile, glm::quat&);
std::ifstream& operator>>(std::ifstream& inputFile, std::wstring& wideString);

std::ifstream& operator>>(std::ifstream& inputFile, Model& model);
std::ifstream& operator>>(std::ifstream& inputFile, Mesh& model);
std::ifstream& operator>>(std::ifstream& inputFile, std::shared_ptr<Material>& material);
std::ifstream& operator>>(std::ifstream& inputFile, Material& material);
std::ifstream& operator>>(std::ifstream& inputFile, Joint& Joint);
std::ifstream& operator>>(std::ifstream& inputFile, Animation& animation);

template<typename T>
std::ifstream& operator>>(std::ifstream& inputFile, std::vector<T>& vec) {
  size_t size;

  inputFile >> size;
  vec.resize(size);
  for (size_t i = 0; i < size; ++i) {
    inputFile >> vec[i];
  }

  return inputFile;
}

#endif
