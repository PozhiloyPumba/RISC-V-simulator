#ifndef INTERPRETER_HART_H
#define INTERPRETER_HART_H

#include "macros.hpp"
#include "virtual_mem.hpp"
#include "interpreter/fetch.h"
#include "interpreter/decoder.h"
#include "interpreter/executor.h"
#include "interpreter/BB.h"

namespace simulator::core {

class Hart final {
public:
    enum class Mode { SIMPLE, BB };

    void RunImpl(Mode mode);

    Hart(mem::VirtualMem *vmem, uintptr_t entry_point) : vmem_(vmem), fetch_(vmem), executor_(vmem_, entry_point) {};
    NO_COPY_SEMANTIC(Hart)
    NO_MOVE_SEMANTIC(Hart)

private:
    mem::VirtualMem *vmem_;
    interpreter::Fetch fetch_;
    interpreter::Decoder decoder_;
    interpreter::Executor executor_;
};

}  // namespace simulator::core

#endif