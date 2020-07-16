.name		"error_bot_name not found"
.comment	""

live:
	live %1
	fork %-10
	live %1
	fork %-10
#	live %1
#	fork %-10
#	live %1
#	fork %-10

#l:
#	zjmp %:live
#	ld %25, r4
#	zjmp %:l

#l1:
#	live	%9999999
#	zjmp	%:l1
#
#b2:
#	live	%9999999
#	zjmp	%:b2