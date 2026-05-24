#pragma once

#include "domain/Types.hpp"

using namespace std;

namespace domain {

enum class EventKind {
    Finish = 0,
    Start = 1,
    Wait = 2,
    Ready = 3,
    Stop = 4
};

struct Event {
    Time time = 0;
    EventKind kind = EventKind::Finish;

    ProductId productId = -1;
    TypeId type = 0;
    MachineId machineId = -1;
    int queuePosition = 0;

    bool operator<(const Event& other) const {
        if (time != other.time) return time > other.time;
        return static_cast<int>(kind) > static_cast<int>(other.kind);
    }
};

} // namespace domain