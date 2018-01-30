# OoT_Randomiser

Commiting stuff:

git add FILE
git commit -m "Note"
git push -u origin master

-------------------------------------------------

Descriptions:

Randomiser | Randomises the items gotten from chests in the game

Extractor | Extract a zscene file and associated zmap files from a decompressed game ROM

-------------------------------------------------

Compiling instructions:

Randomiser | g++ -o Randomise main.cpp

Extractor | g++ -std=c++11 -o Extract extract.cpp

-------------------------------------------------

Usage instructions:

Randomiser | Randomise [Name of ROM file] [Seed (Optional)]

Extractor | Extract [Name of scene] [Start offset] [End offset] [Indoor/Outdoor]

-------------------------------------------------
