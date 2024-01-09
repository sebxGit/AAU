--Exercise 1
fourfirst xs = do
  x <- xs
  return (4,x)

fourFirstBind xs = 
  xs >>= \x ->
    return (4,x)

-- answer: it is because bind is between the lines
-- the function ofc. does [(4,x_1), (4,x_2) ...]

--Exercise 2
data W x = Bingo x deriving Show

instance Functor W where
  fmap f (Bingo x) = Bingo (f x)

instance Applicative W where
  -- pure :: a -> W a
  pure x = Bingo x

  -- (<*>) :: W (a -> b) -> W a -> W b
  Bingo f <*> Bingo x = Bingo (f x)

instance Monad W where
  return x = Bingo x
  Bingo x >>= f = f x

-- answer: Vi unpacker, da det er pakket ind i Bingo.
wrapadd :: Num b => b -> W b -> W b
wrapadd x y = do
  z <- y
  return (x + z)

h :: Num b => W b -> W b -> W b
h x y = do
  a <- x
  z <- y
  return (a * z)

--Exercise 3
data Tree a = Leaf a | Node (Tree a) (Tree a)
minmax :: Ord a => Tree a -> Maybe (a, a)
minmax (Leaf x) = Just (x, x)
minmax (Node l r) = do
  (minL, maxL) <- minmax l
  (minR, maxR) <- minmax r
  if (minL > minR) || (maxL > maxR) then
    Nothing
  else
    return (minL, maxL)

minorder x = do
  (min, _) <- minmax x
  return min
