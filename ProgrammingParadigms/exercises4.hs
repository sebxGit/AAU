-- prep question 1
onlytwo :: [a] -> Bool
onlytwo [_,_] = True
onlytwo _ = False

-- prep question 2
alldots :: Num a =>  [(a,a)] -> [(a,a)] -> [a]
alldots ps qs = [ a*c + b*d| (a,c) <- ps, (b,d) <- qs]

-- exercise 1
sevens :: Int -> [Int]
sevens k = [x | x <- [1..k], (x `mod` 7) == 0 && x < k]

-- exercise 2
pyt :: Int -> [(Int,Int,Int)]
pyt k = [(a,b,c) | a <- [3..k], b <- [4..k], c <- [5..k], a <= b && b < c && a^2 + b^2 == c^2]

-- exercise 3
--headsup x = if head x == head ( tail x ) then True else False
--you can just write headsup x = head x == head ( tail x)
headsup :: Eq a => [a] -> Bool
headsup x = head x == head ( tail x)

-- exercise 4
-- plonk x y z = x+y+z equivalent in lambda expressions is:
plonk = \x -> (\y -> (\z -> x+y+z))

-- exercise 5
test :: (Ord a1, Eq a2) => a2 -> a2 -> (a1, a1) -> a1
test a b (c,d) = if a == b then c else d

-- extra question a.
flop :: [(a,b)] -> [(b,a)]
flop xs = [(b,a) | (a,b) <- xs]

-- extra question b.
dupli :: [Int] -> [Int]
dupli xs = concat [ [x, x] | x <- xs]

-- extra question c. skipped

-- extra question d. skipped

-- extra question e. skipped