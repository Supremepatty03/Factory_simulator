#pragma once

#include <vector>
#include <string>
#include "../domain/Types.hpp"

using namespace std;

struct SimulationConfig {
    int M = 0;
    int N = 0;

    // T[i][j] = время операции i на станке j
    vector<vector<domain::Time>> processingTime;

    // initialQueues[j] = список типов изделий в очереди станка j
    vector<vector<domain::TypeId>> initialQueues;

    // Сюда позже можно добавить уже готовые изделия с их id
};