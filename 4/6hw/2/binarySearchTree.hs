module BinarySearchTree where

import Data.Maybe
import System.Random

data BST a = Node a (BST a) (BST a) | Empty deriving (Show)
  

add value Empty               = Node value Empty Empty
add value (Node x left right) = if x < value
                                    then Node x left (add value right)
                                    else Node x (add value left) right

find Empty value = False
find (Node x left right) value | x == value = True
find (Node x left _) value     | x > value  = find left value
find (Node x _ right) value    | x < value  = find right value

remove Empty value                            = Empty
remove (Node x left right) value | x < value  = Node x left $ remove right value
remove (Node x left right) value | x > value  = Node x (remove left value) right
remove (Node x left right) value | x == value = case (left, right) of
                                                    (Empty, Empty) -> Empty
                                                    (node, Empty)  -> node
                                                    (Empty, node)  -> node
                                                    (l, r)         -> Node m l $ remove r m where
                                                        m = getMin r

getMin (Node x Empty _) = x
getMin (Node x left _)  = getMin left

size Empty = 0
size (Node x l r) = 1 + size l + size r

height Empty = 0
height (Node x l r) = 1 + max (height l) (height r)

fillRandom Empty = Empty
fillRandom (Node x left right) = Node (fst $ random $ mkStdGen x) (fillRandom left) (fillRandom right)