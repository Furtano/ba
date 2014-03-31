#include "Drawer.h"

Drawer::Drawer (){
	window = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "[AntSimulator] Bachelorarbeit - Christian Schade - HTW Berlin 2014");
	// window->setFramerateLimit(FPS);
	shapeSelection = new sf::RectangleShape;
	
	hudFont.loadFromFile("coolvetica.ttf");
	pixels  = new sf::Uint8[800*800*4];
	texture.create(800,800); 
	sprite = new sf::Sprite(texture);
	view = new sf::View(sf::FloatRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT));
}
Drawer::~Drawer(){
	delete shapeSelection;
	delete window;

}
void Drawer::drawHUD(Stats * stats){

	int spaceFromLeft = 290;
	Drawer::drawStatisticText(22, sf::Color::Yellow, "Possible Ants: ", ARRAY_SIZE, WINDOW_WIDTH-spaceFromLeft, 10);
	Drawer::drawStatisticText(22, sf::Color::Yellow, "Ants: ", stats->stats_number_of_living_ants, WINDOW_WIDTH-spaceFromLeft, 50);

	Drawer::drawStatisticText(22, sf::Color::Green, "Food-Catching: ", stats->foodCatchingAnts, WINDOW_WIDTH-spaceFromLeft, 90);
	Drawer::drawStatisticText(22, sf::Color::Magenta, "Pheromon-Searching: ", stats->pheromonSearching, WINDOW_WIDTH-spaceFromLeft, 130);
	Drawer::drawStatisticText(22, sf::Color::Blue, "Collected Food: ", stats->earnedFood, WINDOW_WIDTH-spaceFromLeft, 170);


	Drawer::drawStatisticText(22, sf::Color::Blue,  "Day: ", stats->days, WINDOW_WIDTH-spaceFromLeft, 510);
	Drawer::drawStatisticText(22, sf::Color::Blue, "Month: ", stats->months, WINDOW_WIDTH-spaceFromLeft, 550);
	Drawer::drawStatisticText(22, sf::Color::Blue, "Years: ", stats->years, WINDOW_WIDTH-spaceFromLeft, 590);

	Drawer::drawStatisticText(22, sf::Color::White, "Breed: ", stats->breed , WINDOW_WIDTH-spaceFromLeft, 250);

	Drawer::drawStatisticText(22, sf::Color::Red, "Eggs: ", stats->eggs, WINDOW_WIDTH-spaceFromLeft, 300);
	Drawer::drawStatisticText(22, sf::Color::Red, "Grubs: ", stats->grubs, WINDOW_WIDTH-spaceFromLeft, 350);
	Drawer::drawStatisticText(22, sf::Color::Red, "Puppets: ", stats->puppets, WINDOW_WIDTH-spaceFromLeft, 400);
	Drawer::drawStatisticText(22, sf::Color::Red, "Imagos: ", stats->imagos, WINDOW_WIDTH-spaceFromLeft, 450);

	Drawer::drawStatisticText(22, sf::Color::White, "Speed: ", stats->avgSpeed, WINDOW_WIDTH-spaceFromLeft, 650);

}
void Drawer::drawStatisticText(int fontSize, sf::Color textColor, std::string statisticDescription, int statisticSize, int x, int y){
	sf::Text text;

	
	

	text.setFont(hudFont);
	text.setCharacterSize(fontSize);
	text.setColor(textColor);

	std::stringstream sstm;
	sstm << statisticDescription << statisticSize;

	text.setString(sstm.str());
	text.setPosition(x, y);
	window->draw(text);

}

void Drawer::drawTargets(openCLinit * init, int i){
	if (init->lifeStadium[i] != 0){
		sf::RectangleShape shape2(sf::Vector2f(3,3));
		shape2.setFillColor(sf::Color(255,0,0,200));
		shape2.setPosition(init->targetX[i],init->targetY[i]);
		window->draw(shape2);
	}
}


