-- Exercise 1
test1 :: (Ord a, Num a) => a -> a -> [[Bool]] -> Bool
test1 x y bools = x < y && all or bools

fstAndAdd :: Num a => (t -> a, t) -> a -> a
fstAndAdd (f, x) y = f x + y

-- Fractional t1 => (t2 -> t1) -> (t2 -> t1) -> (t1 -> t3) -> t2 -> t3

-- Exercise 2 && Exercise 3
triples :: Num a => [(a,a,a)] -> ([a],[a],[a])
triples [] = ([],[],[])
triples ((a,b,c):xs) = (a:as, b:bs, c:cs)
  where (as, bs, cs) = triples xs
