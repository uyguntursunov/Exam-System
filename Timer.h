#include <iostream>
#include <chrono>
#include <thread>

using namespace std;

int timer() {
    // Set the duration of the timer
    chrono::seconds duration(5);
    
    // Get the current time
    chrono::time_point<chrono::system_clock> start = chrono::system_clock::now();
    
    // Wait for the specified duration
    while (chrono::system_clock::now() - start < duration) {
        // Compute the time remaining
        chrono::seconds remaining = chrono::duration_cast<chrono::seconds>(duration - (chrono::system_clock::now() - start));
        
        // Print the time remaining
        //cout << "Time remaining: " << remaining.count() << " seconds" << endl;
        
        // Sleep for a short time to reduce CPU usage
        this_thread::sleep_for(chrono::seconds(1));
    }
    
    // The timer has expired
    //cout << "Timer expired!" << endl;
    
    return 0;
}
