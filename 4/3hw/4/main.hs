check :: String -> Bool
check s = check' s []
    where 
        isOpen c = c == '(' || c == '[' || c == '{'
        isClose c = c == ')' || c == ']' || c == '}'
        equalType '(' c = c == ')'
        equalType '[' c = c == ']'
        equalType '{' c = c == '}'
        check' :: String -> String -> Bool
        check' [] st = null st
        check' (c:s) st | isOpen c = check' s (c:st)
        check' (c:s) [] | isClose c = False
        check' (c:s) (cl:st) | isClose c && equalType cl c = check' s st
        check' (c:s) (cl:st) | isClose c && not (equalType cl c) = False
        check' (c:s) st = check' s st