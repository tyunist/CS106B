//
//  main.cpp
//  ReverseQueue
//
//  Created by Rafael Veronezi on 11/04/13.
//
//

#include <iostream>
#include "queue.h"
#include "stack.h"

/*
 * Function: reverseQueue
 * Usage: reverseQueue(q)
 * ----------------------
 * Reverses the order of the received queue
 */
void reverseQueue(Queue<int> &q)
{
    // Temporary stack to do the reversion
    Stack<int> revStack;
    
    // First we include the queue elements in our stack
    while (!q.isEmpty()) {
        revStack.push(q.dequeue());
    }
    
    // Then we set the elements back to our queue
    while (!revStack.isEmpty()) {
        q.enqueue(revStack.pop());
    }
}

/*
 * Program entry-point
 */
int main()
{
    // Create a random queue
    Queue<int> queue;
    queue.enqueue(10);
    queue.enqueue(5);
    queue.enqueue(7);
    queue.enqueue(9);
    queue.enqueue(1);
    queue.enqueue(6);
    queue.enqueue(4);
    
    // Reverses the queue and print it out
    reverseQueue(queue);
    while (!queue.isEmpty()) {
        cout << queue.dequeue() << endl;
    }
    
    return 0;
}
