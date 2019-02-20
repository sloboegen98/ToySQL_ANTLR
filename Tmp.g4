grammar Tmp;


SELECT   : 'SELECT' | 'select'       ; 
FROM     : 'FROM'   | 'from'         ;
WHERE    : 'WHERE'  | 'where'        ;

ALL      : '*'                       ;
AND      : 'AND'    | 'and'          ;
OR       : 'OR'     | 'or'           ; 

WS       : [ \t\r\n]+ -> skip        ;

ATTRNAME : [A-Z]+'.'([a-z]|[0-9])+   ;
TABLENAME: [A-Z]+                    ;
NUMBER   : ('-')?[0-9]+('.'[0-9]+)?  ;
WORD     : '"' ([A-Z]|[a-z])+ '"'    ;