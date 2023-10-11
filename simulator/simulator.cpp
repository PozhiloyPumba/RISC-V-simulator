#include <iostream>
#include "hart.h"
#include "virtual_mem.hpp"

namespace simulator {
int Main(int argc, const char **argv)
{
    if (argc != 2)
        return -1;

    mem::VirtualMem *vmem = mem::VirtualMem::CreateVirtualMem();
    uintptr_t entry_point = vmem->LoadElfFile(argv[1]);
    core::Hart hart(vmem, entry_point);
    hart.RunImpl();
    mem::VirtualMem::Destroy(vmem);
    return 0;
}
}  // namespace simulator

int main(int argc, const char **argv)
{
    return simulator::Main(argc, argv);
}