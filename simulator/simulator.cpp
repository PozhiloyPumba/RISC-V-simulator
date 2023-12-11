#include <iostream>
#include "hart.h"
#include "virtual_mem.hpp"

namespace simulator {
int Main([[maybe_unused]] int argc, [[maybe_unused]] const char **argv)
{
    mem::VirtualMem *vmem = mem::VirtualMem::CreateVirtualMem();
    uintptr_t entry_point = vmem->StoreElfFile("a.out");
    core::Hart hart(vmem, entry_point);
    hart.RunImpl(core::Hart::Mode::BB);
    return 0;
}
}  // namespace simulator

int main(int argc, const char **argv)
{
    return simulator::Main(argc, argv);
}