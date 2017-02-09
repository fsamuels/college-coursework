//: sys_utils.h - definitions of two classes for system utilities that
//:               facilitate the use of time and random numbers in games
// Matt Stallmann, 25 Apr 2000

#ifndef SYS_UTILS_H
#define SYS_UTILS_H

#include<sys/types.h>           // definitions of system types
#include<sys/time.h>            // gettimeofday()
#include<stdlib.h>              // srand48(), lrand48()

class Time {
public:
  Time(): myTime(new timeval())
    { gettimeofday( myTime, 0 ); mySeconds = myTime->tv_sec;
      myMilliseconds = myTime->tv_usec / 1000; }
  ~Time() { delete myTime; }

  u_long milliseconds()         // number of milliseconds since
                                // initialization
    { gettimeofday( myTime, 0 );
      return 1000 * ( myTime->tv_sec - mySeconds )
        + myTime->tv_usec / 1000 - myMilliseconds; } 

private:
  timeval * myTime;
  u_long mySeconds;
  int myMilliseconds;
};

class Random {
public:
  Random()
    { timeval * theTime = new timeval(); gettimeofday( theTime, 0 );
    srand48( theTime->tv_sec ); delete theTime; }
  int integer( int n )          // returns an int in the range 0 to n-1
    { return lrand48() % n; }
};
#endif
