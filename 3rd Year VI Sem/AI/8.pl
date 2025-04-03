power(_, 0, 1).
power(Num, Pow, Ans) :-
    Pow > 0,
    Pow1 is Pow - 1,
    power(Num, Pow1, Ans1),
    Ans is Num * Ans1.

% Demonstration queries:
% ?- power(2, 3, Ans).
