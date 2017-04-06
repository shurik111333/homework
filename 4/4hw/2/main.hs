module Main where

import Text.Read

main = do loop []
    where
        loop l = do
            printInstructions
            s <- getLine
            case s of
                "0" -> return()
                "1" -> doWithList add "add" >>= loop
                "2" -> doWithList remove "remove" >>= loop
                "3" -> (putStrLn . show) l >> loop l
                _   -> loop l
            where
                printInstructions = do
                    putStrLn "0 - exit"
                    putStrLn "1 - add value to list"
                    putStrLn "2 - remove value from list"
                    putStrLn "3 - print list"
                doWithList f s = do
                    putStrLn ("Enter value for " ++ s)
                    x <- getLine >>= (return . readMaybe)
                    case x of
                        Nothing -> doWithList f s
                        Just x  -> return (f l x)

add :: [Integer] -> Integer -> [Integer]
add [] x                = [x]
add (a:l) x | a < x     = a : add l x
add (a:l) x | otherwise = x : a : l

remove :: [Integer] -> Integer -> [Integer]
remove [] x                = []
remove (a:l) x | a == x    = l
remove (a:l) x | otherwise = a : remove l x
