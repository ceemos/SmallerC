/*
Copyright (c) 2013 Marcel Schneider (Hapra CPU codegen)
Based on MIPS codegen:
Copyright (c) 2012-2013, Alexey Frunze
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met: 

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer. 
2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution. 

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

The views and conclusions contained in the software and documentation are those
of the authors and should not be interpreted as representing official policies, 
either expressed or implied, of the FreeBSD Project.
*/

/*****************************************************************************/
/*                                                                           */
/*                                Smaller C                                  */
/*                                                                           */
/*       A simple and small single-pass C compiler ("small C" class).        */
/*                                                                           */
/*                          HAPRA code generator                             */
/*                                                                           */
/*****************************************************************************/

void GenInit(void)
{
  // initialization of target-specific code generator
  SizeOfWord = 4;
  OutputFormat = FormatSegmented;
  CodeHeader = "\t;.text";
  DataHeader = "\t;.data";
  UseLeadingUnderscores = 0;
}

int GenInitParams(int argc, char** argv, int* idx)
{
#ifndef __SMALLER_C__
  (void)argc;
  (void)argv;
  (void)idx;
#endif
  // initialization of target-specific code generator with parameters
  return 0;
}

void GenInitFinalize(void)
{
  // finalization of initialization of target-specific code generator
}

void GenStartCommentLine(void)
{
  printf2(" ; ");
}

void GenWordAlignment(void)
{
  //printf2("\t.align 2\n");
}

void GenLabel(char* Label)
{
  {
    printf2("%s:\n", Label);
  }
}

void GenExtern(char* Label)
{
  if (OutputFormat != FormatFlat)
  {
    printf2("\t;.extern\t%s\n", Label);
  }
}

void GenPrintLabel(char* Label)
{
  {
    if (isdigit(*Label))
      printf2("lbl%s", Label);
    else
      printf2("%s", Label);
  }
}

void GenNumLabel(int Label)
{
  printf2("lbl%d:\n", Label);
}

void GenPrintNumLabel(int label)
{
  printf2("lbl%d", label);
}

void GenZeroData(unsigned Size)
{
	// TODO: prob. sigend
	for(; Size > 0; Size -= 4) {
		printf2("\t.dw 0\n"); 
	}
}

void GenIntData(int Size, int Val)
{
	Val = truncInt(Val);
	printf2("\t.dw\t%d\n", Val);
	if (Size != 4)
		printf2("\t\t; can't alloc size %d\n", Size);
}

void GenStartAsciiString(void)
{
  printf2("\t.ascii\t");
}

void GenAddrData(int Size, char* Label)
{
  if (Size == 1)
    printf2("\t.byte\t");
  else if (Size == 2)
    printf2("\t.half\t");
  else if (Size == 4)
    printf2("\t.word\t");
  GenPrintLabel(Label); puts2("");
}

#define MipsInstrNop    0x00
#define MipsInstrMov    0x01
#define MipsInstrMfLo   0x02
#define MipsInstrMfHi   0x03
#define MipsInstrMovZ   0x04
#define MipsInstrMovN   0x05
#define MipsInstrLA     0x06
#define MipsInstrLI     0x07
#define MipsInstrLUI    0x08
#define MipsInstrLB     0x09
#define MipsInstrLBU    0x0A
#define MipsInstrLH     0x0B
#define MipsInstrLHU    0x0C
#define MipsInstrLW     0x0D
#define MipsInstrSB     0x0E
#define MipsInstrSH     0x0F
#define MipsInstrSW     0x10
#define MipsInstrAddU   0x11
#define MipsInstrSubU   0x12
#define MipsInstrAnd    0x13
#define MipsInstrOr     0x14
#define MipsInstrXor    0x15
#define MipsInstrNor    0x16
#define MipsInstrSLL    0x17
#define MipsInstrSRL    0x18
#define MipsInstrSRA    0x19
#define MipsInstrMul    0x1A
#define MipsInstrDiv    0x1B
#define MipsInstrDivU   0x1C
#define MipsInstrSLT    0x1D
#define MipsInstrSLTU   0x1E
#define MipsInstrJ      0x1F
#define MipsInstrJAL    0x20
#define MipsInstrBEQ    0x21
#define MipsInstrBNE    0x22
#define MipsInstrBLTZ   0x23
#define MipsInstrBGEZ   0x24
#define MipsInstrBLEZ   0x25
#define MipsInstrBGTZ   0x26
#define MipsInstrBreak  0x27
#define HapraInstrLdi   0x28
#define HapraInstrJmp   0x29
#define HapraInstrJz    0x2A

