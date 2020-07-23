.name		"Celebration Funebre v0.99pl42"
.comment	"Jour J"

init:
		ld   %1,r11			#7
		ld   %6,r10			#7
debut:		live %42			#5
		sub  r10,r11,r10		#5
		zjmp %:init			#3
		fork %:debut			
