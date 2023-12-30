##This is a quick manual of how to defuse all the bombs

first open the bomb with gdb

`gdb bomb`

Type "apropos word" to search for commands related to "word"...
Reading symbols from bomb...
(gdb)

- **phase 1**
`(gdb) disas phase_1`
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

`(gdb) x/s 0x402400`
0x402400:       "Border relations with Canada have never been better."

There we are. The password to defuse the first bomb is
**Border relations with Canada have never been better.**

```
which to blow yourself up. Have a nice day!
Border relations with Canada have never been better.
Phase 1 defused. How about the next one?
```



- **phase 2**
I must say I am starting to like this game.
This second phase is a lot fun.

As before, we run `disas phase_2`. Here is what we got.
```
Dump of assembler code for function phase_2:
   0x0000000000400efc <+0>:     push   %rbp
   0x0000000000400efd <+1>:     push   %rbx
   0x0000000000400efe <+2>:     sub    $0x28,%rsp
   0x0000000000400f02 <+6>:     mov    %rsp,%rsi
   0x0000000000400f05 <+9>:     call   0x40145c <read_six_numbers>
   0x0000000000400f0a <+14>:    cmpl   $0x1,(%rsp)
   0x0000000000400f0e <+18>:    je     0x400f30 <phase_2+52>
   0x0000000000400f10 <+20>:    call   0x40143a <explode_bomb>
   0x0000000000400f15 <+25>:    jmp    0x400f30 <phase_2+52>
   0x0000000000400f17 <+27>:    mov    -0x4(%rbx),%eax
   0x0000000000400f1a <+30>:    add    %eax,%eax
   0x0000000000400f1c <+32>:    cmp    %eax,(%rbx)
   0x0000000000400f1e <+34>:    je     0x400f25 <phase_2+41>
   0x0000000000400f20 <+36>:    call   0x40143a <explode_bomb>
   0x0000000000400f25 <+41>:    add    $0x4,%rbx
   0x0000000000400f29 <+45>:    cmp    %rbp,%rbx
   0x0000000000400f2c <+48>:    jne    0x400f17 <phase_2+27>
   0x0000000000400f2e <+50>:    jmp    0x400f3c <phase_2+64>
   0x0000000000400f30 <+52>:    lea    0x4(%rsp),%rbx
   0x0000000000400f35 <+57>:    lea    0x18(%rsp),%rbp
   0x0000000000400f3a <+62>:    jmp    0x400f17 <phase_2+27>
   0x0000000000400f3c <+64>:    add    $0x28,%rsp
   0x0000000000400f40 <+68>:    pop    %rbx
   0x0000000000400f41 <+69>:    pop    %rbp
   0x0000000000400f42 <+70>:    ret
End of assembler dump.
```

There is a "read_six_numbers". Ok as you wish, we are going to send you six numbers.
set a breakpoint at 0x0000000000400f0a, using `b *0x0000000000400f0a` (don't forget the asterisk!)
we just randomly input some numbers [1 2 4 6 7 10], and use the command `stepi` to walk through it.
`(gdb) x/i $pc`    // this command tells us the current instruction we are executing.
```
=> 0x0000000000400f0a <+14>:    cmpl   $0x1,(%rsp)
   0x0000000000400f1e <+34>:    je     0x400f25 <phase_2+41>
   0x0000000000400f20 <+36>:    call   0x40143a <explode_bomb>
```
by checking what's in (%rsp) using `x/d $rsp`,
`(gdb) x $rsp`
```
0x7fffffffe000: 1
```
The number is 1. It is actually the very first integer of our input. If the number is not 1, it leads to explosion.
The following is a very obvious loop. I am getting tired of writing this document, so I'll just put the answers here.
The password is **1 2 4 8 16 32**



- **phase 3**
This is getting more fun.
first gdb it as usual.

~/CSAPP/labs/bomb$ gdb bomb
`(gdb) disas phase_3`

```
Dump of assembler code for function phase_3:
   0x0000000000400f43 <+0>:     sub    $0x18,%rsp
   0x0000000000400f47 <+4>:     lea    0xc(%rsp),%rcx
   0x0000000000400f4c <+9>:     lea    0x8(%rsp),%rdx
   0x0000000000400f51 <+14>:    mov    $0x4025cf,%esi
   0x0000000000400f56 <+19>:    mov    $0x0,%eax
   0x0000000000400f5b <+24>:    call   0x400bf0 <__isoc99_sscanf@plt>
   0x0000000000400f60 <+29>:    cmp    $0x1,%eax
   0x0000000000400f63 <+32>:    jg     0x400f6a <phase_3+39>
   0x0000000000400f65 <+34>:    call   0x40143a <explode_bomb>
   0x0000000000400f6a <+39>:    cmpl   $0x7,0x8(%rsp)
   0x0000000000400f6f <+44>:    ja     0x400fad <phase_3+106>
   0x0000000000400f71 <+46>:    mov    0x8(%rsp),%eax
   0x0000000000400f75 <+50>:    jmp    *0x402470(,%rax,8)
   0x0000000000400f7c <+57>:    mov    $0xcf,%eax
   0x0000000000400f81 <+62>:    jmp    0x400fbe <phase_3+123>
   0x0000000000400f83 <+64>:    mov    $0x2c3,%eax
   0x0000000000400f88 <+69>:    jmp    0x400fbe <phase_3+123>
   0x0000000000400f8a <+71>:    mov    $0x100,%eax
   0x0000000000400f8f <+76>:    jmp    0x400fbe <phase_3+123>
   0x0000000000400f91 <+78>:    mov    $0x185,%eax
   0x0000000000400f96 <+83>:    jmp    0x400fbe <phase_3+123>
   0x0000000000400f98 <+85>:    mov    $0xce,%eax
   0x0000000000400f9d <+90>:    jmp    0x400fbe <phase_3+123>
   0x0000000000400f9f <+92>:    mov    $0x2aa,%eax
   0x0000000000400fa4 <+97>:    jmp    0x400fbe <phase_3+123>
   0x0000000000400fa6 <+99>:    mov    $0x147,%eax
   0x0000000000400fab <+104>:   jmp    0x400fbe <phase_3+123>
   0x0000000000400fad <+106>:   call   0x40143a <explode_bomb>
   0x0000000000400fb2 <+111>:   mov    $0x0,%eax
   0x0000000000400fb7 <+116>:   jmp    0x400fbe <phase_3+123>
   0x0000000000400fb9 <+118>:   mov    $0x137,%eax
   0x0000000000400fbe <+123>:   cmp    0xc(%rsp),%eax
   0x0000000000400fc2 <+127>:   je     0x400fc9 <phase_3+134>
   0x0000000000400fc4 <+129>:   call   0x40143a <explode_bomb>
   0x0000000000400fc9 <+134>:   add    $0x18,%rsp
   0x0000000000400fcd <+138>:   ret
End of assembler dump.
```

phase_3 calls __isoc99_sscanf@plt. We don't know what it is for now but it's fine. As we can stepi into
the function body.

`(gdb) b 89`    // phase_3 is called in line 89 of bomb.c
`(gdb) run defuse`
`(gdb) sdjhksjdf`   // type some random garbage.
`(gdb) stepi`
...
`(gdb) stepi`       // after several rounds of stepi.
0x0000000000400bf0 in __isoc99_sscanf@plt ()      // here it is!
`(gdb) stepi`
```
__GI___isoc99_sscanf (s=0x603820 <input_strings+160> "aksdka",
    format=0x4025cf "%d %d") at ./stdio-common/isoc99_sscanf.c:24
24      ./stdio-common/isoc99_sscanf.c: No such file or directory.
```

So it's clear from the error message that, this function takes two decimal parameters.
But we still don't know which two(that's fine for now!)

