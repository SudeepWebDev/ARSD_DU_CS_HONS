memb(X, [X|_]).
memb(X, [_|T]) :- memb(X, T).

% Demonstration queries:
% ?- memb(3, [1, 2, 3]).
