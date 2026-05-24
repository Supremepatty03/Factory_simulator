#pragma once

#include <iostream>
#include <queue>
#include <vector>
#include "infrastructure/SimulationConfig.hpp"
#include "domain/Machine.hpp"
#include "domain/Product.hpp"
#include "domain/Event.hpp"

#include "application/MachineSelector.hpp"
using namespace std;

class SimulationEngine {
public:
    explicit SimulationEngine(const SimulationConfig& config);

    void run(ostream& out = cout);

private:
    const SimulationConfig& config_;
    MachineSelector selector_;

    vector<domain::Machine> machines_;
    vector<domain::Product> products_;

    struct EventCompare {
        bool operator()(const domain::Event& a, const domain::Event& b) const {
            if (a.time != b.time) return a.time > b.time;
            return static_cast<int>(a.kind) > static_cast<int>(b.kind);
        }
    };

    priority_queue<domain::Event, vector<domain::Event>, EventCompare> events_;

    void initializeProducts();
    void initializeMachines();
    void startIfPossible(domain::Machine& machine, domain::Time currentTime, ostream& out);
    void processFinishEvent(const domain::Event& e, ostream& out);
    void processStartEvent(const domain::Event& e, ostream& out);
    void processWaitEvent(const domain::Event& e, ostream& out);
    void processReadyEvent(const domain::Event& e, ostream& out);
};