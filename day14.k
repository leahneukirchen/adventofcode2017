d:*0:`day14    / d:"flqrgnkx"

/ from day10.k
r:{y@(#y)!x+!#y}

S:256
k:{(r[-m](|y#R),y_R:r[m:S!x 1]@*x;+/y,x 1 2;1+x 2)}
h:{,/+S\(2/2!+/+2\)'16 0N#*64 k/[;0+x,17 31 73 47 23]/(!S;0;0)}

/ adapted from ok/examples/islands.k by John Earnest
+/+/a:+0,'+(0,,/+2\h@d,"-",)'$!128				/ 8226
-1+#?,/{a*|/(,x),((-1 1)r'\:x),(-1 1)r\:x}/a*s#1+!*/s:2##a	/ 1128
