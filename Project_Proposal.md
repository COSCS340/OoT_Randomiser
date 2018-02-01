LoZ: OoT Randomizer Project Proposal

Team_Z
Chris Muncey, Isaac Stone, Demi Obenour, Cole Flemmons

Introduction

Synopsis:
Our proposed project is to create software that will rearrange and modify the english Nintendo 64 version of The Legend of Zelda: Ocarina of Time to increase replay value and create an experience that captures the original spirit of the game but also introduces new exciting and challenges.

Motivation:
Since all members of Team_Z are part of the Nintendo 64 generation, we wanted to bring to the table a classic, but refreshing take on the game. 
Reader Orientation:
For github programmers, code lines will be commented for easy reading and understanding. For the general user, a readme file will be included in the software package that explains how to run the application “out of the box” for everyone to enjoy.

Proposed Solution:
We intend to produce an executable file or package that will add a new and exciting level of gameplay experience by modifying existing Legend of Zelda: Ocarina of Time ROMs with custom and/or randomized game elements. The application will require a .z64 file to modify (not included) and will produce a copy with contents rearranged that will be playable via third party emulator software.
Why we are the right team:
When the forces of evil threaten Hyrule, heroes must rise up and fight to protect it. And we are those heroes. We are the right team to accomplish this task because we enjoy Nintendo's iconic Legend of Zelda franchise and wish to engage in a new game experience while capturing memories of growing up with the game.

Customer Need

Primary customer information:
Our primary user would most likely be OoT (Ocarina of Time) Speedrunners, who are people who try to finish the game as fast as possible. However, the software is designed with everyone in mind. While speedrunners will be able to exploit glitches and tricks to make the game faster, using them will not be required to complete the game, meaning anyone will be able to play.  Because randomizers make the game unpredictable, users will likely need a decent working knowledge of Ocarina of Time to be able to complete the game, but it should be fairly inviting to new players.

What they want:
Our intended primary user will want a new experience out of OoT. They’ve been playing for thousands of hours, and while they still find it fun, they want something more out of it. This delivers that, by making the game a new experience every time they play.

Context of this software on the market:
Though the implementation of our project will be open source and run independently of other applications, its operation will be dependant on the user’s acquisition of their own LoZ: OoT ROM file on their personal computer. Copyright laws prohibit us from distributing this file ourselves. Other supplemental software created by third parties will be used to obtain information we need to know about the game for our application to function properly. We will also use open source C++ compilers and text editors to write the code for our application.

Citations:
http://wiki.spinout182.com/w/Main_Page
https://wiki.cloudmodding.com/oot/Main_Page

Novelty:
Based on our research and awareness of existing software related to our project, no other application like this exists for the Legend of Zelda: Ocarina of Time game.
Proposed Solution Details

What our solution will deliver:
Our solution will deliver a compact, quick, and user friendly way to modify a classic Nintendo 64 video game for all levels of users.  Our application will run on most 64-bit and 32-bit machines.  It will be designed to be secure against malformed or malicious ROMs, so it can safely be used on such files.

How users will benefit:
The user will gain access to an the challenging and immersive world of The Legend of Zelda: Ocarina of Time, but with new twists in story progression. The game can potentially be modified over and over for a little over 1.5*1025 (25!) possibilities so you never play the same game twice! The user will be able to engage in the same classic story they have grown up with, but will be faced with a new strategic method of progressing through the game.

Have we tested idea on anyone?
Since the game’s first release in 1998, the Legend of Zelda: Ocarina of Time has developed a cult following of gamers and programmers alike that thrive within a rich online community. We believe that community would enjoy the application described in this proposal and keep the spirit of the game alive for generations to come.
How we will know if customers get benefits we want to provide:
Since our project will be available via GitHub, any potential users or programmers that wish to offer help in developing the software can submit issues or pull requests that can be revised by the team.

Customer-centric measures for success:
Issue submissions and pull requests on GitHub should be sufficient for any sort of user feedback required to improve the quality of the application.
Technology 	

What our software will do:
The application will require the user to supply a (possibly decoded) Legend of Zelda (LoZ): OoT .z64 ROM file that will be given as an argument. The application will then produce a modified copy of the .z64 ROM file containing random and possibly user specified changes that will be playable by most open source Nintendo 64 emulators.
Enhancements users will likely want:
On top of the randomizer feature of our application, it may be possible to add user specified changes to the original game i.e. changes in character outfits, game difficulty, etc. 

System Testing:
Playability of the modified file is key. We will attempt to avoid any sort of gameplay bugs or any side effect of our applications that could ruin the user’s experience of the game. We will likely track placements of objects randomized by our software by utilizing debugger software for the ROM ( specified below ). 
What we will use to build it:
GitHub will be our main medium of file exchange. Each team member will likely use a C++ compiler/ text editor to his/her preference. The final project will be compiled and ran on multiple machines for testing.

Tools:
-Randomizer will be written in C++ and will modify .z64 file type
-Utility of Time - Ocarina of Time (Debug) level editor/model viewer + editor. version .9. Copyright 2006-2008.
-Zelda Resource Extractor
-https://wiki.cloudmodding.com/oot/
-C++ IDEs / C++ compilers
-GitHub, for code hosting and code review

Team

Team Member backgrounds:

Chris Muncey - Over 2000 hours (probably) in OoT, many hours in other Zelda games. A few years C++ experience.

Isaac Stone - Multiple playthroughs of OoT, 3 years experience with C++ programming, experience with computational numerical methods.

Cole Flemmons - One playthrough of OoT, 3 years of C++ programming

Demi Obenour - 5 years of C++ programming and knowledge of low-level systems programming

Team experience with relevant tools:
Thus far, no one on our team has built anything that resembles our proposed application. However, we all have experience and knowledge of programming, and some of us have experience in the applications cited in “Technology”.
Project Management

Schedule:
At least one weekly meeting will be held via face-to-face contact or other means for each group member to report on progress of his/her work. Based on the progression towards project completion and the changing of realistic tasks/goals involved in the making of the application, we may have to reevaluate the scope of the project as we approach the deadline.

Team Member Roles:
Our goal is to keep team member roles fluid to encourage creativity and access to all parts of the project. We intend to designate and split up tasks to maximize our learning and quality of experience with the software engineering process. 

Constraints:
With less than 400 in-game objects each consisting of 2 bytes of information, application memory management and run speed should not be an issue. Each decoded .z64 file is about 64MB.  The application size will be kept to a reasonable level, depending on the minimal required structure of the software. We intend to create a few hundred objects with a size of about 32 bytes each, although it will vary from object to object. Memory constraints should not be an issue.
