#ifndef MENU_H
#define MENU_H

#include <iostream>
#include "../header/GrafManager.h" // Adjust the path if necessary

// Enum for all possible actions
enum Action {
    LOAD_DATA,
    GENERATE_GRAPH,
    DISPLAY_GRAPH,
    RUN_BNB,
    RUN_SA,
    RUN_GENETIC,
    WRITE_PATH,
    READ_PATH,
    TEST_SA_REPORT,
    TEST_SYMMETRIC_REPORT,
    TEST_BRUTE_FORCE,
    TEST_BF_REPORT,
    TEST_BNB_BFS_REPORT,
    TEST_GEN_REPORT,
    INVALID_ACTION
};

// Menu class declaration
class Menu {
    GrafManager grafManager; // Manager for graph-related operations
    void executeAction(Action action); // Central dispatcher for actions

    void wyswietlSubmenuGraf();    // Graph operations menu
    void wyswietlSubmenuAlgorytmy(); // Optimization algorithms menu
    void setupPath();              // Path operations menu
    void wyswietlTestyMisc();      // Report tests menu

    // Global settings
    void ustawieniaGlobalne(); // Settings for algorithms (e.g., cooling factor)

public:
    Menu() {};             // Default constructor

    void wyswietlMenuGlowne();     // Main menu
};

#endif // MENU_H
