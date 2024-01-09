-- Exercise 1
-- forklaring: Den bruger outermost, lazy evaluation, så den tager 5.
-- x = 1 : (map (1+) x)
-- take 5 x
-- take 5 (1: map (1+) x)
-- = 1 : take 4 (map (+1) (1: (map (+1) x)))
-- = 1 : take 4 ( ((1+1) (map (+1)) (map (+1) x)))
-- = 1 : take 4 (2 : (map (+1) (map(+1) x))))
-- = 1 : 2 : take 3 ((map (+1) (2: (map (+1) x))))

-- Exercise 2
fibsfrom n1 n2 = n1 : n2 : fibStep n1 n2
  where 
    fibStep n1 n2 = n1 + n2 : fibStep n2 (n1+n2)

fibsfrom2 a b = a : fibsfrom2 b (a+b)

-- the normal fib definitino with recursion
fib :: (Eq t, Num t, Num a) => t -> a
fib 1 = 1
fib 2 = 1
fib n = fib (n-1) + fib (n-2)

--Exercise 3
-- del 1: Typen er som set forneden
indflet :: a -> [a] -> [a]
indflet _ [] = [] 
indflet _ [x] = [x]
indflet e (x:y:ys) = x : e : indflet e (y:ys)

-- evaluering af: head (indflet 1 (2:undefined))
-- tager outermost, kræver evaluering af inner: head (indflet 1 (2:undefined))
-- indflet 1 (2:undefined) prøver på base case, kan godt med empty list
-- indflet 2, prøver på 2nd case, fejler pga. den skal nå enden af listen for at kunne evaluere om det er en liste, altså 2:undefined:[] hvor undefined giver fejl.

--Exercise 4
