#include "Simulation.h"

void Simulation::deleteNestFromPheromons (openCLinit * init){
	int radius = 10;
	for (int j = STARTPOSY-radius; j < STARTPOSY+radius; j++){
		for (int i = STARTPOSX-radius; i < STARTPOSX+radius; i++){
			init->pheromonMap[(j*WIDTH)+i] = 0;
		}
	}
}


void Simulation::simulate(openCLinit * init, Stats* stats){

		for (int i  = 0; i < ARRAY_SIZE; i++)
		{

			int tarX = init->targetX[i];
			int tarY = init->targetY[i];


			// Color the Ant Magenta if in Pheromon Search Mode !
			for (int i = 0; i < ARRAY_SIZE; i++){
				if (init->mode[i] == 3){
					init->color[i] = 33;
				}
			}

			/**
			* Here the Ant gets a new Target, if the Target is arrived
			*
			**/
			// only if its not carrying food
			if (init->isCarryingFood[i] == false){
				// Get new Position
				if (
		
					((int)init->antX[i] > tarX-init->speed[i] && (int)init->antX[i] < tarX+init->speed[i])
						){
							int randomm = 0;

							do {
								randomm =  Helper::getRandomInt(WIDTH, 0);
							}
							while (init->targetX[i] == randomm);

							init->targetX[i] = randomm;

							do {
								randomm = Helper::getRandomInt(WIDTH, 0);
							}
							while (init->targetY[i] == randomm);

							init->targetY[i] = randomm;


					}
				

			}

			BOOST ? checkIfAntFoundFood(i, init) : checkIfAntFoundFood2(i, init, stats);

		

		
	}
	elapsePheromons(init);
	deleteNestFromPheromons(init);
}
void Simulation::makeStats(Stats * stats, openCLinit *init){

	stats->stats_number_of_living_ants =0;
	stats->foodCatchingAnts = 0;
	stats->pheromonSearching = 0;
	int averageSpeed = 0;

	for (int i = 0; i < ARRAY_SIZE; i++){
		if (init->lifeStadium[i] != 0){
			stats->stats_number_of_living_ants++;
			averageSpeed += init->speed[i];
		}

		if (init->isCarryingFood[i] == 1){
			stats->foodCatchingAnts++;
		}

		if (init->mode[i] == 3){
			stats->pheromonSearching++;
		}
	}
	// Average Speed of living Ants
	stats->avgSpeed = averageSpeed/stats->stats_number_of_living_ants;


}


void Simulation::checkBreed(Stats * stats){
	stats->eggs = 0;
	stats->grubs = 0;
	stats->puppets = 0;
	stats->imagos = 0;

	int i = 0;
	for (Breed * ant : breed){


		if(ant->status == status_EGG){
			// Egg is developed ready
			if (ant->days > ant->endDate){
				stats->eggs--;
				breed.erase(breed.begin()+i);
				breed.push_back(new Grub(0));
			}
			else {
				stats->eggs++;
			}

		}
		else if (ant->status == status_GRUB){


			// Egg is developed ready
			if (ant->days > ant->endDate){
				stats->grubs--;
				breed.erase(breed.begin()+i);
				breed.push_back(new Puppet(0));

			}
			else {
				stats->grubs++;
			}


		}
		else if (ant->status == status_PUPPET){
			// Egg is developed ready
			if (ant->days > ant->endDate){
				stats->puppets--;
				breed.erase(breed.begin()+i);
				breed.push_back(new Imago(0));
			}
			else {
				stats->puppets++;
			}
		}

		else if (ant->status == status_IMAGO){
			// Egg is developed ready
			if (ant->days >= ant->endDate){
				breed.erase(breed.begin()+i);
				stats->livingAnts++;
				//i--;
			}
			else {
				stats->imagos++;
			}
		}
		// Is an Ant !!!
		else {
			std::cout << "\n\nERROR";
		}

		i++;

	}

	stats->breed = i;

	//int z=0;
	//for (Breed  tempAnt : tempBreed){
	//	z++;
	//	std::cout << "\n\nHAHAHHA GRUBBBBY" << z;
	//	
	//	breed.push_back(tempAnt);
	//}

	//grubs = z;


}

void Simulation::fillMapWithFood(openCLinit *init){
	int howMuchFood = MAXFOOD;

	for (int i = 0; i < howMuchFood; i++){
		int x = Helper::getRandomInt(WIDTH, 0);
		int y = Helper::getRandomInt(HEIGHT,0);

		int howMuch = Helper::getRandomInt(11,1);

		init->pheromonMap[y*WIDTH+x] = howMuch;

	}
}

