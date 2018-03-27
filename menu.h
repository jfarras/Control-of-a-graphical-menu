#ifndef INC_MENU_H_
#define INC_MENU_H_


// Input include
#include "input/input_manager.h"
#include "gui/cursor.h"

struct IMenu {
  // Needed Variables
  std::string menu_option;
  uint32_t    current_selected_option;
  int    current_selected_bar_option;
  uint32_t    start_option; // This is the first option in the current menu
  uint32_t    end_option;   // This is the last option in the current menu
	bool mouse_in_use = false;
  bool mouse_in_use_buttons_bar = false;
	bool scrollable = false;
	bool image = false;
  
	int previous_option = 0;

  const Input::TButton& btUp    = input.key(VK_UP);
  const Input::TButton& btDown  = input.key(VK_DOWN);
  const Input::TButton& btLeft  = input.key(VK_LEFT);
  const Input::TButton& btRight = input.key(VK_RIGHT);
  const Input::TButton& btEnter = input.key(VK_RETURN);
  const Input::TButton& btExit  = input.key(VK_ESCAPE);
  const Input::TButton& btPause = input.key(VK_ESCAPE);

  // Common Menu structures
	std::vector<std::string>        button_widgets;
  std::vector<std::string>        bar_widgets;
  std::vector<std::string>        buttons_bar;

  CCursor cursor;
  std::map<uint32_t, std::string> menu_options;
  std::map<uint32_t, std::string> bar_options;

  // Common Menu functions
  virtual void initMenuOptions() = 0;
  virtual void initMenuWidgets() = 0;
  virtual void initMenuBars() = 0;
  void startMenu(uint32_t first_option, uint32_t last_option);
  void stopMenu();

  void activateMenuWidgets();
 
  void processWidgets(uint32_t current_option, bool to_down);
  void processWidgetsMouse();
  void processBar();
};

#endif