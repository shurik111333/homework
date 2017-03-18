find :: [Int] -> Int -> Int
find xs n = find xs n 1
	where
		find :: [Int] -> Int -> Int -> Int
		find [] n k = -1
		find (x:xs) n k 
			| x == n = k 
			| otherwise = find xs n (k + 1)