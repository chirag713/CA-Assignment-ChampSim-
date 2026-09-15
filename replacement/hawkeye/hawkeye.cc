#include "hawkeye.h"

#include <cstddef>
#include <cstdint>

hawkeye::hawkeye(CACHE* cache)
    : hawkeye(cache, cache->NUM_SET, cache->NUM_WAY)
{
}

hawkeye::hawkeye(CACHE* cache, long num_sets, long num_ways)
    : replacement(cache),
      sets(num_sets),
      ways(num_ways),
      opt(static_cast<size_t>(num_sets),static_cast<size_t>(num_ways)),
      predictor(),
      rrpv(static_cast<size_t>(num_sets),vector<int>(static_cast<size_t>(num_ways), 7)),
      prev_pc(static_cast<size_t>(num_sets))
{
}

void hawkeye::observe_access(long set, champsim::address full_addr, champsim::address ip)
{
    size_t set_idx = static_cast<size_t>(set);
    uint64_t line_addr = full_addr.to<uint64_t>() >> 6;
    uint64_t pc = ip.to<uint64_t>();
    auto& pc_history = prev_pc[set_idx];
    auto it = pc_history.find(line_addr);
    bool opt_hit = opt.access(set_idx, line_addr);
    if (it != pc_history.end()) predictor.train(it->second, opt_hit);
    pc_history[line_addr] = pc;
}

long hawkeye::find_victim(uint32_t triggering_cpu,uint64_t instr_id,long set,const champsim::cache_block* current_set,champsim::address ip,champsim::address full_addr, access_type type){
    size_t set_idx = static_cast<size_t>(set);
    return static_cast<long>(
        ::find_victim(rrpv[set_idx])
    );
}

void hawkeye::replacement_cache_fill(
    uint32_t triggering_cpu,
    long set,
    long way,
    champsim::address full_addr,
    champsim::address ip,
    champsim::address victim_addr,
    access_type type)
{
    size_t set_idx = static_cast<size_t>(set);
    size_t way_idx = static_cast<size_t>(way);
    uint64_t pc = ip.to<uint64_t>();
    bool friendly = predictor.predict(pc);
    Classification cls;
    friendly ? cls = Classification::CACHE_FRIENDLY:cls = Classification::CACHE_AVERSE;
    update_rrpv(rrpv[set_idx],way_idx,cls,false);
}

void hawkeye::update_replacement_state(uint32_t triggering_cpu,long set,long way,champsim::address full_addr,champsim::address ip,champsim::address victim_addr,access_type type,uint8_t hit){
    size_t set_idx = static_cast<size_t>(set);
    size_t way_idx = static_cast<size_t>(way);
    observe_access(set, full_addr, ip);
    if (!hit) return;
    uint64_t pc = ip.to<uint64_t>();
    bool friendly = predictor.predict(pc);
    Classification cls;
    friendly ? cls = Classification::CACHE_FRIENDLY:cls = Classification::CACHE_AVERSE;
    update_rrpv(rrpv[set_idx],way_idx,cls,true);
}