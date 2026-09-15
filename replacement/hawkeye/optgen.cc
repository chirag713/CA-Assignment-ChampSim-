#include "optgen.h"

OPTgen::OPTgen(size_t num_sets, size_t associativity, size_t history_multiplier){
    sets = num_sets;
    ways = associativity;
    history = history_multiplier * associativity;
    occ.resize(sets);
    time.resize(sets);
    last.resize(sets);
    for (size_t i = 0; i < sets; i++){
        occ[i].resize(history, 0);
        time[i] = 0;
    }
}

bool OPTgen::access(size_t idx, uint64_t address){
    uint64_t now = time[idx];
    auto &history_map = last[idx];
    bool hit = false;
    auto it = history_map.find(address);
    if (it != history_map.end()){
        uint64_t previous = it->second;
        uint64_t distance = now - previous;
        if (distance <= history){
            hit = true;
            for (uint64_t t = previous; t < now; t++){
                size_t pos = t % history;
                if (occ[idx][pos] >= static_cast<int>(ways)){
                    hit = false;
                    break;
                }
            }
            if (hit){
                for (uint64_t t = previous; t < now; t++){
                    size_t pos = t % history;
                    occ[idx][pos]++;
                }
            }
        }
    }
    history_map[address] = now;
    occ[idx][now % history] = 0;
    time[idx]++;
    return hit;
}