/*****************************************************************************************************************
@file         GridShowcase.cpp
@project      Custom Framworks
@author       Zen Ho
@brief        This file contains our Grid Showcase Definitions

Copyright (c) 2024 Zen Ho
*****************************************************************************************************************/

// ================================================================================
// INCLUDES
// ================================================================================

#include "..\..\Header\System\pch.hpp"
#include "..\..\Header\Sandbox\GridShowcase.hpp"


void GridSC::State::Load() {

}

void GridSC::State::Init() {
	GOLGrid = std::make_unique<Map::Grid>(sf::Vector2<size_t>(50, 25), exEvents->windowCenter, sf::Vector2f(15.0f, 15.0f), sf::Color::Black, sf::Color::White, sf::Color::Blue, sf::Vector2f(25.0f, 25.0f), 5.0f);
	GOLGrid->setGridRounding(10.0f);

	//GOL Header Init
	GOLHeader = std::make_unique<Drawables::D_Text>("GAME OF LIME SIMULATION", exAssets->fonts["COMIC"], sf::Color::Black, exEvents->windowCenter + sf::Vector2f(0.0f, -350.0f));
	GOLHeader->Custom_OffsetToCenter();
	GOLHeader->setScale(0.4f, 0.4f);
	GOLHeader->Custom_SetFixedScale();

	//GOL Status Init
	GOLStatus = std::make_unique<Drawables::D_Text>("SIMULATION PAUSED", exAssets->fonts["COMIC"], sf::Color::Black, exEvents->windowCenter + sf::Vector2f(0.0f, 375.0f));
	GOLStatus->Custom_OffsetToCenter();
	GOLStatus->setScale(0.4f, 0.4f);
	GOLStatus->Custom_SetFixedScale();

	//Resize Boolean Array
	selectedArray.resize(GOLGrid->getCellCount().y);
	for (size_t i = 0; i < GOLGrid->getCellCount().y; i++) {
		selectedArray[i].resize(GOLGrid->getCellCount().x);
		for (size_t j = 0; j < GOLGrid->getCellCount().x; j++) {
			selectedArray[i][j] = GOLGrid->getCell({ j, i }).getCellSelected();
		}
	}

	//Simulation Flag
	b_SimPaused = true;
}

void GridSC::State::Update() {

	//Check For Cell Click
	if (b_SimPaused) {
		GOLGrid->checkCellClicked();
		GOLStatus->setString("SIMULATION PAUSED");
		bgColor = sf::Color::Cyan;
	}
	else {
		GOLUpdateLogic();
		GOLStatus->setString("SIMULATION ONGOING");
		bgColor = { 100, 100, 100, 255 };
	}

	//Enter Key To Toggle Simulation Status
	if (exEvents->keyTriggered(sf::Keyboard::Scancode::Enter)) {
		b_SimPaused = !b_SimPaused;
	}

	//Go Back To Main Menu Game State
	if (exEvents->keyTriggered(sf::Keyboard::Scancode::Escape)) {
		exGSManager->previousState();
	}
}

void GridSC::State::Draw() {

	//Clear Window
	exEvents->window.clear(bgColor);

	//Draw GOL Header
	exEvents->window.draw(*GOLHeader);

	//Draw GOL Status
	exEvents->window.draw(*GOLStatus);

	//Draw GOL Grid
	GOLGrid->drawGrid();
}

void GridSC::State::Free() {

}

void GridSC::State::Unload() {

}

void GridSC::State::GOLUpdateLogic() {

	//Set Boolean Buffer Grid
	for (size_t i = 0; i < GOLGrid->getCellCount().y; i++) {
		for (size_t j = 0; j < GOLGrid->getCellCount().x; j++) {
			selectedArray[i][j] = GOLGrid->getCell({ j, i }).getCellSelected();
		}
	}

	//Update Cells
	for (size_t i = 0; i < selectedArray.size(); i++) {
		for (size_t j = 0; j < selectedArray[i].size(); j++) {

			//Init Alive Count
			int aliveCount{ 0 };

			//Check Cell Neighbours
			for (int k = std::clamp(static_cast<int>(i - 1), 0, std::numeric_limits<int>::max()); k <= static_cast<int>(i + 1); k++) {
				for (int m = std::clamp(static_cast<int>(j - 1), 0, std::numeric_limits<int>::max()); m <= static_cast<int>(j + 1); m++) {
					if ((k == i && m == j) || k >= GOLGrid->getCellCount().y || m >= GOLGrid->getCellCount().x || k < 0 || m < 0)
						continue;

					//Increment Alive Count
					if(selectedArray[k][m]) {
						aliveCount++;
					}
				}
			}

			/*Decide If Cell Is Alive Or Dead*/
			if (selectedArray[i][j]) {
				if ((aliveCount == 2) || (aliveCount == 3)) {
					GOLGrid->modifyCell({j, i}).setCellSelected(true);
				}
				else {
					GOLGrid->modifyCell({ j, i }).setCellSelected(false);
				}
			}
			else {
				if (aliveCount == 3) {
					GOLGrid->modifyCell({ j, i }).setCellSelected(true);
				}
				else {
					GOLGrid->modifyCell({ j, i }).setCellSelected(false);

				}
			}
		}
	}
}