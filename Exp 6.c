#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Node structure for the linked list (stack node)
struct Node {
    char url[100];  // URL of the page
    struct Node* next;
};

// Push a URL onto a stack
void push(struct Node** top, char* url) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (!newNode) {
        printf("Memory allocation error.\n");
        return;
    }
    strcpy(newNode->url, url);
    newNode->next = *top;
    *top = newNode;
}

// Pop a URL from a stack
char* pop(struct Node** top) {
    if (*top == NULL) {
        return NULL;  // Stack is empty
    }
    struct Node* temp = *top;
    *top = (*top)->next;
    char* poppedUrl = temp->url;
    free(temp);
    return poppedUrl;
}

// Peek at the top URL of a stack without popping it
char* peek(struct Node* top) {
    if (top == NULL) {
        return NULL;
    }
    return top->url;
}

// Display the stack (for debugging purposes)
void display(struct Node* top) {
    if (top == NULL) {
        printf("Stack is empty.\n");
        return;
    }
    printf("Stack elements:\n");
    while (top != NULL) {
        printf("%s\n", top->url);
        top = top->next;
    }
    printf("\n");
}

// Simulating browser navigation
void visitPage(struct Node** backStack, struct Node** forwardStack, char* url) {
    printf("Visiting: %s\n", url);
    push(backStack, url);  // Push the current page onto the back stack
    *forwardStack = NULL;  // Clear the forward stack after a new page is visited
}

// Go back to the previous page (pop from back stack and push to forward stack)
void goBack(struct Node** backStack, struct Node** forwardStack) {
    if (*backStack == NULL || (*backStack)->next == NULL) {
        printf("No previous pages to go back to.\n");
        return;
    }

    char* currentUrl = pop(backStack);
    push(forwardStack, currentUrl);
    printf("Going back to: %s\n", peek(*backStack));
}

// Go forward to the next page (pop from forward stack and push to back stack)
void goForward(struct Node** backStack, struct Node** forwardStack) {
    if (*forwardStack == NULL) {
        printf("No forward pages to go to.\n");
        return;
    }

    char* forwardUrl = pop(forwardStack);
    push(backStack, forwardUrl);
    printf("Going forward to: %s\n", forwardUrl);
}

// Main function to demonstrate browser navigation using stacks
int main() {
    struct Node* backStack = NULL;     // Stack for back history
    struct Node* forwardStack = NULL;  // Stack for forward history

    visitPage(&backStack, &forwardStack, "www.google.com");
    visitPage(&backStack, &forwardStack, "www.github.com");
    visitPage(&backStack, &forwardStack, "www.stackoverflow.com");

    goBack(&backStack, &forwardStack);  // Going back to www.github.com
    goBack(&backStack, &forwardStack);  // Going back to www.google.com

    goForward(&backStack, &forwardStack);  // Going forward to www.github.com

    visitPage(&backStack, &forwardStack, "www.wikipedia.org");  // Visiting a new page, forward stack gets cleared

    goBack(&backStack, &forwardStack);  // Going back to www.github.com

    return 0;
}
