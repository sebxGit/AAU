--Exercise 1 (not done)
-- (Ord a, Num a) => a -> a -> [[Bool]] -> Bool
-- Num a => (t -> a, t) -> a -> a
-- Fractional t1 => (t2 -> t1) -> (t2 -> t1) -> (t1 -> t3) -> t2 -> t3

--Exercise 3
triples :: [(a, b, c)] -> ([a], [b], [c])
triples [] = ([], [], [])
triples ((a, b, c):xs) = (a:as, b:bs, c:cs)
    where (as, bs, cs) = triples xs

--Exercise 4
cfrac :: Float -> Float -> [a]
cfrac r 0 = []
cfrac r _ = 