#pragma once

#include "Types.hpp"

namespace domain {

enum class ProductState {
    Waiting,
    Processing,
    Finished
};

struct Product {
    ProductId id = -1;
    TypeId type = 0;
    MachineId machine = -1;
    ProductState state = ProductState::Waiting;
};

}