import Foreign.Marshal.Utils

countEven1 = sum . map (fromBool . even)

countEven2 = length . filter (even)

countEven3 :: (Foldable t, Integral a) => t a -> a
countEven3 = foldr ((+) . fromBool . even) 0