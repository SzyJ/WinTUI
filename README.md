# WinTUI
Keyboard controlled UI elements for the Windows terminal.

## Example Usage
### Menu Selector

![Menu_Selector](Images/SelectionMenu.png)
```C++
const char* array[] = {
    "First entry",
    "Second entry",
    "Third entry"
};

WinTUI::MenuSelector menu(array, 3);

menu.SetSelectedBefore([](std::ostream& ostream) {
    ostream << "-> ";
    WinTUI::Color::SetConsoleColor(WTUI_DARK_BLUE, WTUI_LIGHT_YELLOW);
});
menu.SetSelectedAfter([](std::ostream& ostream) {
    WinTUI::Color::ResetConsoleColor();
    ostream << " <-";
});

menu.SetUnselectedBefore([](std::ostream& ostream) {
    ostream << "   ";
});

menu.SetUnselectedAfter([](std::ostream& ostream) {
     ostream << "   ";
});

std::cout << menu;
std::cout << "Chosen Item: " << array[menu.GetLastSelected()] << std::endl;
```
### Input Prompt
![Input_Prompt](Images/InputPrompt.png)
```C++
WinTUI::Prompt prompt("Type something");

prompt.SetSelectedBefore([](std::ostream& ostream) {
    WinTUI::Color::SetConsoleColor(WTUI_LIGHT_GREEN, WTUI_DARK_GRAY);
});

prompt.SetSelectedAfter([](std::ostream& ostream) {
    WinTUI::Color::ResetConsoleColor();
    ostream << ": ";
});

std::cout << prompt;
std::cout << prompt.GetLastResponse();
```
