pull block
out y, 25
    
mov x, y
set pins, 1 
    
lp1:
    jmp x-- lp1 
    mov x, y
    set pins, 0 
    
lp2:
    jmp x-- lp2


