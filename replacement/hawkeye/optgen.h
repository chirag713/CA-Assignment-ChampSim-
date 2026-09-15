#ifndef OPTGEN_H
#define OPTGEN_H

#include <cstddef>
#include <cstdint>
#include <unordered_map>
#include <vector>
using namespace std;

class OPTgen {
public:
    OPTgen(size_t num_sets,
           size_t associativity,
           size_t history_multiplier = 8);

    bool access(size_t set_idx, uint64_t address);

private:
    size_t sets;
    size_t ways;
    size_t history;

    vector<vector<int>> occ;
    vector<uint64_t> time;
    vector<unordered_map<uint64_t, uint64_t>> last;
};

#endif