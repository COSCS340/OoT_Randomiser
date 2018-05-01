# LoZ: OoT Randomizer Final Report

## Team_Z (Team 7)

### Chris Muncey, Isaac Stone, Demi Obenour, Cole Flemmons

#### Introduction

The goal of our team was to write a program with a graphical user interface that would modify
an existing Nintendo 64 ROM file. With a few settings selected and the press of a button, the 
user would have a brand new ROM file prepared for them that will be compatible with most 
Nintendo 64 emulators. The randomizer program was designed to randomly switch items around within
the game according to their dependencies so that the game is actually playable and beatable. 
The user interface would also offer a selection of main character outfit color modifications 
to further enhance the gaming experience. Other modifications were to be added to make the game
more streamlined, such as removing various cut-scenes and elimination some of the more tedious
gameplay.

#### Motivation:

The motivation for this project is that many people, including our team, love the game Legend
of Zelda: Ocarina of Time, but playing the same game many times in a row can be boring. This
tool will allow the game to be different every time it is played, prompting new challenges and
greatly enhancing replay value.  

#### Approach:

The code contains several parts: the randomizer in C++, a GUI using C++ and Qt, a color randomizer
in C++, a chest randomizer, and others. Our approach was to build compartmentally. Each group
member took on a different piece of the project, and the different parts came together in the
end to create our randomizer.

#### Changes to Design/Requirements: 

Initially, we were not sure if the N64 ROM files could be modified successfully, as the project
would require. After realizing the initial goal of a simple randomizer was attainable, we sought
to include an optional GUI interface for users that are uncomfortable with the command line. We 
also planned on including a color changer for select elements to further enhance the users
experience. Intense debugging and assimilation of the color changer were not able to be completed
due to time constraints and busy class schedules (Two team members were taking cs360 and two team
members were working on senior projects).

#### Results/Conclusions:

The resulting product is a working randomizer that successfully randomizes the first half of the
game and produces a playable game that can be run via command line arguments or the GUI. The resulting
game is guaranteed to be beatable, and players will never find themselves stuck in any part of the
game. The GUI contains interfaces for the color changer for future development. The color changer is
not finished and is not able to run standalone, unfortunately. Regarding the functionality of the
initial project proposal, it is fair to say that we completed the main goals of our project. With
more time, it would definitely be possible to implement the supplemental functionalities we had intended. 

#### Customer/Developer Value

(No Changes)

Our primary user or “customer” will most likely be gamers who have played OoT (Ocarina of Time) before
and wish to engage in a new experience while reliving a childhood classic. However, the software is
designed with everyone in mind, and someone who has never played the game before will still be able to
play it and beat it (although it may be difficult). The randomizer will greatly increase replay value
for the game, keeping users coming back for more experiences. Anyone who possesses an Ocarina of Time
ROM file and an emulator on their computer will be able to use this software to create as many modified
games as desired.

Though the final randomizer product is aimed toward gamers and Legend of Zelda fans, the individual 
components will be useful to communities of modders and developers that wish to know more about how to
build software that can modify Nintendo 64 game ROMs. Specifically, another classic game: LoZ: Majora’s
Mask contains very similarly structured elements as the Ocarina of Time ( similar game objects, ROM
file structure, etc.), and much of the information we have acquired about the first game can be applied
to the other game. Ideally, someone that is new to modding would be able to find our software and learn
how we built it and how it replaces and inserts values to change the binary game file. The implementation
of the GUI for the program was developed using Qt libraries and environment, so any developer interested
in basic construction of how a GUI is constructed will be able to learn from our project as well. 

#### Technology

#### Changes From Status Reports: 

After completing the functionality of a working game randomizer, we wanted to build an easily accessible
GUI and a supplemental color changer. We also wanted to remove some of the more tedious elements of the
game such as unavoidable extended cutscenes and tutorial-like game elements that make a very slow process
out of starting a new game. Most of the work involved with these tasks revolved around figuring out how to
accomplish them without the game crashing and without ruining game graphics or user experience. Since the
initial goal of a basic implementation, the only technology added included using Qt libraries and the Qt
IDE for development. Other resources were used as references ( such as some of the software and websites
listed below ) to discover more information about how the .z64 file is structured.

#### Technology/Resources:

