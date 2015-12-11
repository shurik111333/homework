struct StackNode
{
	double value;
	StackNode * next;
};

struct Stack
{
	StackNode *top;
};

Stack *getNewStack()
{
	Stack *newStack = new Stack{ nullptr };
	return newStack;
}

double getTop(Stack *stack)
{
	return stack->top->value;
}

bool isEmpty(Stack *stack)
{
	return (stack->top == nullptr);
}

double pop(Stack *stack)
{
	double topValue = stack->top->value;
	StackNode *nextNode = stack->top->next;
	delete stack->top;
	stack->top = nextNode;
	return topValue;
}

void push(Stack *stack, double newValue)
{
	StackNode *newElement = new StackNode{newValue, stack->top};
	stack->top = newElement;
}

void deleteStack(Stack *stack)
{
	while (!isEmpty(stack))
	{
		pop(stack);
	}
	delete stack;
}