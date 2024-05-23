/*****************************************************************************************************************
@file         GridShowcase.cpp
@project      Custom Framworks
@author       Zen Ho
@brief        This file contains our Grid Showcase Definitions

Copyright © 2024, Zen Ho
Licensed under the MIT License. See LICENSE file in the root directory.
GitHub: https://github.com/zendenho7
*****************************************************************************************************************/

// ================================================================================
// INCLUDES
// ================================================================================

#include "..\..\Header\System\pch.hpp"
#include "..\..\Header\Sandbox\GridShowcase.hpp"


void GridSC::State::Load() {

}

void GridSC::State::Init() {

	//Starting BG Color
	bgColor = sf::Color::Cyan;

	//Simulation Flag
	b_SimPaused = true;

	//Init GOL Grid
	GOLGrid = std::make_unique<Map::Grid>(sf::Vector2<size_t>(50, 25), exEvents->windowCenter, sf::Vector2f(15.0f, 15.0f), sf::Color::Transparent, sf::Color::White, sf::Color::Blue, sf::Vector2f(25.0f, 25.0f), 5.0f);
	GOLGrid->setGridRounding(10.0f);

	//Extract Saved Data
	exData->addPath("SavedGrid");
	savedGridData = std::move(exData->loadMultipleData("SavedGrid"));
	dataIndexTracker = -1;

	//Init Next Data Button
	nextData = std::make_unique<Interface::RectButton>(sf::Color::White, sf::Vector2f(100.0f, 50.0f), exEvents->windowCenter + sf::Vector2f(((GOLGrid->getGridSize().x / 2) + (150.0f / 2) + 10.0f), 0.0f), 15.0f, 0.0f);
	nextData->initRectButtonText("NEXT", exAssets->getPrimaryFont(), sf::Color::Black);

	//Init Prev Data Button
	prevData = std::make_unique<Interface::RectButton>(sf::Color::White, sf::Vector2f(100.0f, 50.0f), exEvents->windowCenter + sf::Vector2f(-((GOLGrid->getGridSize().x / 2) + (150.0f / 2) + 10.0f), 0.0f), 15.0f, 0.0f);
	prevData->initRectButtonText("PREV", exAssets->getPrimaryFont(), sf::Color::Black);

	//GOL Header Init
	GOLHeader = std::make_unique<Drawables::D_Text>("GAME OF LIME SIMULATION | EMPTY GRID", exAssets->getPrimaryFont(), sf::Color::Black, exEvents->windowCenter + sf::Vector2f(0.0f, -350.0f));
	GOLHeader->Custom_OffsetToCenter();
	GOLHeader->setScale(0.4f, 0.4f);
	GOLHeader->Custom_SetFixedScale();

	//GOL Status Init
	GOLStatus = std::make_unique<Drawables::D_Text>("SIMULATION PAUSED ( EDITOR MODE )", exAssets->getPrimaryFont(), sf::Color::Black, exEvents->windowCenter + sf::Vector2f(0.0f, 375.0f));
	GOLStatus->Custom_OffsetToCenter();
	GOLStatus->setScale(0.4f, 0.4f);
	GOLStatus->Custom_SetFixedScale();

	//Set FrameRate Display Positon
	exTime->setDisplayPos(sf::Vector2f(0.0f, 0.0f));

	//Resize Boolean Array
	selectedArray.resize(GOLGrid->getGridCellCount().y);
	for (size_t i = 0; i < GOLGrid->getGridCellCount().y; i++) {
		selectedArray[i].resize(GOLGrid->getGridCellCount().x);
		for (size_t j = 0; j < GOLGrid->getGridCellCount().x; j++) {
			selectedArray[i][j] = GOLGrid->getCellSelected(j, i);
		}
	}

	//Init DropDown
	helperDropDown = std::make_unique<Interface::DropDown>("TOOLS", sf::Color::White, sf::Color::Black, sf::Vector2f(100.0f, 50.0f), sf::Vector2f(1525.0f, 50.0f), sf::Color::Black, sf::Vector2f(125.0f, 175.0f), 10.0f, Interface::DropDownBtnType::HOVER, Interface::DropDownAlign::DOWN_RIGHT);
	helperDropDown->addButtons("CLEAR GRID", sf::Color::White, sf::Color::Black);
	helperDropDown->addButtons("TOGGLE SIM", sf::Color::White, sf::Color::Black);
	helperDropDown->addButtons("SAVE GRID", sf::Color::White, sf::Color::Black);
	helperDropDown->addButtons("CLEAR SAVED", sf::Color::White, sf::Color::Black);
	helperDropDown->addButtons("MAIN MENU", sf::Color::White, sf::Color::Black);
	helperDropDown->arrangeButtons(sf::Vector2f(10.0f, 10.0f), 10.0f, 10.0f, Interface::DropDownArrangement::VERTICAL);
}

