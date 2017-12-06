d:.:'0:`day05
w:v:0
/ {(#d)>*|x}{v+:1;(@[*x;*|x;1+];((*x)@*|x)+*|x)}/(d;0);
/ {(#d)>*x}{v+:1;(((*|x)@*x)+*x;@[*|x;*x;1+])}/(0;d);
{(#d)>*x}{v+:1;(*x+(*|x)@*x;@[*|x;*x;1+])}/(0;d);
v    / 358309

d:.:'0:`day05;-1+#{x<#d}{x-1-d[x]+:1}\0     / thanks @vectorprocessing

/ {(#d)>*|x}{w+:1;(@[*x;*|x;$[((*x)[*|x])>2;-1+;1+]];((*x)@*|x)+*|x)}/(d;0);

d:.:'0:`day05
v:0
{(#d)>*x}{v+:1;(*x+(*|x)@*x;@[*|x;*x;{$[x>2;x-1;x+1]}])}/(0;d);
v    / 28178177

d:.:'0:`day05;-1+#{x<#d}{d[x]+:1 -1@2<r:d@x;x+r}\0   / thx @vectorprocessing, inr

\\

/ rlwrap k day05.k  149.90s user 0.01s system 99% cpu 7M memory 2:30.51 total
