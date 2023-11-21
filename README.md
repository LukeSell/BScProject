Luke Sell

Final Year Project

Playing Games and Solving Puzzles using AI

An executable has been built and can be found in src->sudoku->bin->release->sudoku.exe, run this on a Windows OS and on a 1920 x 1080 resolution monitor.

The libraries included are SDL and SDL TTF and can be found in the libs folder, as well as GCC and the C++17 distributions. If running on another OS system these will need to be downloaded and built separately.

The Menu currently has four working buttons, to continue a game of sudoku if you have returned to the menu, start a new game of sudoku or to start the eight queens solver, you can also quit the application.

For eight queens the buttons allow you to solve the puzzle or go back to the main menu.

For sudoku you can click on squares to select them if they are not locked, i.e. grey overlay, a value for the selected square may then be set or modified by using the number keys.

For solving sudoku first make sure the grid is not modified from the initial numbers, i.e. the solver does not know to remove user added numbers that may be placed incorrectly, then click the solve button.

You can use generate to generate a sudoku, save and load to save and load sudokus from a file and benchmark to benchmark the sudoku solving algorithm. These files can be found in src->sudoku as default.save, benchmark.log and example.log for an example benchmark run result.

Documentation can be found in docs-> then either html to view as a webpage, or latex to view as a pdf->annotated.html and then browse the documentation for classes from there.

All reports can be found in the report folder, each report has its own respective folder, with the pdf being inside, there is also a copy of each of the merged reports below the folders.

All code is in src->sudoku.

The below were not added to the repository/submission in time as they were still a work in progress.

All tests are in test->sudoku.

All UML is in docs.
