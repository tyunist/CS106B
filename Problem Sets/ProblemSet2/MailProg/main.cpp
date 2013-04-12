//
//  main.cpp
//  MailProg
//
//  Created by Rafael Veronezi on 11/04/13.
//  Simulates a mail program, as proposed by the Problem 1 of the Problem Set 2
//

#include <iostream>
#include "strlib.h"
#include "vector.h"

using namespace std;

// A struct to hold a email message
struct emailMsg {
    string to;          // i.e. "professor@stanford.edu"
    string from;        // i.e. "student@stanford.edu"
    string message;     // body of message
    string subject;     // i.e. "CS106 Rocks!"
    int date;           // date email was sent
    int time;           // time email was sent
};

// A second version of the emailMsg struct, that allow multiple recipients, as proposed by exercise c
struct emailMsg2 {
    Vector<string> to;      // Allows to send to multiple recipients
    string from;
    string message;
    string subject;
    int date;
    int time;
};

/*
 * Function: removeSpam
 * Usage: removeSpam(messages)
 * ---------------------------
 * A function that remove spam messages, as proposed by exercise b
 */
void removeSpam(Vector<emailMsg> &messages)
{
    string prefix = "SPAM";
    
    // Iterate through messages
    for (int i = 0; i < messages.size(); i++) {
        string lcSubject = toUpperCase(messages[i].subject);
        if (startsWith(lcSubject, prefix)) {
            // Removes the message at the current index, since it starts with a spam
            // A thing to notice here, is that since the for is test against the size()
            //  method, and this size is updated each time you remove a string,
            //  you'll never get acidentally off the bounds of the vector
            messages.remove(i);
        }
    }
}

/*
 * Tests program entry-point
 */
int main()
{
    // Declares a vector to store eMailMessages, as proposed by exercise a
    Vector<emailMsg> messages;
    
    // Some test messages
    emailMsg msg1;
    msg1.to = "professor@stanford.edu";
    msg1.from = "student@stanford.edu";
    msg1.message = "This is a test message";
    msg1.subject = "Test message";
    msg1.date = 1;
    msg1.time = 10;
    messages.add(msg1);
    
    emailMsg msg2;
    msg1.to = "student@stanford.edu";
    msg1.from = "professor@stanford.edu";
    msg1.message = "My teacher is spamming me!";
    msg1.subject = "Spam from your teacher";
    msg1.date = 1;
    msg1.time = 10;
    messages.add(msg1);

    removeSpam(messages);
    for (emailMsg msg : messages) {
        cout << "Message from: " << msg.from << ", to: " << msg.to << endl;
        cout << "Date: " << msg.date << ", time: " << msg.time << endl;
        cout << "Subject: " << msg.subject << endl;
        cout << "Message: " << msg.message << endl;
        cout << endl;
    }
    
    // More tests
    Vector<string> recipients;
    recipients.add("student1@stanford.edu");
    recipients.add("student2@stanford.edu");
    recipients.add("student3@stanford.edu");
    
    emailMsg2 msg3;
    msg3.to = recipients;
    msg3.from = "professor@stanford.edu";
    msg3.message = "This is a test message";
    msg3.subject = "Test message";
    msg3.date = 1;
    msg3.time = 10;
    
    // Access the last recipient in the to line, as proposed by exercise c
    string lastRecipient = msg3.to[msg3.to.size() - 1];
    cout << "Last recipient: " << lastRecipient;
    
    return 0;
}