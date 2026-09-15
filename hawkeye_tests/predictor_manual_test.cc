#include "../replacement/hawkeye/predictor.h"

#include <iostream>
#include <cstdint>

int main()
{
    HawkeyePredictor pred;

    uint64_t pc = 0x123456;

    std::cout << "Initial: "
              << pred.get_counter(pc)
              << " predict=" << pred.predict(pc)
              << "\n";

    // Four OPT hits
    for (int i = 1; i <= 4; ++i) {
        pred.train(pc, true);

        std::cout << "After HIT " << i << ": "
                  << pred.get_counter(pc)
                  << " predict=" << pred.predict(pc)
                  << "\n";
    }

    // More hits to test saturation at 7
    for (int i = 0; i < 10; ++i)
        pred.train(pc, true);

    std::cout << "After many HITs: "
              << pred.get_counter(pc)
              << " predict=" << pred.predict(pc)
              << "\n";

    // More misses to test saturation at 0
    for (int i = 0; i < 20; ++i)
        pred.train(pc, false);

    std::cout << "After many MISSes: "
              << pred.get_counter(pc)
              << " predict=" << pred.predict(pc)
              << "\n";
}