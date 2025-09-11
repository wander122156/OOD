#ifndef FLYWITHWINGS_H
#define FLYWITHWINGS_H

#include "IFlyBehavior.h"
#include <iostream>

class FlyWithWings : public IFlyBehavior
{
public:

	void Fly() override
	{
		flightCount++;
		std::cout << "I'm flying with wings!!" << std::endl;
		std::cout << "I have " << flightCount << " flights" << std::endl;
	}

	int GetFlightCount() const override
	{
		return flightCount;
	}

private:
	int flightCount = 0;
};


#endif
