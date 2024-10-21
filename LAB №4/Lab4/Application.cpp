#include "Application.h"

Application::Application() {}

void Application::MainMenu() {
    for (int len = 0; len < mainMenuItems.size(); len++) {
        std::cout << ((len == arrowPoss) ? (std::to_string(len + 1) + ". " + mainMenuItems[len] + arrow)
            : (std::to_string(len + 1) + ". " + mainMenuItems[len])) << std::endl;
    }
}

void Application::SortMenu() {
    for (int len = 0; len < sortMenuItems.size(); len++) {
        std::cout << ((len == arrowPoss) ? (std::to_string(len + 1) + ". " + sortMenuItems[len] + arrow)
            : (std::to_string(len + 1) + ". " + sortMenuItems[len])) << std::endl;
    }
}
