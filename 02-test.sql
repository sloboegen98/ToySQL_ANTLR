SELECT A.x, B.y 
FROM A,B
WHERE (A.x = 1 AND A.y = 2 AND (B.z = "word" OR B.z = A.z));