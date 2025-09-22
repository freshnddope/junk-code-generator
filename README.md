# c++ build-time junk code generator
## description  
junk code generator is a c++ tool that adds unnecessary code during compilation, making analysis more difficult and preventing detection by antiviruses & anti-cheats (simple bypass).

## usage (c++)  
```cpp
#include <iostream>
#include <windows.h>
#include "JunkGenerator.h"

int main() {
  JUNK_GENERATE(100); // for best performance, use between 500 and 1500
  return 0;
}
```

## before & after
**before**  

![Before](https://cdn.discordapp.com/attachments/1159180148587909202/1419656661127139509/image.png?ex=68d28dcb&is=68d13c4b&hm=704b44fde0e96448d46958ab180913ad52299aff5146e0bd08cba6b0d889ad01&)
![Before](https://cdn.discordapp.com/attachments/1159180148587909202/1419657602211512321/image.png?ex=68d28eac&is=68d13d2c&hm=75af5abc40cfb88aa55296668bf553e7cac2b7f4ebf72bee6495ef296b57b88f&)

**after (used 9999 in JUNK_GENERATE for example)**

![After](https://cdn.discordapp.com/attachments/1159180148587909202/1419657400889245748/image.png?ex=68d28e7c&is=68d13cfc&hm=f4897e5447aa074293a2d2f44396267348e0fc0c19bdb087b5756f39fc314d07&)
![After](https://cdn.discordapp.com/attachments/1159180148587909202/1419657530312884244/image.png?ex=68d28e9b&is=68d13d1b&hm=8d0f578be3c731980d7300c5dffcb94be11c34a501d391571277cefdf637b569&)

## warning
using too much junk code slows down the application.
