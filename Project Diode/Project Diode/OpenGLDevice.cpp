/******************************************************************/
/*!
  All content (C) John Salguero, all rights reserved.
  Reproduction or disclosure of this file or its contents without the
  prior written consent of John Salguero is prohibited.

  \file    OpenGLDevice.cpp
  \author  John Salguero
  \date    June 23, 2023
  \brief
    This cpp file defines the OpenGL Device class, which is
    a class that drives the opengl behavior of the game,
    that is - it executes the low level graphics calls
*/
/********************************************************************/
#include "stdafx.h"
#include "Joint.h"
#include "Animation.h"
#include "Texture.h"


int OpenGLDevice::DrawRenderable(std::shared_ptr<Renderable> const& renderable)
{
  ShaderFlags oldFlags = m_CurrentFlags;
  auto const& model = *renderable->GetModel();

  for (int i = 0; i < model.m_meshes.size(); ++i)
  {
    auto const& mesh = model.m_meshes[i];
    SetShaderProgram(mesh.m_flags);
    SetMaterials(mesh);
    // if the model has a skeleton, populate the bones
      std::vector<glm::mat4> boneTransformations;
    if (!model.m_skeleton.empty())
    {
      boneTransformations.reserve(model.m_skeleton.size());
      GLuint boneLocation = glGetUniformLocation(m_ShaderPrograms[m_CurrentFlags], "finalBonesMatrices");
      for (auto &joint : model.m_skeleton)
      {
        WARN("TODO: HACKED Animation here");
        if (joint.m_Animations.empty())
        {
          boneTransformations.push_back(glm::mat4());
          continue;
        }
        size_t currAnim, currFrame, nextFrame;
        float interpolation;
        renderable->GetAnimationIndices(currAnim, currFrame, interpolation);
        nextFrame = currFrame + 1;
        if (joint.m_Animations[currAnim].m_AnimatedTransform.size() == nextFrame)
          nextFrame = currFrame;
        auto transformation = joint.m_Animations[currAnim].m_AnimatedTransform[currFrame].Interpolate(
          joint.m_Animations[currAnim].m_AnimatedTransform[nextFrame], interpolation).GetTransformation();
        boneTransformations.push_back(transformation);
      }
      glUniformMatrix4fv(boneLocation, static_cast<GLsizei>(boneTransformations.size()), GL_FALSE, &boneTransformations[0][0][0]);
    }
    glm::mat4 transform;
    GetTransform(renderable, transform);
    // Set up the instances
    glBindVertexArray(mesh.m_VAO[0]);
    glBindBuffer(GL_ARRAY_BUFFER, m_matVBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::mat4), &transform, GL_STREAM_DRAW);
    int pos1 = 9;
    int pos2 = pos1 + 1;
    int pos3 = pos2 + 1;
    int pos4 = pos3 + 1;
    glEnableVertexAttribArray(pos1);
    glEnableVertexAttribArray(pos2);
    glEnableVertexAttribArray(pos3);
    glEnableVertexAttribArray(pos4);
    glVertexAttribPointer(pos1, 4, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 4 * 4, (void*)(0));
    glVertexAttribPointer(pos2, 4, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 4 * 4, (void*)(sizeof(float) * 4));
    glVertexAttribPointer(pos3, 4, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 4 * 4, (void*)(sizeof(float) * 8));
    glVertexAttribPointer(pos4, 4, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 4 * 4, (void*)(sizeof(float) * 12));
    glVertexAttribDivisor(pos1, 1);
    glVertexAttribDivisor(pos2, 1);
    glVertexAttribDivisor(pos3, 1);
    glVertexAttribDivisor(pos4, 1);
    // Draw the Mesh
    glDrawElementsInstanced(GL_TRIANGLES, static_cast<GLsizei>(mesh.m_Indices.size()), GL_UNSIGNED_INT, 0, 1);
  }
  SetShaderProgram(oldFlags);
  return 0;
}