void GridSC::State::Update() {

	//Update DropDown
	helperDropDown->updateDropDown();

	//Reset GOL Grid
	if (helperDropDown->isButtonClicked("CLEAR GRID")) {
		dataIndexTracker = -1;
		GOLGrid->resetGrid();
		GOLHeader->Custom_SetString("GAME OF LIME SIMULATION | EMPTY GRID");
	}

	//Enter Key To Toggle Simulation Status
	if (exEvents->keyTriggered(sf::Keyboard::Scancode::Enter) || helperDropDown->isButtonClicked("TOGGLE SIM")) {
		b_SimPaused = !b_SimPaused;
	}

	//Enter Key To Toggle Simulation Status
	if (helperDropDown->isButtonClicked("CLEAR SAVED")) {
		savedGridData.clear();
		exData->saveSingularData("SavedGrid", "");
	}

	//Go Back To Main Menu Game State
	if (exEvents->keyTriggered(sf::Keyboard::Scancode::Escape) || helperDropDown->isButtonClicked("MAIN MENU")) {
		exGSManager->changeState(GSManager::GSTypes::GS_MAINMENU);
	}

	//Simulation Paused
	if (b_SimPaused) {
		//Check For Cell Click
		GOLGrid->updateIsGridClicked();
		GOLStatus->Custom_SetString("SIMULATION PAUSED ( EDITOR MODE )");
		bgColor = sf::Color::Cyan;

		//Save Grid Data
		if (helperDropDown->isButtonClicked("SAVE GRID")) {
			bool duplicate{ false };
			std::string saveData{ GOLGrid->serialize() };

			for (std::string const& data : savedGridData) {
				if (data == saveData)
					duplicate = true;
			}

			if (!duplicate) {
				std::cout << "Grid Data Saved." << '\n';
				
				//Emplace Data Onto Grid Vector
				savedGridData.emplace_back(std::move(saveData));

				//Switch Curr Grid To The Saved Grid
				dataIndexTracker = static_cast<int>(savedGridData.size()) - 1;
				GOLGrid->deserialize(savedGridData.at(dataIndexTracker));
				GOLHeader->Custom_SetString(std::string("GAME OF LIME SIMULATION") + " | SAVED GRID #" + std::to_string(dataIndexTracker + 1));
			}
		}

		//Update Next Data Button
		if (nextData->isButtonClicked()) {
			dataIndexTracker = (dataIndexTracker + 1) <= static_cast<int>(savedGridData.size() - 1) ? (dataIndexTracker + 1) : -1;

			if (dataIndexTracker != -1) {
				GOLGrid->deserialize(savedGridData.at(dataIndexTracker));
				GOLHeader->Custom_SetString(std::string("GAME OF LIME SIMULATION") + " | SAVED GRID #" + std::to_string(dataIndexTracker + 1));
			}
			else {
				GOLGrid->resetGrid();
				GOLHeader->Custom_SetString("GAME OF LIME SIMULATION | EMPTY GRID");
			}
		}

		//Update Prev Data Button
		if (prevData->isButtonClicked()) {
			dataIndexTracker = (dataIndexTracker - 1) >= -1 ? (dataIndexTracker - 1) : static_cast<int>(savedGridData.size() - 1);

			if (dataIndexTracker != -1) {
				GOLGrid->deserialize(savedGridData.at(dataIndexTracker));
				GOLHeader->Custom_SetString(std::string("GAME OF LIME SIMULATION") + " | SAVED GRID #" + std::to_string(dataIndexTracker + 1));
			}
			else {
				GOLGrid->resetGrid();
				GOLHeader->Custom_SetString("GAME OF LIME SIMULATION | EMPTY GRID");
			}
		}
	}
	else {
		GOLUpdateLogic();
		GOLStatus->Custom_SetString("SIMULATION ONGOING ( SPECTATOR MODE )");
		bgColor = { 100, 100, 100, 255 };
	}
}

void GridSC::State::Draw() {

	//Clear Window
	exEvents->window.clear(bgColor);

	//Display FrameRate ( Debugging Tool )
	exTime->displayFrameRate();

	//Draw GOL Header
	exEvents->window.draw(*GOLHeader);

	//Draw GOL Status
	exEvents->window.draw(*GOLStatus);

	//Draw GOL Grid
	GOLGrid->drawGrid();

	//Draw Next & Prev Buttons
	if (savedGridData.size() > 0 && b_SimPaused) {
		nextData->Custom_Draw();
		prevData->Custom_Draw();
	}

	//Draw DropDown
	helperDropDown->drawDropDown();
}

void GridSC::State::Free() {
	exData->saveMultipleData("SavedGrid", savedGridData);
}

void GridSC::State::Unload() {

}

void GridSC::State::GOLUpdateLogic() {

	//Set Boolean Buffer Grid
	for (size_t i = 0; i < GOLGrid->getGridCellCount().y; i++) {
		for (size_t j = 0; j < GOLGrid->getGridCellCount().x; j++) {
			selectedArray[i][j] = GOLGrid->getCellSelected(j, i);
		}
	}

	//Update Cells
	for (size_t i = 0; i < selectedArray.size(); i++) {
		for (size_t j = 0; j < selectedArray[i].size(); j++) {

			//Init Alive Count
			int aliveCount{ 0 };

			//Check Cell Neighbours
			for (int k = static_cast<int>(i - 1); k <= static_cast<int>(i + 1); k++) {
				for (int m = static_cast<int>(j - 1); m <= static_cast<int>(j + 1); m++) {
					if ((k == i && m == j) || k >= GOLGrid->getGridCellCount().y || m >= GOLGrid->getGridCellCount().x || k < 0 || m < 0)
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
					GOLGrid->setCellSelected( j, i ,true);
				}
				else {
					GOLGrid->setCellSelected(j, i, false);
				}
			}
			else {
				if (aliveCount == 3) {
					GOLGrid->setCellSelected(j, i, true);
				}
				else {
					GOLGrid->setCellSelected(j, i, false);
				}
			}
		}
	}
}