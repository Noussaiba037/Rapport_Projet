#ifndef CONFIG_H
#define CONFIG_H

// Screen dimensions
#define SCREEN_WIDTH 900
#define SCREEN_HEIGHT 900

// External variables
extern int CELL_SIZE; // Cell size for maze
extern int GRID_WIDTH; // Number of columns in the maze
extern int GRID_HEIGHT; // Number of rows in the maze

#endif

/**NOTE1:
 * EXTERN DECLARATION IN THE HEADER FILE(config.h) :
 *TELLS THE COMPILER THAT VARIABLES CELL_SIZE,GRID_WIDTH ,GRID_HEIGHT WILL BE DEFINED SOMEWHERE ELSE(config.cpp)
 * So it knows these variables exist and can be used in other source files that include 'config.h'
 */

/**NOTE2:
 * THE ACTUAL VALUES OF THESE VARIABLES ARE PROVIDED IN 'config.cpp'
 * THIS IS WHERE MEMORY IS ALLOCATED FOR VARIABLES AND THEN INITIAL VALUES ARE ASSIGNED
 */

/**NOTE3: WHY DO WE NEED EXTERN ???
  **MULTIPLE DEFINITIONS**: The linker would complain about multiple definitions of the same variables (because they are defined in every source file that includes config.h).
  **CODE DUPLICATION**: You'd have to define the variables in every source file, which is inefficient and error-prone.
  **By using extern, you ensure that the variables are only defined once in the source file (config.cpp),but their declaration is available to any source file that includes config.h.
  **This avoids duplication and resolves the issue of multiple definition**

*/