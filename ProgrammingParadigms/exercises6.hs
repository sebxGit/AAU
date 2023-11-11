--exercise1
within :: Ord a => [a] -> (a,a) -> [a]
within xs (a,b) = [x | x <- xs, x >= a, x <= b]

--exercise2
-- sumrows :: Ord a => [[a]] -> [a]
-- sumrows (xs:xss) = [x | x <- sum xs] : sumrows xss

--exercise3
fact k = product [1..k]

approx :: Double -> Double
approx 0 = 1
approx n = (1 / fact n) + approx (n-1)

--exercise4
fingo :: [a] -> [a] -> [a]
fingo xs ys = foldr (:) xs ys
-- 4:5:6:1:2:3:[]

fingo2 :: [a] -> [a] -> [a]
fingo2 = foldr (:)

--exercise5
--map map :: [a -> b] -> [[a] -> [b]]
--because it takes multiple instances, turns map map into list of functions
