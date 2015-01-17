#ifndef IVIDEO_DRIVER_H_
#define IVIDEO_DRIVER_H_

#include "DriverData.h"
#include "IVideoData.h"

namespace xeng
{
	class IVideoDriver
	{
	public:
		IVideoDriver(){};
		virtual ~IVideoDriver(){};

		virtual bool Init(DriverData *pDriverData) = 0;

		virtual void Begin(IVideoData *pVideoData) = 0;
		virtual void End() = 0;
		virtual void Draw() = 0;
	};

}


#endif