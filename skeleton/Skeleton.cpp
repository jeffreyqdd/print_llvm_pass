#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/Module.h"
#include "llvm/Pass.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"
#include "llvm/Support/raw_ostream.h"
#include <format>
#include <string>
#include <unordered_set>

using namespace llvm;

namespace {

struct SkeletonPass : public PassInfoMixin<SkeletonPass> {
    size_t cnt = 0;
    PreservedAnalyses run(Module &M, ModuleAnalysisManager &AM) {
        LLVMContext &ctx = M.getContext();

        auto ret_type      = Type::getVoidTy(ctx);
        auto char_type     = Type::getInt8Ty(ctx);
        auto char_ptr_type = PointerType::get(Type::getInt8Ty(ctx), 0);
        auto void_ptr_type = PointerType::get(Type::getInt8Ty(ctx), 0);

        auto int8_type  = Type::getInt8Ty(ctx);
        auto int16_type = Type::getInt16Ty(ctx);
        auto int32_type = Type::getInt32Ty(ctx);
        auto int64_type = Type::getInt64Ty(ctx);

        FunctionCallee trace_call = M.getOrInsertFunction("__trace_call", ret_type, char_ptr_type);

        FunctionCallee trace_i8  = M.getOrInsertFunction("__trace_i8", ret_type, int8_type);
        FunctionCallee trace_i16 = M.getOrInsertFunction("__trace_i16", ret_type, int16_type);
        FunctionCallee trace_i32 = M.getOrInsertFunction("__trace_i32", ret_type, int32_type);
        FunctionCallee trace_i64 = M.getOrInsertFunction("__trace_i64", ret_type, int64_type);

        FunctionCallee trace_char = M.getOrInsertFunction("__trace_char", ret_type, char_type);
        FunctionCallee trace_str  = M.getOrInsertFunction("__trace_str", ret_type, char_ptr_type);

        FunctionCallee trace_any = M.getOrInsertFunction("__trace_any", ret_type, char_ptr_type);
        FunctionCallee trace_end = M.getOrInsertFunction("__trace_end", ret_type, char_ptr_type);

        std::unordered_set<std::string_view> forbidden_functions = {
            "__trace_call", "__trace_i8",  "__trace_i16", "__trace_i32", "__trace_i64",
            "__trace_char", "__trace_str", "__trace_any", "__trace_end",
        };

        for (Function &F : M) {
            // skip to avoid infinite loop
            if (forbidden_functions.contains(F.getName())) {
                continue;
            }
            for (BasicBlock &B : F) {
                for (Instruction &I : B) {
                    if (CallInst *call_instruction = dyn_cast<CallInst>(&I)) {
                        const Function *callee             = call_instruction->getCalledFunction();
                        const std::string_view callee_name = callee->getName();
                        const Type *return_type            = callee->getReturnType();
                        const DebugLoc debug_loc           = call_instruction->getDebugLoc();

                        if (call_instruction->isInlineAsm()) {
                            continue;
                        }

                        if (forbidden_functions.contains(callee_name)) {
                            continue;
                        }

                        // get formatted target
                        std::string trace_target = std::format("{}@no-loc", callee_name);
                        if (debug_loc) {
                            const std::string_view filename = debug_loc->getFilename();
                            const size_t lineno             = debug_loc->getLine();
                            trace_target = std::format("{}@{}:{}", callee_name, filename, lineno);
                        }

                        // start
                        IRBuilder<> builder(call_instruction);
                        Value *trace_target_value = builder.CreateGlobalString(
                            trace_target, std::format("trace_target_{}", cnt++));
                        Value *args[] = {trace_target_value};
                        builder.CreateCall(trace_call, args);

                        // args
                        for (size_t i = 0; i < call_instruction->arg_size(); i++) {
                            Value *argument     = call_instruction->getArgOperand(i);
                            Type *argument_type = argument->getType();

                            if (argument_type->isIntegerTy()) {
                                if (argument_type->getIntegerBitWidth() == 8) {
                                    builder.CreateCall(trace_i8, {argument});
                                } else if (argument_type->getIntegerBitWidth() == 16) {
                                    builder.CreateCall(trace_i16, {argument});
                                } else if (argument_type->getIntegerBitWidth() == 32) {
                                    builder.CreateCall(trace_i32, {argument});
                                } else if (argument_type->getIntegerBitWidth() == 64) {
                                    builder.CreateCall(trace_i64, {argument});
                                } else {
                                    errs() << "any type: " << argument_type << "\n";
                                    builder.CreateCall(trace_any, {});
                                }
                                // check if it's char or char* type
                            } else if (argument_type->isPointerTy()) {
                                builder.CreateCall(trace_str, {argument});
                            } else {
                                errs() << "any type: " << argument_type << "\n";
                                builder.CreateCall(trace_any, {});
                            }
                        }

                        // end
                        builder.CreateCall(trace_end, {});
                    }
                }
            }
        }
        return PreservedAnalyses::all();
    }
};

} // namespace

extern "C" LLVM_ATTRIBUTE_WEAK ::PassPluginLibraryInfo llvmGetPassPluginInfo() {
    return {.APIVersion                   = LLVM_PLUGIN_API_VERSION,
            .PluginName                   = "Skeleton pass",
            .PluginVersion                = "v0.1",
            .RegisterPassBuilderCallbacks = [](PassBuilder &PB) {
                PB.registerPipelineStartEPCallback(
                    [](ModulePassManager &MPM, OptimizationLevel Level) {
                        MPM.addPass(SkeletonPass());
                    });
            }};
}
