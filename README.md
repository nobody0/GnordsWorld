GnordsWorld
===========

We need a ne map because the default hashmap is to slow

requirements:
-fast iteration with a known starting node in a known area of x/y coordinates
-fast random access in a known area (roughly 100x100 in size)
-fast "moving" of that known area by a few cells in both or either x/y direction
-virtually unlimeted amount of nodes
-allowing for empty areas, not every x/y coordinate has to be assigned a value


my current idea

a list of double linked nodes which contian another list of double linked nodes
each list is dedicated for x or y respectively and is sorted
on insertion we have to pass a known node close to our insertion
on find we also have to give  known node close to what we want to find
this should solve the requirements for fast iteration, virtually unlimited size and fast insertion with a known node nearby
to improve the speed of random access in a known area we also have a 2d array which can be accessed with the x/y coordinates, this area is kept in sync with the current update area and player position
