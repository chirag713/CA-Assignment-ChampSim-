#include "rrip.h"

namespace {
    constexpr int MAX_RRPV = 7;
    constexpr int MAX_FRIENDLY_RRPV = 6;
}

void update_rrpv(vector<int>& rrpv,size_t way,Classification cls,bool is_hit){
    if (cls == Classification::CACHE_AVERSE){
        rrpv[way] = MAX_RRPV;
        return;
    }
    rrpv[way] = 0;
    if (!is_hit){
        for (size_t i = 0; i < rrpv.size(); i++){
            if (i != way && rrpv[i] < MAX_FRIENDLY_RRPV) rrpv[i]++;
        }
    }
}

size_t find_victim(vector<int>& rrpv){
    while (true){
        for (size_t i = 0; i < rrpv.size(); i++){
            if (rrpv[i] == MAX_RRPV) return i;
        }
        for (int& value : rrpv){
            if (value < MAX_RRPV) value++;
        }
    }
}