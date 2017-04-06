module Main where

import Text.Read
import Record

main = loop [] where
    loop book = do
        printInstructions
        c <- getLine
        case c of
            "0" -> return ()
            "1" -> addRecord >>= loop
            "2" -> findByName >> loop book
            "3" -> findByPhone >> loop book
            "4" -> saveToFile >> loop book
            "5" -> loadFromFile >>= loop
            _   -> loop book
        where
            printInstructions = do
                putStrLn "0 - exit"
                putStrLn "1 - add a record"
                putStrLn "2 - find record by name"
                putStrLn "3 - find record by phone"
                putStrLn "4 - save to file"
                putStrLn "5 - load from file"
                
            addRecord = do
                name <- getName
                phone <- getPhone
                return (add book (Record name phone)) where
                    add book r | any (== r) book = book
                    add book r | otherwise = r : book
            
            findByName = do 
                recName <- getName
                printResult (filter ((== recName) . name) book)
            
            findByPhone = do
                recPhone <- getPhone
                printResult (filter ((== recPhone) . phone) book)
            
            saveToFile = getFile >>= (flip writeFile) (unlines (map (encode) book))
            
            loadFromFile = do
                content <- getFile >>= readFile
                return (map (decode) (lines content))
            
            printResult [] = putStrLn "No records found" >> return ()
            printResult l  = (putStrLn . show) l >> return ()
            
            getName = putStrLn "Enter name" >> getLine
                
            getPhone = do
                putStrLn "Enter phone"
                phone <- getLine >>= return . readMaybe
                case phone of
                    Nothing -> getPhone
                    Just x  -> return x
            
            getFile = putStrLn "Enter file name" >> getLine
