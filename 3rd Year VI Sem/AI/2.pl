conc([], L, L).
conc([H|T], L2, [H|L3]) :- conc(T, L2, L3).

% Demonstration queries:
% ?- conc([1, 2], [3, 4], L3).
