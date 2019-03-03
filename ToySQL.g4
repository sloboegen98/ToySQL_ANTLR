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
    ATTRNAME (',' ATTRNAME )*
    | ALL
    ;

frparams 
    :
    TABLENAME (',' TABLENAME)*
    ;

whparams
    :
    whparam ((AND|OR) rp=whparams)*
    | '(' brp=whparams ')'
    ;

whparam
    :
    ATTRNAME relation
    (ATTRNAME 
    | WORD
    | NUMBER)
    ;

relation
    :
      '=' 
    | '<'
    | '>'
    ;
