# LoZ: OoT Randomizer Status Report

### Team_Z (Team 7)

### Chris Muncey, Isaac Stone, Demi Obenour, Cole Flemmons

## Introduction

Our team is creating a program with a graphical user interface that will modify an existing Nintendo 
64 ROM file. With a few settings selected and the press of a button, the user will have a brand new ROM 
file prepared for them that will be compatible with most Nintendo 64 emulators. The randomizer program will 
randomly switch items around within the game according to their dependencies so that the game is actually playable 
and beatable. The user interface will also offer a selection of main character outfit color modifications to 
further enhance the gaming experience. Other modifications will be added to make the game more streamlined, such 
as removing various cut-scenes and elimination some of the more tedious gameplay.

## Accomplishments:

Thus far, we have completed the working randomizer for the first three levels of the game (This is intentional, as
our project is a demo version). We also have a simple GUI interface up and running, which is able to run the randomizer and the color changer.

## Customer Value:

Our primary user or “customer” will most likely be gamers who have played OoT (Ocarina of Time) before and wish to
engage in a new experience while reliving a childhood classic. However, the software is designed with everyone in mind,
and someone who has never played the game before will still be able to play it and beat it (although it may be difficult).
The randomizer will greatly increase replay value for the game, keeping users coming back for more experiences. Anyone
who possesses an Ocarina of Time ROM file and an emulator on their computer will be able to use this software to create
as many modified games as desired.

## Developer Value:

Though the final randomizer product is aimed toward gamers and Legend of Zelda fans, the individual components will 
be useful to communities of modders and developers that wish to know more about how to build software that can modify
Nintendo 64 game ROMs. Specifically, another classic game: LoZ: Majora’s Mask contains very similarly structured elements 
as the Ocarina of Time and much can be learned from one that can be carried over to the other. Ideally, someone that is
new to modding would be able to find our software and learn from how we built it and how it replaces and inserts values 
to change the binary file. The intended implementation of the GUI for the program is being developed using Qt libraries and 
environment, so any developer interested in basic construction of how a GUI is constructed will be able to learn from our 
project as well. 

## Technology/Resources:

* Qt GUI (written by Demi)
   * Small, manageable window with randomizer seed options
   * Character color selection
   * Drop-down to choose file path
   * Calls Randomizer to copy and edit file 
* Randomizer written in C++ and will modify .z64 file type (written by Chris)
   * Decompresses .z64 file
   * Stores entire binary game file (65Mb) as an array
   * Changes indexes (addresses) of elements based on randomized values
   * Writes entire edited file to a new .z64 file for user
* Utility of Time - Ocarina of Time level editor/model viewer + editor. version .9. Copyright 2006-2008.
* https://wiki.cloudmodding.com/oot/
* C++ IDEs / C++ compilers, in particular Qt Creator
* GitHub, for code hosting and code review
* Online OoT Interactive Map at https://ootmap.com
* Groupme App (group communication)

## Team:

Team meeting frequency has declined to once per sprint to allow time for other class work. In the final month before the project
is due, meeting frequency and sprint assignments will increase in order to be sure that a working version of the project will be 
completed. Thus far, all team members have been present at most meetings. From this point onward, the group will increase 
communication with respect to what is expected from each group member, checking each other’s sprint work, and meeting more 
frequently. We are considering splitting into two separate teams, one for the GUI and one for the randomizer and color changer.

## Contributions:

* Isaac Stone - Color Changer
* Chris Muncey - Extractor/Randomizer
* Demi Obenour - Qt GUI and interaction with Randomizer
* Cole Flemmons - Support

## Project Management:

The first sprint of the project was to find and document the various chest object locations found throughout the game data. The
skeleton of the randomiser was completed in the first few weeks, but the rest of it has been collected over the past few sprints.
The next few sprints are going to be figuring out the item dependencies of the remaining chests, and implementing those into the
randomizer, as well as finishing up the GUI. Once this is done, the project should be in working order and ready for a beta release. 
We plan to compile for Windows, Linux, and MacOS distributions so that the user doesn’t have to compile the project. 

## Reflection:

The previous sprints have been informative with regard to group performance as a result of communication, clear goals, and frequency
of group meetings. It has come to our attention that all of these elements are required for a productive team environment. In the
weeks approaching the final presentation, extra effort will be directed toward documenting our experience of developing the project
and making sure all team members know what is expected of them. Almost everything went smoothly, apart from the GUI. While it did
work, it was hard for the rest of the team to compile it, making communication harder.  This was due to the use of a complex GUI toolking (Qt).

## Items to be Included in Final Report:

* Project Modules
   * Item Dependency Tree 
   * ROM Decompressor
   * GUI
   * Color Change Feature
* Locations/addresses of where data is modified in game file (for modders)
* Audience/Target users
* Outside resources (Address Map, Wiki Site, helpful software )
* Tools used for development ( languages, IDEs, libraries for compilation, etc. )
* Progress Timeline
* Project Management Outline
* Team Member Contributions
* User Manual
* Explanation of chest object, how we changed them