int OpenGLDevice::DrawTransparentRenderable(std::shared_ptr<Renderable> const& renderable)
{
  ShaderFlags oldFlags = m_CurrentFlags;
  auto const& model = *renderable->GetModel();

  for (int i = 0; i < model.m_meshes.size(); ++i)
  {
    auto const& mesh = model.m_meshes[i];
    if (!(mesh.m_flags & TRANSPARENCY_FLAG))
      continue;
    SetShaderProgram(mesh.m_flags);
    SetMaterials(mesh);
    glm::mat4 transform;
    GetTransform(renderable, transform);
    // Set up the instances
    glBindVertexArray(mesh.m_VAO[0]);
    glBindBuffer(GL_ARRAY_BUFFER, m_matVBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::mat4), &transform, GL_STREAM_DRAW);
    int pos1 = 9;
    int pos2 = pos1 + 1;
    int pos3 = pos2 + 1;
    int pos4 = pos3 + 1;
    glEnableVertexAttribArray(pos1);
    glEnableVertexAttribArray(pos2);
    glEnableVertexAttribArray(pos3);
    glEnableVertexAttribArray(pos4);
    glVertexAttribPointer(pos1, 4, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 4 * 4, (void*)(0));
    glVertexAttribPointer(pos2, 4, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 4 * 4, (void*)(sizeof(float) * 4));
    glVertexAttribPointer(pos3, 4, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 4 * 4, (void*)(sizeof(float) * 8));
    glVertexAttribPointer(pos4, 4, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 4 * 4, (void*)(sizeof(float) * 12));
    glVertexAttribDivisor(pos1, 0);
    glVertexAttribDivisor(pos2, 0);
    glVertexAttribDivisor(pos3, 0);
    glVertexAttribDivisor(pos4, 0);
    // Draw the Mesh
    glDrawElementsInstanced(GL_TRIANGLES, static_cast<GLsizei>(mesh.m_Indices.size()), GL_UNSIGNED_INT, 0, 1);
  }
  SetShaderProgram(oldFlags);
  return 0;
}

int OpenGLDevice::DrawBatchedRenderables(std::multiset<std::shared_ptr<Renderable>, RenderableComparator> const& renderableSet)
{
  std::vector<glm::mat4> instancedTransformations;
  auto modIt = renderableSet.begin(), modEnd = renderableSet.end();
  // iterate through the models, instance the meshes that are alike
  while (modIt != modEnd)
  {
    auto const& currModel = (*modIt)->GetModel();
    auto currIt = modIt;
    // if the model has an animation, cannot instance it - draw it and continue
    if (!currModel->m_skeleton.empty())
    {
      DrawRenderable((*modIt));
      ++modIt;
      continue;
    }
    for(int i = 0; i < (*currIt)->GetModel()->m_meshes.size(); ++i)
    {
      auto const& currMesh = currModel->m_meshes[i];
      if (currMesh.m_flags != m_CurrentFlags)
        continue;
      modIt = currIt;
      glBindVertexArray((*currIt)->GetModel()->m_meshes[i].m_VAO[0]);
      // Bind the material to the uniform
      SetMaterials(currMesh);
      while (modIt != modEnd && (*modIt)->GetModelID() == currModel->GetID())
      {
        glm::mat4 transform;
        GetTransform(*modIt, transform);
        instancedTransformations.push_back(transform);
         ++modIt;
      }
      // Set up the instances
      glBindBuffer(GL_ARRAY_BUFFER, *m_matVBO);
      glBufferData(GL_ARRAY_BUFFER, instancedTransformations.size() * sizeof(glm::mat4), instancedTransformations.data(), GL_STATIC_DRAW);
      int pos1 = 9;
      int pos2 = pos1 + 1;
      int pos3 = pos2 + 1;
      int pos4 = pos3 + 1;
      glEnableVertexAttribArray(pos1);
      glEnableVertexAttribArray(pos2);
      glEnableVertexAttribArray(pos3);
      glEnableVertexAttribArray(pos4);
      glVertexAttribPointer(pos1, 4, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 4 * 4, (void*)(0));
      glVertexAttribPointer(pos2, 4, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 4 * 4, (void*)(sizeof(float) * 4));
      glVertexAttribPointer(pos3, 4, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 4 * 4, (void*)(sizeof(float) * 8));
      glVertexAttribPointer(pos4, 4, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 4 * 4, (void*)(sizeof(float) * 12));
      glVertexAttribDivisor(pos1, 1);
      glVertexAttribDivisor(pos2, 1);
      glVertexAttribDivisor(pos3, 1);
      glVertexAttribDivisor(pos4, 1);
      // Draw the instances
      glDrawElementsInstanced(GL_TRIANGLES, static_cast<GLsizei>(currMesh.m_Indices.size()), GL_UNSIGNED_INT, 0, static_cast<GLsizei>(instancedTransformations.size()));
    }
  }

  return 0;
}

