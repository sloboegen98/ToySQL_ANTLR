grammar ToySQL;

import Scanner;

query
    :
    whole_query
    ;

whole_query
    :
    basic_query  ';'
    | basic_query WHERE whparams ';'
    ;

basic_query
    :
    SELECT selparams FROM frparams 
    ;

selparams
    :
    ATTRNAME (AS ALIAS)? (',' ATTRNAME (AS ALIAS)?)*
    | ALL
    ;

frparams 
    :
    TABLENAME (AS ALIAS)? (',' TABLENAME (AS ALIAS)?)*
    ;

whparams
    :
    whparam ((AND|OR) rp=whparams)*
    | '(' brp=whparams ')'
    ;

whparam
    :
    (ATTRNAME | ALIAS) relation
    (ATTRNAME 
    | ALIAS
    | WORD
    | NUMBER)
    ;

relation
    :
      '=' 
    | '<'
    | '>'
    ;
