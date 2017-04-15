supermap :: [a] -> (a -> [b]) -> [b]
supermap = (>>=)
