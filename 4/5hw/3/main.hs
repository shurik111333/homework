import Control.Monad

firstBigger (a:b:c:l) = foldl (\x y -> x `mplus` get y) Nothing $ zip (a:b:c:l) (zip (b:c:l) $ c:l) where
    get (a, (b, c)) = if a < b && c < b then Just b else Nothing
firstBigger l = Nothing
