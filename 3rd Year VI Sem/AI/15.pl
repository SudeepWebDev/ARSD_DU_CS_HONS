delete(1, [_|T], T).
delete(N, [H|T], [H|R]) :-
    N > 1,
    N1 is N - 1,
    delete(N1, T, R).

% Demonstration queries:
% ?- delete(3, [1, 2, 3, 4], R).
