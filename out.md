	jmp label1
KANNA_fib:
	push 1
	push xFP
	push -1
	add
	push ST
	push 2.000000
	lt
	push 0
	jeq label2
	push 1.000000
	ret
label2:
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
	push 5.000000
	call KANNA_fib
	print
