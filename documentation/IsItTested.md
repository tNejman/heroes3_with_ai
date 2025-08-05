# Is it tested?

As of 30.06.2025; 20:11; commit name: "suck me off nigga"

✅ -> Yes
❌ -> No (should specify why)
⚪ -> N/A (also should specify why)
🛠️ -> WiP

Algorithms:
    - MinimaxAI.h ❌(not yet)

Artifacts:
    - Artifact.h ✅

Battle:
    Moves:
        - AttackMove.h ❌(not yet)
        - Move.hpp ⚪(is an interface)
        - MoveFactory.h ❌(not yet)
        - MoveMove.h ❌(not yet)
        - WaitMove.h ❌(not yet)
    - Battle.h 🛠️
    - BattleField.h 🛠️
    - Obstacle.h ❌(not yet)
    - Tile.h ❌(not yet)
    - TileObject.h ❌(not yet)

Characters:
    - Character.h 🛠️
    - SecondarySkill.h ✅

Exceptions:
    ⚪(pure inheritance from std::exception, nothing to test)

Game:
    - Game.h ❌(not yet)
    - KeyHandler.h 🛠️

Graphic:
    Renderers:
        - IRenderer.hpp ❌(not yet)
        - MapRenderer.h ❌(not yet)
    - Printable.h ❌(not yet)
    - SpriteVisitor.h ❌(not yet)

LoadAndSaveTools:
    - CharacterJsonLoader.h ❌(not yet)
    - CharacterLoader.h ❌(not yet)
    - CharacterSaver.h ❌(not yet)
    - IJsonLoader.hpp ⚪(is an interface)
    - ILoader.hpp ⚪(is an interface)
    - ISaver.h ⚪(is an interface)
    - MapLoader.h ❌(not yet)
    - MapSaver.h ❌(not yet)

Magic:
    - Spell.h ❌(not yet)
    - SpellBook.h ❌(not yet)

Miscellaneous:
    - ArtifactLib.h ⚪(is an library)
    - CharacterLib.h ⚪(is an library)
    - Coords.h ✅
    - ProjectLib.h ⚪(is an interface)
    - UnitLib.h ⚪(is an library)

Player:
    Personalities:
        - Personality.h ❌(not yet)
    - AIPlayer.h ❌(not yet)
    - HumanPlayer.h ❌(not yet)
    - Player.h ❌(not yet)

Resource:
    - Resource.h ❌(not yet)

Units:
    - Faction.hpp ❌(not yet)
    - RangedUnit.h ❌(not yet)
    - Unit.h 🛠️
    - UnitStack.h ❌(not yet)
    - WarMachine.hpp ❌(not yet)

WorldMap:
    Castles:
        - Castle.h ❌(not yet)
        - CastleInterface.h ❌(not yet)
    - Building.h ❌(not yet)
    - GridTile.h ✅
    - MapObject.h ⚪(is an interface)
    - OverworldObstacle.h ❌(not yet)
    - WorldMap.h ✅
