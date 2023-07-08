////////////////////////////////////////////////////////////////////////////////////////
//
// 저작권 표기 License_ver_3.2
// 본 소스 코드의 소유권은 홍윤기에게 있습니다.
// 어떠한 형태든 기여는 기증으로 받아들입니다.
// 본 소스 코드는 아래 사항에 동의할 경우에 사용 가능합니다.
// 아래 사항에 대해 동의하지 않거나 이해하지 못했을 경우 사용을 금합니다.
// 본 소스 코드를 사용하였다면 아래 사항을 모두 동의하는 것으로 자동 간주 합니다.
// 본 소스 코드의 상업적 또는 비 상업적 이용이 가능합니다.
// 본 소스 코드의 내용을 임의로 수정하여 재배포하는 행위를 금합니다.
// 본 소스 코드의 사용으로 인해 발생하는 모든 사고에 대해서 어떠한 법적 책임을 지지 않습니다.
// 본 소스 코드의 어떤 형태의 기여든 기증으로 받아들입니다.
//
// Home Page : http://cafe.naver.com/yssoperatingsystem
// Copyright 2023. 홍윤기 all right reserved.
//
////////////////////////////////////////////////////////////////////////////////////////

#if defined(__SEGGER_LINKER)

#include <stdarg.h>
#include <stdio.h>
#include <yss/Mutex.h>
#include <drv/peripheral.h>
#include <yss/thread.h>
#include <RTT/SEGGER_RTT.h>

static Mutex gMutex;

int32_t  debug_printf(const char *fmt,...) 
{
	char buffer[128];  
	va_list args;  
	va_start (args, fmt);  
	int32_t  n = vsnprintf(buffer, sizeof(buffer), fmt, args);  
	gMutex.lock();
	SEGGER_RTT_Write(0, buffer, n);  
	gMutex.unlock();
	va_end(args);  
	return n;
}

#endif

#if defined(DEBUG)
#include <__cross_studio_io.h>

extern "C"
{
	void __assert(const char *__expression, const char *__filename, int __line)
	{
		debug_printf("expression = %s / file name = %s / line number = %d\n",  __expression, __filename, __line);
		while(1);
	}
}

#endif
