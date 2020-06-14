//Generating Random numbers

#include <iostream>
#include <time.h>

using namespace std;

class RandomGeneration
{
    int low,high;

    public:
        RandomGeneration();
        void setTimerSeed();
        int drawRandomNumber();
        int getHigh();
        int getLow();
};

RandomGeneration :: RandomGeneration()
{
    low = 1;
    high = 100; 
}

void RandomGeneration :: setTimerSeed()
{
    time_t seedTime;
    struct tm seedDate;
    seedTime = time(0);
    seedDate = *localtime(&seedTime);
    int finalSeed = seedTime + seedDate.tm_mday + (seedDate.tm_mon+1) + (seedDate.tm_year+1900);
    srand((unsigned int) finalSeed);
}

int RandomGeneration :: drawRandomNumber()
{
    int interval = getHigh() - getLow() + 1;
    int randomOffset = rand() % interval ;
    int randomNumber = getLow() + randomOffset;
    return randomNumber;
}

int RandomGeneration :: getHigh()
{
    return high;
}

int RandomGeneration :: getLow()
{
    return low;
}
