
--exercise1
data Aexp = Add Aexp Aexp | Var String | Int | Mul Aexp Aexp
type Ass k v = [(k, v)]

--exercise2
-- eval :: Aexp -> Ass -> Int
-- eval exp t = foldr exp t

--exercise3
--data Dir a String b Int = Empty Null | Mult Dir Dir | Subdir Dir

--exercise4, see https://gist.github.com/Kedrigern/1239141/5ee8f5f45facdf4f48785fc92a78ad4104f16537
data Tree a = Leaf a | Empty | Node (Tree a) a (Tree a)
insert :: Ord a => Tree a -> a -> Tree a
insert Empty a = Node Empty a Empty
insert (Node left a right) b
  | b == a = Node left a right
  | b < a = Node (insert left b) a right
  | b > a = Node left a (insert right b)

--exercise5
-- type Vector a = (a,a)
-- addVector :: Vector a -> Vector a -> Vector a