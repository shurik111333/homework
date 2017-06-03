module Poly where

import Data.List

data Poly = Poly [Int]

instance Show Poly where
    show (Poly l) = intercalate " + " $ map (show') $ reverse $ filter ((/= 0) . fst) $ zip l [0..] where
        show' (c, 0) = show c
        show' (c, 1) = show c ++ "*x"
        show' (c, i) = show c ++ "*x^" ++ show i
   
degree :: Poly -> Int
degree (Poly l) = length l - 1;
   
add (Poly l1) (Poly l2) = if length l1 < length l2 
                          then Poly $ zipWith (+) (l1 ++ replicate (length l2 - length l1) 0) (l2)
                          else add (Poly l2) (Poly l1)                         

multiply p1 p2 = if degree p1 <= degree p2
                    then multiply' p1 p2
                    else multiply' p2 p1 where
    multiply' (Poly []) (Poly l2) = Poly []
    multiply' (Poly [a]) (Poly l) = Poly $ map (*a) l
    multiply' p1 p2 = multiply'' p1 p2 0 $ Poly []
    
    multiply'' (Poly []) _ _ ans = ans
    multiply'' (Poly (x:xs)) p d ans | x == 0    = multiply'' (Poly xs) p (d + 1) ans
    multiply'' (Poly (x:xs)) p d ans | otherwise = multiply'' (Poly xs) p (d + 1) $ add (multiply (Poly [x]) $ multiplyByX p d) (ans)
    
    multiplyByX (Poly l) deg = Poly $ replicate deg 0 ++ l
