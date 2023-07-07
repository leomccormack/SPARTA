#pragma once

#include "JuceHeader.h"
#include <functional>

class AdHocActionListener : public juce::ActionListener {
public:
	AdHocActionListener();
	AdHocActionListener(std::function<void(const String&)> callback);
	void actionListenerCallback(const String& message) override;
	void setCallback(std::function<void(const String&)> callback);

private:
	std::function<void(const String&)> callback;
};