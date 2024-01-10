#### Dependancies
utf8.h - https://github.com/sheredom/utf8.h  
raylib - https://github.com/raysan5/raylib

#### FA
NFA Top  
    =       -> DFA assign stm  
    ;       -> DFA field  
    import  -> DFA import  
    fn      -> DFA function  
    struct  -> DFA struct  
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
            -> NFA Block  
    BlockEnd-> END  
NFA Block  
            -> NFA Statement  
            -> NFA Block  
NFA Statement  
    =       -> DFA assign stm  
    ;       -> DFA declare stm  
    if      -> DFA if stm  
    do      -> DFA while stm  
    while   -> DFA while stm  
    for     -> DFA for stm  
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