#include "stdafx.h"

WindowCreatedData::WindowCreatedData(SDL_Window* window, int width, int height) : m_Window(window), m_Width(width), m_Height(height)
{
}

SDL_Window* WindowCreatedData::GetWindow() const
{
	return m_Window;
}

int WindowCreatedData::GetWidth() const
{
	return m_Height;
}

int WindowCreatedData::GetHeight() const
{
	return m_Width;
}


