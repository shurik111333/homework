import Expression

test1 = Plus (Const 1) (Variable)
test2 = Plus 
            (Multiply 
                (Variable) 
                (Const 3)
            ) 
            (Power 
                (Plus 
                    (Multiply 
                        (Variable) 
                        (Const 0)
                    )
                    (Multiply
                        Variable
                        Variable
                    )
                )
                2
            )