void Drawer::drawBackground(){
	sf::Texture texture;
	if (!texture.loadFromFile("grasTexture.png"))
		std::cout << "Texture (Gras) load failure";
	sf::Sprite sprite;
	sprite.setTexture(texture, true);
	//window->draw(sprite);

	/*sf::Texture textureAntHill;
	if (!textureAntHill.loadFromFile("antHill.png"))
	std::cout << "Texture (Anthill) load failure";
	sf::Sprite spriteAnthill;
	spriteAnthill.setTexture(textureAntHill, true);
	spriteAnthill.setPosition(STARTPOSX-100, STARTPOSY-100);
	window->draw(spriteAnthill);*/
	int circleRadius = 20;
	sf::CircleShape circle (circleRadius);
	circle.setFillColor(sf::Color(201,119,30));
	circle.setPosition(STARTPOSX-circleRadius,STARTPOSY-circleRadius);
	circle.setOutlineThickness(10);
	circle.setOutlineColor(sf::Color(156,92,23));
	window->draw(circle);

}

void Drawer::drawGrid (int gridSize){
	for (int y = 0; y < HEIGHT; y+= gridSize){
		for (int x = 0; x < WIDTH; x += gridSize){
			sf::RectangleShape shape(sf::Vector2f(gridSize,gridSize));
			shape.setOutlineColor(sf::Color(255,255,255,10));
			shape.setFillColor(sf::Color::Transparent);
			shape.setOutlineThickness(1);
			shape.setPosition(x,y);
			window->draw(shape);
		}
	}
}



void Drawer::drawPheromonMap (openCLinit * init){
	
	int x = 0;
	int y = 0;
	sf::VertexArray lines(sf::Points, ARRAY_SIZE);

	for (int i = 0; i < WIDTH*HEIGHT; i++){
		
		//int linn = 0;
		if (init->pheromonMap[i] > 0){
			int phColor;
			sf::RectangleShape pheromon(sf::Vector2f(1,1));
			if (init->pheromonMap[i]/4 >= 255)
				phColor = 255;
			else 
				phColor = init->pheromonMap[i]/4;
			pheromon.setFillColor(sf::Color(255,0,0,phColor));

			if (init->pheromonMap[i] == 100000)
				pheromon.setFillColor(sf::Color::Blue);

			pheromon.setPosition(x,y);

			window->draw(pheromon);
			
			/*lines[linn].position = sf::Vector2f(x, y);
			lines[linn].color = sf::Color(255,0,0,100);

			linn++;*/



		}

		if (i%WIDTH == 0){
			y++;
			x = 0;
		}


		x++;
	}

	window->draw(lines);


}


void Drawer::drawFood (openCLinit * init, std::vector <Food*> food){


	for (Food * thisFood : food){
		if (thisFood->volume > 1){
			sf::RectangleShape pheromon(sf::Vector2f(1,1));
			sf::RectangleShape pheromonRadius(sf::Vector2f(20,20));
			//sf::RectangleShape pheromon(sf::Vector2f(thisFood->volume/10,thisFood->volume/10));
			pheromon.setFillColor(sf::Color(255,196,0,255));
			pheromonRadius.setFillColor(sf::Color(255,196,0,thisFood->volume/FOOD_FACTOR));
			pheromon.setPosition(thisFood->x,thisFood->y);
			pheromonRadius.setPosition(thisFood->x-10,thisFood->y-10);
			window->draw(pheromon);
			window->draw(pheromonRadius);
		}
	}


}

