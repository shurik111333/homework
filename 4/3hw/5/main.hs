fib :: Int -> Int
fib n = fib' n 1 1
	where
		fib' :: Int -> Int -> Int -> Int
		fib' n _ _ | n < 0 = 0
		fib' 0 a _ = a
		fib' 1 _ b = b
		fib' n a b = fib' (n - 1) b (a + b)