/******************************************************************************/
/*!
          DrawTransparentRenderables

\author   John Salguero

\brief    Draws Renderables in reverse order from the map, using the renderable's
          flage along the way - this does not make use of instancing

\param    vecRenderabls
          The Renderables to Draw

\return   int
          Error code of setting the program
*/
/******************************************************************************/
int OpenGLDevice::DrawTransparentRenderables(std::multimap<float, std::shared_ptr<Renderable>> const& mapRenderabls)
{
  for (auto it = mapRenderabls.rbegin(), end = mapRenderabls.rend(); it != end; ++it)
  {
    DrawTransparentRenderable(it->second);
  }


  return 0;
}

/******************************************************************************/
/*!
          SetShaderProgram

\author   John Salguero

\brief    Sets the program used to render objects

\param    flags
          The flags used to determine what shader to use

\return   int
          Error code of setting the program
*/
/******************************************************************************/
int OpenGLDevice::SetShaderProgram(ShaderFlags flags)
{
  flags &= ~(TRANSPARENCY_FLAG);
  if (m_CurrentFlags == flags || flags == (UNUSED_FLAGS & ~(TRANSPARENCY_FLAG)))
    return 0;
  if (m_ShaderPrograms.find(flags) != m_ShaderPrograms.end())
    glUseProgram(m_ShaderPrograms[flags]);
  else
  {
    GLuint shaderProgram = LoadShaderProgram(flags);
    m_ShaderPrograms[flags] = shaderProgram;
    glUseProgram(shaderProgram);
  }

  // Everytime the uniform state changes, update view position
  GLuint location = glGetUniformLocation(m_ShaderPrograms[flags], "viewPos");
  glUniform1fv(location, 3, &m_ViewPos[0]);

  m_CurrentFlags = flags;
  return 0;
}

/******************************************************************************/
/*!
          SetBuffer

\author   John Salguero

\brief    Sets the buffer to draw to

\param    id
          The ID of the buffer to draw to

\return   int
          the error code, 0 means success
*/
/******************************************************************************/
int OpenGLDevice::SetBuffer(int id)
{
  return 0;
}

/******************************************************************************/
/*!
          SetBuffer

\author   John Salguero

\brief    Sets Materials in the uniform to draw with

\param    mesh
          The Mesh to populate the materials with

\return   int
          the error code, 0 means success
*/
/******************************************************************************/
int OpenGLDevice::SetMaterials(Mesh const& mesh)
{
  // the collection of texture unit indicies used in the shader
  std::vector<std::vector<GLint>> textureUnitIndices;
  // a count of the texture unit index to use
  GLint textureUnitIndex = 0;

  // Bind the UBO
  glBindBuffer(GL_UNIFORM_BUFFER, m_materialUBO[0]);

  // Map the buffer to update the data
  MaterialBuffer* materialBuffer = (MaterialBuffer*)glMapBuffer(GL_UNIFORM_BUFFER, GL_WRITE_ONLY);

  // Copy the material data to the buffer
  // Use the same loop to associate the textures to texture unit indices
  for (size_t i = 0; i < mesh.m_Materials.size(); ++i)
  {
    Material const& material = *mesh.m_Materials[i];
    materialBuffer[i] = material;

    // Set the Textures for the materials
    for (size_t index = 0; index < static_cast<size_t>(MapType::Count); ++index) {
      auto &texture = material.m_MappingTextures[index];
      if (texture)
      {
        std::string uniformName = m_TextureLocationMap[1 << index] + std::string("[") + std::to_string(i) + "]";
        GLuint location = glGetUniformLocation(m_ShaderPrograms[m_CurrentFlags], uniformName.c_str());
        glActiveTexture(static_cast<GLenum>(GL_TEXTURE0 + textureUnitIndex));
        glBindTexture(GL_TEXTURE_2D, texture->m_textureID);
        glUniform1i(location, textureUnitIndex++);
      }
    }

  }
  // Unmap the buffer
  glUnmapBuffer(GL_UNIFORM_BUFFER);

  GLuint bindingPoint = 0; // The binding point/index to which the buffer object is bound
  glBindBufferBase(GL_UNIFORM_BUFFER, MATERIAL_BINDING_POINT, m_materialUBO[0]);

  return 0;
}

