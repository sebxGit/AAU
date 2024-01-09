-- COMMANDS --
-- see types   		> :t "apple"   result: "apple" :: String
-- reload ghci 		> :r (u don't have to exit and re-enter ghci after changes)
-- clear terminal > :! cls   or   :! clear   (depends on OS)


-- TYPES CLASSES -- 
-- Eq:    equivalence type class
-- Enum:  allows sequential or ordered functionality
--        commands: succ, pred, Bool, Char etc.  
--                  (> succ 12  is successor of 12 aka. 13)
--                  (> pred 5   is the preceding item in enum 4)
-- Ord:   ordering types, allowing comparison operators < > <= etc., 
--        types: Int Integer Float Double Bool Char
-- Num:   takes classes with numeric operations
--        types: Int Integer Float Double
-- Integral: subclass of Num for types Int Integer
-- Floating: subclass of Num for types Float Double
-- show:  printing arguments converted to a String
-- read:  printing arguments converted to an Int


-- BUILT IN FUNCTIONS -- (works on strings too)
-- head     [1,2,3] -> 1        	get first element 
-- last     [1,2,3] -> 3        	get last element
-- tail     [1,2,3] -> [2,3]    	remove first element
-- init     [1,2,3] -> [1,2]    	remove last element
-- null     [1,2,3] -> false    	return true if empty 
-- reverse  [1,2,3] -> [3,2,1]  	get reverse list
-- length   [1,2,3] -> 3        	get length of list
-- take 2   [1,2,3] -> [1,2]    	take x first elements
-- drop 2   [1,2,3] -> [3]      	drop x first elements
-- maximum  [1,2,3] -> 3        	get maximum number
-- minimum  [1,2,3] -> 1        	get minimum number
-- sum      [1,2,3] -> 5        	get sum of list elements
-- product  [1,2,3] -> 6        	get product of list elements
-- [1,2,3] !! 1			-> 2					select element at position
-- [1,2,3] ++ [4] 	-> [1,2,3,4]	appends two lists
-- [1,2] : [3] : [] -> [1,2,3,4]  prepend elements to last element


-- with predicates (pred)
-- all pred [2,4,6,8] -> True/False		decides if all elements satisfy the predicate
-- any pred [2,4,6,8] -> True/False		decides if any elements satisfy the predicate
-- takeWhile pred [2,4,6] -> result		take element while predicate is satisfied
-- dropWhile pred [2,4,6] -> result		drop element while predicate is satisfied
-- 14 `elem` [1,2,14]			-> True			returns True if list contains item equal to the first argument


-- higher-order functions, function (func), predicate (pred), operator (op), variable (var, can be any type)
-- map func [2,4,6,8] -> result				maps the function into every element of the list
-- filter pred [2,4,6] -> result			filters (selects) elements from list satisfying the predicate
-- funcName = foldr (op) var					fold right applies operator on all elements in list 
--																		the var is needed to finish the folding correctly
-- funcName = foldl (op) var					fold left applies operator on all elements in list 
--																		likewise but with left associativity instead
-- iterate pred var 									iteratively applies the function infinitely, meaning that:
--																		[x, f x, f (f x), f (f (f x)) etc.] (use lazy evaluation)
-- replicate int var									replicates var, int times.
-- (.) :: (a->b) -> (b->c) -> (a->c)	composite operator combines the two functions into a single function
-- 				f . g = \x -> f (g x) 			


-- interactive functions, value (v)		(program now has side effects)
-- getChar 		x <- getChar 						waits until one character is typed
-- getCh			x <- getCh							takes one character but does not echo the character
-- getLine 		xs <- getLine						reads a string of characters from the keyboard, terminated by newline char '\n'
-- sgetLine 	xs <- getLine						reads a string of characters but echoes characters using '-' symbol (keep word secret)
-- putChar 														writes the character to the screen, returning an empty tuple
-- putString "string"									writes the string to the screen, returning an empty tuple
-- putStringLn "string"								writes the string to the screen, returning an empty tuple
-- return v														returns result value without any interaction with the user
-- show xs 														shows the element in the terminal


-- FUNCTION APPLICATION 
-- math 	vs 	haskell
-- f(x) 			-> f x
-- f(x,y) 		-> f x y
-- f(g(x))		-> f (g x)
-- f(x,g(y))	-> f x (g y)
-- f(x)g(y) 	-> f x * g y

-- MODULES -- (works on strings too)
-- splitAt 2    [1,2,3] -> ([1,2], [3])   split at index

-- requirement: import Data.List
-- sort         [1,3,2] -> [1,2,3]        sorts a list
-- intersperse '.' "usa" -> "u.s.a"       inserts characters in between

-- requirement: import Data.Char 
-- toUpper      'a' -> 'A'
-- toLower      'A' -> 'a'


-- THINGS TO KNOW --

-- curied functions take their ARGUMENTS ONE AT A TIME
-- e.g. add :: Int -> Int -> Int

-- uncurried functions does NOT TAKE ARGUMENTS ONE AT A TIME
-- e.g. fst :: (a,b) -> a							(takes variable a and b in one tuple)

-- parametric polymorphism takes MULTIPLE TYPES OF VARIABLES IN
-- e.g. length :: [a] -> Int 					(variable a can be any type)
-- e.g. take :: Int -> [a] -> [a]

-- ad-hoc polymorphism (overloading) is when a function CONTAINS ONE OR MORE CLASS RESTRAINTS.
-- e.g. (+) :: Num a => a -> a -> a 	(variable a has type constraint Num and is overloaded)

-- higher-order function is when a function: TAKES A FUNCTION AS AN ARGUMENT OR
-- 																					 RETURNS A FUNCTION AS A RESULT
