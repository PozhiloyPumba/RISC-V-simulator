// #include <asmjit/asmjit.h>
#include <cstddef>
#include "compiler/compiler.hpp"
#include "generated/instructions_enum_gen.h"
#include "interpreter/BB.h"
#include "interpreter/gpr.h"
#include "interpreter/instruction.h"
#include "interpreter/executor.h"

namespace simulator::compiler {


void Compiler::run(interpreter::DecodedBB &decodedBB) {
    asmjit::CodeHolder code_holder;
    code_holder.init(runtime_.environment(), runtime_.cpuFeatures());

    asmjit::x86::Compiler compiler_(&code_holder);

    static auto entry_signature = asmjit::FuncSignatureT<void, interpreter::Executor *, const Instruction *>();
    auto *entry_node = compiler_.addFunc(entry_signature);

    executor_p_ = compiler_.newGpq();
    instruction_p_ = compiler_.newGpq();
    entry_node->setArg(0, executor_p_);
    entry_node->setArg(1, instruction_p_);

    auto offset_to_gprf = interpreter::Executor::getOffsetToGprf() +
                                         GPR_file::getOffsetToStartOfRegisters();

    pc_p_ = compiler_.newGpq();
    compiler_.mov(pc_p_, executor_p_);
    compiler_.add(pc_p_, offset_to_gprf + sizeof(Register)*GPR_file::PC);

    registers_p_ = compiler_.newGpq();
    compiler_.mov(registers_p_, executor_p_);
    compiler_.add(registers_p_, offset_to_gprf);

    auto body = decodedBB.getBody();

    for (size_t i = 0; i < body.size(); ++i) {
        if (body[i].inst_id == InstructionId::BB_END_INST) 
            break;
        compileInstr(compiler_, body[i], i);
    }

    compiler_.endFunc();
    compiler_.finalize();
    interpreter::DecodedBB::CompiledEntry entry = nullptr;
    runtime_.add(&entry, &code_holder);
    decodedBB.setCompiledEntry(entry);
    decodedBB.setCompileStatus(interpreter::DecodedBB::CompileStatus::COMPILED);
}

void Compiler::compileInvoke(asmjit::x86::Compiler &compiler, const interpreter::DecodedBB::CompiledEntry executor, size_t instr_offset) {
    auto instr = compiler.newGpq();
    compiler.mov(instr, instruction_p_);
    compiler.add(instr, sizeof(Instruction) * instr_offset);

    static auto executor_signature = asmjit::FuncSignatureT<void, interpreter::Executor *, const Instruction *>();
    asmjit::InvokeNode *invokeNode = nullptr;
    compiler.invoke(&invokeNode, executor, executor_signature);
    invokeNode->setArg(0, executor_p_);
    invokeNode->setArg(1, instr);
}

void Compiler::compileInstr(asmjit::x86::Compiler &compiler, const Instruction &instr, size_t instr_offset) {
    switch (instr.inst_id) {
        case InstructionId::LUI:
            compileInvoke(compiler, interpreter::runInstrIface, instr_offset);
            return;
        case InstructionId::AUIPC:
            compileInvoke(compiler, interpreter::runInstrIface, instr_offset);
            return;
        case InstructionId::JAL:
            compileInvoke(compiler, interpreter::runInstrIface, instr_offset);
            return;
        case InstructionId::JALR:
            compileInvoke(compiler, interpreter::runInstrIface, instr_offset);
            return;
        case InstructionId::BEQ:
            compileInvoke(compiler, interpreter::runInstrIface, instr_offset);
            return;
        case InstructionId::BNE:
            compileInvoke(compiler, interpreter::runInstrIface, instr_offset);
            return;
        case InstructionId::BLT:
            compileInvoke(compiler, interpreter::runInstrIface, instr_offset);
            return;
        case InstructionId::BGE:
            compileInvoke(compiler, interpreter::runInstrIface, instr_offset);
            return;
        case InstructionId::BLTU:
            compileInvoke(compiler, interpreter::runInstrIface, instr_offset);
            return;
        case InstructionId::BGEU:
            compileInvoke(compiler, interpreter::runInstrIface, instr_offset);
            return;
        case InstructionId::LB:
            compileInvoke(compiler, interpreter::runInstrIface, instr_offset);
            return;
        case InstructionId::LH:
            compileInvoke(compiler, interpreter::runInstrIface, instr_offset);
            return;
        case InstructionId::LW:
            compileInvoke(compiler, interpreter::runInstrIface, instr_offset);
            return;
        case InstructionId::LD:
            compileInvoke(compiler, interpreter::runInstrIface, instr_offset);
            return;
        case InstructionId::LBU:
            compileInvoke(compiler, interpreter::runInstrIface, instr_offset);
            return;
        case InstructionId::LHU:
            compileInvoke(compiler, interpreter::runInstrIface, instr_offset);
            return;
        case InstructionId::LWU:
            compileInvoke(compiler, interpreter::runInstrIface, instr_offset);
            return;
        case InstructionId::SB:
            compileInvoke(compiler, interpreter::runInstrIface, instr_offset);
            return;
        case InstructionId::SH:
            compileInvoke(compiler, interpreter::runInstrIface, instr_offset);
            return;
        case InstructionId::SW:
            compileInvoke(compiler, interpreter::runInstrIface, instr_offset);
            return;
        case InstructionId::SD:
            compileInvoke(compiler, interpreter::runInstrIface, instr_offset);
            return;
        case InstructionId::ADDI:
            compileInvoke(compiler, interpreter::runInstrIface, instr_offset);
            return;
        case InstructionId::SLLI:
            compileInvoke(compiler, interpreter::runInstrIface, instr_offset);
            return;
        case InstructionId::SLTI:
            compileInvoke(compiler, interpreter::runInstrIface, instr_offset);
            return;
        case InstructionId::SLTIU:
            compileInvoke(compiler, interpreter::runInstrIface, instr_offset);
            return;
        case InstructionId::XORI:
            compileInvoke(compiler, interpreter::runInstrIface, instr_offset);
            return;
        case InstructionId::SRLI:
            compileInvoke(compiler, interpreter::runInstrIface, instr_offset);
            return;
        case InstructionId::SRAI:
            compileInvoke(compiler, interpreter::runInstrIface, instr_offset);
            return;
        case InstructionId::ORI:
            compileInvoke(compiler, interpreter::runInstrIface, instr_offset);
            return;
        case InstructionId::ANDI:
            compileInvoke(compiler, interpreter::runInstrIface, instr_offset);
            return;
        case InstructionId::ADDIW:
            compileInvoke(compiler, interpreter::runInstrIface, instr_offset);
            return;
        case InstructionId::SLLIW:
            compileInvoke(compiler, interpreter::runInstrIface, instr_offset);
            return;
        case InstructionId::SRLIW:
            compileInvoke(compiler, interpreter::runInstrIface, instr_offset);
            return;
        case InstructionId::SRAIW:
            compileInvoke(compiler, interpreter::runInstrIface, instr_offset);
            return;
        case InstructionId::ADD:
            compileInvoke(compiler, interpreter::runInstrIface, instr_offset);
            return;
        case InstructionId::SLL:
            compileInvoke(compiler, interpreter::runInstrIface, instr_offset);
            return;
        case InstructionId::SLT:
            compileInvoke(compiler, interpreter::runInstrIface, instr_offset);
            return;
        case InstructionId::SLTU:
            compileInvoke(compiler, interpreter::runInstrIface, instr_offset);
            return;
        case InstructionId::XOR:
            compileInvoke(compiler, interpreter::runInstrIface, instr_offset);
            return;
        case InstructionId::SRL:
            compileInvoke(compiler, interpreter::runInstrIface, instr_offset);
            return;
        case InstructionId::OR:
            compileInvoke(compiler, interpreter::runInstrIface, instr_offset);
            return;
        case InstructionId::AND:
            compileInvoke(compiler, interpreter::runInstrIface, instr_offset);
            return;
        case InstructionId::SUB:
            compileInvoke(compiler, interpreter::runInstrIface, instr_offset);
            return;
        case InstructionId::SRA:
            compileInvoke(compiler, interpreter::runInstrIface, instr_offset);
            return;
        case InstructionId::ADDW:
            compileInvoke(compiler, interpreter::runInstrIface, instr_offset);
            return;
        case InstructionId::SUBW:
            compileInvoke(compiler, interpreter::runInstrIface, instr_offset);
            return;
        case InstructionId::SLLW:
            compileInvoke(compiler, interpreter::runInstrIface, instr_offset);
            return;
        case InstructionId::SRLW:
            compileInvoke(compiler, interpreter::runInstrIface, instr_offset);
            return;
        case InstructionId::SRAW:
            compileInvoke(compiler, interpreter::runInstrIface, instr_offset);
            return;
        case InstructionId::FENCE:
            compileInvoke(compiler, interpreter::runInstrIface, instr_offset);
            return;
        case InstructionId::ECALL:
            compileInvoke(compiler, interpreter::runInstrIface, instr_offset);
            return;
        case InstructionId::EBREAK:
            compileInvoke(compiler, interpreter::runInstrIface, instr_offset);
            return;
        case InstructionId::MUL:
            compileInvoke(compiler, interpreter::runInstrIface, instr_offset);
            return;
        case InstructionId::MULH:
            compileInvoke(compiler, interpreter::runInstrIface, instr_offset);
            return;
        case InstructionId::MULHSU:
            compileInvoke(compiler, interpreter::runInstrIface, instr_offset);
            return;
        case InstructionId::MULHU:
            compileInvoke(compiler, interpreter::runInstrIface, instr_offset);
            return;
        case InstructionId::DIV:
            compileInvoke(compiler, interpreter::runInstrIface, instr_offset);
            return;
        case InstructionId::DIVU:
            compileInvoke(compiler, interpreter::runInstrIface, instr_offset);
            return;
        case InstructionId::REM:
            compileInvoke(compiler, interpreter::runInstrIface, instr_offset);
            return;
        case InstructionId::REMU:
            compileInvoke(compiler, interpreter::runInstrIface, instr_offset);
            return;
        case InstructionId::MULW:
            compileInvoke(compiler, interpreter::runInstrIface, instr_offset);
            return;
        case InstructionId::DIVW:
            compileInvoke(compiler, interpreter::runInstrIface, instr_offset);
            return;
        case InstructionId::DIVUW:
            compileInvoke(compiler, interpreter::runInstrIface, instr_offset);
            return;
        case InstructionId::REMW:
            compileInvoke(compiler, interpreter::runInstrIface, instr_offset);
            return;
        case InstructionId::REMUW:
            compileInvoke(compiler, interpreter::runInstrIface, instr_offset);
            return;
        default:
            std::abort();
    }
}

}  // namespace simulator::compiler
