#### Dependancies
utf8.h - https://github.com/sheredom/utf8.h  
raylib - https://github.com/raysan5/raylib

#### FA
NFA Top  
    import  -> DFA import  
    fn      -> DFA function  
    struct  -> DFA struct  
    ;       -> DFA field  
    public  -> valid  
    const   -> valid  
    static  -> valid  
DFA import  
    "       -> valid  
    <       -> valid   
    ;       -> END  
DFA field  
    =       -> DFA Assign exp  
    ;       -> END  
DFA function  
            -> NFA Statements  
    }       -> END  
NFA Statements  
    ;       -> DFA declare stm  
    if      -> DFA if stm  
    while   -> DFA while stm  
    for     -> DFA for stm  
    =       -> DFA assign stm  
    return  -> DFA return stm  
DFA exp  
    "       -> DFA Const String  
    (       -> DFA exp  
    )       -> END  
DFA struct  
    =       -> DFA assign stm   
    ;       -> DFA declare stm  
    fn      -> DFA function  
    }       -> END  