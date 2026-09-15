#ifndef PREDICTOR_H
#define PREDICTOR_H

#include <cstddef>
#include <cstdint>
#include <vector>

using namespace std;

class HawkeyePredictor {
public:
    HawkeyePredictor(size_t num_entries = 8192, int counter_bits = 3);

    void train(uint64_t pc, bool opt_hit);

    bool predict(uint64_t pc) const;

    int get_counter(uint64_t pc) const;

private:
    size_t entries;
    int bits;

    int max_counter;
    int threshold;

    vector<int> counters;

    size_t index(uint64_t pc) const;
};

#endif