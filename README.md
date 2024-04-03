# mips_assembler
MIPS processors use ROMs to store the instructions that are ran at execution.
The first field in an instruction is the opCode, this code allows instructions to be differentiated and for their arguments to be parsed correctly.
As such, there are 3 standard types of instructions:
R type:
+------------+---------+---------+---------+--------+----------+
| 6          | 5       | 5       | 5       | 5      | 6        |
+------------+---------+---------+---------+--------+----------+
| opcode = 0 | rs      | rt      | rd      | sa     | function |
+------------+---------+---------+---------+--------+----------+
| 31..26     | 25...21 | 20...15 | 15...10 | 10...5 | 5...0    |
+------------+---------+---------+---------+--------+----------+
R type instructions operate on registers, these instructions usually take 3 arguments: the source,target and destination registers identified by their address (5 bits).
The sa(shift amount) field is read when we have instructions that shift bits in any register.
The opcode of these instructions is 0, and the functions are differentiated by the function field.
The instructions recognized by the assembler are:
add
and
or
sll
sllv
slt:
sra
srl
sub
xor
jr
