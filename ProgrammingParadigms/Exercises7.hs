-- prep question 1
data Unary = Z | I Unary

unary2int :: Unary -> Integer
unary2int Z = 0
unary2int (I n) = 1 + unary2int n
-- requires: unary2int (I (I (I (I Z))))

-- prep question 2 (names used below too)
--data Tree a = Leaf a | Node (Tree a) a (Tree a) 
-- least :: Ord a => Tree a -> Int

-- exercise 1
data Aexp = Add Aexp Aexp | Var String | Const Integer | Mul Aexp Aexp

-- exercise 2
type Assignment = [(String, Integer)]
eval :: Aexp -> Assignment -> Integer
eval (Add e1 e2) ass = eval e1 ass + eval e2 ass
eval (Var x) ass = case lookup x ass of
                Just val -> val
                Nothing -> error ("Variable " ++ x ++" not found in assignment")
eval (Const n) _ = n
eval (Mul e1 e2) ass = eval e1 ass * eval e2 ass
-- let ass = [("x", 3), ("y", 4)]
-- eval (Add (Mul (Const 2) (Var "x")) (Var "y")) ass
-- answer: 10

-- exercise 3
data Dir = Var2 String | Mult Dir Dir | Subdir Dir 

-- exercise 4, see https://gist.github.com/Kedrigern/1239141/5ee8f5f45facdf4f48785fc92a78ad4104f16537
data Tree a = Leaf a | Empty | Node (Tree a) a (Tree a)
insert :: Ord a => Tree a -> a -> Tree a
insert Empty a = Node Empty a Empty
insert (Node left a right) b
  | b == a = Node left a right
  | b < a = Node (insert left b) a right
  | b > a = Node left a (insert right b)

-- exercise 5
class InVector a where
  (&&&) :: a -> a -> a
  (∗∗∗) :: a -> a -> Int

instance InVector Bool where
  (&&&) = (&&)
  (∗∗∗) True True = 1
  (∗∗∗) _ _ = 0

-- extra questions: skipped