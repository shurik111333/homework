seq179 = 1:7:9:zipWith ((+) . (*) 10) (triple seq179) (seq179')
    where
        seq179' = 1:7:9:seq179'
        triple (x:xs) = x:x:x:triple xs