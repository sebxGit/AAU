--Exercise 1
lgd :: [a] -> Int
lgd xs = f(xs, id)
  where
    f ([], cont) = cont 0
    f((_:xs), cont) = f(xs, \n -> cont (n+1))

--Exercise 2
fib :: Int -> Int
fib n = f(n, id)
  where
    f (0, cont) = cont 1
    f (1, cont) = cont 1
    f (n, cont) = f(n-1, \r1 -> f(n-2, \r2 -> cont (r1+r2)))

--Exercise 3
-- En funktion som kalder sig selv er slack, da den først fejler i runtime men ikke well-typed
-- e.g. f f
-- da typen er f:: a -> b og f::a, så a= a->b
-- giver ikke køretidsfejl

--Exercise 4
-- 3 + ”2”        = '32'
-- 3 ∗ ”2”        = 6 
-- ”3” ∗ ”2”      = 2
-- 3 + {}         = '3[object Object]'
-- {} + 2         = 2
-- {3}            = 3
-- 3+{2}          = Uncaught SyntaxError: Unexpected number
-- {3}+2          = 2 