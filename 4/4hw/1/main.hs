countEven1 = sum . map ((`mod` 2) . (+) 1)

countEven2 = length . filter ((== 0) . (`mod` 2))

countEven3 :: (Foldable t, Integral a) => t a -> a
countEven3 = foldr ((+) . (`mod` 2) . (+) 1) 0