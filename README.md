# War-Simulation
Object-Oriented Project built in Visual Studio 2022 using C and CPP.
This is a war game simulator that is built upon finite state machines structure with graphics.

# General Info
there is two teams fighting each other. the map is filled with black and red storages .
- Blue Team - Team 1 2 soldiers and squire
- Green Team - Team 2 : 2 soldier and squire
- Black Box - Ammo Storage
- Red box - Health Storage

![image](https://github.com/cohenyuval315/War-Simulation/assets/61754002/4124efbf-c3f0-4fde-af08-264266880449)


## Map
- randomly generation of rooms
- A star algorithm to create the tunnels
- Teams Random Room Spawn


## Soldiers:
- Patrolling rooms randomly
- Attacking enemy soldiers until no ammo or low hp ,
- Retreating searching squire for health or ammo
- if squire dont have more ammo or health , soldier will keep fighting
- has 2d vision not going though walls
- main path algorithm used Astar
### States
- Attacking
- Retreating
- Patrolling

  
## Squires:
- only squire can interact with storages
- Take resourses from the map's storages while remembering the storages content.
- if full go to base and stay until soldier comes and take resources.
- 2d vision not going through walls
- main path algorithm used Astar

### States
- Going to Spawn
- Search Resourses


# Preview
![cp](https://github.com/cohenyuval315/War-Simulation/assets/61754002/65fc85c0-078f-4341-9fa1-becba1efac4c)

# Todo
- optimize performance
- add cuda support
- add more states











