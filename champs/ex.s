.name "zork"
.comment "just a basic living prog"
		
l2:	and	r1, %0, r1
live:	live	%1
	fork %:l2