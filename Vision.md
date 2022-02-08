# Vision

## Entities

### Commodity
- has type
    - industrial, illegal, essentials, luxury, ores, mineral cores...
    - some special types
- has **manufacturer**
- has **value range** in $

### Ship frame
- has **name**
- has amount of empty **slots** for modules
- has some **pre-built combinations** of modules
    - mainly for bots
- has **general stats** like
    - speed
    - hull integrity points
    - evasion chance
    - inventory size
- has **class**
    - imposing limitations on slots capacity 
    - and general stats
- has **manufacturer**
- has **value range** in $

### Ship module
- at least:
    - several weapon types
        - damage type
        - accuracy
        - cd/alpha combinations
        - energy cost
    - several shield types
        - damage type
        - recharge rate/delay
        - energy cost
    - several armor plating types
    - several general boosters
        - like drives for speed/eva
    - several grades of reactors
    - several drills
- 3 types: attack, defense, support
- has **manufacturer**
- has **value range** in $

### Planetary systems
- has commodity type preference
- has order/stability level
- has manufacturer affinity
    - stuff from him cheaper and more common
- has tech level

- has 1 trade station
- has chance of triggering **random event** on enter
- has asteroid belt with option for player to use event *mine stuff*
    - **supposed source for staring capital**
- **can take modificators**

### Hyperlane
- connects 2 systems
- has traverse time in days
- can be stable or unstable
    - unstable can become unusable 
    depending on order level of systems

### Trade station
- has semi-random stock of commodities and modules
    - depending on system paramerers
- stock refreshes every *range of days*, modified by order level
    - for oprimisation reasons refreshes *if that amount of days passed since last player visit*
- goods sold by player remain in stock until next refresh

### Random event
- sth like 
    - pirate attack
    - manufacturers raid
    - enforcers raid on pirate base
    - etc..
- **always** produce modificatiors
    - for system where happened
    - maybe for neighboring
    - maybe for same manufacturer

### Modificator
- **can** have duration
- have impact on system's parameters
- p.e
    - taking side on manufacturers raid changes affinity
    - war changes preferred commodity type
    - piracy shenanigans - same
    - etc..

### Mercenaries
- bot ships enhabiting some systems
- on encountering have options
    - to fight
    - run to previous system
- fight victory gives option 
    - transfer to mercenary ship frame
    - salvage mercenary ship frame

## Game goal
Defeat all mercenaries *ASAP* and **produce custom "personal" frame**

## Game flow
Player spawns in galaxy in given state (systems, hyperlanes & their parameters). 
Player travels between systems, buying and selling commodities for earning money  
For forming starter capital player can use *mining* event, but in small amounts  
Player starts in weak ship with pre-built modules combinations  
Player can upgrade ship with new bought modules  
Player can transfer to new ship, salvaging previous for $.  

## In-game battles
Ships *take turns*, based ton their modules; *combat log* is shown, player can *retreat* and *modificator* can be applied to system afterwards 

## Game uniqueness
Each game has its *subset of all ship frames* available in game world.
All ship frames consist of *designed by developer and by players*, who won the game.
Before each game, *client contacts the server* for given subset,
and victor *gets access to creating* ship frame with his personal parameters (yet limited by ship class for balance reasons) and *uploading* it to the server

## Databases
One on client for game managing (logging new events, getting parameters for regenerating stock)
One on server for storing all uploaded ship frames including developer's *and maybe leaderboards*
Client stores only starter ship

## UI
All interaction is textual, like in old quest games.
*Maybe* with meaningless vector images on top, for stations, ships, suns and hyperlane travel
### Screens:
- system view
on docking with trade station:
- ship slots + inventory overview
- trade station stock
- news in galaxy feed (events log in other systems)
on battle:
- combat screen
on game victory: 
- ship frame creation screen