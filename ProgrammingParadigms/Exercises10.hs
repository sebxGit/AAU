--Exercise 1
data UTree a = Node a [UTree a] deriving Show

instance Functor UTree where
    --fmap :: (a -> b) -> UTree a -> uTree b
    fmap g (Node a xs) = Node (g a) (fmap (fmap g) xs)

a = Node 1 [Node 2 [], Node 3 [Node 4 []]]

--Exercise 2
-- instance Functor ((->) r) where
--     fmap f g = \x -> f(g x)
--     -- fmap f v = (f . v)

--Exercise 3
instance Applicative [] where
    [] <*> _ = []
    (g:gs) <*> xs = fmap g xs ++ (gs <*> xs)
