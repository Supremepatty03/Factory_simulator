#include "application/MachineSelector.hpp"

#include <limits>

MachineSelector::MachineSelector(const SimulationConfig& config)
    : config_(config) {}

domain::Time MachineSelector::waitTimeForMachine(
    int nextType,
    const domain::Machine& machine,
    domain::Time /*currentTime*/) const
{
    (void)nextType;

    domain::Time sum = 0;
    for (const auto& item : machine.queue) {
        sum += config_.processingTime[item.type][machine.id];
    }
    return sum;
}

int MachineSelector::chooseMachineForType(
    int nextType,
    domain::Time currentTime,
    const std::vector<domain::Machine>& machines) const
{
    int bestMachine = 0;
    domain::Time bestValue = std::numeric_limits<domain::Time>::max();

    for (int j = 0; j < static_cast<int>(machines.size()); ++j) {
        const auto& machine = machines[j];
        const domain::Time value = waitTimeForMachine(nextType, machine, currentTime);

        if (value < bestValue || (value == bestValue && j < bestMachine)) {
            bestValue = value;
            bestMachine = j;
        }
    }

    return bestMachine;
}