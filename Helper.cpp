#include "Helper.h"


Helper::Helper (){

	viewRadiusMode = 0;
	targetMode = 0;
	gridMode = 0;
	selectionMode = 0;
	
	pheromonMode = false;

}
	// starts at 1 to WIDTH
 int Helper::getRandomInt(int high, int low ){
		int randomInt = rand() % high + low;
		//std::cout << "\n\n\nNew Random Int" <<  randomInt << "\n\n\n";
		return randomInt;

	}

 float Helper::getLenghtOfVector(float x, float y){
 
	 return sqrt(pow(x,2)+pow(y,2));
 }

 long Helper::filesize(const char *filename) 
{ 
	long size; 
	FILE *fp; 

	if ((fp = fopen(filename, "r")) == NULL) return -2;   
	fclose(fp); 
	if ((fp = fopen(filename, "ab")) == NULL) return -3; 
	fseek (fp, 0, SEEK_END);
	size = ftell(fp); 

	//std::cout << size << "\n";
	fclose(fp); 
	return size; 
}

 void Helper::checkInput(openCLinit *init, Stats* stats, sf::RenderWindow *window, std::vector <Food*> *food){
	 /***
			*
			* CONTROLS
			*
			**/

			sf::Vector2i old = sf::Vector2i(0,0);
			int countSelections = 0;

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
				std::cout << "SPEED+";
				for (int i = 0; i < ARRAY_SIZE; i++){
					init->speed[i] += 1;

				}
			}
			// Auswahl löschen
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace)){
				// Vektor von Selected Ants löschen
				selectedAnts.clear();
				// Auswahlfeld zurücksetzen
				//drawer->shapeSelection->setSize(sf::Vector2f(1,1));

				for (int x = 0; x < ARRAY_SIZE; x++){

					init->color[x] = 0;
				}

			}

			if (sf::Mouse::isButtonPressed(sf::Mouse::Right)){
				std::cout << "FOOD" << food->size();
				sf::Vector2i globalPosition = sf::Mouse::getPosition(*window);
				sf::Vector2f worldPos = window->mapPixelToCoords(globalPosition);

				food->push_back(new Food(worldPos.x, worldPos.y, 100*FOOD_FACTOR));
			}


			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
				sf::Vector2i globalPosition = sf::Mouse::getPosition(*window);
				sf::Vector2f worldPos = window->mapPixelToCoords(globalPosition);

				init->lifeStadium[stats->livingAnts] = 1;
				init->antX[stats->livingAnts] = worldPos.x;
				init->antY[stats->livingAnts] = worldPos.y;
				stats->livingAnts++;
			
			}

			// DEBUG MODE
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
				sf::Vector2i globalPosition = sf::Mouse::getPosition(*window);
				sf::Vector2f worldPos = window->mapPixelToCoords(globalPosition);

				// Get ANT at Mouse Position
				for (int i = 0; i < ARRAY_SIZE; i++){
					if (init->antX[i] == worldPos.x && init->antY[i] == worldPos.y){
						std::cout << "\nSpecific Ant ID: " << i;
						std::cout << "\nMode: " << init->mode[i];
						std::cout << "\nCarrying Food?: " << init->isCarryingFood[i];


					}
				}
			}


			// MOVE LEFT
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
				init->moveX-= 3;
			}
			// MOVE RIGHT
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
				init->moveX+= 3;
			}
			// MOVE DOWN
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
				init->moveY+= 3;
			}
			// MOVE UP
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
				init->moveY-= 3;
			}
			// ZOOM OUT
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y)){
				init->viewSize+= 0.01;
			}
			// ZOOM IN
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::X)){
				init->viewSize-= 0.01;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)){
				std::cout << "HEY" << this->pheromonMode;
				this->pheromonMode = !this->pheromonMode; 
				//std::cout << "Pheromon Mode " << this->pheromonMode;
			}
			// Displays the Targets of the Ants
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)){
				viewRadiusMode = !viewRadiusMode; 
				std::cout << "ViewRadius Mode " << viewRadiusMode;
			}
			// Displays the Targets of the Ants
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::T)){
				targetMode = !targetMode; 
				std::cout << "Target Mode " << targetMode;
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::G)){
				gridMode = !gridMode; 
				std::cout << "gridMode " << gridMode;
			}

			// SELECTION MODE
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){						
				//old =  sf::Mouse::getPosition(*drawer->window);
				selectionMode = !selectionMode;


				for (int x = 0; x < ARRAY_SIZE; x++){
					countSelections = 0;
					for (int *that : selectedAnts){
						if (*that == x){
							countSelections++;
						}
					}

					// Selected Ant
					if (countSelections > 0){
						// yellow
						init->color[x] = 1;
					}
					// Ant not Selected
					else {
						init->color[x] = 0;
					}


				}
			}
 }
  


 void Helper::initTestPheromon(openCLinit *init){
 
	

			 for (int x = 0; x < WIDTH; x++){
				
				init->pheromonMap[x*WIDTH+x] = x;
			 }
		 
		 
	 
 }