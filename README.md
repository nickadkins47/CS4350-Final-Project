
# CS4350 Final Project - Nicholas Adkins

### Abstract
Here is my work on implementing a Minecraft clone into the AftrBurner Engine, namely being able to create a randomly generated terrain using some sort of pre-existing algorithm, alongside implementing the game's chunk rendering system to make displaying several thousand blocks feasible & efficient.

### Motivation
I’ve played the game for a very long time, and over the years I have watched quite a few videos covering all the many techniques used for Minecraft, various fan-made clones, and other similar voxel games. This is one of the main reasons I gained an interest in how games simulate things & how other people craft intricate solutions to these computational problems that games like Minecraft can have. This interest is my main driving reason why I ended up taking this course.

### Methodology

1. Used my previous work done in AftrBurner as a base (such as my code for managing camera controls & keyboard inputs).
2. Only used one Third-Party library, being [this perlin noise library](https://github.com/Reputeless/PerlinNoise).
3. I used this perlin noise function to randomly generate terrain across the grid/map.
4. I used AftrBurner's built-in WORawQuads class to create a VBO that handles all quads / cube faces within a given chunk, mimicing how Minecraft & other voxel games handle this. This way, I was able to render the map with far fewer objects on screen, and thus at a far higher framerate.
5. Additionally, i made it so that the chunks only render cube faces that are not obscured by other blocks, also increasing performance substantially.

### Milestones
Main Milestones (in order of completion):
- [x] (Apr 17th) Create a grid of equally sized/spaced blocks...
- [ ] ...and have each block get specific textures on each of its 6 faces. [^1]
- [x] (Apr 18th) Interim Report
- [x] (Apr 22nd) Implement a terrain generation algorithm to randomly create this sized grid of blocks, with varying heights/elevations.
- [x] (Apr 25th) Blog Post
- [x] (Apr 26th) Organize these blocks into chunks. Terrain generation will generate chunks instead (Still only a limited world, perhaps only 8 chunks by 8 chunks).
- [x] (Apr 29th) Implement several other optimization techniques to improve the performance of the simulation.
- [x] (Apr 30th) Code Review / Freeze
- [ ] (May 1st) Final Report
- [ ] (May 2nd) Final Demo

### Optional / Extra Ideas (of no particular order):
- [ ] Faint outline over the block you’re looking at.
- [ ] Have the ability to break & place blocks depending on which block face you’re looking at.
- [ ] Different Types of blocks: Grass blocks on the surface & stone blocks beneath them. [^1]
- [ ] “Infinite” Worlds, IE Procedural Generation up until a specified limit. In Minecraft’s case it’s the 32-bit integer limit, roughly (-2^31, +2^31) by (-2^31, +2^31) block width.
- [ ] Ability to save & load maps from a file (format is undecided as of yet).
- [ ] Player character that can walk around the world.

[^1]: Originally had this set up, but had to scrap it due to changes in how i set up chunk rendering. The WORawQuads class doesn't have an easy way to map textures to specific quad faces, so i'd have to reimplement the whole class myself.