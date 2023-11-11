--exercise set 2
-- opg1
allbutsecond :: (Ord a) => [a] -> [a]

allbutsecond [] = []
allbutsecond (x:xs) = [x] ++ (tail test)
                      where test = [a | a <- xs]

-- opg2

midtover :: (Ord a) => [a] -> ([a], [a])
midtover myList = splitAt ((length myList) `div` 2) myList

-- opg3
bingo (x,y) = x `mod` z
              where z = y + 42

-- a. returns last element of a given list
final myList = head (reverse myList)

-- b. qsort in descending order
qsort :: (Ord a) => [a] -> [a]

qsort [] = []
qsort (x:xs) = big  ++ [x] ++ small
                 where small = qsort [a | a <- xs, a <= x]
                       big   = qsort [a | a <- xs, a > x]

-- c. what happens if < instead of <= in qsort? ANSWER: no difference spotted,
--    	   	      		      	 	        as x is already placed
--							in the middle.
qsort2 [] = []
qsort2 (x:xs) = big  ++ [x] ++ small
                 where small = qsort [a | a <- xs, a < x]
                       big   = qsort [a | a <- xs, a > x]