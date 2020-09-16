define show
    echo -- regs --\n
    info reg rdi rsi rsp rbp
    echo -- stack --
    x/10a $rsp
end
