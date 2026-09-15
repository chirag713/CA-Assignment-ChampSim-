#include "predictor.h"

HawkeyePredictor::HawkeyePredictor(size_t num_entries, int counter_bits){
    entries = num_entries;
    bits = counter_bits;
    max_counter = (1 << bits) - 1;
    threshold = 1 << (bits - 1);
    counters.resize(entries, threshold);
}

size_t HawkeyePredictor::index(uint64_t pc) const{
    uint64_t hashed_pc = pc ^ (pc >> 12);
    return hashed_pc % entries;
}

void HawkeyePredictor::train(uint64_t pc, bool opt_hit){
    size_t idx = index(pc);
    if (opt_hit){
        if (counters[idx] < max_counter) counters[idx]++;
    }
    else{
        if (counters[idx] > 0) counters[idx]--;
    }
}

bool HawkeyePredictor::predict(uint64_t pc) const{
    size_t idx = index(pc);
    return counters[idx] >= threshold;
}

int HawkeyePredictor::get_counter(uint64_t pc) const{
    size_t idx = index(pc);
    return counters[idx];
}