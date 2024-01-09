-- prep question 1
data Onion a = Core a | Layer ( Onion a )
instance Functor Onion where
  -- fmap :: (a -> b) -> Onion a -> Onion b
  fmap g (Core a) = Core (g a)
  fmap g (Layer onion) = Layer (fmap g onion)

-- prep question 2
-- applicable laws that should hold:
-- pure id <*> x = x
-- pure (g x) = pure g <*> pure x

-- answer: you can see that the definitions of the funny star operator covers both cases.

-- --Exercise 1
data UTree a = Node a [UTree a] deriving Show

instance Functor UTree where
    --fmap :: (a -> b) -> UTree a -> uTree b
    fmap g (Node a xs) = Node (g a) (fmap (fmap g) xs)

a = Node 1 [Node 2 [], Node 3 [Node 4 []]]

--Exercise 2
-- instance Functor ((->) r) where
--     fmap f g = \x -> f(g x)
--     -- fmap f v = (f . v)

-- --Exercise 3
-- instance Applicative [] where
--     [] <*> _ = []
--     (g:gs) <*> xs = fmap g xs ++ (gs <*> xs)

-- exercise 4 (but did not find a solution with <*> )
prodthree xs ys zs = [x * y * z | x <- xs, y <- ys, z <- zs]