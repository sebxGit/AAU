import Control.Applicative
import Parsing

-- ghc −I. −−make Parsing.hs

-- Exercise 1
-- can cause left recursion and hard to follow what the parser actually does
-- and if the grammar is actually followed.
-- better to split it up and simplify
-- Exercise 2
data Rexp = A | B | Conc Rexp Rexp | Union Rexp Rexp | Star Rexp 
              | Par Rexp deriving Show

-- R -> S U R | S
-- S -> F . S | F
-- F -> B* | B
-- B -> a | b | (R)

-- regexp = do
--   s <- summand
--   symbol "U"
--   r <- regexp
--   return (Union s r)
--   <|>
--   do
--     s <- summand
--     return s

-- summand = do
--   f <- factor
--   symbol "."
--   s <- summand
--   return (Conc f s)
--   <|>
--   do
--     f <- factor
--     return f

-- factor = do
--   b <- base
--   symbol "*"
--   return (Star b)
--   <|>
--   do
--     b <- base
--     return b

-- base = do
--   symbol "a"
--   return A
--   <|>
--   do 
--     symbol "b"
--     return B
--   <|>
--   do
--     symbol "("
--     r <- regexp
--     symbol ")"
--     return (Par r)

-- e.g. usage > parse regexp "(aUb)*.b"
-- result: [(Conc (Star (Par (Union A B))) B,"")]


-- ALTERNATIVE

-- Formation rules:
-- R ::= a | b | R1 ◦ R2 | R1 ∪ R2 | R* | (R_1)
-- These formation rules do not show how each input should be parsed e.g. what output it should return

-- value =
--   do
--     some (char 'a')
--     <|> some (char 'b')
--     <|> error "Invalid char"

-- concatn = do
--   x <- regex
--   char 'o'
--   y <- regex
--   return x

-- union = do
--   x <- regex
--   char 'U'
--   y <- regex
--   return x <|> return y

-- paranth =
--   do
--     char '('
--     x <- regex
--     char ')'
--     return x
--     <|> value

-- regex =
--   do
--     paranth
--     <|> union
--     <|> concatn
--     <|> value

-- -- regexp = do
-- --  do
-- --    char "a"
-- --    <|> char "b"
-- --  do
-- --    char "b"
-- --    many (char "c")
-- --    return "Ok"