chapK(0,_,1) :- !.
chapK(K,K,1) :- !.
chapK(K, N, X) :- K1 is K-1,N1 is N-1, chapK(K, N1, X1), chapK(K1, N1, X2), X is X1+X2.