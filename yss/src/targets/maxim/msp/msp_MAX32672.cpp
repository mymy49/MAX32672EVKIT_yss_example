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

#include <drv/peripheral.h>

#if defined(MAX32672)

#include <config.h>
#include <yss/reg.h>

#include <yss/instance.h>

void __WEAK initializeSystem(void)
{
	using namespace define::clock;

	// 클록의 내부 값들을 초기화 하기 위해 무조건 호출한다.
	clock.initialize();

	// OVR 설정을 이곳에 추가
	// 이 설정에서 SYS_OSC를 INRO로 변경함
	clock.setOperatingVoltageRange(ovr::V_CORE_0_9V);

	// 외부 크리스탈 활성화 설정
	// 기본적으로 MAX32672는 100MHz가 기본 클럭 소스로 활성화되어 기본 클럭으로 동작중이다.
	// 그러므로 외부 클럭 설정은 옵션이다.
	//clock.enableErfo(ERFO_CLOCK_FREQ);

	// IBRO 클럭 활성화 설정
	clock.enableIbro();

	// ERTCO(32.768 kHz) 클럭 활성화 설정
	clock.enableErtco();
	
	// SYS_OSC 클럭 소스 변경
	// 리셋 후, 기본 클럭 소스가 IPO이다. 
	// 그러나 FLASH WAIT STATE 업데이트를 위해 IPO를 그대로 사용하더라도 한번 호출해줘야 한다.
	clock.setSysclk(sysclk::src::IBRO, sysclk::div::DIV_1);

	// 캐시를 활성화 한다.
	clock.enableCache();
}

void __WEAK initializeDma(void)
{

}

extern "C"
{
void __WEAK SystemCoreClockUpdate(void)
{

}
}

#endif