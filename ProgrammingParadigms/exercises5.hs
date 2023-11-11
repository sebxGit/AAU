--exercise set 5
-- opg1
rev :: [a] -> [a]
rev [] = []
rev (x:xs) = rev xs ++ [x]

myrev :: [a] -> [a]
myrev xs = [xs !! (length xs - a) | (a,b) <- zip [1..] xs]

rev2 :: [a] -> [a]
rev2 = foldl (\acc x -> x : acc) []

--opg2
mylast :: [a] -> a
mylast xs = xs !! (length xs - 1)

mylast2 :: [a] -> a
mylast2 [x] = x
mylast2 (_:xs) = mylast2(xs)

--opg3
-- isolate :: eq a => [a] -> x -> ([a],[a])
-- isolate (x:xs) z = (noteq, eq) where{
--   | noteq = [a | a <- xs, a /= z]
--   | eq = [b | b <- xs, b = z]
-- }

--opg4
wrapup :: Eq a => [a] -> [[a]]
wrapup [] = []
wrapup [x] = [[x]]
wrapup (x:xs) = if x == h
                then (x:fst):rst
                else [x] : (fst:rst)
                where fst:rst = wrapup xs
                      (h:t) = fst

--opg5
-- triples :: Num a => [(a,a,a)] -> ([a],[a],[a])
-- triples [(a,b,c)] = ([a],[b],[c])
-- triples (x:xs, y:ys, z:zs) = [x,y,z] : triples [(xs,ys,zs)]