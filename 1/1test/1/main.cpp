#include <iostream>

using namespace std;

// сложность алгоритма O(N + M), где
// N - количество элементов в первой стопке
// M - количество элементов во второй стопке
// т.к. по каждому массиву алгоритм проходит только один раз

void copySegmentOfArray(int startIndex, int lastIndex, int *inputArray,
                        int startIndexInResult, int *resultArray)
{
    for (int i = startIndex; i <= lastIndex; i++)
    {
        resultArray[startIndexInResult + i - startIndex] = inputArray[i];
    }
}

int *getStackFromInput(int &number, int numberOfStack)
{
    cout << "¬ведите количество предметов в стопке " << numberOfStack << endl;
    cin >> number;
    cout << "¬ведите элементы из стопки " << numberOfStack << endl;
    int *stack = new int[number];
    for (int i = 0; i < number; i++)
    {
        cin >> stack[i];
    }
    return stack;
}

int *mergeStacks(int numberOfStack1, int *stack1, int numberOfStack2, int *stack2)
{
    int *resultStack = new int[numberOfStack1 + numberOfStack2];
    int pointerOfStack1 = 0;
    int pointerOfStack2 = 0;
    while (pointerOfStack1 < numberOfStack1 && pointerOfStack2 < numberOfStack2)
    {
        if (stack1[pointerOfStack1] < stack2[pointerOfStack2])
        {
            resultStack[pointerOfStack1 + pointerOfStack2] = stack2[pointerOfStack2];
            pointerOfStack2++;
        }
        else
        {
            resultStack[pointerOfStack1 + pointerOfStack2] = stack1[pointerOfStack1];
            pointerOfStack1++;
        }
    }
    copySegmentOfArray(pointerOfStack1, numberOfStack1 - 1, stack1,
                       pointerOfStack1 + pointerOfStack2, resultStack);
    copySegmentOfArray(pointerOfStack2, numberOfStack2 - 1, stack2,
                       pointerOfStack1 + pointerOfStack2, resultStack);
    return resultStack;
}

int main()
{
    setlocale(LC_ALL, "rus");
    int numberInStack1 = 0;
    int numbeInStack2 = 0;
    int *stack1 = getStackFromInput(numberInStack1, 1);
    int *stack2 = getStackFromInput(numbeInStack2, 2);
    int *resultStack = mergeStacks(numberInStack1, stack1, numbeInStack2, stack2);
    delete[] stack1;
    delete[] stack2;
    cout << "»тогова€ стопка:" << endl;
    for (int i = 0; i < numberInStack1 + numbeInStack2; i++)
    {
        cout << resultStack[i] << " ";
    }
    delete[] resultStack;
    cout << endl;
    return 0;
}

