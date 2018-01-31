# OoT_Randomiser

--------------------------------------------------

TODO List

Find chests:
    1. Deku Tree
    2. Dodongo's Cavern
    3. Jabu Jabu's Belly
    4. Kakariko + Graveyard
    5. Zora’s Domain

Add items:
    1. A bunch of them

Figure out how to edit grotto chests

Add an item combo unlock system

--------------------------------------------------

Descriptions:

Randomiser | Randomises the items gotten from chests in the game

Extractor | Extract a zscene file and associated zmap files from a decompressed game ROM

--------------------------------------------------

Compiling instructions:

Randomiser | g++ -o Randomise main.cpp

Extractor | g++ -std=c++11 -o Extract extract.cpp

--------------------------------------------------

Usage instructions:

Randomiser | Randomise [Name of ROM file] [Seed (Optional)]

Extractor | Extract [Name of scene] [Start offset] [End offset] [Indoor/Outdoor]

--------------------------------------------------

Commiting stuff:

git add FILE

git commit -m "Note"

git push -u origin master
