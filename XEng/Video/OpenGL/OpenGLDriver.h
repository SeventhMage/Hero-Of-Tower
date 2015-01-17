#ifndef OPENGL_DRIVER_H_
#define OPENGL_DRIVER_H_

#include "../IVideoDriver.h"

namespace xeng
{
	class OpenGLDriver : public IVideoDriver
	{
	public:
		OpenGLDriver();
		virtual ~OpenGLDriver();

		virtual bool Init(DriverData *pDriverData);
		virtual void Begin(IVideoData *pVideoData);
		virtual void End();
		virtual void Draw();
	};
}

#endif