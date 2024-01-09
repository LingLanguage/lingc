#### Dependancies
utf8.h - https://github.com/sheredom/utf8.h  
raylib - https://github.com/raysan5/raylib

#### FSM
guess -> import / static variable / static function  
import -> guess  
static variable -> guess  
static function -> guess  
struct -> guess  
    field -> struct  
    function -> struct  
        expression(and statement) -> fuction  
            call function -> expression  
                const string -> call function  
            const string -> expression  