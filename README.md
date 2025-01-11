# MillisTimer

A straightforward, non-blocking library for timing process execution

# Example
```C++
#include "MillisTimer.h"

MillisTimer msTimer;
MillisTimer usTimer;

void setup()
{
  Serial.begin(115200);

  msTimer.begin(1000);
  usTimer.begin(1000000, MICRO_SECONDS);

  msTimer.start();
  usTimer.start();
}

void loop()
{
  if(msTimer.fire())
    Serial.println("ms");

  if(usTimer.fire())
    Serial.println("us");
}
```

# Example Explanation
Include the library to use:
```c++
#include "MillisTimer.h"
```

Instantiate 2 instances of the MillisTimer class - one for keeping time with millis() and another for keeping time with micros():
```c++
MillisTimer msTimer;
MillisTimer usTimer;
```

Initialize the timers to both fire off at 1 second intervals without blocking. The first argument of "begin()" is the timeout and the second (optional) argument of "begin()" is the units of the timeout argument (ms or us):
```c++
msTimer.begin(1000);
usTimer.begin(1000000, MICRO_SECONDS);
```

Determine if enough time has elapsed (timeout) based on the return value of "elapsed()". The "elapsed()" method returns a bool - true if timeout has occurred and false if not. If a timeout has occurred, it will automatically reset the timer (this "resetting" can be overridden passing a "false" value). Here, once the timout has occurred, we print "ms" or "us" depending on the timer:
```c++
if(msTimer.fire())
  Serial.println("ms");

if(usTimer.fire())
  Serial.println("us");
 ```
 
# Other
To check for a timeout without resetting the timer:
```c++
msTimer.fire(false) // Passing "false" prevents the timer from automatically resetting
```

To force a timer reset:
```c++
msTimer.start();
```

To update the timer's timeout value without resetting the timer:
```c++
msTimer.update(100); // Save 100ms as the new timeout value
```

To update the timer's timeout value resetting the timer:
```c++
msTimer.update(100, true); // Save 100ms as the new timeout value and reset the timer
```
