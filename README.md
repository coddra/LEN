# LEN
Inspect the encoding of an assembly instruction with a single line!
*This short program does in fact do nothing special, it invokes other programs.*
## Usage
Prerequisites:
- as
- objdump
```
$ len <instruction>
```
**IMPORTANT: this program uses AT&T syntax**
<br>
For example:
```
$ len div %rbx
```
Outputs:
```
  48 f7 f3                div    %rbx
```