//default
void Simulation::fillMapWithFood2(openCLinit *init){
	int howMuchFood = MAXFOOD;

	for (int i = 0; i < howMuchFood; i++){
		int x = 0;
		int y = 0;
		do {
			x = Helper::getRandomInt(WIDTH, 0);
			y = Helper::getRandomInt(HEIGHT,0);

		}
		while (
			(x > STARTPOSX-50 && x < STARTPOSX+50)		
			&&
			(y > STARTPOSY-50 && y < STARTPOSY+50)
			);
		std::cout << "\ni " << i << "X : " << x << " Y: " << y;

		int howMuch = Helper::getRandomInt(255*FOOD_FACTOR, 0);


		int countSameFoodPlaces = 0;
		for (Food *thisFood : food){
			if (thisFood->x == x && thisFood->y == y){
				std::cout << "\n SAME FOOOOOOD";
				countSameFoodPlaces++;
			}
		}

		if (countSameFoodPlaces == 0){
			food.push_back(new Food(x, y, howMuch));
		}
		//init->pheromonMap[y*WIDTH+x] = howMuch;

	}

	//food.push_back(new Food(400, 400, 300));
}

void Simulation::checkIfAntFoundFood (int antid, openCLinit *init){


	for (int y = init->antY[antid]-ANT_VIEWRADIUS; y < init->antY[antid]+ANT_VIEWRADIUS; y++){
		if (y >= HEIGHT)
			break;
		for (int x = init->antX[antid]-ANT_VIEWRADIUS; x < init->antX[antid]+ANT_VIEWRADIUS; x++){
			if (x >= WIDTH)
				break;
			int iz = y*800+x;

			if (init->pheromonMap[iz] >= 100){
				init->color[antid]  = 3;
				init->targetX[antid] = STARTPOSX; 
				init->targetY[antid] = STARTPOSY;
			}

			if (x == STARTPOSX && y == STARTPOSY)
				init->color[antid] = 0;

		}
	}
}

void Simulation::elapsePheromons(openCLinit * init){
	for (int i = 0; i < WIDTH*HEIGHT; i++){
		if (init->pheromonMap[i] > 0){
			init->pheromonMap[i] -= 10;
		}
	}
}

void Simulation::checkIfAntFoundFood2 (int antid, openCLinit *init, Stats* stats){


	// SEARCH FOR FOOD
	if (init->isCarryingFood[antid] == false){


		for (int i = 0; i < food.size(); i ++){
			// Index

			//thisFood = food[0];
			float x = abs(food[i]->x - init->antX[antid]);
			float y = abs(food[i]->y - init->antY[antid]);



			//float lenghtFoodVector = sqrt(pow(thisFood->x,2)+pow(thisFood->y,2));
			//float lengthTargetVector = sqrt(pow(init->antX[antid],2)+pow(init->antY[antid],2));
			//float differenz  = abs(lengthTargetVector-lenghtFoodVector);
			//// Distance Check


			// IF IN PHEROMONMODE AND SEARCHING FOR FOOD
			//if (init->mode[i] != 3){
				// FOOD IS AVIABLE IN DISTANCE OF ANT
				if (food[i]->volume > 1 && init->isCarryingFood[antid] == false){


					// FOUND FOOD
					if (Helper::getLenghtOfVector(x,y) <= ANT_VIEWRADIUS){
						//std::cout << std::endl << "HIT";
						food[i]->volume--;

						init->isCarryingFood[antid] = true;
						init->color[antid]  = 3;
						init->targetX[antid] = STARTPOSX; 
						init->targetY[antid] = STARTPOSY;
						init->mode[i] = 100;

						// Set Pheromon @ FOOD Position
						int id = (food[i]->y*WIDTH)+food[i]->x;
						std::cout << "\n FX: " << food[i]->x << " FY: " << food[i]->y << " ID: " << id;

						init->pheromonMap[id] = 100000;


					}

					else{
						
						/*	std::cout << "\nLV: " << Helper::getLenghtOfVector(x,y);
							std::cout << "\nVR: " << ANT_VIEWRADIUS;*/
						
					}



				}
				if (food[i]->volume <= 1){
					int id = (food[i]->y*WIDTH)+food[i]->x;
						//std::cout << "\n*PLOP* (FOOD)";

						init->pheromonMap[id] = 0;
				}
			//}

			//// Skalarprodukt
			//float scalar = (init->antX[antid]*init->pheromonMap[x])+(init->antY[antid]*init->pheromonMap[y]);
			//float alpha = scalar / (lenghtFoodVector*lengthTargetVector);


		}



	}





	if (init->isCarryingFood[antid]){
		// ARRIVED ANT THE ANT NEST? 
		if (
			((int)init->antX[antid] > STARTPOSX-init->speed[antid]
		&&
			(int)init->antX[antid] < STARTPOSX+init->speed[antid])
			)
		{
			init->isCarryingFood[antid] = false;
			// normal ant color
			init->color[antid] = 0;
			stats->earnedFood++;
			// reset euter
			init->pheromonEuter[antid] = 800;
		}

		int id = ((int)init->antY[antid]*WIDTH)+(int)init->antX[antid];
		init->pheromonEuter[antid] -= 1;
		init->pheromonMap[id] = init->pheromonEuter[antid];

		// [GO BACK TO NEST] == Do not follow your Nose
		init->mode[antid] = 100;



	}




}
