#include "../replacement/hawkeye/predictor.h"

#include <iostream>
#include <cstdint>

int main()
{
    HawkeyePredictor pred;

    uint64_t pc1 = 0x0;
    uint64_t pc2 = 0x2002;

    std::cout << "Before training:\n";
    std::cout << "pc1 counter = " << pred.get_counter(pc1) << "\n";
    std::cout << "pc2 counter = " << pred.get_counter(pc2) << "\n";

    // Train only pc1
    pred.train(pc1, true);
    pred.train(pc1, true);
    pred.train(pc1, true);

    std::cout << "After training pc1 three times:\n";
    std::cout << "pc1 counter = " << pred.get_counter(pc1) << "\n";
    std::cout << "pc2 counter = " << pred.get_counter(pc2) << "\n";
}