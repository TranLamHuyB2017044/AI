fibo(1, 1) :- !.
fibo(2, 1) :- !.
fibo(N, X) :- N1 is N-1, N2 is N-2, fibo(N1, X1), fibo(N2, X2), X is X1+X2. 