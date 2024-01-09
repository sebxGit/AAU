-- prep question 1
-- quango :: a -> [a]

-- answer: 
-- is polymorphic since variable a can be different types
-- not overloaded, since no type class is defined for a.

-- tango :: Num p1 => ( a, b ) −> p2 −> p1

-- answer: 
-- is polymorphic, since it takes different types in
-- is overloaded, since it takes a Num type class in for p1

-- prep question 2: Lambda calculus, skipped

-- exercise 1
-- type is (t -> t) -> t -> t
-- since it takes a function (t -> t) and a value x (-> t)
-- and returns the evaluated expression (-> t)
twice f x = f (f x)

-- it is parametric polymorphic, but not overloaded

-- exercise 2: Lambda calculus, skipped

-- exercise 3
-- type is (t, t) -> [t]
-- (t, t) since it takes two parameters from a tuple
-- -> [t] since it is simply the type array with two elements
dingo (x,y) = [x,y]

-- it is parametric polymorphic but not overloaded

-- exercise 4: has to be Int instead of Num, as some types in 
-- type class Num does not allow this.
test :: [Int] -> Int
test (n:ns) = n

-- exercise 5: answer: some function types are probably not comparable
-- and therefore I believe function types are not in the Eq type class

-- extra questions a.
-- type is Num a => a -> a -> a -> a
mango x y z = x * y + z - 42

-- extra questions b.
bingo :: a -> a
bingo x = x
-- parametric polymorphism yes, overloading no

-- extra questions c.
-- type is (Num a, Num b) => [(a,b)] -> [(a,b)]

-- extra questions d.
-- the type of [ (+) , ( ∗ ) , (+) , (−) , (++) ] is that
-- it is of Eq type class, but a part of Num type class
-- answer: [(+), (*)] :: Num a => [a -> a -> a]

-- extra questions e.
double n = 2 * n
-- type: map double [1,2,3,4] :: Num b => [b]

-- skipping extra questions f. and g.