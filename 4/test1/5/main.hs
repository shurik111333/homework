import Prelude hiding (all)

all p l = foldr (&&) True (map p l)