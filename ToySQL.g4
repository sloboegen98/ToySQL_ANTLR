grammar ToySQL;

import Tmp;

@header {
#include <iostream>
#include "Query.h"
}

@members {
Query q;
}

query
    :
    whole_query
    ;

whole_query
    :
    basic_query  ';'
    |
    basic_query WHERE whparams ';' {q.where = $whparams.preds;}
    ;

basic_query
    :
    SELECT selparams {q.selattrs = $selparams.attrs;}
    FROM frparams {q.from = $frparams.tables;}
    ;

selparams returns [ std::vector <std::string> attrs ]
    :
    ATTRNAME {$attrs.push_back($ATTRNAME.text);} 
    (',' ATTRNAME{$attrs.push_back($ATTRNAME.text);})*
    |
    ALL {$attrs.push_back("ALL");}
    ;

frparams returns [ std::vector <std::string> tables ]
    :
    TABLENAME {$tables.push_back($TABLENAME.text);}
    (',' TABLENAME {$tables.push_back($TABLENAME.text);})*
    ;

whparams returns [ std::vector <Predicate> preds ]
    :
    whparam {$preds.push_back($whparam.pr);}
    ((AND|OR) rp=whparams
    {
        for (int i = 0; i < $rp.preds.size(); i++)
            $preds.push_back($rp.preds[i]);
    }
    )*
    |
    '(' brp=whparams ')'
    {
        for (int i = 0; i < $brp.preds.size(); i++)
            $preds.push_back($brp.preds[i]);
    }
    ;

whparam returns [ Predicate pr ]
    :
    ATTRNAME {$pr.left = $ATTRNAME.text;} relation {$pr.rel = $relation.r;} 
    (ATTRNAME {$pr.right = $ATTRNAME.text;} 
    |WORD {$pr.right = $WORD.text;}
    |NUMBER {$pr.right = $NUMBER.text;})
    ;

relation returns [ char r ]
    :
    '=' {$r = '=';}
    |
    '<' {$r = '<';}
    |
    '>' {$r = '>';}
    ;
