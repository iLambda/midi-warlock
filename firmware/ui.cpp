#include "menu.h"
#include "ui.h"

UI::UI(Screen* screen, Input* input) {
  this->m_screen = screen;
  this->m_input = input;
  this->m_history = nullptr;
}

void UI::begin(Menu* menu) {
  /* Initialize the backstack */
  this->go(menu);
}


void UI::update() {
  this->m_history->menu->update(this);
}

void UI::go(Menu* menu) {
  /* Check if menu is null */
  if (menu == nullptr) {
    return;
  }
  /* Push on the backstack */
  this->m_history = new Backstack { this->m_history, menu };
  /* Clear screen */
  this->m_screen->clear();
  this->m_history->menu->reset(this);
  this->m_history->menu->draw(this, true);
  
}

void UI::back() {
  /* Check if pop allowed */
  if (this->m_history->previous == nullptr) {
    return;
  }
  
  /* Pop the backstack */
  auto pop = this->m_history;
  this->m_history = pop->previous;
  delete pop;
  
  /* Clear screen */
  this->m_screen->clear();
  this->m_history->menu->draw(this, true);
}

Screen* UI::getScreen() {
  return this->m_screen;  
}

Input* UI::getInput() {
  return this->m_input;
}
