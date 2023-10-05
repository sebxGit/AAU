--exercise set 5
-- opg1
rev :: [a] -> [a]
rev [] = []
rev (x:xs) = rev xs ++ [x]

-- opg2
mylast :: [a] -> b
mylast 
