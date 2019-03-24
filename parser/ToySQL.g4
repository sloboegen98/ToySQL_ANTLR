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
    result_column (',' result_column)*
    | ALL
    ;

frparams 
    :
    from_table (',' from_table)*
    ;

whparams
    :
    whparam ((AND|OR) rp=whparams)*
    | '(' brp=whparams ')'
    ;

whparam
    :
    whparam_left relation whparam_right
    ;

whparam_left
    :
    ATTRNAME
    | ALIAS
    ;

relation
    :
      '=' 
    | '<'
    | '>'
    ;

whparam_right
    :
    ATTRNAME
    | ALIAS
    | NUMBER
    | WORD
    ;

result_column
    :
    ATTRNAME (AS ALIAS)?
    ; 

from_table
    :
    TABLENAME (AS ALIAS)?
    ;
