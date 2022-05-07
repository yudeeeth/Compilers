	decl KANNA_n
	push 5.000000
	push 5.000000
	add
	pop KANNA_n
	push KANNA_n
	push 1.000000
	eq
	push 0
	jeq label2
	push KANNA_n
	print
	jmp label1
label2:
	push KANNA_n
	push 1.000000
	add
	print
label1:
	push 0.000000
	pop KANNA_n
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
	jmp label5
KANNA_add:
	pop KANNA_a_nwlrbbmqb
	pop KANNA_b_nwlrbbmqb
	push KANNA_a_nwlrbbmqb
	push KANNA_b_nwlrbbmqb
	add
	ret
label5:
	push 3.000000
	push 5.000000
	call KANNA_add
	jmp label6
KANNA_fact:
	pop KANNA_n_hcdarzowk
	push KANNA_n_hcdarzowk
	push 1.000000
	sub
	call KANNA_fact
	push KANNA_n_hcdarzowk
	mul
	ret
label6:
	jmp label7
KANNA_fib:
	pop KANNA_n_kyhiddqsc
	push KANNA_n_kyhiddqsc
	push 2.000000
	lt
	push 0
	jeq label8
	push 0.000000
	ret
label8:
	push KANNA_n_kyhiddqsc
	push 1.000000
	sub
	call KANNA_fib
	push KANNA_n_kyhiddqsc
	push 2.000000
	sub
	call KANNA_fib
	add
	ret
label7:
