listPower2 :: Int -> [Int]
listPower2 n = listPower2 n 2
	where 
		listPower2 :: Int -> Int -> [Int]
		listPower2 0 k = []
		listPower2 n k = k:listPower2 (n - 1) (2 * k)