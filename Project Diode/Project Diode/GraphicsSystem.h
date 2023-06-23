#ifndef _GraphicsSystem
#define _GraphicsSystem

// System to handle and maintain the window state
class GraphicsSystem : public System, public std::enable_shared_from_this<GraphicsSystem> {
public:
  // Constructor
  GraphicsSystem(std::wstring& name);

  // Updates the function on a per frame basis
  virtual void Update(double dt);

  // Releases the system and deletes all allocations
  virtual int Release();

  // Initializes the system
  virtual void Initialize();

private:
};


#endif // !_GraphicsSystem

