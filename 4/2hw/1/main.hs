myReverse :: [Int] -> [Int]
myReverse x = reverse x []
	where
		reverse :: [Int] -> [Int] -> [Int]
		reverse [] y = y
		reverse (x:xs) y = reverse xs (x:y)