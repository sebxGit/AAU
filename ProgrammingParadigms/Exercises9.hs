
--exercise2 
letters = do
    w <- getLine
    loop w
    where
        loop [] = return()
        loop (x:xs) = do
            putChar x
            putChar '\n'
            loop xs
    
--exercise3
letters_ = do 
    w <- getLine
    sequence_ [putStrLn [x] | x <- w]

--exercise4
-- hugorm :: IO()
-- hugorm = do
--     putStr "How many numbers would you like to add? "
--     ns :: Int <- readLn
--     let y = [ putStrLn (show val) | val<-[1..ns]]
--     sequence_ y
--     let theSum = sum([1..ns])
--     putStr "The sum is"
--     putStr (show theSum)

-- hugorm = do putStr "How many numbers would you like to add? "
--   w <- getLine
--   loop (read w :: Int) 0
--   where
--     loop 0 a = putStrLn ("The sum is" ++ show a)
--     loop x a = do n <- getLine
--       loop (x-1) (a+(read n ::Int))

    -- w <- getLine
    -- loop ( (read w) :: Int)
    -- where
    --     loop (x:xs) = do
    --         putStr (show x)
    --         loop (xs)