/******************************************************************/
/*!
	All content (C) John Salguero, all rights reserved.
	Reproduction or disclosure of this file or its contents without the
	prior written consent of John Salguero is prohibited.

	\file    OpenGLDevice.h
	\author  John Salguero
	\date    June 23, 2023
	\brief
		This header file declares the OpenGL Device class, which is
		a class that drives the opengl behavior of the game,
		that is - it executes the low level graphics calls
*/
/********************************************************************/
#ifndef OpenGLDevice_H
#define OpenGLDevice_H

#define VIEW_BINDING_POINT 1

// forward Declarations
class GraphicsSystem;
struct RenderableComparator;

class OpenGLDevice {

	using UpdateFxn = void (OpenGLDevice::*)(double);

	// called after being initialized
	void InitializedUpdate(double dt);
	// Called when uninitialized
	void DoNothing(double dt);

public:
	// Draws a Renderable to the current buffer
	int DrawRenderable(std::shared_ptr<Renderable> const& renderable);
	// Draws a TransparentRenderable to the current buffer
	int DrawTransparentRenderable(std::shared_ptr<Renderable> const& renderable);
	// Draws a Batch of Renderables to the current Buffer
	int DrawBatchedRenderables(std::multiset<std::shared_ptr<Renderable>, RenderableComparator> const&);
	// Draws Renderables in the order given, switching between shaders
	int DrawTransparentRenderables(std::multimap<float, std::shared_ptr<Renderable>> const& vecRenderabls);
	// Draws the current set skymap
	int DrawSkyMap(std::shared_ptr<Camera> const&);
	// Switches between the different shaders
	int SetShaderProgram(ShaderFlags flags);
	// Switches between buffers to draw on
	int SetBuffer(GLuint id);
	// Populates the Material Uniform based on the mesh
	int SetMaterials(Mesh const&);
	// Gets the stats from the camera, like position, width, fov, etc
	int SetCamera(std::shared_ptr<Camera> const&);
	// Called to update it every game tick
	void Update(double dt);
	// Used to initialize the device
	bool Initialize(std::shared_ptr<WindowCreatedData> const& data);
	// Used to Release all resources it owns
	int Release();

private:
	// Create the openGL Context
	void CreateContext(std::shared_ptr<WindowCreatedData> const& msgData);
	// Create the Viewport
	void CreateViewport(std::shared_ptr<WindowCreatedData> const& msgData);
	// Create Buffers Used
	void CreateBuffers();
	// Register Listeners for messages
	void RegisterListeners();
	// Retrieves, Compiles, and Links a Shader Program
	GLuint LoadShaderProgram(ShaderFlags flags);
	// Reads in the code from a shader
	std::string ReadShaderCode(fs::path const& filePath);
	// compiles the shader code
	GLuint CompileShader(GLenum shaderType, const std::string& shaderCode);
	// Links the shader code
	GLuint LinkShaderProgram(GLuint vertexShader, GLuint fragmentShader);
	// Get The current Transform From Model space to projection from renderable and Model World Transform
	glm::mat4& GetMWVPTransform(std::shared_ptr<Component> const&, glm::mat4& mwvpOut, glm::mat4& mwOut) const;
	// Set the Attribute for the Matrix Transformatioins
	void SetMWVP(std::vector<glm::mat4> const&, int divisor);
	// Initializes the map that allows for finding the right texture location
	void InitializeTextureMap();
	// Handles the window resize event
	void HandleWindowResize(std::shared_ptr<Message> const&);

	// the current state of the device - will only draw certain flags
	ShaderFlags m_CurrentFlags = UNUSED_FLAGS;
	// The function used to update the device
	UpdateFxn m_UpdateFxn = &OpenGLDevice::DoNothing;
	// the openGL Context
	SDL_GLContext m_glContext;
	// The current Camera Transformation
	glm::mat4 m_CameraTransformation;
	// the current Projection Transformation
	glm::mat4 m_ProjectionTransformation;
	// the current World to View Matrix
	glm::mat4 m_WorldToViewTransformation;
	// The Current View Pos
	glm::vec3 m_ViewPos;
	// Map of the shaders programs
	std::unordered_map<ShaderFlags, GLuint> m_ShaderPrograms;
	// VBO for Instanced Matrix Transformations
	GLuint m_matVBO[1] = { 0 };
	// VBO for Bone Matrix Transformations
	GLuint m_boneVBO[1] = { 0 };
	// UBO for Materials
	GLuint m_materialUBO[MAX_MATERIALS] = { 0 };
	// mesh for skyboxes
	Mesh m_skyMesh;
	// Map used to get the correct location of texture maps
	std::unordered_map<ShaderFlags, const char*> m_TextureLocationMap;
};

#endif