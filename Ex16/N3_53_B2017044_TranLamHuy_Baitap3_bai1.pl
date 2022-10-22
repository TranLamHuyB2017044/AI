luythua(_, 0, 1) :- !.
luythua(A, N, X) :- N1 is N-1,luythua(A, N1, X1),X is X1 * A.



