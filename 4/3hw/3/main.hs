find :: [Int] -> Int
find l = find' l 0 (-1) 2
    where
        find' :: [Int] -> Int -> Int -> Int -> Int
        find' l _ i _ | (length l) < 3 = i
        find' (a:b:c:l) m im i = if (a + c) > m || im == (-1)
                                    then find' (b:c:l) (a + c) i (i + 1)
                                    else find' (b:c:l) m im (i + 1)