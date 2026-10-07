#include <iostream>
#include <string>
using namespace std;

struct QueueNode {
    int jobId;
    string docName;
    int pages;
    QueueNode* next;

    QueueNode(int id, string doc, int p) {
        jobId = id;
        docName = doc;
        pages = p;
        next = nullptr;
    }
};

// custom linked queue class following fifo
class PrintQueue {
private:
    QueueNode* frontNode;
    QueueNode* rearNode;
    int jobCount;

public:
    PrintQueue() {
        frontNode = nullptr;
        rearNode = nullptr;
        jobCount = 0;
    }

    // destructor to free all allocated memory
    ~PrintQueue() {
        clearQueue();
    }

    // check if queue contains any jobs
    bool isEmpty() {
        return frontNode == nullptr;
    }

    // return total count of waiting jobs
    int countJobs() {
        return jobCount;
    }

    // insert new print job at the rear
    void addJob(int id, string doc, int p) {
        QueueNode* newNode = new QueueNode(id, doc, p);
        if (isEmpty()) {
            frontNode = rearNode = newNode;
        } else {
            rearNode->next = newNode;
            rearNode = newNode;
        }
        jobCount++;
        cout << "added job " << id << endl;
    }

    // remove and process job at the front
    void processJob() {
        if (isEmpty()) {
            cout << "cannot process: queue is empty" << endl;
            return;
        }
        QueueNode* temp = frontNode;
        cout << "processed job: " << temp->jobId << " (" << temp->docName << ", " << temp->pages << " pages)" << endl;
        frontNode = frontNode->next;

        // reset rear if queue becomes empty
        if (frontNode == nullptr) {
            rearNode = nullptr;
        }

        delete temp;
        jobCount--;
    }

    // view front job without removing it
    void viewNextJob() {
        if (isEmpty()) {
            cout << "queue is empty" << endl;
            return;
        }
        cout << "next job: " << frontNode->jobId << " (" << frontNode->docName << ", " << frontNode->pages << " pages)" << endl;
    }

    // displaying all waiting jobs
    void displayQueue() {
        if (isEmpty()) {
            cout << "queue is empty" << endl;
            return;
        }
        cout << "current queue (" << jobCount << " jobs):" << endl;
        QueueNode* temp = frontNode;
        while (temp != nullptr) {
            cout << "  id: " << temp->jobId << " | doc: " << temp->docName << " | pages: " << temp->pages << endl;
            temp = temp->next;}}

    // remove all jobs and release memory
    void clearQueue() {
        while (!isEmpty()) {
            QueueNode* temp = frontNode;
            frontNode = frontNode->next;
            delete temp;
        }
        rearNode = nullptr;
        jobCount = 0;
    }
};

int main() {
    PrintQueue pq;
    // adding initial test jobs
    pq.addJob(101, "Assignment1.pdf", 10);
    pq.addJob(102, "Report.docx", 25);
    pq.addJob(103, "Notes.pdf", 5);
    pq.addJob(104, "LabTask.docx", 15);

    cout << endl << "1 display all jobs" << endl;
    pq.displayQueue();
    cout << endl<< " 2 process two jobs" << endl;
    pq.processJob();
    pq.processJob();
    cout << endl<< " 3 display remaining jobs" << endl;
    pq.displayQueue();
    cout << endl << "4 add a new job " << endl;
    pq.addJob(105, "Project.pdf", 30);
    cout << endl<< " 5 display next job" << endl;
    pq.viewNextJob();
    cout << endl<< " 6 process all remaining jobs " << endl;
    while (!pq.isEmpty()) {
        pq.processJob();
    }
    cout << endl<< " 7 attempt to process empty queue" << endl;
    pq.processJob();
    return 0;
}