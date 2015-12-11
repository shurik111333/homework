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
	if (stack->top == nullptr)
	{
		return -1;
	}
	return stack->top->value;
}

double pop(Stack *stack)
{
	if (stack->top == nullptr)
	{
		return -1;
	}
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
	while (stack->top != nullptr)
	{
		pop(stack);
	}
	delete stack;
}