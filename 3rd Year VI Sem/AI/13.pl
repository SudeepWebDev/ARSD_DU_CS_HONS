maxlist([X], X).
maxlist([H|T], M) :-
    maxlist(T, M1),
    M is max(H, M1).

% Demonstration queries:
% ?- maxlist([1, 5, 3, 9, 2], M).
