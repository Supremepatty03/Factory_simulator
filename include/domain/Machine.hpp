#pragma once
#include "Types.hpp"
#include <deque>

using namespace std;

namespace domain {

struct QueueItem {
    ProductId productId = -1;
    TypeId type = 0;
};

struct Machine {
    MachineId id = 0;
    deque<QueueItem> queue;

    bool busy = false;
    ProductId currentProductId = -1;
    TypeId currentProductType = 0;
    Time busyUntil = 0;
};

}