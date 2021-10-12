# PA1: Particle System
This project is based on the OpenFrameworks Particle example.
 This repository is part of a Programming Assignment for the Advanced Programming Course.
 The purpose of this project is to help the student create practical programming skills by implementing
 changes to the base code that require strong understanding of the concepts discussed in class.
## Setup
1. Clone this project inside an OpenFrameworks installation's "apps/myApps/" directory
2. Run the command "make" in the terminal or the "Build" Task in VSCode.

## Submitting Assignment
To submit this assignment, create a Release with the branch that holds all the changes you have added. If no Release is made,
the last commit to the master branch will be graded.

Don't forget that you must also fill out an evaluation form in Moodle to consider the project submitted.

## Grading
You will only be graded for specs that were completed.

Any project that doesn't compile will receive a 0.

If a partner has no commits in the repositories, he will receive a 0.

## Student Notes
If you have any notes to add for your TA about the project specs or creative additions, you may do so in this section of the README

New Particle shape:
You can change the shape of the particles by pressing the 5 or 6 key. 5) changes the particles to squares and 6) changes the particles back to circles. This was achieved by creating a new set of enums inside the Particle.h file to be able to change the particles without altering the modes themselves and this results in being able to change between the two shapes and adjust them no matter the mode.