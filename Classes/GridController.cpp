#include "GridController.h"
#include "Enemy.h"
#include "Zombie.h"

void GridController::createGrid()
{
	int row, col,
		gridWidthAmount = (Constants::gridWidth / Constants::nodeHeight) - 1,
		gridHeightAmount = (Constants::gridHeight / Constants::nodeWidth ) - 1;

	//cocos2d::Vec2 anchor(-Constants::nodeHeight, -Constants::nodeWidth);

	for (row = 0; row < gridWidthAmount; row++) {

		for (col = 0; col < gridHeightAmount; col++) {
			if (gridHeightAmount - 1 == col && row % 2 != 0) { continue; }
			Cell* cell = dynamic_cast<Cell*>(CSLoader::createNode("Cell.csb"));

			/////////////////////////////////////////////
			int rand = cocos2d::random(0, 10);
			if (rand <= 1) {
				cell->setCanPass(false);
				cell->visualise();
			/*	rand = cocos2d::random(1, 2);
				if (rand == 2) {
					std::vector<Effect*> effects;
					effects.push_back(new EnergyInstantEffect());
					effects.push_back(new EnergyInstantEffect());
					effects.push_back(new EnergyInstantEffect());
					ConsumedActorModifier* buffer = new ConsumedActorModifier(cell, effects);
					cell->setActorModifier(buffer);
				}*/
			}
			//cell->setAnchorPoint(anchor);

			cell->setGridPos(GridCoordinates(row, col));

			this->nodes.pushBack(cell);
			this->addChild(cell);
		}
	}
}

Cell* GridController::getGridCellByCoordinate(int row, int col)
{
	Cell* current;
	for (int i = 0; i < this->nodes.size(); i++) {
		current = this->nodes.at(i);
		GridCoordinates currentPos = current->getGridPos();

		if (currentPos.col == col && currentPos.row == row) {
			return current;
		}
	}

	return nullptr;
}

void GridController::setSplit(bool split)
{
	this->isSplitting = split;
}

void GridController::setEdges()
{
	int i, j, p, size = this->nodes.size(), startJ, endJ, startP, endP,
		gridWidthAmount = (Constants::gridWidth / Constants::nodeHeight) - 1,
		gridHeightAmount = (Constants::gridHeight / Constants::nodeWidth) - 1;

	Cell* current;
	Cell* child;

	for (i = 0; i < size; i++) {
		current = this->nodes.at(i);
		GridCoordinates currentCoord = current->getGridPos();
		startJ = std::max(currentCoord.row - 1, 0);
		endJ = std::min(currentCoord.row + 1, gridWidthAmount - 1);
		startP = std::max(currentCoord.col - 1, 0);
		endP = std::min(currentCoord.col + 1, gridHeightAmount - 1);

		for (j = startJ; j <= endJ; j++)
		{
			for (p = startP; p <= endP; p++)
			{
				if (gridHeightAmount - 1 == p && j % 2 != 0) { continue; }
				if (j != currentCoord.row && ( (p == currentCoord.col + 1 && currentCoord.row % 2 == 0) || (p == currentCoord.col - 1 && currentCoord.row % 2 != 0) )) { continue; }

				child = this->getGridCellByCoordinate(j, p);
				
				if (child && !(current == child)) {
					current->addNeighbour(child);
				}
			}
		}
		current->listNeighbours();
	}
}

bool GridController::init()
{
	if (!Node::init())
	{
		return false;
	}

	this->createGrid();
	this->setEdges();
	//--------------------Config-------------------------------------
	Hero* hero = dynamic_cast<Hero*>(CSLoader::createNode("Hero.csb"));

	int row = ((Constants::gridWidth / Constants::nodeHeight) - 1) / 2,
		col = ((Constants::gridHeight / Constants::nodeWidth) - 1) / 2;
	//----------------------------------------------------------------
	Cell* current1 = this->getGridCellByCoordinate(row, col);

	this->addActor(hero, current1);

	return true;
}

