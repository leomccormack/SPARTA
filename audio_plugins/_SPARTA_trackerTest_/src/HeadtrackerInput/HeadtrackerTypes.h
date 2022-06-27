#pragma once

#include <functional>

namespace HeadtrackerTypes {
	enum Source { SOURCE_NATNET, SOURCE_OSC, SOURCE_MIDI };
	typedef std::function<void(Source, float, float, float, float, float, float)> xyzyprCallback;
};