void Drawer::selectAnts (int x, openCLinit * init, sf::RectangleShape *shapeSelection, std::vector <int*> selectedAnts, bool selectionMode){
	int countSelections = 0;
	// Ant zwischen X-Bereich
	// @TODO:: Ant Selection nach beendigung des Modus löschen
	if (selectionMode){
		// Wenn die Ant in dem Selection-Bereich ist 
		if ( 
			((init->antX[x] >shapeSelection->getPosition().x) && ( init->antX[x] < shapeSelection->getPosition().x+shapeSelection->getSize().x)) 
			&&
			((init->antY[x] >shapeSelection->getPosition().y) && ( init->antY[x] < shapeSelection->getPosition().y+shapeSelection->getSize().y))
			){

				// is ant already in Vector???
				for (int *that : selectedAnts){
					// Ant existiert noch nicht im  Selection Vector
					if (*that == x){
						countSelections++;
						//std::cout << "\n\nANT IN VECTOR::::" << x;
					}
				}
				// No! add it
				if(countSelections == 0){
					selectedAnts.push_back(new int(x));
					init->color[x] = 1;
				}

				countSelections = 0;
		}
	}

}

//
//
//
//
void Drawer::drawAnts (openCLinit * init, Helper * helper){
	for (int antid = 0; antid < ARRAY_SIZE; antid++){
		sf::RectangleShape antShape(sf::Vector2f(SIZEOFANANT,SIZEOFANANT));
		// Do this only for Living Ants
		if (init->lifeStadium[antid] != 0){
			// Selection Mode
			
			////////////////////////////////////////////////////////Drawer::selectAnts(antid, targetMode);
			Drawer::selectAnts( antid, init, shapeSelection, helper->selectedAnts, helper->selectionMode);


			if (init->color[antid] == 0){
				antShape.setFillColor(sf::Color(255,255,255,255));
			}
			if (init->color[antid] == 1){
				antShape.setFillColor(sf::Color::Yellow);
			}
			if (init->color[antid] == 3){
				antShape.setFillColor(sf::Color::Green);
			}
			if (init->color[antid] == 33){
				antShape.setFillColor(sf::Color::Magenta);
			}
			if (helper->viewRadiusMode){
				sf::CircleShape radius;
				int transparency;
				BOOST ? transparency =255 : transparency = 25;
				init->isCarryingFood[antid] ? radius.setFillColor(sf::Color(0,255,0,transparency)) : radius.setFillColor(sf::Color(255,0,0,transparency));
				
				radius.setRadius(ANT_VIEWRADIUS);
				radius.setPosition(init->antX[antid]-ANT_VIEWRADIUS+2,init->antY[antid]-ANT_VIEWRADIUS+2);
				window->draw(radius);
			}

			antShape.setPosition(init->antX[antid],init->antY[antid]);


			window->draw(antShape);



			if (helper->targetMode){
				Drawer::drawTargets(init, antid);

				sf::Vertex line[] =
				{
					sf::Vertex(sf::Vector2f(init->antX[antid], init->antY[antid])),
					sf::Vertex(sf::Vector2f(init->targetX[antid], init->targetY[antid]))
				};

				window->draw(line, 2, sf::Lines);

			}


			// Check 



		}


	}



}

void Drawer::drawSimulation(openCLinit * init, Helper * helper, Simulation *sim, Stats *stats){
	/*
	*
	* DRAWING
	* 
	*/

	/**
	VIEW !!!
	**/
	
	window->setView(*view);
	*view = window->getDefaultView();
	view->zoom(init->viewSize);
	view->move(init->moveX, init->moveY);
	window->setView(*view);
	



	// clear the window with black color
	window->clear(sf::Color::Black);

	drawBackground();
	// Draws Grid
	if (helper->gridMode){
		Drawer::drawGrid(50);
	}


	BOOST ? drawPheromonMap(init) :
		drawFood(init, sim->food);	
	if (helper->pheromonMode){
		drawPheromonMap(init);
	}

	// Draws Ants
	drawAnts(init, helper);
	//std::cout << "\nANTDRAW " << clcl.getElapsedTime().asMilliseconds();
	drawHUD(stats);




	/*if (selectionMode){
	shapeSelection->setSize(sf::Vector2f(sf::Mouse::getPosition(window).x - old.x,sf::Mouse::getPosition(window).y - old.y ));
	shapeSelection->setPosition(old.x, old.y);
	shapeSelection->setFillColor(sf::Color(255, 0, 0, 50));
	window.draw(*shapeSelection);
	}*/

	window->display();
}