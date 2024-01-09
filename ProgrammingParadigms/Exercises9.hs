-- prep question 1
mainz :: IO ()
mainz = do 
  putStrLn "What is your name?"
  name <- getLine
  putStrLn ("Hello " ++ name)

  -- prep question 2
  sequence_ [putStr "rip", putStr "rap", return ()]
  -- complains since you need to return at least a tuple

-- Exercise 1
-- loops through each iteration until 1 is found. x/2 if even, otherwise 3x + 1
main = do
  w <- getLine
  loop ( (read w) :: Int)
  where
    loop 1 = putStr (show 1)
    loop x = do
      putStr (show x)
      if even x
        then loop (x `div` 2)
        else loop (3*x + 1) 

-- Exercise 2 
letters = do
    w <- getLine
    loop w
    where
        loop [] = return()
        loop (x:xs) = do
            putChar x
            putChar '\n'
            loop xs
    
-- Exercise 3
letters_ = do 
    w <- getLine
    sequence_ [putStrLn [x] | x <- w]

--exercise4
hugorm :: IO()
hugorm = do
    putStr "How many numbers would you like to add? "
    ns :: Int <- readLn
    let y = [ putStrLn (show val) | val<-[1..ns]]
    sequence_ y
    let theSum = sum([1..ns])
    putStr "The sum is"
    putStr (show theSum)

