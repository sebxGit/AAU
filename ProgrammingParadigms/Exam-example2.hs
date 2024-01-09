-- problem 1.1
-- the type for partition can be seen below.
partition :: (a -> Bool) -> [a] -> ([a], [a])
-- polymorphism: It is parametric polymorphism, since it can take multiple types in

-- problem 1.2
partition p lst = (yes, no)
                  where
                    yes = [ x | x <- lst, p x]
                    no = [ x | x <- lst, not (p x)]
-- problem 1.3
partition' p [] = ([], [])
partition' p (x:xs) = if p x then (x:yes, no)
                      else (yes,x:no)
                        where
                          (yes,no) = partition' p xs

-- problem 2.1
data MixedTree a b = Empty | ALeaf a | BLeaf b | ANode a (MixedTree a b) (MixedTree a b) | BNode b (MixedTree a b) (MixedTree a b)


-- problem 2.2
t = BNode 4 (ANode "dudu" (BLeaf 2) (BLeaf 9)) (ANode "zyzy" (BLeaf 6) (BLeaf 7))

-- problem 2.3
data Label = A | B

islayered :: MixedTree a b -> Bool
islayeredWith :: MixedTree a b -> Label -> Bool

islayeredWith Empty _ = True
islayeredWith (ALeaf _) A = True
islayeredWith (BLeaf _) B = True
islayeredWith (ANode _ t1 t2) A = islayeredWith t1 B &&
                                  islayeredWith t2 B
islayeredWith (BNode _ t1 t2) B = islayeredWith t1 A &&
                                  islayeredWith t2 A
islayeredWith _ _ = False

islayered t = islayeredWith t A || islayeredWith t B

-- problem 3.1
-- 1. both forms, ad hoc, parametric
f :: (Eq a, Num a) => a -> a -> [b] -> (b, b)
f x y (z:zs) = if x == y then (head zs, z) else (z,z)

-- 2. both forms, ad hoc, parametric
g :: (Show a, Fractional a) => p -> a -> [Char]
g x y = show (y / 2.0)

-- 3. parametric 
h xs ys = xs ++ ys

-- 4. parametric
i :: (t1 -> t2) -> ((b, b) -> t1) -> b -> t2
i f g y = f( g (y,y))

-- problem 4.1
-- answer: is ad hoc and parametric

-- problem 4.2, using recursion
lists :: Int -> [[Int]]
lists 0 = []
lists n = replicate n n : lists (n+1)

-- problem 4.3, using higher-order functions (map)
lists' :: Int -> [[Int]]
lists' n = map (\x -> replicate x x) [n..]

-- problem 5.1
newtype Funpair a = Fun (Bool -> a, String -> a)

-- define expression mypair of type Funpair Integer
mypair :: Funpair Integer
mypair = Fun (f,g)
          where 
            f True = 42
            f False = 17
            g "horse" = 1
            g _ = -3

-- alternative solution
mypair2 :: Funpair Integer
mypair2 = Fun (\_ -> 42, \_ -> 17)

-- problem 5.2
instance Functor Funpair where
  -- fmap :: (a -> b) -> Funpair a -> Funpair b
  fmap f (Fun (g,h)) = Fun (f . g, f . h)

-- problem 6
data W x = Bingo x deriving Show

instance Functor W where
  fmap f (Bingo x) = Bingo (f x)

instance Monad W where
  return x = Bingo x
  Bingo x >>= f = f x

-- problem 6.1: write a definition of W as an applicative functor
instance Applicative W where
  -- pure :: a -> W a
  -- <*> W (a -> b) -> W a -> W b
  pure x = Bingo x
  Bingo f <*> Bingo x = Bingo (f x)

-- problem 6.2
wrapadd :: Int -> W Int -> W Int
wrapadd x w = do
                y <- w
                return (x+y)

temp v w = do
          x <- v
          y <- w
          return (x*y)