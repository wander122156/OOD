#include "lib/Duck/DecoyDuck.h"
#include "lib/Duck/MallardDuck.h"
#include "lib/Duck/ModelDuck.h"
#include "lib/Duck/RedheadDuck.h"
#include "lib/Duck/RubberDuck.h"
#include "lib/DuckFunctions.h"
#include <cstdlib>

int main()
{
	MallardDuck mallardDuck;
    PlayWithDuck(mallardDuck);
	PlayWithDuck(mallardDuck);

	if (mallardDuck.CanQuack())
		{std::cout << "yes quack" << std::endl;}
	else
		{std::cout << "no quack" << std::endl;}

	RedheadDuck redheadDuck;
	PlayWithDuck(redheadDuck);

	RubberDuck rubberDuck;
	PlayWithDuck(rubberDuck);

	DecoyDuck decoyDuck;
	PlayWithDuck(decoyDuck);

	if (decoyDuck.CanQuack())
	{std::cout << "yes quack" << std::endl;}
	else
	{std::cout << "no quack" << std::endl;}

	ModelDuck modelDuck;
	PlayWithDuck(modelDuck);

	modelDuck.SetFlyBehavior(std::make_unique<FlyWithWings>());
	PlayWithDuck(modelDuck);
	std::cout << "-------" << std::endl;
	modelDuck.SetFlyBehavior(std::make_unique<FlyNoWay>());
 	PlayWithDuck(modelDuck);

	return EXIT_SUCCESS;
}