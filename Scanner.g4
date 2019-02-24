grammar Scanner;

SELECT   : S E L E C T               ; 
FROM     : F R O M                   ;
WHERE    : W H E R E                 ;

ALL      : '*'                       ;
AND      : A N D                     ;
OR       : O R                       ; 

WS       : [ \t\r\n]+ -> skip        ;

ATTRNAME : [A-Z]+'.'([a-z]|DIGIT)+   ;
TABLENAME: [A-Z]+                    ;
NUMBER   : ('-')?DIGIT+('.'DIGIT+)?  ;
WORD     : '"' ([A-Z]|[a-z])+ '"'    ;

fragment DIGIT : [0-9];

fragment A : [aA];
fragment B : [bB];
fragment C : [cC];
fragment D : [dD];
fragment E : [eE];
fragment F : [fF];
fragment G : [gG];
fragment H : [hH];
fragment I : [iI];
fragment J : [jJ];
fragment K : [kK];
fragment L : [lL];
fragment M : [mM];
fragment N : [nN];
fragment O : [oO];
fragment P : [pP];
fragment Q : [qQ];
fragment R : [rR];
fragment S : [sS];
fragment T : [tT];
fragment U : [uU];
fragment V : [vV];
fragment W : [wW];
fragment X : [xX];
fragment Y : [yY];
fragment Z : [zZ];