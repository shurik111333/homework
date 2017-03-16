digitSum :: Int -> Int
digitSum x
	| x < 10 = x
	| otherwise = mod x 10 + digitSum (div x 10)