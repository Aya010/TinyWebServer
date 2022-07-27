#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include "../lock/locker.h"

using namespace std;
int a = 0;
int b = 0;
locker locker_a;
locker locker_b;
void *testworker(void *args)
{
    if (locker_b.lock())
    {
        cout << "in child thread , got mutex locker b, wait for a" << endl;
        // sleep(5);
        ++b;
        locker_a.lock();
        b += a++;
        locker_a.unlock();
    }
    locker_b.unlock();
    pthread_exit(NULL);
}
int main(int argc, char *argv[])
{
    cout << "hello test " << endl;
    pthread_t id;
    pthread_create(&id, NULL, testworker, NULL);
    locker_a.lock();
    cout << "in main thread , got mutex locker a, waiting for b " << endl;
    // sleep(5);
    ++a;
    locker_b.lock();
    a += b++;
    locker_b.unlock();
    locker_a.unlock();
    pthread_join(id, NULL);
    return 0;
}