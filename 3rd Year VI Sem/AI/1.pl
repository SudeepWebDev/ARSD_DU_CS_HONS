parent(Balram Singh, Umesh Singh).
parent(Balram Singh, Rahul Singh).
parent(Umesh Singh, Atul Kumar Singh).
parent(Umesh Singh, Sudeep Kumar Singh).
parent(Rahul Singh, Harshit Singh).

% Rules
grandparent(X, Y) :- parent(X, Z), parent(Z, Y).
sibling(X, Y) :- parent(Z, X), parent(Z, Y), X \= Y.
ancestor(X, Y) :- parent(X, Y).
ancestor(X, Y) :- parent(X, Z), ancestor(Z, Y).

% Demonstration queries:
% ?- grandparent(Balram Singh, Sudeep Kumar Singh).
% ?- sibling(Umesh Singh, Rahul Singh).
% ?- ancestor(Harshit Singh, Balram Singh).
