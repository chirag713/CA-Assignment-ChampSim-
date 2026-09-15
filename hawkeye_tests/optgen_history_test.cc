#include "../replacement/hawkeye/optgen.h"
#include <iostream>

int main()
{
    // -------- Case 1: exactly at history boundary --------
    OPTgen opt1(1, 1);  // W = 1, history = 8

    opt1.access(0, 0xA); // time 0

    opt1.access(0, 0x1);
    opt1.access(0, 0x2);
    opt1.access(0, 0x3);
    opt1.access(0, 0x4);
    opt1.access(0, 0x5);
    opt1.access(0, 0x6);
    opt1.access(0, 0x7);

    bool boundary_hit = opt1.access(0, 0xA); // time 8

    std::cout << "distance 8: "
              << (boundary_hit ? "HIT" : "MISS")
              << "\n";


    // -------- Case 2: older than history --------
    OPTgen opt2(1, 1);

    opt2.access(0, 0xA); // time 0

    opt2.access(0, 0x1);
    opt2.access(0, 0x2);
    opt2.access(0, 0x3);
    opt2.access(0, 0x4);
    opt2.access(0, 0x5);
    opt2.access(0, 0x6);
    opt2.access(0, 0x7);
    opt2.access(0, 0x8);

    bool outside_hit = opt2.access(0, 0xA); // time 9

    std::cout << "distance 9: "
              << (outside_hit ? "HIT" : "MISS")
              << "\n";
}