import Tree

-- | Returns values from Tree in pre-order traversal
getValues :: (Foldable t) => t a -> [a]
getValues = foldl (flip (:)) []