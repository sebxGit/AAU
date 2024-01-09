--exercise set 2

-- prep question 1
prod :: [Int] -> Int
prod [] = 1
prod (n:ns) = n * prod ns

-- prep question 2
second :: [a] -> a
second ns = ns !! 1

-- exercise 1
allbutsecond :: [a] -> [a]
allbutsecond ns = [head ns] ++ drop 2 ns

allbutsecond2 :: [a] -> [a]
allbutsecond2 (n:ns) = [n] ++ tail ns

-- exercise 2
midtover :: [a] -> ([a],[a])
midtover ns = (take (length ns `div` 2) ns, drop (length ns `div` 2) ns) 

midtover2 :: (Ord a) => [a] -> ([a], [a])
midtover2 ns = splitAt ((length ns) `div` 2) ns

-- exercise 3: solution is mod -> `mod` and indentations on where
bingo (x,y) = x `mod` z
  where
    z = y + 42

-- extra questions a.
final :: Ord a => [a] -> a
final ns = head (reverse ns)

-- extra questions b. change to descending order qsort
qsort [] = []
qsort (x:xs) = qsort larger ++ [x] ++ qsort smaller
  where
    smaller = [a | a <- xs, a <= x]
    larger = [b | b <- xs, b > x]

-- extra questions c. replace <= with <
qsort2 [] = []
qsort2 (x:xs) = qsort smaller ++ [x] ++ qsort larger
  where
    smaller = [a | a <- xs, a < x]
    larger = [b | b <- xs, b > x]
-- answer: it puts every second element into the list regardless of ordering