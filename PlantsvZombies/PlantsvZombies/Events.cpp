#include "Events.h"
#include <Windows.h>
namespace Events {
	bool keyDown(unsigned char key) {
		return GetAsyncKeyState(key) >> 15 & 1;
	}
}
