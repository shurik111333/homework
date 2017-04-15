rhombus n = (putStr . unlines) ([1..n] ++ reverse [1..(n - 1)] >>= return . (getLine n)) where
    getLine n k = replicate (n - k) ' ' ++ replicate (2 * k - 1) 'x'