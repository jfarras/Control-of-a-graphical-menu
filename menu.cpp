/*Generic menu that the different submenus implements.Priority management when you press keyboard or mouse */

#include "mcv_platform.h"
#include "menu.h"
// GUI include
#include "gui/gui_manager.h"
// Input include
#include "input/devices/device_mouse.h"
Vector2 prevPos = input[0].mouse().position;
extern Input::CDevice_Mouse game_mouse;

void IMenu::startMenu(uint32_t first_option, uint32_t last_option) {
  start_option = first_option;
  end_option = last_option;
  current_selected_option = first_option;
  cursor.initialize(gui.getWidget("cursor"));
  initMenuOptions();
  initMenuWidgets();
  CApp::get().setClippedMouse(false);
  CApp::get().setMouseGameplay(false);


}

//Disable the menu widgets.
void IMenu::stopMenu() {

  gui.deactivateWidgets();

  button_widgets.clear();
  buttons_bar.clear();

}

//Activate menu widgets
void IMenu::activateMenuWidgets() {
  current_selected_option = 0;
  for (uint32_t i = 0; i < button_widgets.size(); ++i) {
    gui.activateWidget(button_widgets[i]);
    if (i == current_selected_option) {
      gui.getWidget(button_widgets[i])->inUse = true;
    }

  }
}
// Process the widgets with the keyboard buttons without there being mouse movement.

void IMenu::processWidgets(uint32_t current_option, bool to_down) {
  if (game_mouse.position_delta.x == 0 || game_mouse.position_delta.y == 0) {

    cursor.setActivated(false);

    auto& it = menu_options.find(current_option);
    if (to_down) {
      if (it->second == menu_options[end_option])
        it = menu_options.begin();
      else
        ++it;
    }
    else {
      if (it == menu_options.begin())
        it = menu_options.find(end_option);
      else
        --it;
    }

    current_selected_option = it->first;
    menu_option = it->second;
    int prev_count = 0;

    for (uint32_t i = 0; i < button_widgets.size(); ++i) {

      if (i == current_selected_option) {
        if (!gui.getWidget(button_widgets[i])->isCheckBox) {

          gui.getWidget(button_widgets[i])->inUse = true;
        }
      }
      else {
        gui.getWidget(button_widgets[i])->isCheckBox = false;

      }
    }
  }
}

// Process the widgets with the mouse
void IMenu::processWidgetsMouse() {

  if (cursor.inside == true) {
    if (game_mouse.position_delta.x != 0 || game_mouse.position_delta.y != 0) {

      if (cursor.getActivated() == false) cursor.setActivated(true);

      VEC2 pos(gui.getResolution().x* game_mouse.n_pos.x, gui.getResolution().y * game_mouse.n_pos.y);

      int mouse_selected = -1;

      for (uint32_t i = 0; i < button_widgets.size(); ++i) {

        Vector2 widgetPos = gui.getWidget(button_widgets[i])->params.pos;
        Vector2 widgetSize = gui.getWidget(button_widgets[i])->params.size;

        if ((pos.x >= widgetPos.x) && ((pos.y) >= widgetPos.y) && (pos.x <= (widgetPos.x + widgetSize.x)) && ((pos.y) <= (widgetPos.y + widgetSize.y))) {

          mouse_selected = i;

        }
        else gui.getWidget(button_widgets[i])->inUse = false;

      }if (mouse_selected != -1) {

        if (gui.getWidget(button_widgets[mouse_selected])->inUse == false) {

          gui.getWidget(button_widgets[mouse_selected])->inUse = true;

          current_selected_option = mouse_selected;

        }
        mouse_in_use = true;
      }
      else {
        mouse_in_use = false;
      }

      prevPos = pos;
    }
  }
}

//process the bars of the options menus
void IMenu::processBar() {
  VEC2 pos(gui.getResolution().x* game_mouse.n_pos.x, gui.getResolution().y * game_mouse.n_pos.y);
  int mouse_selected = -1;
  for (uint32_t i = 0; i < buttons_bar.size(); ++i) {

    Vector2 widgetPos = gui.getWidget(buttons_bar[i])->params.pos;
    Vector2 widgetSize = gui.getWidget(buttons_bar[i])->params.size;

    if ((pos.x >= widgetPos.x) && ((pos.y) >= widgetPos.y) && (pos.x <= (widgetPos.x + widgetSize.x)) && ((pos.y) <= (widgetPos.y + widgetSize.y))) {
      mouse_selected = i;

    }
    else gui.getWidget(buttons_bar[i])->inUse = false;

  }
  if (mouse_selected != -1) {

    if (gui.getWidget(buttons_bar[mouse_selected])->inUse == false) {

      gui.getWidget(buttons_bar[mouse_selected])->inUse = true;

      current_selected_bar_option = mouse_selected;

    }  mouse_in_use_buttons_bar = true;

  }
  else {
    mouse_in_use_buttons_bar = false;
  }

}