void GenPrintInstr(int instr, int val)
{
  char* p = "";

#ifndef __SMALLER_C__
  (void)val;
#endif

  switch (instr)
  {
  case MipsInstrNop  : p = "nop"; break;
  case MipsInstrMov  : p = "cp"; break;
  case MipsInstrMfLo : p = "_mflo"; break;
  case MipsInstrMfHi : p = "_mfhi"; break;
  case MipsInstrMovZ : p = "_movz"; break;
  case MipsInstrMovN : p = "_movn"; break;
  case MipsInstrLA   : p = "?la"; break;
  case MipsInstrLI   : p = "?li"; break;
  case MipsInstrLUI  : p = "ldih"; break;
  case MipsInstrLB   : p = "?lb"; break;
  case MipsInstrLBU  : p = "?lbu"; break;
  case MipsInstrLH   : p = "?lh"; break;
  case MipsInstrLHU  : p = "?lhu"; break;
  case MipsInstrLW   : p = "ld"; break;
  case MipsInstrSB   : p = "?sb"; break;
  case MipsInstrSH   : p = "?sh"; break;
  case MipsInstrSW   : p = "st"; break;
  case MipsInstrAddU : p = "add"; break;
  case MipsInstrSubU : p = "sub"; break;
  case MipsInstrAnd  : p = "and"; break;
  case MipsInstrOr   : p = "or"; break;
  case MipsInstrXor  : p = "_xor"; break;
  case MipsInstrNor  : p = "_nor"; break;
  case MipsInstrSLL  : p = "sal"; break;
  case MipsInstrSRL  : p = "_srl"; break;
  case MipsInstrSRA  : p = "sar"; break;
  case MipsInstrMul  : p = "mul"; break;
  case MipsInstrDiv  : p = "_div"; break;
  case MipsInstrDivU : p = "_divu"; break;
  case MipsInstrSLT  : p = "_slt"; break;
  case MipsInstrSLTU : p = "_sltu"; break;
  case MipsInstrJ    : p = "j"; break;
  case MipsInstrJAL  : p = "call"; break;
  case MipsInstrBEQ  : p = "_beq"; break;
  case MipsInstrBNE  : p = "_bne"; break;
  case MipsInstrBLTZ : p = "_bltz"; break;
  case MipsInstrBGEZ : p = "_bgez"; break;
  case MipsInstrBLEZ : p = "_blez"; break;
  case MipsInstrBGTZ : p = "_bgtz"; break;
  case MipsInstrBreak: p = "_break"; break;
  case HapraInstrLdi : p = "ldi"; break;
  case HapraInstrJmp : p = "jmp"; break;
  case HapraInstrJz  : p = "jz"; break;
  }

  printf2("\t%s\t", p);
}

#define MipsOpRegZero                    0x00
#define MipsOpRegAt                      0x01
#define MipsOpRegV0                      0x02
#define MipsOpRegV1                      0x03
#define MipsOpRegA0                      0x04
#define MipsOpRegA1                      0x05
#define MipsOpRegA2                      0x06
#define MipsOpRegA3                      0x07
#define MipsOpRegT0                      0x08
#define MipsOpRegT1                      0x09
#define MipsOpRegT2                      0x0A
#define MipsOpRegT3                      0x0B
#define MipsOpRegT4                      0x0C
#define MipsOpRegT5                      0x0D
#define MipsOpRegT6                      0x0E
#define MipsOpRegT7                      0x0F
#define MipsOpRegS0                      0x10
#define MipsOpRegS1                      0x11
#define MipsOpRegS2                      0x12
#define MipsOpRegS3                      0x13
#define MipsOpRegS4                      0x14
#define MipsOpRegS5                      0x15
#define MipsOpRegS6                      0x16
#define MipsOpRegS7                      0x17
#define MipsOpRegT8                      0x18
#define MipsOpRegT9                      0x19
#define MipsOpRegSp                      0x1D
#define MipsOpRegFp                      0x1E
#define MipsOpRegRa                      0x1F

#define MipsOpIndRegZero                 0x20
#define MipsOpIndRegAt                   0x21
#define MipsOpIndRegV0                   0x22
#define MipsOpIndRegV1                   0x23
#define MipsOpIndRegA0                   0x24
#define MipsOpIndRegA1                   0x25
#define MipsOpIndRegA2                   0x26
#define MipsOpIndRegA3                   0x27
#define MipsOpIndRegT0                   0x28
#define MipsOpIndRegT1                   0x29
#define MipsOpIndRegSp                   0x3D
#define MipsOpIndRegFp                   0x3E
#define MipsOpIndRegRa                   0x3F

#define MipsOpConst                      0x80
#define MipsOpLabel                      0x81
#define MipsOpNumLabel                   0x82
#define MipsOpIndLocal                   MipsOpIndRegFp

void GenPrintOperand(int op, int val)
{
  if (op < MipsOpConst)
  {
    printf2("$%d", op);
  }
  else
  {
    switch (op)
    {
    case MipsOpConst: printf2("%d", truncInt(val)); break;
    case MipsOpLabel: GenPrintLabel(IdentTable + val); break;
    case MipsOpNumLabel: GenPrintNumLabel(val); break;
    default: error("WTF!\n"); break;
    }
  }
}

void GenPrintOperandSeparator(void)
{
  printf2(", ");
}

void GenPrintNewLine(void)
{
  puts2("");
}

void GenPrintInstrNoOperand(int instr)
{
  GenPrintInstr(instr, 0);
  GenPrintNewLine();
}

void GenPrintCallFxn(char* name)
{
  GenPrintInstr(HapraInstrLdi, 0);
  GenPrintOperand(1, 0);
  GenPrintOperandSeparator();
  GenPrintLabel(name);
  GenPrintNewLine();
  GenPrintInstr(MipsInstrJAL, 0);
  GenPrintOperand(31, 0);
  GenPrintOperandSeparator();
  GenPrintOperand(1, 0);
  GenPrintNewLine();
  
  
}

int GenPrepareOperand(int operand, int val) {
	if (operand < MipsOpIndRegZero)
		return operand;
	if (operand == MipsOpConst || operand == MipsOpNumLabel || operand == MipsOpLabel) {
		printf2("\tldi\t$1, ");
		GenPrintOperand(operand, val);
		printf2("\n");
		return 1;
	}
	operand -= MipsOpIndRegZero;
	printf2("\tldi\t$1, %d\n", val);
	printf2("\tadd\t$1, $1, $%d\n", operand);
	return 1;
}

void GenPrintInstr1Operand(int instr, int instrval, int operand, int operandval)
{
  GenPrintInstr(instr, instrval);
  GenPrintOperand(operand, operandval);
  GenPrintNewLine();
}

