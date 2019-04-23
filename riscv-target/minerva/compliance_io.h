// RISC-V Compliance IO Test Header File

/*
 * Copyright (c) 2005-2018 Imperas Software Ltd., www.imperas.com
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
 * either express or implied.
 *
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */


#ifndef _COMPLIANCE_IO_H
#define _COMPLIANCE_IO_H

#define CSR_UART_RXTX_ADDR 0xe0001800 // FIXME hardcoded
#define CSR_UART_TXFULL_ADDR 0xe0001804 // FIXME hardcoded

#define STRINGIFY(x) #x
#define TOSTRING(x)  STRINGIFY(x)

#define RVTEST_IO_INIT \
	li zero, -1;

#define RVTEST_IO_WRITE_STR(_R, _STR) \
	.pushsection .rodata; \
20001:	.asciz _STR; \
	.popsection; \
	la t0, 20001b; \
	lui t1, %hi(CSR_UART_RXTX_ADDR); \
	addi t1, t1, %lo(CSR_UART_RXTX_ADDR); \
	lui t2, %hi(CSR_UART_TXFULL_ADDR); \
	addi t2, t2, %lo(CSR_UART_TXFULL_ADDR); \
20002:	lb t3, 0(t0); \
	beqz t3, 20004f; \
20003:  lb t4, 0(t2); \
	bnez t4, 20003b; \
	sb t3, 0(t1); \
	addi t0, t0, 1; \
	j 20002b; \
20004:

#define RVTEST_IO_CHECK()

#define RVTEST_IO_ASSERT_GPR_EQ(_SP, _R, _I) \
	li t0, _I; \
	beq _R, t0, 20005f; \
	RVTEST_IO_WRITE_STR(_SP, "Assertion violation: file "); \
	RVTEST_IO_WRITE_STR(_SP, __FILE__); \
	RVTEST_IO_WRITE_STR(_SP, ", line "); \
	RVTEST_IO_WRITE_STR(_SP, TOSTRING(__LINE__)); \
	RVTEST_IO_WRITE_STR(_SP, ": "); \
	RVTEST_IO_WRITE_STR(_SP, # _R); \
	RVTEST_IO_WRITE_STR(_SP, "("); \
	RVTEST_IO_WRITE_STR(_SP, ") != "); \
	RVTEST_IO_WRITE_STR(_SP, # _I); \
	RVTEST_IO_WRITE_STR(_SP, "\n"); \
	li TESTNUM, 100; \
	RVTEST_FAIL; \
20005:

#define RVTEST_IO_ASSERT_SFPR_EQ(_F, _R, _I)
#define RVTEST_IO_ASSERT_DFPR_EQ(_D, _R, _I)

#endif // _COMPLIANCE_IO_H
