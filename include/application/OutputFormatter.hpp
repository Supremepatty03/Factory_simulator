#pragma once

#include <string>
#include "domain/Event.hpp"

using namespace std;

class OutputFormatter {
public:
    static string start(domain::Time t, domain::ProductId k, domain::TypeId i, domain::MachineId j);
    static string finish(domain::Time t, domain::ProductId k, domain::TypeId i, domain::MachineId j);
    static string ready(domain::Time t, domain::ProductId k, domain::MachineId j);
    static string wait(domain::Time t, domain::ProductId k, domain::TypeId i, domain::MachineId j, int p);
    static string stop(domain::Time t);
};