- Utility of Time - Ocarina of Time level editor/model viewer + editor. version .9. Copyright 2006-2008.
- https://wiki.cloudmodding.com/oot/
- C++ IDEs / C++ compilers, in particular Qt Creator
- GitHub, for code hosting and code review
- Online OoT Interactive Map at https://ootmap.com
- Groupme App (group communication)

#### Tests:
After compiling the project and making sure the game elements were actually randomized, we made sure 
that the changes made did not crash the game and that the game was beatable (or at least the portion 
that we changed was beatable). This required playthroughs to test the game and was an aspect of 
development where a community of users would have been very helpful to communicate with to identify
and fix bugs that arose. The removal of tedious obstacles sometimes required the replacement of a 
game object or simply moving it somewhere else, which could trigger unpredictable behavior. We had
to make sure the game would allow for the variations we made.

#### Test Results:

Simply playing through the our edited section of the game was enough to test cutscenes and obstacle
removals. If the game did not crash immediately, no glitches or other hidden issues presented
themselves. An unbeatable game was not encountered by anyone on our team and should not be possible
with Chris’s randomizing algorithm, but there was always a possibility of a bad combination of items
that could lead to getting stuck at a particular point if an item is misplaced or a mistake is made
with respect to the item dependencies in the code.  

#### Modules/Components:
+ Qt GUI (written by Demi)
    - Small, manageable window with randomizer seed options
    - Character color selection
    - Drop-down to choose file path
    - Calls Randomizer to copy and edit file 
+ Randomizer written in C++ and will modify .z64 file type (written by Chris)
    - Decompresses .z64 file
    - Stores entire binary game file (64MB) as an array
    - Changes indexes (addresses) of elements based on randomized values
    - Writes entire edited file to a new .z64 file for user
+Color Selector
    - Changes RGB or RGBa values at specified location in file
    - User selected color preferences
    - Change color of player clothes/gear and Navi ( the fairy )
    - Not Finished 


#### Team

After the goal of the project was decided, team meetings generally took place once per sprint to allow
time for other class work. In the final month before the project was due, meeting frequency and sprint
assignments increased in order to prepare a working version of the project to be presented. After a
lull in productivity in the middle of the semester we decided to increase communication with respect
to what is expected from each group member, frequently check each other’s sprint work, and meet more
frequently to discuss putting the components of the project together. These changes increased productivity
and participation, though most of the actual coding was done by Chris and Demi.  All team members have
been present at group meetings and actively participated with varying degrees of performance. 

Roles were generally static. As stated above, Chris was in charge of the randomizer development and
Demi was in charge of the GUI. Isaac attempted to write the color changer, which is almost complete but
not integrated into the project. Cole researched file structure with Chris and contributed to debugging.
All group members participated in brainstorming, testing, and writing the reports throughout the
semester. Generally, Chris and Demi spearheaded the construction of the project and the merging of
their respective components. 

#### Project Management

Throughout the duration of the project it became more apparent that it is important to examine the scope
of the project frequently and have a clear goal in mind for all team members at each sprint. It was very
easy to lose focus on what the team was trying to accomplish because there were always more functionalities
to add, more opportunities to increase security, and more ways to optimize. It may have been more beneficial
for our team to appoint a designated leader with a clear view of what the outcome of the project should be
to make sure that all goals were met. A leader would have been able to supervise out compartmental approach
and spread around his/her time to whichever part of the project need it most. Generally, sprint goals were
met on schedule with the exception of the GUI compilation. There were stretches of time in the middle of the
semester where there were not many goals set. The main reason for this was because the team had other difficult
classes taking up time away from the project. 


#### Reflection

In retrospect, our group has begun to understand the difficulty of building a project with regard to group
performance as a result of communication, clear goals, and frequency of group meetings. It has come to our 
attention that all of these elements are required for a productive team environment. In the weeks approaching 
the final presentation, extra effort was directed toward documenting our experience of developing the project 
and making sure all team members know what is expected of them. Almost everything went smoothly, apart from the
GUI. While it did work, it was hard for the rest of the team to compile it on their personal machines, making
communication about debugging it difficult. Were we to attempt a project like this again, we would try to be 
more concise about goals and our strategy for development ( for instance, come up with a clear task, get the 
software up and running and then optimize later ). Overall, We are satisfied with the foundation we have built 
for a working piece of software that will hopefully be used for years to come. It provides many of possibilities 
for entertainment and development for the Legend of Zelda fan community.
