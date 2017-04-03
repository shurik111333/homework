fib :: Int -> Int
fib n = fib' n 0 1
    where
        fib' :: Int -> Int -> Int -> Int
        fib' 0 a _ = a
        fib' n a b | n > 0 = fib' (n - 1) b (a + b)
        fib' n a b | n < 0 = fib' (n + 1) b (a - b)