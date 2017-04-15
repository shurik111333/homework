import Data.List

printDecompose = putStr . unlines . map (intercalate " + ") . map (map show) . decompose

decompose n = decompose' n 1 where
    decompose' n k | n < 0     = []
                   | n == 0    = [[]]
                   | otherwise = [k..n] >>= \x -> map (x :) (decompose' (n - x) x)
