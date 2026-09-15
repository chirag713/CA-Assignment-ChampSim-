#include "../replacement/hawkeye/optgen.h"

#include <iostream>
#include <vector>
#include <utility>
#include <cstdint>

int main()
{
    // 2 cache sets, each 2-way
    OPTgen opt(2, 2);

    std::vector<std::pair<std::size_t, uint64_t>> accesses = {
        {0, 0xA},   // first A in set 0
        {1, 0xA},   // first A in set 1
        {0, 0xB},   // first B in set 0
        {1, 0xB},   // first B in set 1
        {0, 0xA},   // reuse A in set 0
        {1, 0xA}    // reuse A in set 1
    };

    int hits = 0;

    for (auto& [set_idx, addr] : accesses) {
        bool hit = opt.access(set_idx, addr);

        std::cout << "set=" << set_idx
                  << " addr=" << std::hex << addr << std::dec
                  << " -> " << (hit ? "HIT" : "MISS")
                  << "\n";

        if (hit)
            hits++;
    }

    std::cout << "TOTAL HITS: " << hits << "\n";
}