
#include <iostream>
#include <string>
using namespace std;

struct OrderNode
{
    int orderID;
    string customerName;
    string productName;
    int priority;
    OrderNode* next;
};

class OrderPriorityQueue
{
private:
    OrderNode* front;
    OrderNode* rear;
    int count;

public:

    // Constructor
    OrderPriorityQueue()
    {
        front = NULL;
        rear = NULL;
        count = 0;
    }

    // Add order according to priority
    void Add(OrderNode* order)
    {
        order->next = NULL;

        if (front == NULL)
        {
            front = rear = order;
        }
        else if (order->priority < front->priority)
        {
            order->next = front;
            front = order;
        }
        else
        {
            OrderNode* temp = front;

            while (temp->next != NULL &&
                   temp->next->priority <= order->priority)
            {
                temp = temp->next;
            }

            order->next = temp->next;
            temp->next = order;

            if (order->next == NULL)
            {
                rear = order;
            }
        }

        count++;
    }

    // Remove highest-priority order
    OrderNode* Remove()
    {
        if (front == NULL)
        {
            return NULL;
        }

        OrderNode* temp = front;
        front = front->next;

        if (front == NULL)
        {
            rear = NULL;
        }

        temp->next = NULL;
        count--;

        return temp;
    }

    // Check if empty
    bool IsEmpty()
    {
        return front == NULL;
    }

    // Check if not empty
    bool IsNotEmpty()
    {
        return front != NULL;
    }

    // Display all orders
    void PrintQueue()
    {
        if (front == NULL)
        {
            cout << "No orders available." << endl;
            return;
        }

        OrderNode* temp = front;

        while (temp != NULL)
        {
            cout << "\nOrder ID: " << temp->orderID << endl;
            cout << "Customer: " << temp->customerName << endl;
            cout << "Product: " << temp->productName << endl;
            cout << "Priority: " << temp->priority << endl;
            cout << "------------------------" << endl;

            temp = temp->next;
        }
    }

    // Copy constructor
    OrderPriorityQueue(const OrderPriorityQueue& other)
    {
        front = NULL;
        rear = NULL;
        count = 0;

        OrderNode* temp = other.front;

        while (temp != NULL)
        {
            OrderNode* newNode = new OrderNode;

            newNode->orderID = temp->orderID;
            newNode->customerName = temp->customerName;
            newNode->productName = temp->productName;
            newNode->priority = temp->priority;

            Add(newNode);
            temp = temp->next;
        }
    }

    // Assignment operator
    OrderPriorityQueue& operator=(const OrderPriorityQueue& other)
    {
        if (this == &other)
        {
            return *this;
        }

        while (front != NULL)
        {
            OrderNode* temp = front;
            front = front->next;
            delete temp;
        }

        rear = NULL;
        count = 0;

        OrderNode* temp = other.front;

        while (temp != NULL)
        {
            OrderNode* newNode = new OrderNode;

            newNode->orderID = temp->orderID;
            newNode->customerName = temp->customerName;
            newNode->productName = temp->productName;
            newNode->priority = temp->priority;

            Add(newNode);
            temp = temp->next;
        }

        return *this;
    }

    // Destructor
    ~OrderPriorityQueue()
    {
        while (front != NULL)
        {
            OrderNode* temp = front;
            front = front->next;
            delete temp;
        }

        rear = NULL;
    }
};

int main()
{
    OrderPriorityQueue orders;

    // Order 1
    OrderNode* o1 = new OrderNode;
    o1->orderID = 1001;
    o1->customerName = "Ali";
    o1->productName = "Laptop";
    o1->priority = 3;

    orders.Add(o1);

    // Order 2
    OrderNode* o2 = new OrderNode;
    o2->orderID = 1002;
    o2->customerName = "Ahmed";
    o2->productName = "Mobile Phone";
    o2->priority = 1;

    orders.Add(o2);

    // Order 3
    OrderNode* o3 = new OrderNode;
    o3->orderID = 1003;
    o3->customerName = "Usman";
    o3->productName = "Headphones";
    o3->priority = 2;

    orders.Add(o3);

    // Order 4
    OrderNode* o4 = new OrderNode;
    o4->orderID = 1004;
    o4->customerName = "Hamza";
    o4->productName = "Smart Watch";
    o4->priority = 1;

    orders.Add(o4);

    cout << "===== E-Commerce Order Priority Queue =====" << endl;

    cout << "\nAll Orders (Highest Priority First):" << endl;
    orders.PrintQueue();

    // Check queue status
    if (orders.IsNotEmpty())
    {
        cout << "\nOrder queue is not empty." << endl;
    }

    // Process highest-priority order
    cout << "\n===== Processing Order =====" << endl;

    OrderNode* processed = orders.Remove();

    if (processed != NULL)
    {
        cout << "Order ID: " << processed->orderID << endl;
        cout << "Customer: " << processed->customerName << endl;
        cout << "Product: " << processed->productName << endl;
        cout << "Priority: " << processed->priority << endl;

        delete processed;
    }

    // Display remaining orders
    cout << "\n===== Remaining Orders =====" << endl;
    orders.PrintQueue();

    // Copy constructor demonstration
    OrderPriorityQueue copiedOrders(orders);

    cout << "\n===== Copied Orders =====" << endl;
    copiedOrders.PrintQueue();

    // Assignment operator demonstration
    OrderPriorityQueue anotherOrders;
    anotherOrders = orders;

    cout << "\n===== Assigned Orders =====" << endl;
    anotherOrders.PrintQueue();

    return 0;
}
