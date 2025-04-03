evenlength([]).
evenlength([_|T]) :- oddlength(T).

oddlength([_]).
oddlength([_|T]) :- evenlength(T).

% Demonstration queries:
% ?- evenlength([1, 2, 3, 4]).
% ?- oddlength([1, 2, 3]).
