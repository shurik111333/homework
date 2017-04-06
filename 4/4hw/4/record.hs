module Record where

data Record = Record { name :: String, phone :: Integer }
    deriving Eq
    
instance Show Record where
    show r = encode r
    
encode (Record n p) = show (n, p)
decode s = (uncurry Record) (read s :: (String, Integer))