void GenPrintInstr2Operands(int instr, int instrval, int operand1, int operand1val, int operand2, int operand2val)
{
  if (operand2 == MipsOpConst && operand2val == 0 &&
      (instr == MipsInstrAddU || instr == MipsInstrSubU))
    return;
  
  int realop = GenPrepareOperand(operand2, operand2val);

  GenPrintInstr(instr, instrval);
  GenPrintOperand(operand1, operand1val);
  GenPrintOperandSeparator();
  if (instr == MipsInstrLW || instr == MipsInstrSW) {
	printf2("(");
	GenPrintOperand(realop, 0);
	printf2(")");
  } else {
	GenPrintOperand(realop, 0);
  }
  GenPrintNewLine();
}

void GenPrintInstr3Operands(int instr, int instrval,
                            int operand1, int operand1val,
                            int operand2, int operand2val,
                            int operand3, int operand3val)
{
  if (operand3 == MipsOpConst && operand3val == 0 &&
      (instr == MipsInstrAddU || instr == MipsInstrSubU))
    return;

  int realop = GenPrepareOperand(operand3, operand3val);
  
  GenPrintInstr(instr, instrval);
  GenPrintOperand(operand1, operand1val);
  GenPrintOperandSeparator();
  GenPrintOperand(operand2, operand2val);
  GenPrintOperandSeparator();
  GenPrintOperand(realop, 0);
  GenPrintNewLine();
}

void GenExtendRegIfNeeded(int reg, int opSz)
{
  if (opSz == 1)
  {
    if (CharIsSigned)
    {
      GenPrintInstr3Operands(MipsInstrSLL, 0,
                             reg, 0,
                             reg, 0,
                             MipsOpConst, 24);
      GenPrintInstr3Operands(MipsInstrSRA, 0,
                             reg, 0,
                             reg, 0,
                             MipsOpConst, 24);
    }
    else
    {
      GenPrintInstr3Operands(MipsInstrAnd, 0,
                             reg, 0,
                             reg, 0,
                             MipsOpConst, 0xFF);
    }
  }
}

void GenJumpUncond(int label)
{
	GenPrintInstr(HapraInstrLdi, 0);
	GenPrintOperand(1, 0);
	GenPrintOperandSeparator();
	GenPrintOperand(MipsOpNumLabel, label);
	GenPrintNewLine();
	GenPrintInstr(HapraInstrJmp, 0);
	GenPrintOperand(1, 0);
	GenPrintNewLine();
}

void GenJumpIfNotEqual(int val, int label)
{
  GenPrintInstr2Operands(HapraInstrLdi, 0,
                         MipsOpRegT1, 0,
                         MipsOpConst, val);
  GenPrintInstr2Operands(HapraInstrLdi, 0,
                         MipsOpRegAt, 0,
                         MipsOpNumLabel, label); 
  GenPrintInstr3Operands(MipsInstrSubU, 0,
                         MipsOpRegT1, 0,
                         MipsOpRegT1, 0,
                         MipsOpRegV0, 0);
  GenPrintInstr2Operands(HapraInstrJz, 0,
                         MipsOpRegAt, 0,
                         MipsOpRegT1, 0);
}

void GenJumpIfZero(int label)
{
#ifndef NO_ANNOTATIONS
  printf2(" ; JumpIfZero\n");
#endif
  GenPrintInstr2Operands(HapraInstrLdi, 0,
                         MipsOpRegAt, 0,
                         MipsOpNumLabel, label); 
  GenPrintInstr2Operands(HapraInstrJz, 0,
                         MipsOpRegAt, 0,
                         MipsOpRegV0, 0);
}

int jnzlbl = 0;
void GenJumpIfNotZero(int label)
{
#ifndef NO_ANNOTATIONS
  printf2(" ; JumpIfNotZero\n");
#endif
  printf2("\tldi\t$1, jnz%d\n"
          "\tjz\t$1, $2\n"
          "\tldi\t$1, lbl%d\n"
          "\t jmp\t$1\n"
          "jnz%d:\tnop\n",
          jnzlbl, label, jnzlbl);
  jnzlbl++;
}

void GenFxnProlog(void)
{
  GenPrintInstr3Operands(MipsInstrSubU, 0,
                         MipsOpRegSp, 0,
                         MipsOpRegSp, 0,
                         MipsOpConst, 8);

  GenPrintInstr2Operands(MipsInstrSW, 0,
                         MipsOpRegRa, 0,
                         MipsOpIndRegSp, 4);

  GenPrintInstr2Operands(MipsInstrSW, 0,
                         MipsOpRegFp, 0,
                         MipsOpIndRegSp, 0);

  GenPrintInstr2Operands(MipsInstrMov, 0,
                         MipsOpRegFp, 0,
                         MipsOpRegSp, 0);

  if (CurFxnParamCntMax)
  {
    int i, cnt = CurFxnParamCntMax;
    if (cnt > 4)
      cnt = 4;
    for (i = 0; i < cnt; i++)
      GenPrintInstr2Operands(MipsInstrSW, 0,
                             MipsOpRegA0 + i, 0,
                             MipsOpIndRegFp, 8 + 4 * i);
  }
}

void GenLocalAlloc(int size)
{
  GenPrintInstr3Operands(MipsInstrSubU, 0,
                         MipsOpRegSp, 0,
                         MipsOpRegSp, 0,
                         MipsOpConst, size);
}

void GenFxnEpilog(void)
{
  GenPrintInstr2Operands(MipsInstrMov, 0,
                         MipsOpRegSp, 0,
                         MipsOpRegFp, 0);

  GenPrintInstr2Operands(MipsInstrLW, 0,
                         MipsOpRegFp, 0,
                         MipsOpIndRegSp, 0);

  GenPrintInstr2Operands(MipsInstrLW, 0,
                         MipsOpRegRa, 0,
                         MipsOpIndRegSp, 4);

  GenPrintInstr3Operands(MipsInstrAddU, 0,
                         MipsOpRegSp, 0,
                         MipsOpRegSp, 0,
                         MipsOpConst, 8);

  GenPrintInstr1Operand(MipsInstrJ, 0,
                        MipsOpRegRa, 0);
}

