# mips_assembler
MIPS processors use ROMs to store the instructions that are ran at execution. <br>
The first field in an instruction is the opCode, this code allows instructions to be differentiated and for their arguments to be parsed correctly. <br>
As such, there are 3 standard types of instructions: <br>
R type: <br>
+------------+---------+---------+---------+--------+----------+  <br>
| 6          | 5       | 5       | 5       | 5      | 6        |  <br>
+------------+---------+---------+---------+--------+----------+  <br>
| opcode = 0 | rs      | rt      | rd      | sa     | function |  <br>
+------------+---------+---------+---------+--------+----------+  <br>
| 31..26     | 25...21 | 20...15 | 15...10 | 10...5 | 5...0    |  <br>
+------------+---------+---------+---------+--------+----------+  <br>
R type instructions operate on registers, these instructions usually take 3 arguments: the source,target and destination registers identified by their address (5 bits).  <br>
The sa(shift amount) field is read when we have instructions that shift bits in any register.  <br>
The opcode of these instructions is 0, and the functions are differentiated by the function field.  <br>
The instructions recognized by the assembler are:  <br>
add  <br>
and  <br>
or  <br>
sll  <br>
sllv  <br>
slt  <br>
sra  <br>
srl  <br>
sub  <br>
xor  <br>
jr  <br>
