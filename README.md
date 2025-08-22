
# CS4350 Final Project - Nicholas Adkins
Here is my work on implementing a Minecraft clone into the AftrBurner Engine, namely being able to create a randomly generated terrain using some sort of pre-existing algorithm, alongside implementing the game's chunk rendering system to make displaying several thousand blocks feasible & efficient.

### Motivation
I’ve played the game for a very long time, and over the years I have watched quite a few videos covering all the many techniques used for Minecraft, various fan-made clones, and other similar voxel games. This is one of the main reasons I gained an interest in how games simulate things & how other people craft intricate solutions to these computational problems that games like Minecraft can have. This interest is my main driving reason why I ended up taking this course.

### Methodology

1. Used my previous work done in AftrBurner as a base (such as my code for managing camera controls & keyboard inputs).
2. Only used one Third-Party library, being [this perlin noise library](https://github.com/Reputeless/PerlinNoise).
3. I used this perlin noise function to randomly generate terrain across the grid/map.
4. I used AftrBurner's built-in WORawQuads class to create a VBO that handles all quads / cube faces within a given chunk, mimicing how Minecraft & other voxel games handle this. This way, I was able to render the map with far fewer objects on screen, and thus at a far higher framerate.
5. Additionally, i made it so that the chunks only render cube faces that are not obscured by other blocks, also increasing performance substantially.

### How To Run It

Make sure you have the AftrBurner engine installed, and copy this repository to your aftr/usr/modules. I did all of my development on VSCode (as opposed to the recommended Visual Studio), so within VSCode i used Microsoft's NMake and MSBuild to compile/run the program. To run this project the way i did it: add both programs to your computer's PATH, open powershell to this project's root directory, and type "nmake" to run NMake. This will cover making the solution file, compiling the program, and running it.

### `src` Folder Breakdown
Folder containing all source code for the Module
* `main.cpp` : Root of the program
* `ModuleIncludes` : All included files from Aftr & my own other files.
* `ModuleHdr` : Definition of the Aftr Module.
* `ModuleLoad` : Defines the Module's loadMap function, handling what to do upon starting the program.
* `ModuleUpdate` : Defines what the Module does upon calling updateWorld every game tick (For this project, this is largely empty).
* `ModuleMain` : Aftr Module's constructors & other extraneous Module functions.

##### `ThirdParty/`
Folder for third-party headers i included (which for this project is just one).
* `ThirdParty/PerlinNoise` : The aforementioned Perlin Noise library.

##### `My/`
Folder for custom classes / helper functions that i defined.
* `My/CubeIDs` : Defines an enum of Cube IDs, and a map mapping said IDs to a set of 6 block textures per ID.
* `My/Chunk` : Code handling the block data stored in a chunk, as well as chunk generation & most of the chunk rendering.
* `My/Grid` : Handles the whole map, containing 32x32 chunks.
* `My/Cam` : Additional functionality for Aftr's Camera, giving me simple W/A/S/D/Q/E controls
* `My/Keyboard` : Additional functionality for handling Keyboard inputs.
* `My/StdIncludes` : Couple of shared includes from the standard library, plus a couple of use statements.

#####
* `gtest`, `My/Audio`, `My/GUIs` : Unused.

### Milestones
Main Milestones (in order of completion):
- [x] (Apr 17th) Create a grid of equally sized/spaced blocks...
- [ ] ...and have each block get specific textures on each of its 6 faces. [^1]
- [x] (Apr 18th) Interim Report
- [x] (Apr 22nd) Implement a terrain generation algorithm to randomly create this sized grid of blocks, with varying heights/elevations.
- [x] (Apr 25th) Blog Post
- [x] (Apr 26th) Organize these blocks into chunks. Terrain generation will generate chunks instead (Still only a limited world, only 10 chunks by 10 chunks).
- [x] (Apr 29th) Implement several other optimization techniques to improve the performance of the simulation.
- [x] (Apr 30th) Code Review / Freeze
- [x] (May 1st) Final Report
- [x] (May 2nd) Final Demo

### Optional / Extra Ideas (of no particular order):
- [ ] Faint outline over the block you’re looking at.
- [ ] Have the ability to break & place blocks depending on which block face you’re looking at.
- [ ] Different Types of blocks: Grass blocks on the surface & stone blocks beneath them. [^1]
- [ ] “Infinite” Worlds, IE Procedural Generation up until a specified limit. In Minecraft’s case it’s the 32-bit integer limit, roughly (-2^31, +2^31) by (-2^31, +2^31) block width.
- [ ] Ability to save & load maps from a file (format is undecided as of yet).
- [ ] Player character that can walk around the world.

[^1]: Originally had this set up, but had to scrap it due to changes in how i set up chunk rendering. The WORawQuads class doesn't have an easy way to map textures to specific quad faces, so i'd have to reimplement the whole class myself. Thus i decided to skip out of the block texturing altogether.
