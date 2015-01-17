#ifndef LOG_H_
#define LOG_H_

#include <stdio.h>

namespace xeng
{
#ifdef _DEBUG
#define DLOG printf
#else
#define DLOG
#endif
}

#endif