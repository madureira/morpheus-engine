#pragma once

#include "../Event.h"

namespace Morpheus {

	class WindowResizeEvent : public Event {
	private:
		int m_Width;
		int m_Height;

	public:
		WindowResizeEvent(int width, int height)
		{
			this->m_Width = width;
			this->m_Height = height;
		}

		int GetWidth() const
		{
			return this->m_Width;
		}

		int GetHeight() const
		{
			return this->m_Height;
		}
	};
}
