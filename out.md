	print "Eval block:"
	print ""
	decl KANNA_n
	decl KANNA_m
	push 5.000000
	push 5.000000
	add
	push 3.000000
	mul
	pop KANNA_n
	push 9.000000
	push KANNA_n
	add
	pop KANNA_m
	print "Kanna_n: "
	push KANNA_n
	print
	print ""
	print "KANNA_m: "
	push KANNA_m
	print
	print ""
	print "Jump block:"
	print ""
	push KANNA_n
	push 10.000000
	sub
	push 0.000000
	lt
	push 0
	jeq label2
	print "kanna_n < 10"
	jmp label1
label2:
	print "Kanna_n > 10"
label1:
	print ""
	push 0.000000
	pop KANNA_n
label3:
	push KANNA_n
	push 5.000000
	lt
	push 0
	jeq label4
	push KANNA_n
	print
	print " "
	push KANNA_n
	push 1.000000
	add
	pop KANNA_n
	jmp label3
label4:
	print "Function block:"
	print ""
	jmp label5
KANNA_fib:
	push 1
	push xFP
	push -1
	add
	push ST
	push 0.000000
	eq
	push 0
	jeq label6
	push 0.000000
	ret
label6:
	push xFP
	push -1
	add
	push ST
	push 1.000000
	eq
	push 0
	jeq label7
	push 1.000000
	ret
label7:
	push xFP
	push -1
	add
	push ST
	push 1.000000
	sub
	call KANNA_fib
	push xFP
	push -1
	add
	push ST
	push 2.000000
	sub
	call KANNA_fib
	add
	ret
label5:
	print "Printing Fibonacci sequence from 0 to 20..."
	print ""
	decl KANNA_n
	push 0.000000
	pop KANNA_n
label8:
	push KANNA_n
	push 20.000000
	lt
	push 0
	jeq label9
	push KANNA_n
	call KANNA_fib
	print
	print " "
	push KANNA_n
	push 1.000000
	add
	pop KANNA_n
	jmp label8
label9:
	print ""