/******************************************************************************/
/*!
          SetCamera

\author   John Salguero

\brief    Sets the camera and projection transforms

\param    camera
          The Camera that defines the transforms

\return   void
*/
/******************************************************************************/
int OpenGLDevice::SetCamera(std::shared_ptr<Camera> const& camera)
{
  m_CameraTransformation = camera->GetCameraTransformation();
  m_ProjectionTransformation = camera->GetPerpectiveMatrix();
  m_WorldToViewTransformation = m_ProjectionTransformation * m_CameraTransformation;
  auto transform = camera->GetParent().lock()->has(Transform);
  if (transform.expired())
    m_ViewPos = glm::vec3(0.0f);
  else
    m_ViewPos = transform.lock()->GetPosition(), 1.0f;
  return 0;
}

/******************************************************************************/
/*!
          InitializedUpdate

\author   John Salguero

\brief    The Update function after the device is properly initialized

\param    dt
          The delta in time since last game tick

\return   void
*/
/******************************************************************************/
void OpenGLDevice::InitializedUpdate(double)
{
}

/******************************************************************************/
/*!
          DoNothing

\author   John Salguero

\brief    The update function before the device is initialized.

\param    double
          The delta in time since last game tick(ignored)

\return   void
*/
/******************************************************************************/
void OpenGLDevice::DoNothing(double)
{
}

/******************************************************************************/
/*!
          Update

\author   John Salguero

\brief    The function called every game tick. uses a function pointer to stop
          using an if check every game tick

\param    dt
          The delta in time since last game tick

\return   void
*/
/******************************************************************************/
void OpenGLDevice::Update(double dt)
{
  (this->*m_UpdateFxn)(dt);
}

/******************************************************************************/
/*!
          Initialize

\author   John Salguero

\brief    Given a WindowCreatedData pointer, initializes the glDevice.

\param    msgData
          The Data that comes with window creation

\param    system
          The Graphics System that takes care of the resources

\return   void
*/
/******************************************************************************/
bool OpenGLDevice::Initialize
(std::shared_ptr<WindowCreatedData> const& msgData)
{
  // Create the context
  CreateContext(msgData);
  // Set up the viewport
  CreateViewport(msgData);
  // Create Universal Buffers
  CreateBuffers();
  // Initialize the texture map lookup table
  InitializeTextureMap();
  // Register the message listener for resized Windows
  RegisterListeners();
  // Set the update function
  m_UpdateFxn = &OpenGLDevice::InitializedUpdate;
  return true;
}

/******************************************************************************/
/*!
          Release

\author   John Salguero

\brief    Releases the resources held by the glDevice.

\return   the error code caused by release. 0 is a success
*/
/******************************************************************************/
int OpenGLDevice::Release()
{
  for (auto const& program : m_ShaderPrograms)
    glDeleteProgram(program.second);
  glDeleteBuffers(1, m_matVBO);
  glDeleteBuffers(1, m_boneVBO);
  SDL_GL_DeleteContext(m_glContext);
  UnRegisterClassListener(MessageType::WindowResized, OpenGLDevice, &OpenGLDevice::HandleWindowResize);
  return 0;
}

/******************************************************************************/
/*!
          CreateContext

\author   John Salguero

\brief    Creates the openGL Context

\return   
*/
/******************************************************************************/
void OpenGLDevice::CreateContext(std::shared_ptr<WindowCreatedData> const& msgData)
{
  // Create an OpenGL context
  m_glContext = SDL_GL_CreateContext(msgData->GetWindow());
  FATAL_ERRORIF(!m_glContext, std::string("OpenGL Context could not be created ") + SDL_GetError());

  // Initialize GLEW (OpenGL Extension Wrangler)
  glewExperimental = GL_TRUE;
  FATAL_ERRORIF(glewInit(), "GLEW Failed to initialize");

  // Enable the Stencil Buffer
  //glEnable(GL_STENCIL_TEST);

  // Enable Depth Testing
  glEnable(GL_DEPTH_TEST);

  // Print OpenGL version
  DEBUG_POPUP(std::string("OpenGL version: ") + reinterpret_cast<const char*>(glGetString(GL_VERSION)));
}

