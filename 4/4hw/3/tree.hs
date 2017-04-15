module Tree where

import Control.Monad

data Tree a = Empty | Leaf a | Node (Tree a) a (Tree a)

instance Foldable Tree where
    foldr f z Empty = z
    foldr f z (Leaf x) = f x z
    foldr f z (Node l x r) = foldr f (foldr f (f x z) l) r