Rerun the whole process, while this time we put some random decimal numbers.
`(gdb) 114 514`
`(gdb) stepi`
...
`(gdb) stepi`
```
0x00007ffff7e1c132      24      in ./stdio-common/isoc99_sscanf.c
```
`(gdb) finish`
Run till exit from #0  0x00007ffff7e1c136 in __GI___isoc99_sscanf (
    s=0x603820 <input_strings+160> "114 514", format=0x4025cf "%d %d")
    at ./stdio-common/isoc99_sscanf.c:24
0x0000000000400f60 in phase_3 ()
Value returned is $1 = 2

Return value is stored in %eax.
As we can see in:
```
  0x0000000000400f60 <+29>:    cmp    $0x1,%eax
  0x0000000000400f63 <+32>:    jg     0x400f6a <phase_3+39>
  0x0000000000400f65 <+34>:    call   0x40143a <explode_bomb>
```
if there's not exactly 2 input decimal numbers, the bomb explodes.

`(gdb) x/3i $pc`    // this command help us know where pc at(what instruction are we executing) and the following two.
`(gdb) x/5i $pc`
```
=> 0x400e6f <main+207>: mov    %rax,%rdi
   0x400e72 <main+210>: call   0x400f43 <phase_3>
   0x400e77 <main+215>: call   0x4015c4 <phase_defused>
```

After a few instructions, we are brought to here:
```
 0x0000000000400f6a <+39>:    cmpl   $0x7,0x8(%rsp)
```

by checking the value stored in 0x8(%rsp), using `x/d $rsp+0x8` gives us the value of 114, which is the
first value we input in. Likewise, the second number is stored in 0xc(%rsp).

This following lines indicate that, if the first decimal number is greater than 7, then BOOM!
```
   0x0000000000400f6f <+44>:    ja     0x400fad <phase_3+106>
   0x0000000000400fad <+106>:   call   0x40143a <explode_bomb>
```

Just to recap a little bit, based on what we have learnt by now, two decimal numbers are the password, while the first one
should be no larger than 7. We still don't know what exactly should it be, so let's try it out.

`(gdb) run defuse`
4 1919810      // randomly choose the second number

After several `stepi`s, we are here:
```
=> 0x0000000000400f91 <+78>:    mov    $0x185,%eax
   0x0000000000400f96 <+83>:    jmp    0x400fbe <phase_3+123>
```

a number (0x185, 389 in decimal) is moved to %eax. and the program jumps to <phase_3+123>.
```
   0x0000000000400fbe <+123>:   cmp    0xc(%rsp),%eax
   0x0000000000400fc2 <+127>:   je     0x400fc9 <phase_3+134>
   0x0000000000400fc4 <+129>:   call   0x40143a <explode_bomb>
   0x0000000000400fc9 <+134>:   add    $0x18,%rsp
   0x0000000000400fcd <+138>:   ret
```

As we can see, if the second input number(which is stored in 0xc(%rsp) as we mentioned earlier) is equal to
what is in %eax(389), the bomb will defuse!
So we have our final answer : 4 389

But wait. what about the other part of the code? Are they completely useless? Actually if we dig deeper into this,
it turned out that there are seven different ways of guiding us to <phase_3+123>, and this number corresponds exactly
to the first number which cannot be greater than 7. So it's a **switch** structure, and there are seven pairs of valid
answers, which are:
**1 311    2 707     3 256      4 389      5 206      6 682      7 327**

