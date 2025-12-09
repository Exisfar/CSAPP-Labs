# Writeup

```sh
objdump -d bomb > bomb.asm
```

## Phase1

关键代码：

```asm
0000000000400da0 <main>:
  ...
  400e32:	e8 67 06 00 00       	call   40149e <read_line>
  400e37:	48 89 c7             	mov    %rax,%rdi
  400e3a:	e8 a1 00 00 00       	call   400ee0 <phase_1>
  400e3f:	e8 80 07 00 00       	call   4015c4 <phase_defused>
  400e44:	bf a8 23 40 00       	mov    $0x4023a8,%edi
  ...
```

在代码中，`rax` 存储了从 `read_line` 函数返回的值。`read_line` 的作用是读取用户输入的一行数据，并将其返回。因此，`rax` 中存储的是**指向用户输入字符串的指针**。之后将其复制到`rdi`中作为`phase_1`函数的参数。

```asm
0000000000400ee0 <phase_1>:
  400ee0:	48 83 ec 08          	sub    $0x8,%rsp
  400ee4:	be 00 24 40 00       	mov    $0x402400,%esi
  400ee9:	e8 4a 04 00 00       	call   401338 <strings_not_equal>
  400eee:	85 c0                	test   %eax,%eax
  400ef0:	74 05                	je     400ef7 <phase_1+0x17>
  400ef2:	e8 43 05 00 00       	call   40143a <explode_bomb>
  400ef7:	48 83 c4 08          	add    $0x8,%rsp
  400efb:	c3                   	ret
```

phase_1函数中，首先把`0x402400`传入了`esi`中作为`strings_not_equal`函数的参数。这个函数返回后测试了`eax`的值，`eax`等于0时跳转到`400ef7`，否则继续执行`explode_bomb`。所以只有`string_not_equal`返回0才能接触炸弹。

```asm
0000000000401338 <strings_not_equal>:
  40133c:	48 89 fb             	mov    %rdi,%rbx
  40133f:	48 89 f5             	mov    %rsi,%rbp
  401342:	e8 d4 ff ff ff       	call   40131b <string_length>
  ...
  40135a:	75 3f                	jne    40139b <strings_not_equal+0x63>
  40135c:	0f b6 03             	movzbl (%rbx),%eax
  40135f:	84 c0                	test   %al,%al
  ...
```

这段代码实现了两个字符串的逐字节比较，如果字符串相等，返回0。


所以用gdb去查看`0x402400`处的字符串即可，命令：

```gdb
x /s 0x402400
```

Answer: "Border relations with Canada have never been better."


## Phase2

Answer: 1 2 4 8 16 32

## Phase3

Answer: 有8种答案，其中一种是 1 311


## Phase4

Answer: 有4种答案，其中一种是 0 0

## Phase5

Answer: ionefg

## Phase6

Answer: 4 3 2 1 6 5
