# AsciiEngine
An open source game engine for building terminal-based games on Linux using ncurses.

## Prerequisites
- c++20
- ncurses

## API
Including `API.hpp` is all you need for usage, e.g.:
```c++
#include <AsciiEngine/API.hpp>
```

For convenience, you may use:
```c++
using namespace AsciiEngine;
using namespace AsciiEngine::Math;
using namespace AsciiEngine::Physics;
```

> [!NOTE]
> The rest of this documentation assumes these namespaces are used.

### Engine
To access the engine:
```c++
Engine &engine = Engine::instance();
engine.registerQuitKey('q'); // press 'q' to quit
```

Start the engine:
```c++
engine.run();
```

#### Objects
Objects are the core elements of the game engine.

Create an object:
```c++
AsciiObject *object = engine.createAsciiObject();
```

Destroy an object:
```c++
object->destroy();
```

> [!NOTE]
> - Destroyed objects are ignored by the engine for the rest of runtime
> - Any components attached to the destroyed object are also ignored

##### Reusing Objects
If you frequently create and remove objects, consider enabling/disabling instead:
```c++
object->setEnabled(false);
// reuse later
object->setEnabled(true);
```

> [!NOTE]
> The object retains its components and state.\
> If you need a completely fresh object, create a new one or implement a reset
>  function

#### Components
Components add behaviour to objects.

Add a component:
```c++
object->addComponent<T>(args...);
```

#### Rendering
To display ASCII characters, attach an `AsciiRenderer` to an object.

Example:
```c++
AsciiRenderer *rend = object->addComponent<AsciiRenderer>(0, 0, "#");
```

Hide the object without destroying it:
```c++
rend->setVisible(false);
```

