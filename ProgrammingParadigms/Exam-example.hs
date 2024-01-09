-- Problem 1
-- allAnswers f [] = Just []
-- allAnswers f (x:xs) = let fun = f x
--   in if (fun == Nothing) then Nothing
--   else x : (allAnswers f xs)
--     where x = x


-- 1. the code have the mistakes:
-- type in line 1 allAnswers :: -> -> Maybe [..]
-- whereas in line 4 (wtih else) allAnswers :: -> -> []
-- meaning there is a type error
-- where x=x is an infinite loop

-- 2. 
allAnswers' :: Eq b => (a -> Maybe b) -> [a] -> Maybe [b]
allAnswers' f xs = if (any (== Nothing) ys) then Nothing
                   else Just (map smth ys)
                   where 
                    ys = map f xs 
                    smth (Just x) = x

-- 3.
allAnswers'' f [] = Just []
allAnswers'' f (x:xs) = do
                          z <- allAnswers'' f xs
                          v <- f x 
                          return (v:z)

myfun x = if (x > 3) then (Just (x+3)) else Nothing

-- use allAnswers' myfun [17,4,5]

-- Problem 2
-- 1.
-- a.
f a (b,c) = if b == c then [a] else []
-- b. 
-- g :: Eq a => (a -> a -> Bool) -> Bool -> a -> a -> Bool
g f x y z = (f (head [y,z]) z) && x
-- c. 
h x action = do
  putStr (show x)
  result <- action
  putStrLn "completed"
  return result

-- or
h' x y = do
  putStr (show x)
  z <- getLine
  y

-- d.
applyToPair f x y = [f x, f y]

-- 2.
-- a. mixed polymorphism, parametric for a2, ad hoc for a1

-- b. ad hoc only (overloading)

-- c. mixed polymorphism, parametric for b, ad hoc for a

-- d. parametric polymorphism only

-- Problem 3
-- 1.
data Tree a = Leaf a | Node (Tree a) (Tree a)
t :: Tree String
t = Node (Leaf "dog") (Node (Leaf "cat") (Leaf "hamster"))

-- 2.
minimax :: Ord a => Tree a -> (a, a)
minimax (Leaf x) = (x, x)
minimax (Node l r) = (u,v)
  where (x1, y1) = minimax l
        (x2, y2) = minimax r
        u = min x1 x2
        v = max y1 y2

-- Problem 4
-- 1.
echo =  (putStr "Please type a word:") >>= (\_ -> getLine >>= (\s -> putStrLn("You typed " ++ s)))
      
-- 2.
seconds = do
            s <- getLine
            let blist = read s :: [(Bool, Bool)]
                w = map (\(x,y) -> y) blist in
                do
                  putStr (show w)

-- Problem 5
-- 1. This is not allowed in Haskell, since Haskell only allows lists containing one type only
-- 2. 
data Alternating a b = Empty | Cons a (Alternating b a) deriving Show
myalt = Cons 5 (Cons True (Cons 6 (Cons False (Cons 7 (Cons True Empty)))))

-- separate :: Alternate a b -> ([a],[b])

-- 3.
separate Empty = ([],[])
separate (Cons x Empty) = ([x], [])
separate (Cons x (Cons y z)) = (x:xs, y:ys)
                                      where
                                        (xs, ys) = separate z

-- 4.
large n = Cons n (Cons nas (large (n+1))) 
          where
            nas = replicate n 'a'

inflist = large 1

-- Problem 6
newtype ToPairs a = TP (a,a)

-- 1.
-- val1 :: ToPairs Bool
val1 = TP (True, False)

val2 :: ToPairs ((Maybe Int) -> Int)
val2 = TP (f,g)
          where 
            f Nothing = 1
            f (Just x) = x
            g Nothing = 2
            g (Just x) = x

-- 2.
instance Functor ToPairs where
  -- fmap :: (a -> b) -> ToPairs a -> ToPairs b
  fmap f (TP(x,y)) = TP(f x, f y)

-- 3.
instance Applicative ToPairs where
  -- pure :: a -> ToPairs a
  -- <*> :: ToPairs (a -> b) -> ToPairs a -> ToPairs b
  pure x = TP (x,x)
  (TP (f,g)) <*> (TP (u,v)) = TP (f u,f v)
