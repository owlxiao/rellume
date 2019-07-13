/**
 * This file is part of Rellume.
 *
 * (c) 2016-2019, Alexis Engelke <alexis.engelke@googlemail.com>
 *
 * Rellume is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License (LGPL)
 * as published by the Free Software Foundation, either version 2.1 of
 * the License, or (at your option) any later version.
 *
 * Rellume is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with Rellume.  If not, see <http://www.gnu.org/licenses/>.
 */

/**
 * \file
 **/

#ifndef LL_BASIC_BLOCK_H
#define LL_BASIC_BLOCK_H

#include "config.h"
#include "regfile.h"
#include <llvm/IR/BasicBlock.h>


namespace rellume {

class BasicBlock
{
public:
    BasicBlock(llvm::BasicBlock* llvm);

    BasicBlock(BasicBlock&& rhs);
    BasicBlock& operator=(BasicBlock&& rhs);

    BasicBlock(const BasicBlock&) = delete;
    BasicBlock& operator=(const BasicBlock&) = delete;

    void AddInst(LLInstr* inst, LLConfig& cfg);
    void AddToPhis(BasicBlock& pred) {
        AddToPhis(pred.llvmBB, pred.regfile);
    }
    void AddToPhis(llvm::BasicBlock* pred, RegFile& pred_rf);

    llvm::BasicBlock* Llvm() {
        return llvmBB;
    }

private:
    /// The LLVM basic block
    llvm::BasicBlock* llvmBB;

public:
    /// The register file for the basic block
    RegFile regfile;

private:
    /// PHI node containing the value of RIP, used only for the terminating
    /// block.
    llvm::PHINode* phi_rip;

    /// The phi nodes for the registers
    ValueMapGp phis_gp[LL_RI_GPMax];
    /// The phi nodes for the registers
    ValueMapSse phis_sse[LL_RI_XMMMax];

    /// The phi nodes for the flags
    llvm::PHINode* phiFlags[RFLAG_Max];
};

}

#endif