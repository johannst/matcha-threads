# Copyright (c) 2020 Johannes Stoelp

define show_ctx
    echo -- regs --\n
    info reg rdi rsi rsp rbp
    echo -- stack --
    x/10a $rsp
end
