#include "../replacement/hawkeye/rrip.h"

#include <iostream>
#include <vector>

int main()
{
    // Test insertion
    std::vector<int> rrpv = {2, 2, 2, 2};

    update_rrpv(rrpv, 0, Classification::CACHE_AVERSE, false);
    update_rrpv(rrpv, 1, Classification::CACHE_FRIENDLY, false);

    std::cout << "After insertions: ";

    for (int v : rrpv)
        std::cout << v << " ";

    std::cout << "\n";

    std::size_t victim = find_victim(rrpv);

    std::cout << "Victim: " << victim << "\n";


    // Test aging
    std::vector<int> rrpv2 = {0, 2, 4, 6};

    std::size_t victim2 = find_victim(rrpv2);

    std::cout << "After aging: ";

    for (int v : rrpv2)
        std::cout << v << " ";

    std::cout << "\n";

    std::cout << "Victim: " << victim2 << "\n";
}