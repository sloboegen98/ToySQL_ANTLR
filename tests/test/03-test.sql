SELECT A.x AS ax, A.x AS axx, B.z AS bz 
FROM A, B 
WHERE (ax = 1 OR axx = 2 AND bz = "hello");