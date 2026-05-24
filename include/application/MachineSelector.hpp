#pragma once

#include <vector>
#include "infrastructure/SimulationConfig.hpp"
#include "domain/Machine.hpp"

using namespace std;

class MachineSelector {
public:
    explicit MachineSelector(const SimulationConfig& config);

    int chooseMachineForType(int nextType,
                             domain::Time currentTime,
                             const vector<domain::Machine>& machines) const;

    domain::Time waitTimeForMachine(int nextType,
                                    const domain::Machine& machine,
                                    domain::Time currentTime) const;

private:
    const SimulationConfig& config_;
};