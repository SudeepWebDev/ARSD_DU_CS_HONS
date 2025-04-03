max(X, Y, X) :- X >= Y.
max(X, Y, Y) :- Y > X.

% Demonstration queries:
% ?- max(3, 4, M).