/******************************************************************************/
/*!
          CreateViewport

\author   John Salguero

\brief    Creates the Viewport used to render to the window

\param    msgData
          The message holding the data from the created Window 

\param    system
          The Graphics System that is using the device

\return   void
*/
/******************************************************************************/
void OpenGLDevice::CreateViewport(std::shared_ptr<WindowCreatedData> const& msgData)
{
  // Set up the viewport
  int width, height;
  SDL_GL_GetDrawableSize(msgData->GetWindow(), &width, &height);
  glViewport(0, 0, width, height);
  glEnable(GL_CULL_FACE);
}

/******************************************************************************/
/*!
          CreateBuffers

\author   John Salguero

\brief    Creates the univeral buffers used for rendering

\return   the error code caused by comiliation. 0 is a success
*/
/******************************************************************************/
void OpenGLDevice::CreateBuffers()
{
  // Create the VBO that will define transformation Instanced Drawing
  glCreateBuffers(1, m_matVBO);
  // Create the VBO that will define bone transformations Drawing
  glCreateBuffers(1, m_boneVBO);
  // Create the UBO that will define the uniform for materials
  glCreateBuffers(1, m_materialUBO);
  // Allocate size for the UBOs
  glBindBuffer(GL_UNIFORM_BUFFER, m_materialUBO[0]);
  glBufferData(GL_UNIFORM_BUFFER, sizeof(MaterialBuffer) * MAX_MATERIALS, nullptr, GL_DYNAMIC_DRAW);
}

/******************************************************************************/
/*!
          RegisterListeners

\author   John Salguero

\brief    Registers the message liseners for the class

\return   void

/******************************************************************************/
void OpenGLDevice::RegisterListeners()
{
  RegisterClassListener(MessageType::WindowResized, OpenGLDevice, &OpenGLDevice::HandleWindowResize);
}

/******************************************************************************/
/*!
          LoadShaderProgram

\author   John Salguero

\brief    Loads in, compiles, and links a program for the meshes

\param    flags
          the flags used to identify the shader

\return   the error code caused by comiliation. 0 is a success
*/
/******************************************************************************/
GLuint OpenGLDevice::LoadShaderProgram(ShaderFlags flags)
{
  std::wstring fragShader, vertShader;
  std::string vertShaderCode, fragShaderCode;
  GLuint vertShaderID, fragShaderID;
  GLuint programID;

  if (flags & ANIMATION_FLAG)
    vertShader = L"Animation.vert";
  else
    vertShader = L"Non-Anim.vert";
  flags &= ~(ANIMATION_FLAG | TRANSPARENCY_FLAG);
  fragShader = std::to_wstring(flags) + L".frag";
  
  vertShaderCode = ReadShaderCode(SHADER_DIRECTORY + vertShader);
  fragShaderCode = ReadShaderCode(SHADER_DIRECTORY + fragShader);

  vertShaderID = CompileShader(GL_VERTEX_SHADER, vertShaderCode);
  fragShaderID = CompileShader(GL_FRAGMENT_SHADER, fragShaderCode);

  programID = LinkShaderProgram(vertShaderID, fragShaderID);

  glDeleteShader(vertShaderID);
  glDeleteShader(fragShaderID);

  return programID;
}

/******************************************************************************/
/*!
          ReadShaderCode

\author   John Salguero

\brief    Loads in a shader from a file and returns the code in string format

\param    filePath
          location of the shader

\return   the error code caused by comiliation. 0 is a success
*/
/******************************************************************************/
std::string OpenGLDevice::ReadShaderCode(fs::path const& filePath)
{
  std::ifstream file(filePath);
  FATAL_ERRORIF(!file, "Failed to open shader file: " + filePath.string());

  std::stringstream buffer;
  buffer << file.rdbuf();
  file.close();
  return buffer.str();
}

