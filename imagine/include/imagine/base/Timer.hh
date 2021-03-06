#pragma once

/*  This file is part of Imagine.

	Imagine is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	Imagine is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with Imagine.  If not, see <http://www.gnu.org/licenses/> */

#include <imagine/config/defs.hh>
#include <imagine/base/timerDefs.hh>
#include <imagine/base/EventLoop.hh>
#include <imagine/util/bits.h>

#if defined __linux
#include <imagine/base/timer/TimerFD.hh>
#elif defined __APPLE__
#include <imagine/base/timer/CFTimer.hh>
#endif

namespace Base
{

struct Timer : public TimerImpl
{
public:
	enum Flags
	{
		HINT_NONE = 0,
		HINT_REUSE = IG::bit(0) // timer resources should't be de-allocated automatically after firing or from cancel()
	};

	Timer() {}
	void callbackAfterNSec(CallbackDelegate callback, int ns, int repeatNs, EventLoop loop, Flags flags);
	void callbackAfterMSec(CallbackDelegate callback, int ms, int repeatMs, EventLoop loop, Flags flags);
	void callbackAfterSec(CallbackDelegate callback, int s, int repeatS, EventLoop loop, Flags flags);
	void cancel();
	void deinit();

	// shortcuts with no Flags
	void callbackAfterNSec(CallbackDelegate callback, int ns, int repeatNs, EventLoop loop)
	{
		callbackAfterNSec(callback, ns, repeatNs, loop, HINT_NONE);
	}
	void callbackAfterMSec(CallbackDelegate callback, int ms, int repeatMs, EventLoop loop)
	{
		callbackAfterMSec(callback, ms, repeatMs, loop, HINT_NONE);
	}
	void callbackAfterSec(CallbackDelegate callback, int s, int repeatS, EventLoop loop)
	{
		callbackAfterSec(callback, s, repeatS, loop, HINT_NONE);
	}

	// shortcuts for one-shot non-repeating timers
	void callbackAfterNSec(CallbackDelegate callback, int ns, EventLoop loop);
	void callbackAfterMSec(CallbackDelegate callback, int ms, EventLoop loop);
	void callbackAfterSec(CallbackDelegate callback, int s, EventLoop loop);
};

}
