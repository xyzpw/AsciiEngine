# Objects
## Creating
Creating an object:
```cpp
auto *player = engine.createAsciiObject("player");
```

### Adding Components
Add component:
```cpp
auto *renderer = player->addComponent<AsciiRenderer>(0, 0, "#");
auto *controller = player->addComponent<Controller>();
controller->addKey(' ', [&]() { engine.debug.success("pressed space"); });
```

## Usage
**Fields**:
| Type | Name | Description |
| -----|------| ------------|
| int | id   | ID of object|
| int | layer | Layer of object |
| string | name | Name of object |

**Methods**:
| Return | Usage | Description |
| ------ | ----- | ----------- |
| Component* | addComponent\<T\>(...Args) |
| Component* | getComponent\<T\> |
| Component* | getAllComponents\<T\> |
| Component* | getOrAddComponent\<T\>(...Args) | Return attached component if it exists, otherwise add |
| Controller* | addController(MovementControlType) | Add a controller to move the renderer sprite |
| bool | hasComponent\<T\> |
| bool | hasAnyComponent\<...T> |
| bool | hasEnabledComponent\<...T> |
| bool | hasAnyEnabledComponent\<...T> |
| bool | hasAllEnabledComponents\<...T> |
| bool | hasAllComponents\<...T> |
| bool | isActiveAndEnabled | True if not destroyed and enabled |
| bool | isDestroyed | True if destroyed |
| vector\<T\> | getAllComponents\<T\>() | Return all components of type |
| void | destroy | Destroy the object (it will no longer be used or accessed) |
| void | setEnabled(bool) | Enable or disable |
| void | setLayer(int) | Set layer |
