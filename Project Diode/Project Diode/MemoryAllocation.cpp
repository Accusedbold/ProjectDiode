#include "stdafx.h"

void* operator new(size_t size) noexcept(false)
{
  return Engine::GetInstance()->m_MemoryManager.BestAllocate(size);
}

void* operator new(size_t size, const std::nothrow_t&) noexcept(true)
{
  try {
    return Engine::GetInstance()->m_MemoryManager.BestAllocate(size);
  }
  catch (std::bad_alloc ex) {
    return nullptr;
  }
}

void* operator new[](size_t size) noexcept(false)
{
  return Engine::GetInstance()->m_MemoryManager.BestAllocate(size);
}

void* operator new[](size_t size, const std::nothrow_t&) noexcept(true)
{
  try {
    return Engine::GetInstance()->m_MemoryManager.BestAllocate(size);
  }
  catch (std::bad_alloc ex) {
    return nullptr;
  }
}

void operator delete(void* ptr) noexcept(true)
{
  Engine::GetInstance()->m_MemoryManager.Deallocate(ptr);
}

void operator delete(void* ptr, const std::nothrow_t&) noexcept(true)
{
  Engine::GetInstance()->m_MemoryManager.Deallocate(ptr);
}

void operator delete[](void* ptr) noexcept(true)
{
  Engine::GetInstance()->m_MemoryManager.Deallocate(ptr);
}

void operator delete[](void* ptr, const std::nothrow_t&) noexcept(true)
{
  Engine::GetInstance()->m_MemoryManager.Deallocate(ptr);
}
