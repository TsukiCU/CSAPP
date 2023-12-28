##This is a quick manual of how to defuse all the bombs

first open the bomb with gdb

`gdb bomb`

Type "apropos word" to search for commands related to "word"...
Reading symbols from bomb...
(gdb)

- **phase 1**
(gdb) `disas phase_1`
Dump of assembler code for function phase_1:
   0x0000000000400ee0 <+0>:     sub    $0x8,%rsp
   0x0000000000400ee4 <+4>:     mov    $0x402400,%esi
   0x0000000000400ee9 <+9>:     call   0x401338 <strings_not_equal>
   0x0000000000400eee <+14>:    test   %eax,%eax
   0x0000000000400ef0 <+16>:    je     0x400ef7 <phase_1+23>
   0x0000000000400ef2 <+18>:    call   0x40143a <explode_bomb>
   0x0000000000400ef7 <+23>:    add    $0x8,%rsp
   0x0000000000400efb <+27>:    ret
End of assembler dump.

We can see from the above asm code that, something stored at 0x402400
was moved to esi, and then a function `strings_not_equal` is executed
to compare the input and whatever is there beginning at $0x402400. So
we use `x/s` command to print out that content in the form of string,
and here's the output :

(gdb) `x/s 0x402400`
0x402400:       "Border relations with Canada have never been better."

There we are. The password to defuse the first bomb is
**Border relations with Canada have never been better.**

```
which to blow yourself up. Have a nice day!
Border relations with Canada have never been better.
Phase 1 defused. How about the next one?
```