struct StackNode
{
	char value;
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

char getTop(Stack *stack)
{
	return stack->top->value;
}

char pop(Stack *stack)
{
	char topValue = stack->top->value;
	StackNode *nextNode = stack->top->next;
	delete stack->top;
	stack->top = nextNode;
	return topValue;
}

void push(Stack *stack, char newValue)
{
	StackNode *newElement = new StackNode{newValue, stack->top};
	stack->top = newElement;
}

bool isEmpty(Stack *stack)
{
	return (stack->top == nullptr);
}

void deleteStack(Stack *stack)
{
	while (!isEmpty(stack))
	{
		pop(stack);
	}
	delete stack;
}