int GenGetBinaryOperatorInstr(int tok)
{
  switch (tok)
  {
  case tokPostAdd:
  case tokAssignAdd:
  case '+':
    return MipsInstrAddU;
  case tokPostSub:
  case tokAssignSub:
  case '-':
    return MipsInstrSubU;
  case '&':
  case tokAssignAnd:
    return MipsInstrAnd;
  case '^':
  case tokAssignXor:
    return MipsInstrXor;
  case '|':
  case tokAssignOr:
    return MipsInstrOr;
  case '<':
  case '>':
  case tokLEQ:
  case tokGEQ:
  case tokEQ:
  case tokNEQ:
  case tokULess:
  case tokUGreater:
  case tokULEQ:
  case tokUGEQ:
    return MipsInstrNop;
  case '*':
  case tokAssignMul:
    return MipsInstrMul;
  case '/':
  case '%':
  case tokAssignDiv:
  case tokAssignMod:
    return MipsInstrDiv;
  case tokUDiv:
  case tokUMod:
  case tokAssignUDiv:
  case tokAssignUMod:
    return MipsInstrDivU;
  case tokLShift:
  case tokAssignLSh:
    return MipsInstrSLL;
  case tokRShift:
  case tokAssignRSh:
    return MipsInstrSRA;
  case tokURShift:
  case tokAssignURSh:
    return MipsInstrSRL;

  default:
    error("Error: Invalid operator\n");
    return 0;
  }
}

void GenReadIdent(int regDst, int opSz, int label)
{
  if (opSz == 1)
  {
    if (CharIsSigned)
    {
      GenPrintInstr2Operands(MipsInstrLB, 0,
                             regDst, 0,
                             MipsOpLabel, label);
    }
    else
    {
      GenPrintInstr2Operands(MipsInstrLBU, 0,
                             regDst, 0,
                             MipsOpLabel, label);
    }
  }
  else
  {
    GenPrintInstr2Operands(MipsInstrLW, 0,
                           regDst, 0,
                           MipsOpLabel, label);
  }
}

void GenReadLocal(int regDst, int opSz, int ofs)
{
  if (opSz == 1)
  {
    if (CharIsSigned)
    {
      GenPrintInstr2Operands(MipsInstrLB, 0,
                             regDst, 0,
                             MipsOpIndRegFp, ofs);
    }
    else
    {
      GenPrintInstr2Operands(MipsInstrLBU, 0,
                             regDst, 0,
                             MipsOpIndRegFp, ofs);
    }
  }
  else
  {
    GenPrintInstr2Operands(MipsInstrLW, 0,
                           regDst, 0,
                           MipsOpIndRegFp, ofs);
  }
}

void GenReadIndirect(int regDst, int regSrc, int opSz)
{
  if (opSz == 1)
  {
    if (CharIsSigned)
    {
      GenPrintInstr2Operands(MipsInstrLB, 0,
                             regDst, 0,
                             regSrc + MipsOpIndRegZero, 0);
    }
    else
    {
      GenPrintInstr2Operands(MipsInstrLBU, 0,
                             regDst, 0,
                             regSrc + MipsOpIndRegZero, 0);
    }
  }
  else
  {
    GenPrintInstr2Operands(MipsInstrLW, 0,
                           regDst, 0,
                           regSrc + MipsOpIndRegZero, 0);
  }
}

void GenWriteIdent(int regSrc, int opSz, int label)
{
  if (opSz == 1)
  {
    GenPrintInstr2Operands(MipsInstrSB, 0,
                           regSrc, 0,
                           MipsOpLabel, label);
  }
  else
  {
    GenPrintInstr2Operands(MipsInstrSW, 0,
                           regSrc, 0,
                           MipsOpLabel, label);
  }
}

void GenWriteLocal(int regSrc, int opSz, int ofs)
{
  if (opSz == 1)
  {
    GenPrintInstr2Operands(MipsInstrSB, 0,
                           regSrc, 0,
                           MipsOpIndRegFp, ofs);
  }
  else
  {
    GenPrintInstr2Operands(MipsInstrSW, 0,
                           regSrc, 0,
                           MipsOpIndRegFp, ofs);
  }
}

void GenWriteIndirect(int regDst, int regSrc, int opSz)
{
  if (opSz == 1)
  {
    GenPrintInstr2Operands(MipsInstrSB, 0,
                           regSrc, 0,
                           regDst + MipsOpIndRegZero, 0);
  }
  else
  {
    GenPrintInstr2Operands(MipsInstrSW, 0,
                           regSrc, 0,
                           regDst + MipsOpIndRegZero, 0);
  }
}

void GenIncDecIdent(int regDst, int opSz, int label, int tok)
{
  int instr = MipsInstrAddU;

  if (tok != tokInc)
    instr = MipsInstrSubU;

  GenReadIdent(regDst, opSz, label);
  GenPrintInstr3Operands(instr, 0,
                         regDst, 0,
                         regDst, 0,
                         MipsOpConst, 1);
  GenWriteIdent(regDst, opSz, label);
  GenExtendRegIfNeeded(regDst, opSz);
}

void GenIncDecLocal(int regDst, int opSz, int ofs, int tok)
{
  int instr = MipsInstrAddU;

  if (tok != tokInc)
    instr = MipsInstrSubU;

  GenReadLocal(regDst, opSz, ofs);
  GenPrintInstr3Operands(instr, 0,
                         regDst, 0,
                         regDst, 0,
                         MipsOpConst, 1);
  GenWriteLocal(regDst, opSz, ofs);
  GenExtendRegIfNeeded(regDst, opSz);
}

