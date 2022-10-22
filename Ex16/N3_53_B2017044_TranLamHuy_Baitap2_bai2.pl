people(marcus).
lanhchua(ceasar).
people(X).
lanhchua(Y).
pompeian(X) :- people(X).
lama(X) :- pompeian(X).
not(trungthanh(X)) :- lama(X).
amsat(X, Y) :- lama(X), lanhchua(Y).



