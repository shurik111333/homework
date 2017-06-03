import Control.Monad.State
import Data.List

data Graph v = Graph [(Int,v)] [(Int,Int,Int)]

data Dist v = Dist (v, Int) deriving (Show)

vertex (Dist a) = fst a
distance (Dist a) = snd a

graph = Graph [(1, 1), (2, 2), (3, 3), (4, 4)] [(1, 2, 5), (1, 3, 10), (3, 4, 1), (2, 3, 2)]

dijkstra (Graph vs es) start = evalState (dijkstra' (Graph vs es) [if x == start then Dist (x, 0) else Dist (x, 100000) | x <- map fst vs]) (map fst vs)  where
    dijkstra' (Graph vs es) d = do
        st <- get
        if null st
            then return d
            else let v = minimumBy (\a b -> compare (getDistance d a) $ getDistance d b) st
                 in do
                    put (filter (/= v) st)
                    dijkstra' (Graph vs es) $ relax (filter ((== v) . from) es) d

relax [] d = d
relax (x:xs) d = relax xs $ (Dist (u, getDistance d v + w)):(filter ((/= u) . vertex) d) where
    v = from x
    u = to x
    w = weight x

getDistance l v = distance $ head $ filter ((== v) . vertex) l

from (a, b, c)    = a
to (a, b, c)      = b
weight (a, b, c)  = c