void GenIncDecIndirect(int regDst, int regSrc, int opSz, int tok)
{
  int instr = MipsInstrAddU;

  if (tok != tokInc)
    instr = MipsInstrSubU;

  GenReadIndirect(regDst, regSrc, opSz);
  GenPrintInstr3Operands(instr, 0,
                         regDst, 0,
                         regDst, 0,
                         MipsOpConst, 1);
  GenWriteIndirect(regSrc, regDst, opSz);
  GenExtendRegIfNeeded(regDst, opSz);
}

void GenPostIncDecIdent(int regDst, int opSz, int label, int tok)
{
  int instr = MipsInstrAddU;

  if (tok != tokPostInc)
    instr = MipsInstrSubU;

  GenReadIdent(regDst, opSz, label);
  GenPrintInstr3Operands(instr, 0,
                         regDst, 0,
                         regDst, 0,
                         MipsOpConst, 1);
  GenWriteIdent(regDst, opSz, label);
  GenPrintInstr3Operands(instr, 0,
                         regDst, 0,
                         regDst, 0,
                         MipsOpConst, -1);
  GenExtendRegIfNeeded(regDst, opSz);
}

void GenPostIncDecLocal(int regDst, int opSz, int ofs, int tok)
{
  int instr = MipsInstrAddU;

  if (tok != tokPostInc)
    instr = MipsInstrSubU;

  GenReadLocal(regDst, opSz, ofs);
  GenPrintInstr3Operands(instr, 0,
                         regDst, 0,
                         regDst, 0,
                         MipsOpConst, 1);
  GenWriteLocal(regDst, opSz, ofs);
  GenPrintInstr3Operands(instr, 0,
                         regDst, 0,
                         regDst, 0,
                         MipsOpConst, -1);
  GenExtendRegIfNeeded(regDst, opSz);
}

void GenPostIncDecIndirect(int regDst, int regSrc, int opSz, int tok)
{
  int instr = MipsInstrAddU;

  if (tok != tokPostInc)
    instr = MipsInstrSubU;

  GenReadIndirect(regDst, regSrc, opSz);
  GenPrintInstr3Operands(instr, 0,
                         regDst, 0,
                         regDst, 0,
                         MipsOpConst, 1);
  GenWriteIndirect(regSrc, regDst, opSz);
  GenPrintInstr3Operands(instr, 0,
                         regDst, 0,
                         regDst, 0,
                         MipsOpConst, -1);
  GenExtendRegIfNeeded(regDst, opSz);
}

int CanUseTempRegs;
int TempsUsed;

void GenPushReg(int reg)
{
  if (CanUseTempRegs && TempsUsed < 6)
  {
    GenPrintInstr2Operands(MipsInstrMov, 0,
                           MipsOpRegT2 + TempsUsed, 0,
                           reg, 0);
    TempsUsed++;
    return;
  }

  GenPrintInstr3Operands(MipsInstrSubU, 0,
                         MipsOpRegSp, 0,
                         MipsOpRegSp, 0,
                         MipsOpConst, 4);

  GenPrintInstr2Operands(MipsInstrSW, 0,
                         reg, 0,
                         MipsOpIndRegSp, 0);

  TempsUsed++;
}

int GenPopReg(int reg)
{
  TempsUsed--;

  if (CanUseTempRegs && TempsUsed < 6)
  {
    return MipsOpRegT2 + TempsUsed;
  }

  GenPrintInstr2Operands(MipsInstrLW, 0,
                         reg, 0,
                         MipsOpIndRegSp, 0);

  GenPrintInstr3Operands(MipsInstrAddU, 0,
                         MipsOpRegSp, 0,
                         MipsOpRegSp, 0,
                         MipsOpConst, 4);
  return reg;
}

