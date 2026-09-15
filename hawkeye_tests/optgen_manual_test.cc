#include "../replacement/hawkeye/optgen.h"

#include <iostream>
#include <vector>
#include <utility>
#include <cstdint>

int main()
{
    // 1 cache set, 2-way associativity
    OPTgen opt(1, 2);

    // Sequence: A B A C B A D C
    std::vector<std::pair<std::size_t, uint64_t>> accesses = {
        {0, 0xA},
        {0, 0xB},
        {0, 0xA},
        {0, 0xC},
        {0, 0xB},
        {0, 0xA},
        {0, 0xD},
        {0, 0xC}
    };

    int hits = 0;

    for (auto& [set_idx, addr] : accesses) {
        bool hit = opt.access(set_idx, addr);

        std::cout << std::hex << addr << std::dec
                  << ": " << (hit ? "HIT" : "MISS") << "\n";

        if (hit)
            hits++;
    }

    std::cout << "TOTAL HITS: " << hits << "\n";
}