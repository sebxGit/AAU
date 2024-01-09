-- prep question 1
positions :: String -> [Int]
positions = map (\c -> fromEnum c - 96)

-- prep question 2
sumsq :: Int -> Int
sumsq n = foldr (\x acc -> x^2 + acc) 0 [1..n]

-- exercise1
within :: [Int] -> (Int, Int) -> [Int]
within xs (a,b) = filter (\x -> x >= a && x <= b) xs

-- exercise2
sumrows :: [[Int]] -> [Int]
sumrows = map sum

-- exercise3
fact k = product [1..fromIntegral k]

approx :: Int -> Double
approx n = sum (map (\k -> 1 / fromIntegral (fact k)) [0..n])

-- exercise4
fingo :: [a] -> [a] -> [a]
fingo xs ys = foldr (:) xs ys
-- 4:5:6:1:2:3:[]

-- exercise5
--map map :: [a -> b] -> [[a] -> [b]]
--because it takes multiple instances, turns map map into list of functions

-- extra question 1 skipped

-- extra question 2
foldrFilter :: (a -> Bool) -> [a] -> [a]
foldrFilter p = foldr (\x acc -> if p x then x : acc else acc) []

-- extra question 3
-- elem returns true if list contains an item equal to the first argument
remove :: String -> String -> String
remove xs ys = foldr (\x acc -> if x `elem` xs then acc else x : acc) [] ys

-- extra question 4
count a xs = length [x|x<-xs, a==x]

min2 xs = if (count minValue xs > 1) then minValue else min2Value
  where
    minValue = foldr1 min xs
    min2Value = foldr1 min (filter (/=minValue) xs)