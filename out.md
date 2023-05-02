	push 10.000000
	push 9.000000
	push 8.000000
	push 7.000000
	push 6.000000
	push 5.000000
	push 4.000000
	push 3.000000
	push 2.000000
	push 1.000000
	push 10
	arr
	decl KANNA_arr
	push 9
	arr
	pop KANNA_arr
	push 8
	arr
	pop KANNA_arr
	push 7
	arr
	pop KANNA_arr
	push 6
	arr
	pop KANNA_arr
	push 5
	arr
	pop KANNA_arr
	push 4
	arr
	pop KANNA_arr
	push 3
	arr
	pop KANNA_arr
	push 2
	arr
	pop KANNA_arr
	push 1
	arr
	pop KANNA_arr
	push 0
	arr
	pop KANNA_arr
	decl KANNA_n
	push 10.000000
	pop KANNA_n
	decl KANNA_temp
	decl KANNA_i
	decl KANNA_j
	jmp label1
KANNA_swap:
function is called here
inside first!=NULL
	push 2
after pushing 0s
exit first!=NULL
	push xFP
	push -2
	add
	push ST
	arr
	push KANNA_arr
	pop KANNA_temp
	push xFP
	push -1
	add
	push ST
	arr
	push KANNA_arr
	push xFP
	push -2
	add
	push ST
	arr
	pop KANNA_arr
	push KANNA_temp
	push xFP
	push -1
	add
	push ST
	arr
	pop KANNA_arr
	push 0.000000
	ret
before function exit
label1:
	jmp label2
KANNA_bubble:
function is called here
inside first!=NULL
	push 1
after pushing 0s
exit first!=NULL
	push 0.000000
	pop KANNA_i
label3:
	push KANNA_i
	push KANNA_n
	push 1.000000
	sub
	lt
	push 0
	jeq label4
	push 0.000000
	pop KANNA_j
label5:
	push KANNA_j
	push KANNA_n
	push 1.000000
	sub
	lt
	push 0
	jeq label6
	push KANNA_j
	push 1.000000
	add
	arr
	push KANNA_arr
	push KANNA_j
	arr
	push KANNA_arr
	lt
	push 0
	jeq label7
	push KANNA_j
	push 1.000000
	add
	push KANNA_j
	call KANNA_swap
label7:
	push KANNA_j
	push 1.000000
	add
	pop KANNA_j
	jmp label5
label6:
	push KANNA_i
	push 1.000000
	add
	pop KANNA_i
	jmp label3
label4:
	push 0.000000
	ret
before function exit
label2:
	jmp label8
KANNA_part:
function is called here
inside first!=NULL
	push 3