// Original, primitive stack-based code generator
// DONE: test 32-bit code generation
void GenExpr0(void)
{
  int i;
  int gotUnary = 0;
  int maxCallDepth = 0;
  int callDepth = 0;
  int paramOfs = 0;

  for (i = 0; i < sp; i++)
    if (stack[i][0] == '(')
    {
      if (++callDepth > maxCallDepth)
        maxCallDepth = callDepth;
    }
    else if (stack[i][0] == ')')
    {
      callDepth--;
    }

  CanUseTempRegs = maxCallDepth == 0;
  TempsUsed = 0;

  for (i = 0; i < sp; i++)
  {
    int tok = stack[i][0];
    int v = stack[i][1];

#ifndef NO_ANNOTATIONS
    switch (tok)
    {
    case tokNumInt: printf2(" ; %d\n", truncInt(v)); break;
    case tokNumUint: printf2(" ; %uu\n", truncUint(v)); break;
    case tokIdent: printf2(" ; %s\n", IdentTable + v); break;
    case tokLocalOfs: printf2(" ; local ofs\n"); break;
    case ')': printf2(" ; ) fxn call\n"); break;
    case tokUnaryStar: printf2(" ; * (read dereference)\n"); break;
    case '=': printf2(" ; = (write dereference)\n"); break;
    case tokShortCirc: printf2(" ; short-circuit "); break;
    case tokLogAnd: printf2(" ; short-circuit && target\n"); break;
    case tokLogOr: printf2(" ; short-circuit || target\n"); break;
    case tokIf: case tokIfNot: break;
    default: printf2(" ; %s\n", GetTokenName(tok)); break;
    }
#endif

    switch (tok)
    {
    case tokNumInt:
    case tokNumUint:
      if (!(i + 1 < sp && (strchr("+-&^|", stack[i + 1][0]) ||
                           stack[i + 1][0] == tokLShift ||
                           stack[i + 1][0] == tokRShift ||
                           stack[i + 1][0] == tokURShift)))
      {
        if (gotUnary)
          GenPushReg(MipsOpRegV0);

        GenPrintInstr2Operands(MipsInstrLI, 0,
                               MipsOpRegV0, 0,
                               MipsOpConst, v);
      }
      gotUnary = 1;
      break;

    case tokIdent:
      if (gotUnary)
        GenPushReg(MipsOpRegV0);
      if (!(i + 1 < sp && (stack[i + 1][0] == ')' ||
                           stack[i + 1][0] == tokUnaryStar ||
                           stack[i + 1][0] == tokInc ||
                           stack[i + 1][0] == tokDec ||
                           stack[i + 1][0] == tokPostInc ||
                           stack[i + 1][0] == tokPostDec)))
      {
        GenPrintInstr2Operands(MipsInstrLA, 0,
                               MipsOpRegV0, 0,
                               MipsOpLabel, v);
      }
      gotUnary = 1;
      break;

    case tokLocalOfs:
      if (gotUnary)
        GenPushReg(MipsOpRegV0);
      if (!(i + 1 < sp && (stack[i + 1][0] == tokUnaryStar ||
                           stack[i + 1][0] == tokInc ||
                           stack[i + 1][0] == tokDec ||
                           stack[i + 1][0] == tokPostInc ||
                           stack[i + 1][0] == tokPostDec)))
      {
        GenPrintInstr3Operands(MipsInstrAddU, 0,
                               MipsOpRegV0, 0,
                               MipsOpRegFp, 0,
                               MipsOpConst, v);
      }
      gotUnary = 1;
      break;

    case '(':
      if (gotUnary)
        GenPushReg(MipsOpRegV0);
      gotUnary = 0;
      if (v < 16)
        GenLocalAlloc(16 - v);
      paramOfs = v - 4;
      break;

    case ',':
      if (maxCallDepth == 1)
      {
        if (paramOfs == 16)
        {
          GenPushReg(MipsOpRegV0);
          gotUnary = 0;
        }
        if (paramOfs >= 0 && paramOfs <= 12)
        {
          GenPrintInstr2Operands(MipsInstrMov, 0,
                                 MipsOpRegA0 + paramOfs / 4, 0,
                                 MipsOpRegV0, 0);
          gotUnary = 0;
        }
        paramOfs -= 4;
      }
      break;

    case ')':
      if (maxCallDepth != 1)
      {
        if (v >= 4)
          GenPrintInstr2Operands(MipsInstrLW, 0,
                                 MipsOpRegA0, 0,
                                 MipsOpIndRegSp, 0);
        if (v >= 8)
          GenPrintInstr2Operands(MipsInstrLW, 0,
                                 MipsOpRegA1, 0,
                                 MipsOpIndRegSp, 4);
        if (v >= 12)
          GenPrintInstr2Operands(MipsInstrLW, 0,
                                 MipsOpRegA2, 0,
                                 MipsOpIndRegSp, 8);
        if (v >= 16)
          GenPrintInstr2Operands(MipsInstrLW, 0,
                                 MipsOpRegA3, 0,
                                 MipsOpIndRegSp, 12);
      }
      else
      {
        int vv = v;
        if (vv > 16)
          vv = 16;
        if (vv)
          GenLocalAlloc(vv);
      }
      if (stack[i - 1][0] == tokIdent)
      {
        GenPrintInstr2Operands(MipsInstrJAL, 0,
                              31, 0,
                              MipsOpLabel, stack[i - 1][1]);
      }
      else
      {
        GenPrintInstr2Operands(MipsInstrJAL, 0,
                              31, 0,
                              MipsOpRegV0, 0);
      }
      if (v < 16)
        v = 16;
      GenLocalAlloc(-v);
      break;

    case tokUnaryStar:
      if (stack[i - 1][0] == tokIdent)
        GenReadIdent(MipsOpRegV0, v, stack[i - 1][1]);
      else if (stack[i - 1][0] == tokLocalOfs)
        GenReadLocal(MipsOpRegV0, v, stack[i - 1][1]);
      else
        GenReadIndirect(MipsOpRegV0, MipsOpRegV0, v);
      break;

    case tokUnaryPlus:
      break;
    case '~':
      GenPrintInstr3Operands(MipsInstrNor, 0,
                             MipsOpRegV0, 0,
                             MipsOpRegV0, 0,
                             MipsOpRegV0, 0);
      break;
    case tokUnaryMinus:
      GenPrintInstr3Operands(MipsInstrSubU, 0,
                             MipsOpRegV0, 0,
                             MipsOpRegZero, 0,
                             MipsOpRegV0, 0);
      break;

    case '+':
    case '-':
    case '*':
    case '&':
    case '^':
    case '|':
    case tokLShift:
    case tokRShift:
    case tokURShift:
      if ((stack[i - 1][0] == tokNumInt || stack[i - 1][0] == tokNumUint) && tok != '*')
      {
        int instr = GenGetBinaryOperatorInstr(tok);
        GenPrintInstr3Operands(instr, 0,
                               MipsOpRegV0, 0,
                               MipsOpRegV0, 0,
                               MipsOpConst, stack[i - 1][1]);
      }
      else
      {
        int instr = GenGetBinaryOperatorInstr(tok);
        int reg = GenPopReg(MipsOpRegT0);
        GenPrintInstr3Operands(instr, 0,
                               MipsOpRegV0, 0,
                               reg, 0,
                               MipsOpRegV0, 0);
      }
      break;

    case '/':
    case tokUDiv:
    case '%':
    case tokUMod:
      {
        int reg = GenPopReg(MipsOpRegT0);
        if (tok == '/' || tok == '%')
          GenPrintInstr2Operands(MipsInstrDiv, 0,
                                 reg, 0,
                                 MipsOpRegV0, 0);
        else
          GenPrintInstr2Operands(MipsInstrDivU, 0,
                                 reg, 0,
                                 MipsOpRegV0, 0);
        if (tok == '%' || tok == tokUMod)
          GenPrintInstr1Operand(MipsInstrMfHi, 0,
                                MipsOpRegV0, 0);
        else
          GenPrintInstr1Operand(MipsInstrMfLo, 0,
                                MipsOpRegV0, 0);
      }
      break;

    case tokInc:
    case tokDec:
      if (stack[i - 1][0] == tokIdent)
      {
        GenIncDecIdent(MipsOpRegV0, v, stack[i - 1][1], tok);
      }
      else if (stack[i - 1][0] == tokLocalOfs)
      {
        GenIncDecLocal(MipsOpRegV0, v, stack[i - 1][1], tok);
      }
      else
      {
        GenPrintInstr2Operands(MipsInstrMov, 0,
                               MipsOpRegT0, 0,
                               MipsOpRegV0, 0);
        GenIncDecIndirect(MipsOpRegV0, MipsOpRegT0, v, tok);
      }
      break;
    case tokPostInc:
    case tokPostDec:
      if (stack[i - 1][0] == tokIdent)
      {
        GenPostIncDecIdent(MipsOpRegV0, v, stack[i - 1][1], tok);
      }
      else if (stack[i - 1][0] == tokLocalOfs)
      {
        GenPostIncDecLocal(MipsOpRegV0, v, stack[i - 1][1], tok);
      }
      else
      {
        GenPrintInstr2Operands(MipsInstrMov, 0,
                               MipsOpRegT0, 0,
                               MipsOpRegV0, 0);
        GenPostIncDecIndirect(MipsOpRegV0, MipsOpRegT0, v, tok);
      }
      break;

    case tokPostAdd:
    case tokPostSub:
      {
        int instr = GenGetBinaryOperatorInstr(tok);
        int reg = GenPopReg(MipsOpRegT0);
        GenPrintInstr2Operands(MipsInstrMov, 0,
                               MipsOpRegT1, 0,
                               MipsOpRegV0, 0);

        GenReadIndirect(MipsOpRegV0, reg, v);
        GenPrintInstr3Operands(instr, 0,
                               MipsOpRegT1, 0,
                               MipsOpRegT1, 0,
                               MipsOpRegV0, 0);
        GenWriteIndirect(reg, MipsOpRegT1, v);
      }
      break;

    case tokAssignAdd:
    case tokAssignSub:
    case tokAssignMul:
    case tokAssignAnd:
    case tokAssignXor:
    case tokAssignOr:
    case tokAssignLSh:
    case tokAssignRSh:
    case tokAssignURSh:
      {
        int instr = GenGetBinaryOperatorInstr(tok);
        int reg = GenPopReg(MipsOpRegT0);
        GenPrintInstr2Operands(MipsInstrMov, 0,
                               MipsOpRegT1, 0,
                               MipsOpRegV0, 0);

        GenReadIndirect(MipsOpRegV0, reg, v);
        GenPrintInstr3Operands(instr, 0,
                               MipsOpRegV0, 0,
                               MipsOpRegV0, 0,
                               MipsOpRegT1, 0);
        GenWriteIndirect(reg, MipsOpRegV0, v);

        GenExtendRegIfNeeded(MipsOpRegV0, v);
      }
      break;

    case tokAssignDiv:
    case tokAssignUDiv:
    case tokAssignMod:
    case tokAssignUMod:
      {
        int reg = GenPopReg(MipsOpRegT0);

        GenReadIndirect(MipsOpRegT1, reg, v);
        if (tok == '/' || tok == '%')
          GenPrintInstr2Operands(MipsInstrDiv, 0,
                                 MipsOpRegT1, 0,
                                 MipsOpRegV0, 0);
        else
          GenPrintInstr2Operands(MipsInstrDivU, 0,
                                 MipsOpRegT1, 0,
                                 MipsOpRegV0, 0);
        if (tok == '%' || tok == tokUMod)
          GenPrintInstr1Operand(MipsInstrMfHi, 0,
                                MipsOpRegV0, 0);
        else
          GenPrintInstr1Operand(MipsInstrMfLo, 0,
                                MipsOpRegV0, 0);
        GenWriteIndirect(reg, MipsOpRegV0, v);

        GenExtendRegIfNeeded(MipsOpRegV0, v);
      }
      break;

    case '=':
      {
        int reg = GenPopReg(MipsOpRegT0);
        GenWriteIndirect(reg, MipsOpRegV0, v);
        GenExtendRegIfNeeded(MipsOpRegV0, v);
      }
      break;

/*
  i = il < ir;  // i = slt(il, ir);
  i = il <= ir; // i = slt(ir, il) ^ 1;
  i = il > ir;  // i = slt(ir, il);
  i = il >= ir; // i = slt(il, ir) ^ 1;
  i = il == ir; // i = sltu(il ^ ir, 1);
  i = il != ir; // i = sltu(0, il ^ ir);
*/
    case '<':
      {
        int reg = GenPopReg(MipsOpRegT0);
        GenPrintInstr3Operands(MipsInstrSLT, 0,
                               MipsOpRegV0, 0,
                               reg, 0,
                               MipsOpRegV0, 0);
      }
      break;
    case tokULess:
      {
        int reg = GenPopReg(MipsOpRegT0);
        GenPrintInstr3Operands(MipsInstrSLTU, 0,
                               MipsOpRegV0, 0,
                               reg, 0,
                               MipsOpRegV0, 0);
      }
      break;
    case '>':
      {
        int reg = GenPopReg(MipsOpRegT0);
        GenPrintInstr3Operands(MipsInstrSLT, 0,
                               MipsOpRegV0, 0,
                               MipsOpRegV0, 0,
                               reg, 0);
      }
      break;
    case tokUGreater:
      {
        int reg = GenPopReg(MipsOpRegT0);
        GenPrintInstr3Operands(MipsInstrSLTU, 0,
                               MipsOpRegV0, 0,
                               MipsOpRegV0, 0,
                               reg, 0);
      }
      break;
    case tokLEQ:
      {
        int reg = GenPopReg(MipsOpRegT0);
        GenPrintInstr3Operands(MipsInstrSLT, 0,
                               MipsOpRegV0, 0,
                               MipsOpRegV0, 0,
                               reg, 0);
        GenPrintInstr3Operands(MipsInstrXor, 0,
                               MipsOpRegV0, 0,
                               MipsOpRegV0, 0,
                               MipsOpConst, 1);
      }
      break;
    case tokULEQ:
      {
        int reg = GenPopReg(MipsOpRegT0);
        GenPrintInstr3Operands(MipsInstrSLTU, 0,
                               MipsOpRegV0, 0,
                               MipsOpRegV0, 0,
                               reg, 0);
        GenPrintInstr3Operands(MipsInstrXor, 0,
                               MipsOpRegV0, 0,
                               MipsOpRegV0, 0,
                               MipsOpConst, 1);
      }
      break;
    case tokGEQ:
      {
        int reg = GenPopReg(MipsOpRegT0);
        GenPrintInstr3Operands(MipsInstrSLT, 0,
                               MipsOpRegV0, 0,
                               reg, 0,
                               MipsOpRegV0, 0);
        GenPrintInstr3Operands(MipsInstrXor, 0,
                               MipsOpRegV0, 0,
                               MipsOpRegV0, 0,
                               MipsOpConst, 1);
      }
      break;
    case tokUGEQ:
      {
        int reg = GenPopReg(MipsOpRegT0);
        GenPrintInstr3Operands(MipsInstrSLTU, 0,
                               MipsOpRegV0, 0,
                               reg, 0,
                               MipsOpRegV0, 0);
        GenPrintInstr3Operands(MipsInstrXor, 0,
                               MipsOpRegV0, 0,
                               MipsOpRegV0, 0,
                               MipsOpConst, 1);
      }
      break;
    case tokEQ:
      {
        int reg = GenPopReg(MipsOpRegT0);
        GenPrintInstr3Operands(MipsInstrXor, 0,
                               MipsOpRegV0, 0,
                               reg, 0,
                               MipsOpRegV0, 0);
        GenPrintInstr3Operands(MipsInstrSLTU, 0,
                               MipsOpRegV0, 0,
                               MipsOpRegV0, 0,
                               MipsOpConst, 1);
      }
      break;
    case tokNEQ:
      {
        int reg = GenPopReg(MipsOpRegT0);
        GenPrintInstr3Operands(MipsInstrXor, 0,
                               MipsOpRegV0, 0,
                               reg, 0,
                               MipsOpRegV0, 0);
        GenPrintInstr3Operands(MipsInstrSLTU, 0,
                               MipsOpRegV0, 0,
                               MipsOpRegZero, 0,
                               MipsOpRegV0, 0);
      }
      break;

    case tok_Bool:
      GenPrintInstr3Operands(MipsInstrSLTU, 0,
                             MipsOpRegV0, 0,
                             MipsOpRegZero, 0,
                             MipsOpRegV0, 0);
      break;

    case tokShortCirc:
#ifndef NO_ANNOTATIONS
      if (v >= 0)
        printf2("&&\n");
      else
        printf2("||\n");
#endif
      if (v >= 0)
        GenJumpIfZero(v); // &&
      else
        GenJumpIfNotZero(-v); // ||
      gotUnary = 0;
      break;

    case tokLogAnd:
      GenNumLabel(v);
      break;
    case tokLogOr:
      GenNumLabel(v);
      break;

    case tokVoid:
      gotUnary = 0;
      break;

    case tokComma:
      break;

    case tokIf:
      GenJumpIfNotZero(stack[i][1]);
      break;
    case tokIfNot:
      GenJumpIfZero(stack[i][1]);
      break;

    default:
      error("Error: Internal Error: GenExpr0(): unexpected token %s\n", GetTokenName(tok));
      break;
    }
  }
}

