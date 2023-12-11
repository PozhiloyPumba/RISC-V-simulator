#ifndef INTERPRETER_FETCH_H
#define INTERPRETER_FETCH_H

#include "configs/macros.hpp"
#include "memory/includes/virtual_mem.hpp"
#include "gpr.h"
#include "interpreter/BB.h"

namespace simulator::interpreter {

class Fetch final {
public:
    Fetch(mem::VirtualMem *vmem) : vmem_(vmem) {};
    NO_COPY_SEMANTIC(Fetch)
    NO_MOVE_SEMANTIC(Fetch)

    [[nodiscard]] inline uint32_t loadInstr(Register PC_)
    {
        return vmem_->LoadFourBytesFast(uintptr_t(PC_));
    };

    inline void loadBB(Register PC_, BB &bb)
    {
        bb.clear();
        for (size_t i = 0; i < BB::MAX_SIZE; ++i) {
            uint32_t raw_instr = vmem_->LoadFourBytesFast(uintptr_t(PC_ + i * 4));

            auto opcode = raw_instr & OPCODE_MASK;
            [[unlikely]] if (bb.add_instr(raw_instr) && ((opcode == 99) || (opcode == 103) || (opcode == 111)))
                // jal jalr branches (end BB)
                break;
        }
    };

private:
    mem::VirtualMem *vmem_;
};

}  // namespace simulator::interpreter

#endif