void GridController::setupTouchHandling()
{
	auto touchListener = EventListenerTouchOneByOne::create();


	// trigger when you push down
	touchListener->onTouchBegan = [&](Touch* touch, Event* event) {
		Vec2 touchLocation = this->convertTouchToNodeSpace(touch);
		GameActor* actor = this->getActorByTouchLocation(touchLocation);
		GameActor* clone;

		if (actor) {
			clone = actor->click(this->isSplitting);
			this->isSplitting = false;

			if (clone) {
				this->actors.pushBack(clone);
				this->addChild(clone);
			}
		}

		return true; // if you are consuming it
	};

	// trigger when moving touch
	touchListener->onTouchMoved = [&](Touch* touch, Event* event) {
		GameActor* hero;
		for (auto iter = this->actors.begin(); iter != this->actors.end(); iter++) {
			hero = *iter;
			if (hero->getIsMoving()) {
				Vec2 touchLocation = this->convertTouchToNodeSpace(touch);
				Cell* current = this->getCellByTouchLocation(touchLocation);

				if (current && !current->getIsActivated() && current->isPassable()) { // TODO: move getIsActivated check to addPath (it must check if cell is already in path);
					hero->addPath(current);
				}
			}
		}
	};

	// trigger when you let up
	touchListener->onTouchEnded = [&](Touch* touch, Event* event) {
		GameActor* actor;
		for (auto iter = this->actors.begin(); iter != this->actors.end(); iter++) {
			actor = *iter;
			actor->setIsMoving(false);
		}
	};

	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
}

Cell* GridController::getCellByTouchLocation(Vec2 touchLocation)
{
	int row, heightLeft, col, widthLeft;
	float difference = 0.0f;
	bool isMiddlePart = false;
	int widthPart;
	int widthPartLeft;
	int heightPartLeft;

	heightLeft = (int)(touchLocation.y + 0.5f) % Constants::triangleAndRectangle;
	isMiddlePart = heightLeft >= Constants::triangleHeight;

	row = (int)(touchLocation.y + 0.5f) / Constants::triangleAndRectangle;

	if (isMiddlePart) {
		difference = ((row % 2 != 0) ? (float)(Constants::nodeWidth / 2) : 0.0);
		col = (int)(touchLocation.x + 0.5f - difference) / Constants::nodeWidth;
		widthLeft = (int)(touchLocation.x + 0.5f - difference) % Constants::nodeWidth;

		if (touchLocation.x - difference >= 0) {
			Cell* cell = this->getGridCellByCoordinate(row, col);
			return cell;
		}
	}

	return nullptr;
}

GameActor* GridController::getActorByTouchLocation(Vec2 touchLocation)
{
	GameActor* current;
	GameActor* closest = nullptr;
	GridCoordinates currentCoord;
	int radius = Constants::nodeHeight, 
		mid = Constants::nodeHeight / 2;
	float xx, yy, distance,
		  minDistance = 100000.0;

	for (auto iter = this->actors.begin(); iter != this->actors.end(); iter++)
	{
		current = *iter;
		currentCoord = current->getGridPos();

		if (currentCoord.row % 2 == 0) {
			xx = (float)(currentCoord.col * Constants::nodeWidth) + mid;
		}
		else {
			xx = (float)(currentCoord.col * Constants::nodeWidth) + (float)(Constants::nodeWidth / 2) + mid;
		}

		yy = (float)((currentCoord.row * Constants::nodeHeight) - (currentCoord.row * Constants::triangleHeight)) + mid;

		distance = (xx - touchLocation.x) * (xx - touchLocation.x) + (yy - touchLocation.y) * (yy - touchLocation.y);

		if (distance < radius * radius && distance < minDistance) {
			minDistance = distance;
			closest = *iter;
		}
	}

	return closest;
}

void GridController::spawnRandomBuff()
{
	int doSpawn = cocos2d::random(0, 100);
	int random = cocos2d::random(0, (int)this->nodes.size() - 1);
	int randomAmount = cocos2d::random(1, (int)Constants::maxBuffAmount);
	int randomType = cocos2d::random(1, (int)Constants::buffTypes);
	Cell* randomCell = this->nodes.at(random);

	if (randomCell->isPassable() && !randomCell->getVisitor() && doSpawn <= Constants::buffSpawnChance) {
		std::vector<Effect*> effects;
		for (int i = 0; i < randomAmount; i++)
		{
			if (randomType == 1) {
				effects.push_back(new EnergyInstantEffect());
			}
			else {
				effects.push_back(new HealthInstantEffect());
			}
		}
		ConsumedActorModifier* buffer = new ConsumedActorModifier(randomCell, effects);
		randomCell->setActorModifier(buffer);
	}
}

