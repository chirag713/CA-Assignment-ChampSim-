#ifndef RRIP_H
#define RRIP_H

#include <cstddef>
#include <vector>
using namespace std;

enum class Classification {
    CACHE_FRIENDLY,
    CACHE_AVERSE
};

void update_rrpv(vector<int>& rrpv,size_t way,Classification cls,bool is_hit);

size_t find_victim(vector<int>& rrpv);

#endif