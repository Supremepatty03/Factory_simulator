#include "application/SimulationEngine.hpp"

#include <algorithm>
#include <iostream>
#include <utility>

#include "application/OutputFormatter.hpp"

SimulationEngine::SimulationEngine(const SimulationConfig& config)
    : config_(config), selector_(config) {}

void SimulationEngine::initializeMachines() {
    machines_.clear();
    machines_.resize(config_.N);
    for (int j = 0; j < config_.N; ++j) {
        machines_[j].id = j;
    }
}

void SimulationEngine::initializeProducts() {
    products_.clear();

    domain::ProductId id = 0;
    for (int j = 0; j < config_.N; ++j) {
        for (domain::TypeId type : config_.initialQueues[j]) {
            domain::Product p;
            p.id = id++;
            p.type = type;
            p.machine = j;
            p.state = domain::ProductState::Waiting;
            products_.push_back(p);

            machines_[j].queue.push_back({p.id, p.type});
        }
    }
}

void SimulationEngine::startIfPossible(domain::Machine& machine, domain::Time currentTime, std::ostream& out) {
    if (machine.busy || machine.queue.empty()) {
        return;
    }

    const auto item = machine.queue.front();
    machine.queue.pop_front();

    machine.busy = true;
    machine.currentProductId = item.productId;
    machine.currentProductType = item.type;
    machine.busyUntil = currentTime + config_.processingTime[item.type][machine.id];

    out << OutputFormatter::start(currentTime, item.productId, item.type, machine.id) << '\n';

    events_.push(domain::Event{
        machine.busyUntil,
        domain::EventKind::Finish,
        item.productId,
        item.type,
        machine.id,
        0
    });
}

void SimulationEngine::processFinishEvent(const domain::Event& e, std::ostream& out) {
    out << OutputFormatter::finish(e.time, e.productId, e.type, e.machineId) << '\n';

    auto& machine = machines_[e.machineId];
    machine.busy = false;
    machine.currentProductId = -1;
    machine.currentProductType = 0;
    machine.busyUntil = e.time;

    if (e.type == config_.M - 2) {
        events_.push(domain::Event{
            e.time,
            domain::EventKind::Ready,
            e.productId,
            static_cast<domain::TypeId>(config_.M - 1),
            e.machineId,
            0
        });
    } else {
        const int nextType = e.type + 1;
        const int selected = selector_.chooseMachineForType(nextType, e.time, machines_);
        auto& target = machines_[selected];

        const int p = static_cast<int>(target.queue.size());

        events_.push(domain::Event{
            e.time,
            domain::EventKind::Wait,
            e.productId,
            static_cast<domain::TypeId>(nextType),
            selected,
            p
        });

        target.queue.push_back({
            e.productId,
            static_cast<domain::TypeId>(nextType)
        });

        if (!target.busy) {
            events_.push(domain::Event{
                e.time,
                domain::EventKind::Start,
                e.productId,
                static_cast<domain::TypeId>(nextType),
                selected,
                0
            });
        }
    }

    if (!machine.queue.empty()) {
        events_.push(domain::Event{
            e.time,
            domain::EventKind::Start,
            -1,
            0,
            e.machineId,
            0
        });
    }
}

void SimulationEngine::processStartEvent(const domain::Event& e, std::ostream& out) {
    auto& machine = machines_[e.machineId];
    if (machine.busy || machine.queue.empty()) {
        return;
    }

    const auto item = machine.queue.front();
    machine.queue.pop_front();

    machine.busy = true;
    machine.currentProductId = item.productId;
    machine.currentProductType = item.type;
    machine.busyUntil = e.time + config_.processingTime[item.type][machine.id];

    out << OutputFormatter::start(e.time, item.productId, item.type, machine.id) << '\n';

    events_.push(domain::Event{
        machine.busyUntil,
        domain::EventKind::Finish,
        item.productId,
        item.type,
        machine.id,
        0
    });
}

void SimulationEngine::processWaitEvent(const domain::Event& e, std::ostream& out) {
    out << OutputFormatter::wait(e.time, e.productId, e.type, e.machineId, e.queuePosition) << '\n';
}

void SimulationEngine::processReadyEvent(const domain::Event& e, std::ostream& out) {
    out << OutputFormatter::ready(e.time, e.productId, e.machineId) << '\n';
}

void SimulationEngine::run(std::ostream& out) {
    initializeMachines();
    initializeProducts();

    for (int j = 0; j < config_.N; ++j) {
        if (!machines_[j].queue.empty()) {
            events_.push(domain::Event{
                0,
                domain::EventKind::Start,
                machines_[j].queue.front().productId,
                machines_[j].queue.front().type,
                j,
                0
            });
        }
    }

    domain::Time lastTime = 0;

    while (!events_.empty()) {
        const auto e = events_.top();
        events_.pop();

        lastTime = std::max(lastTime, e.time);

        switch (e.kind) {
            case domain::EventKind::Finish:
                processFinishEvent(e, out);
                break;
            case domain::EventKind::Start:
                processStartEvent(e, out);
                break;
            case domain::EventKind::Wait:
                processWaitEvent(e, out);
                break;
            case domain::EventKind::Ready:
                processReadyEvent(e, out);
                break;
            case domain::EventKind::Stop:
                break;
        }
    }

    out << OutputFormatter::stop(lastTime) << '\n';
}