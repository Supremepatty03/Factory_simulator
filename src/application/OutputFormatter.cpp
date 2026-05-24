#include "application/OutputFormatter.hpp"

#include <sstream>
using namespace std;

string OutputFormatter::start(domain::Time t, domain::ProductId k, domain::TypeId i, domain::MachineId j) {
    ostringstream out;
    out << "start " << t << ' ' << k << ' ' << i << ' ' << j;
    return out.str();
}

string OutputFormatter::finish(domain::Time t, domain::ProductId k, domain::TypeId i, domain::MachineId j) {
    ostringstream out;
    out << "finish " << t << ' ' << k << ' ' << i << ' ' << j;
    return out.str();
}

string OutputFormatter::ready(domain::Time t, domain::ProductId k, domain::MachineId j) {
    ostringstream out;
    out << "ready " << t << ' ' << k << ' ' << j;
    return out.str();
}

string OutputFormatter::wait(domain::Time t, domain::ProductId k, domain::TypeId i, domain::MachineId j, int p) {
    ostringstream out;
    out << "wait " << t << ' ' << k << ' ' << i << ' ' << j << ' ' << p;
    return out.str();
}

string OutputFormatter::stop(domain::Time t) {
    ostringstream out;
    out << "stop " << t;
    return out.str();
}