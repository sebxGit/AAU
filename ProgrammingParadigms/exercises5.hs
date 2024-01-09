-- prep question 1
replic :: Int -> a -> [a]
replic 0 x = []
replic n x = x : replic (n-1) x

-- prep question 2
improve :: [a] -> [a]
improve [] = []
improve (x:xs) |  length xs > 1 = x : improve (tail xs)
               |  otherwise = x : improve xs

-- exercise 1
rev :: [a] -> [a]
rev [] = []
rev (x:xs) = rev xs ++ [x]

-- exercise 2
mylast :: [a] -> a
mylast [x] = x
mylast (_:xs) = mylast xs

-- exercise 3
isolate :: Eq a => [a] -> a -> ([a], [a])
isolate xs z = (noteq, eq) where
  noteq = [a | a <- xs, a /= z]
  eq = [b | b <- xs, b == z]

-- exercise 4
wrapup :: Eq a => [a] -> [[a]]
wrapup [] = []
wrapup [x] = [[x]]
wrapup (x:xs) = if x == h
                then (x:fst):rst
                else [x] : (fst:rst)
                where fst:rst = wrapup xs
                      (h:t) = fst

-- exercise 5
triples :: Num a => [(a,a,a)] -> ([a],[a],[a])
triples [] = ([],[],[])
triples ((a,b,c):xs) = (a:as, b:bs, c:cs)
  where (as, bs, cs) = triples xs

-- extra questions a.
rle :: Eq a => [a] -> [(a, Int)]
rle [] = []
rle (x:xs) = go x 1 xs
  where
    go :: Eq a => a -> Int -> [a] -> [(a, Int)]
    go curr count [] = [(curr, count)]
    go curr count (y:ys)
      | curr == y = go curr (count + 1) ys
      | otherwise = (curr, count) : go y 1 ys

-- extra questions b.
amy :: (a -> Bool) -> [a] -> Bool
amy f [] = False
amy f (x:xs) | f x = True
             | otherwise = amy f xs

-- extra questions c. and d. skipped