void GridController::spawnRandomEnemy()
{
	int doSpawn = cocos2d::random(0, 100);
	int random = cocos2d::random(0, (int)this->nodes.size() - 1);
	Cell* randomCell = this->nodes.at(random);

	if (randomCell->isPassable() && !randomCell->getVisitor() && doSpawn <= Constants::enemySpawnChance) {
		Zombie* zombie = new Zombie();
		Enemy* enemy = dynamic_cast<Enemy*>(CSLoader::createNode("Enemy.csb"));
		enemy->setBehaviour(zombie);
		this->addActor(enemy, randomCell);
	}
}

void GridController::addActor(GameActor* actor, Cell* cell)
{
	actor->setGridPos(cell->getGridPos());
	actor->setCurrent(cell);

	cell->setVisitor(actor);
	cell->setCanPass(false);

	this->actors.pushBack(actor);
	this->addChild(actor);
}

//void GridController::removeActor(GameActor* actor) {
//	Cell* current = actor->getCurrent();
//
//	current->setVisitor(nullptr);
//	current->setCanPass(true);
//
//	actor->clearPaths();
//	this->removeChild(actor);
//	actor = nullptr;
//	this->actors.eraseObject(actor);
//}


void GridController::moveActors()
{
	GameActor* actor;
	int i, j;
	for (i = 0; i < this->actors.size(); i++) {
		actor = this->actors.at(i);
		for (j = 0; j < actor->getSpeed(); j++) {
			moveComand.execute(actor);
		}
	}
}

void GridController::regenerateActors()
{
	int i;
	for (i = 0; i < this->actors.size(); i++) {
		this->actors.at(i)->regenerate();
	}
}

void GridController::interactActors()
{
	int i;
	for (i = 0; i < this->actors.size(); i++) {
		this->actors.at(i)->interact();
	}
}

void GridController::clearDeadActors()
{
	GameActor* current;
	for (auto iter = this->actors.begin(); iter != this->actors.end();)
	{
		current = *iter;
		if (current->getIsDead()) {
			this->removeChild(current);
			current = nullptr;
			iter = this->actors.erase(iter);
		}
		else {
			iter++;
		}
	}
}

void GridController::checkForBattles()
{
	GameActor* currentActor;
	GameActor* actorEnemy;
	Vector<Cell*> neightbours;
	int actorPower;
	int enemyPower;
		  
	for (auto iter = this->actors.begin(); iter != this->actors.end(); iter++)
	{
		currentActor = *iter;
		if (!currentActor->getIsDead())
		{
			actorPower = currentActor->getHealth();
			neightbours = currentActor->getCurrent()->getNeighbours();
		  
			for (auto j = neightbours.begin(); j != neightbours.end(); j++) {
				actorEnemy = (*j)->getVisitor();
				if (actorEnemy && actorEnemy->getTeamID() != currentActor->getTeamID()) {
					enemyPower = actorEnemy->getHealth();
					if (actorPower > enemyPower) {
						currentActor->setHealth(actorPower - enemyPower);
						actorEnemy->setIsDead(true);
					}
					else if (actorPower == enemyPower) {
						actorEnemy->setIsDead(true);
						currentActor->setIsDead(true);
					}
					else {
						actorEnemy->setHealth(enemyPower - actorPower);
						currentActor->setIsDead(true);
					}
				}
			}
		}
	}
}

void GridController::playStep()
{
	EventCustom event("playStep");
	this->getEventDispatcher()->dispatchEvent(&event);

	this->spawnRandomBuff();
	this->spawnRandomEnemy();
	this->clearDeadActors();
	this->moveActors();
	this->regenerateActors();
	this->interactActors();
	this->checkForBattles();
}