/******************************************************************************/
/*!
          CompileShader

\author   John Salguero

\brief    Compiles shader code to a shader object

\param    shaderType
          GLenum identifying the typs of shader
          
\param    shaderCode
          entire code of the shader in string format

\return   the error code caused by comiliation. 0 is a success
*/
/******************************************************************************/
GLuint OpenGLDevice::CompileShader(GLenum shaderType, const std::string& shaderCode)
{
  GLuint shader = glCreateShader(shaderType);
  const char* codePtr = shaderCode.c_str();
  glShaderSource(shader, 1, &codePtr, nullptr);
  glCompileShader(shader);

  // Check for compilation errors
  GLint success;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    GLchar infoLog[512];
    glGetShaderInfoLog(shader, 512, nullptr, infoLog);
    FATAL_ERROR(std::string("Failed to compile shader:\n") + infoLog);
  }

  return shader;
}

/******************************************************************************/
/*!
          LinkShaderProgram

\author   John Salguero

\brief    Compiles shader code to a shader object

\param    shaderType
          GLenum identifying the typs of shader

\param    shaderCode
          entire code of the shader in string format

\return   the error code caused by comiliation. 0 is a success
*/
/******************************************************************************/
GLuint OpenGLDevice::LinkShaderProgram(GLuint vertexShader, GLuint fragmentShader)
{
  GLuint program = glCreateProgram();
  glAttachShader(program, vertexShader);
  glAttachShader(program, fragmentShader);
  glLinkProgram(program);

  // Check for linking errors
  GLint success;
  glGetProgramiv(program, GL_LINK_STATUS, &success);
  if (!success) {
    GLchar infoLog[512];
    glGetProgramInfoLog(program, 512, nullptr, infoLog);
    FATAL_ERROR(std::string("Failed to compile shader:\n") + infoLog);
    return 0;
  }

  return program;
}

/******************************************************************************/
/*!
          GetTransform

\author   John Salguero

\brief    Given a Renderable and a reference to a mat4, populates the mat4 with
          World Transformation of the Renderable

\param    renderable
          Renderable to get Transformation Data from

\param    transOut
          The transformation data calculated

\return   The mat4 calculated
*/
/******************************************************************************/
glm::mat4& OpenGLDevice::GetTransform(std::shared_ptr<Renderable> const& renderable, glm::mat4& transOut) const
{
  auto transform = renderable->GetParent().lock()->has(Transform);
  if (transform.expired())
    transOut = glm::mat4(1.0f);
  else
    transOut = transform.lock()->GetWorldMatrix();
  transOut = m_WorldToViewTransformation * transOut;

  return transOut;
}

/******************************************************************************/
/*!
          InitializeTextureMap

\author   John Salguero

\brief    Initializes the texture map used to find texture locations

\return   void
*/
/******************************************************************************/
void OpenGLDevice::InitializeTextureMap()
{
  m_TextureLocationMap[1 << 0] = "diffuseTex";
  m_TextureLocationMap[1 << 1] = "emissiveTex";
  m_TextureLocationMap[1 << 2] = "emissiveFactorTex";
  m_TextureLocationMap[1 << 3] = "ambientTex";
  m_TextureLocationMap[1 << 4] = "ambientFactorTex";
  m_TextureLocationMap[1 << 5] = "diffuseFactorTex";
  m_TextureLocationMap[1 << 6] = "specularTex";
  m_TextureLocationMap[1 << 7] = "normalTex";
  m_TextureLocationMap[1 << 8] = "specularFactorTex";
  m_TextureLocationMap[1 << 9] = "shininessTex";
  m_TextureLocationMap[1 << 10] = "bumpTex";
  m_TextureLocationMap[1 << 11] = "transparencyTex";
  m_TextureLocationMap[1 << 12] = "transparencyFactorTex";
  m_TextureLocationMap[1 << 13] = "reflectionTex";
  m_TextureLocationMap[1 << 14] = "reflectionFactorTex";
  m_TextureLocationMap[1 << 15] = "displacementTex";
  m_TextureLocationMap[1 << 16] = "displacementVectorTex";
}

void OpenGLDevice::HandleWindowResize(std::shared_ptr<Message> const& msg)
{
  auto data = GET_DATA_FROM_MESSAGE(SDL_WindowEvent, msg);
  int width, height;
  SDL_GL_GetDrawableSize(SDL_GetWindowFromID(data->windowID), &width, &height);
  glViewport(0, 0, width, height);
}
