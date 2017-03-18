import Data.List

sum3 :: [Int] -> [Int] -> [Int] -> [Int]
sum3 a b c = sum3 (sortBy myComparer [a, b, c])
	where
		myComparer :: [Int] -> [Int] -> Ordering
		myComparer x y = compare (length y) (length x)
		
		sum3 :: [[Int]] -> [Int]
		sum3 [[], [], []] = []
		sum3 [(x:xs), [], []] = (x:xs)
		sum3 [(x:xs), (y:ys), []] = (x + y):sum3 [xs, ys, []]
		sum3 [(x:xs), (y:ys), (z:zs)] = (x + y + z):sum3 [xs, ys, zs]