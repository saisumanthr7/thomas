#pragma once
#include <string>
#include "EventType.h"

class Observer {
public:
    virtual ~Observer() {}
    virtual void onNotify(EventType event) = 0;
};