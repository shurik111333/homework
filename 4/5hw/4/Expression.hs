module Expression where

data Expression = Const Double
    | Variable
    | UMinus Expression
    | Plus Expression Expression
    | Minus Expression Expression
    | Multiply Expression Expression
    | Divide Expression Expression
    | Power Expression Double
    
instance Show Expression where
    show (Const x) = show x
    show Variable = "x" 
    show (UMinus e) = "-(" ++ (show e) ++ ")"
    show (Plus a b) = show a ++ " + " ++ show b
    show (Minus a b) = show a ++ " - (" ++ show b ++ ")"
    show (Multiply a b) = show a ++ " * (" ++ show b ++ ")"
    show (Divide a b) = show a ++ " / (" ++ show b ++ ")"
    show (Power a b) = "(" ++ show a ++ ") ^ (" ++ show b ++ ")"

derivative :: Expression -> Expression
derivative = simplify . derivative' where    
    derivative' :: Expression -> Expression
    derivative' (Const _) = Const 0
    derivative' Variable = Const 1
    derivative' (UMinus a) = UMinus (derivative' a)
    derivative' (Plus a b) = Plus (derivative' a) (derivative' b)
    derivative' (Minus a b) = Minus (derivative' a) (derivative' b)
    derivative' (Multiply a b) = Plus (Multiply (derivative' a) b) (Multiply (derivative' b) a)
    derivative' (Divide a b) = Divide (Minus (Multiply (derivative' a) b) $ Multiply (derivative' b) a) $ Power b 2
    derivative' (Power a b) = Multiply (Multiply (Const b) (Power a $ b - 1)) (derivative' a)

simplify :: Expression -> Expression
simplify (UMinus e) = simplify' $ UMinus $ simplify e
simplify (Plus a b) = simplify' $ Plus (simplify a) $ simplify b
simplify (Minus a b) = simplify' $ Minus (simplify a) $ simplify b
simplify (Multiply a b) = simplify' $ Multiply (simplify a) $ simplify b
simplify (Divide a b) = simplify' $ Divide (simplify a) $ simplify b
simplify (Power a b) = simplify' $ Power (simplify a) b
simplify e = e

simplify' (Const x) = Const x
simplify' (UMinus (Const x)) = Const (-x)
simplify' (UMinus a) = UMinus a
simplify' (Variable) = Variable
simplify' (Plus (Const a) (Const b)) = Const (a + b)
simplify' (Plus (Const 0) b) = b
simplify' (Plus a (Const 0)) = a
simplify' (Plus a (Const x)) | x < 0 = Minus a (Const (-x))
simplify' (Plus a b) = Plus a b
simplify' (Minus (Const a) (Const b)) = Const (a - b)
simplify' (Minus a (Const 0)) = a
simplify' (Minus (Const 0) b) = simplify' $ UMinus $ b
simplify' (Minus a (Const x)) | x < 0 = Plus a (Const x)
simplify' (Minus a b) = Minus a b
simplify' (Multiply (Const a) (Const b)) = Const (a * b)
simplify' (Multiply (Const 0) b) = Const 0
simplify' (Multiply a (Const 0)) = Const 0
simplify' (Multiply a (Const 1)) = a
simplify' (Multiply (Const 1) b) = b
simplify' (Multiply a (Const (-1))) = simplify' $ UMinus a
simplify' (Multiply (Const (-1)) b) = simplify' $ UMinus b
simplify' (Multiply Variable Variable) = Power Variable 2
simplify' (Multiply (Power Variable a) Variable) = Power Variable (a + 1)
simplify' (Multiply Variable (Power Variable a)) = Power Variable (a + 1)
simplify' (Multiply (Power Variable a) (Power Variable b)) = Power Variable (a + b)
simplify' (Multiply a b) = Multiply a b
simplify' (Divide (Const a) (Const b)) = Const (a / b)
simplify' (Divide (Const 0) b) = Const 0
simplify' (Divide a (Const 1)) = a
simplify' (Divide a b) = Divide a b
simplify' (Power a 0) = Const 1
simplify' (Power a 1) = a
simplify' (Power a x) = Power a x
