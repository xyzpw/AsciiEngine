# First Game
Creating a simple game where you can move a character around the screen.

## Include the Engine
```c++
#include <AsciiEngine/API.hpp>

using namespace AsciiEngine;
using namespace Math;
using namespace Physics;
```

This gives access to the engine.

## Create the Engine
```c++
Engine &engine = Engine::instance();
```

This gets the global instance.

## Add a Quit Key
```c++
engine.registerQuitKey('q');
```

> [!WARNING]
> Always register a quit key.
> Without a quit key, the game can keep running without exit.

## Create a Player Object
```c++
auto *object = engine.createAsciiObject({0, 0}, Sprite({"#"}));
```

- `{0, 0}` are the coordinates
- `Sprite({"#"})` is the sprite

## Add Movement Controls
```c++
object->addController(MovementControlType::WASD);
```

This allows movement with the `w, a, s, d` keys.

## Run the Game
```c++
engine.run();
```

## Full Example
```c++
#include <AsciiEngine/API.hpp>

using namespace AsciiEngine;
using namespace Math;
using namespace Physics;

int main()
{
    Engine &engine = Engine::instance();

    auto *object = engine.createAsciiObject({0, 0}, Sprite({"#"}));
    object->addController(MovementControlType::WASD);

    engine.run();
    return 0;
}
```

Expected result is a character `#` on the screen, it will move when pressing\
`w, a, s, d` keys, pressing `q` will quit.

## Debugging
> [!TIP]
> Use `engine.debug.log` to print debug messages.
