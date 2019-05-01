#include "menu.h"

MenuList::MenuList(uint8_t nbItems, const Item items[], Align align) : m_align(align), m_items(items), m_nbItems(nbItems), m_selected(0) {

}

void MenuList::reset(UI* parent) {
  /* Reset item */
  this->m_selected = 0;
}

void MenuList::draw(UI* parent, bool firstTime) {

  /* Get peripherals */
  auto screen = parent->getScreen();
  auto input = parent->getInput();

  /* If less one item */
  switch (this->m_nbItems) {
    case 1:
      /* If not first time, do nothing */
      if (!firstTime) {
        return;
      }
      /* Draw cursor */
      screen->setCursor(0, 0);
      screen->put(2);

      /* Check align */
      if (this->m_align== Align::CENTER) {
        /* Draw reverse cursor */
        screen->setCursor(15, 0);
        screen->put(3);
        /* Center text */
        screen->setCursor(8 - (strlen(this->m_items[0].name) / 2), 0);
      }
      /* Draw text */
      screen->write(this->m_items[0].name);

      /* Done */
      break;

    case 2:
      /* Erase */
      screen->setCursor(0, 1 - this->m_selected);
      screen->write(" ");
      if (this->m_align== Align::CENTER) {
        screen->setCursor(15, 1 - this->m_selected);
        screen->write(" ");
      }
      /* Draw */
      screen->setCursor(0, this->m_selected);
      screen->put(2);
      if (this->m_align== Align::CENTER) {
        screen->setCursor(15, this->m_selected);
        screen->put(3);
      }


      /* No redraw text if not first time */
      if (!firstTime) {
        return;
      }

      /* Draw first text  */
      if (this->m_align== Align::CENTER) {
        screen->setCursor(8 - (strlen(this->m_items[0].name) / 2), 0);
      } else {
        screen->setCursor(1, 0);
      }
      screen->write(this->m_items[0].name);

      /* Draw second text  */
      if (this->m_align== Align::CENTER) {
        screen->setCursor(8 - (strlen(this->m_items[1].name) / 2), 1);
      } else {
        screen->setCursor(1, 1);
      }
      screen->write(this->m_items[1].name);

      /* Done */
      break;

    default:

      /* No redraw selector if not first time */
      if (firstTime) {
        /* Draw selected on top line */
        if (this->m_align== Align::CENTER) {
          screen->setCursor(15, 0);
          screen->put(3);
        }
        screen->setCursor(0, 0);
        screen->put(2);
      }

      /* Erase text */
      screen->setCursor(1, 0);
      screen->write("              ");
      screen->setCursor(1, 1);
      screen->write("              ");

      /* Write first item */
      if (this->m_align== Align::CENTER) {
        screen->setCursor(8 - (strlen(this->m_items[this->m_selected].name) / 2), 0);
      }
      screen->write(this->m_items[this->m_selected].name);


      /* Check it bottom line exists */
      if (this->m_selected + 1 < this->m_nbItems) {
        /* Place cursor */
        if (this->m_align== Align::CENTER) {
          screen->setCursor(8 - (strlen(this->m_items[this->m_selected + 1].name) / 2), 1);
        } else {
          screen->setCursor(1, 1);
        }
        /* Write */
        screen->write(this->m_items[this->m_selected + 1].name);
      }

      /* Check if not in center mode */
      if (this->m_align != Align::CENTER) {
        /* Can scroll up ?*/
        if (this->m_selected != 0) {
          screen->setCursor(15, 0);
          screen->put(0);
        }
        /* Can scroll down ? */
        if (this->m_selected != this->m_nbItems - 1) {
          screen->setCursor(15, 1);
          screen->put(1);
        }
      }
      /* Done */
      break;
  }
}

void MenuList::update(UI* parent){
  /* Get peripherals */
  auto screen = parent->getScreen();
  auto input = parent->getInput();

  /* If enter is pressed */
  if (input->isKnobPressed()) {
    /* Go to element */
    if (this->m_items[this->m_selected].target != nullptr) {
      parent->go(this->m_items[this->m_selected].target);
    } else {
      parent->back();
    }
    /* Done */
    return;
  }

  /* Check if knob moved */
  if (input->getKnob() != 0) {
    /* Edit the selected */
    this->m_selected = (this->m_selected + this->m_nbItems + input->getKnob()) % this->m_nbItems;
    /* Clear & show */
    this->draw(parent);
  }
}
