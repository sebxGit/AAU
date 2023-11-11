--exercise set 4
-- opg1
sevens :: Int  -> [Int]
sevens k = [x | x <- [1..k], x `mod` 7 == 0]

-- opg2
pyt :: Int -> [(Int, Int, Int)]
pyt k = [(a,b,c) | a <- [1..k], b <- [1..k], c<-[1..k], a^2 + b^2 == c^2]

-- opg3
-- headsup :: Eq a => [] -> Bool
headsup x = if head x == head (tail x) then True else False

-- opg4
temp :: Int -> Int -> Int -> Int
temp = \x -> (\y -> (\z -> x+y+z))

-- opg5

temp2 :: (Ord a1, Eq a2) => a2 -> a2 -> (a1,a1)->a1
temp2 a b (x,y) = if a > b then a else if (x/=y) then a else b

-- a
flop :: Ord a => (a,a) => [(a,a)]
flop (x,y) = 