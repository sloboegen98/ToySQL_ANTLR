#!/bin/bash

# EOF in end of file can be an error

for t in $(ls test); do
    n=${t%%-*}
    .././parsertestexe test/$t > output.txt
    
    if cmp output.txt result/$n.txt; then
        echo Test $n passed
    else 
        echo Test $n failed
    fi
done

rm -f output.txt
