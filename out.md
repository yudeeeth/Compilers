	jmp label1
KANNA_fib:
	push 1
	push xFP
	push -1
	add
	push ST
	push 0.000000
	eq
	push 0
	jeq label2
	push 0.000000
	ret
label2:
	push xFP
	push -1
	add
	push ST
	push 1.000000
	eq
	push 0
	jeq label3
	push 1.000000
	ret
label3:
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
label1:
	print "Printing Fibonacci sequence from 0 to 20..."
	print ""
	decl KANNA_n
	push 0.000000
	pop KANNA_n
label4:
	push KANNA_n
	push 20.000000
	lt
	push 0
	jeq label5
	push KANNA_n
	call KANNA_fib
	print
	print " "
	push KANNA_n
	push 1.000000
	add
	pop KANNA_n
	jmp label4
label5:
	print ""
