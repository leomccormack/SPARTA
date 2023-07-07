#include "AdHocActionListener.h"

AdHocActionListener::AdHocActionListener()
    : AdHocActionListener([this](const String& message) { /* do nothing */ })
{
}

AdHocActionListener::AdHocActionListener(std::function<void(const String&)> callback) {
    setCallback(callback);
}

void AdHocActionListener::setCallback(std::function<void(const String&)> callback) {
    this->callback = callback;
}

void AdHocActionListener::actionListenerCallback(const String& message) {
    this->callback(message);
}