void GenStrData(int insertJump)
{
  int i;

  // insert string literals into the code
  for (i = 0; i < sp; i++)
  {
    int tok = stack[i][0];
    char* p = IdentTable + stack[i][1];
    if (tok == tokIdent && isdigit(*p))
    {
      int label = atoi(p);
      int len;

      p = FindString(label);
      len = *p++;

      if (OutputFormat == FormatFlat)
      {
        if (insertJump)
          GenJumpUncond(label + 1);
      }
      else
      {
        if (insertJump)
          puts2(CodeFooter);
        puts2(DataHeader);
      }
      GenNumLabel(label);

      GenStartAsciiString();
      printf2("\"");
      while (len--)
      {
        // quote ASCII chars for better readability
        if (*p >= 0x20 && *p <= 0x7E)
        {
          if (*p == '\"' || *p == '\\')
            printf2("\\");
          printf2("%c", *p);
        }
        else
        {
          printf2("\\%03o", *p & 0xFFu);
        }
        p++;
      }
      printf2("\"");
      puts2("");

      if (OutputFormat == FormatFlat)
      {
        if (insertJump)
          GenNumLabel(label + 1);
      }
      else
      {
        puts2(DataFooter);
        if (insertJump)
          puts2(CodeHeader);
      }
    }
  }
}

void GenExpr(void)
{
  GenStrData(1);
  GenExpr0();
}
