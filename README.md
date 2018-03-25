# GroundZero ⚰️

### To Build
This project requires [Raylib](https://github.com/raysan5/raylib).  
It uses an old-fashioned makefile because why not, and I usually statically link it so it can be shared easily.  
Just make sure raylib and possibly [GLFW](https://github.com/glfw/glfw) is in your search path somewhere and it should build fine.  
I use MSYS2 64bit with Clang on Windows and Xcode on macOS.  

### **ADTs** used in GroundZero:
- A graph **ADT** represents the Town, with building objects as nodes and road objects as edges. Which nodes are connected (and by what distance) can be access via an adjacency matrix. The graph supports adding nodes (buildings) and edges (roads) to itself, and querying connections. It does not support removing nodes and edges as the model the graph represents (the town) does not change once it has been created.
- A resizable array is used in many places in this data model, using the vector data type in C++. It supports the set and get operations, as well as an append operation. This **ADT** is used to store which entities are at each building (node), and to store the rendering components (buildings, roads and entities). These use cases are suited to a resizable array because their length is not known when they are created, and a fast get operation is needed (not supplied by a list).
- An array **ADT** is used to
 store the adjacency matrix. It is created once the number of nodes is known, so it does not need to be resizable. While algorithms expect a 2D matrix to represent connections between nodes, in reality it is stored as a contiguous block of memory for faster access times. A 2 coordinate access interface is used to keep compatibility.

### Design Patterns
While not an **ADT**, a useful design pattern used in GroundZero is the singleton. A singleton ensures that there is always only one instance of a given object, in this case a town. It does not make sense to create more than one town, so access is restricted to the initialiser (function to create the town object) and a global constant holds a reference to the current town.
```cpp
Town* town = Town::Instance();
```

### Model Design
This model of a small, rural town has been designed to be expandable and modular so that any town can be created using it. Other features, such as entities for cars and emergency services, hospitals and multistorey buildings can easily be implemented while still using the same framework. The graphical representation of the model is separated from the data itself with the use of a renderer object, so graphics can be easily updated without changing the underlying data model.

### Using the Model
To create the town, a graph representation must be created. To add buildings, a new building object must be created with a name, a capacity, a defensibility and a resource count (food and water). 
```cpp
// Building has parameters:         Name       Capacity   Defensibility  Resources
Building* minas = new Building("Minas Morgul",   10,          80,          5);
```
These are the basic statistics of each buildings. 
Its position, visual size and colour can then be specified for the renderer. 
```cpp
minas->position = {120, 100};
minas->size = {130, 120};
minas->colour = DARKGRAY;
```
This object can then be added to the town. 
```cpp
town->addBuilding(minas);
```

To connect up these buildings, roads must be created. A new road is created with a width and its two connecting buildings. 
```cpp
// Road has parameters:  width   from      to
Road* road = new Road(   10,    minas, townCentre);
town->addRoad(road);
```
The width specifies how many entities can move across the road in 1 time tick. The connecting buildings specify both the endpoint positions of the road and the length, which is calculated using the Pythagorean Theorem. 

### And another thing
Once all the roads and edges have been added to the town, an adjacency matrix is generated. By looking through all of the roads, its connecting buildings can be shown to be connected by setting
```cpp
adjacencyMatrix[building_1][building_2] = road_length
adjacencyMatrix[building_2][building_1] = road_length
```
The matrix is set twice due to the town being an _undirected_ graph, which means entities can move in both directions. If an entity was to look up if it can get from building 2 to building 1, it is better for it to have to check once, and that the matrix has been set twice, than for the entity to check twice, as that can introduce bugs down the track.


The renderer object is created at the start of the project, which will create the window
```cpp
// Renderer object controls how objects look
Renderer* renderer = new Renderer();
```
The renderer also has a mainloop() function, which runs after the town has been created and keeps running until the window is closed.
```cpp
// Render and simulate Town
renderer->mainloop();
```
It will update the town and then render the town, based on the position, size and colour properties defined earlier. The town update will be used when the simulation begins, to update each entity based on its environment. The graphics themselves will be updated as the simulation progresses.
