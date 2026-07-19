# Components
- [AsciiBody](##AsciiBody)
- [AsciiCollider](##AsciiCollider)
- [AsciiRenderer](##AsciiRenderer)
- [AsciiAnimation](##AsciiAnimation)
- [AudioSource](##AudioSource)
- [Behaviour](##Behaviour)
- [Clickable](##Clickable)
- [ConditionalAction](##ConditionalAction)
- [Controller](##Controller)
- [Hud](##Hud)

Adding components can be done via:
```c++
auto *a = eng.createAsciiObject(); // create object
a->addComponent<T>(...Args);
```

Components with `virtual` returns can be overridden, e.g.:
```c++
struct A : Behaviour {
    void update() override
    {
        // this will be called at the beginning of each frame
    }
};

// to add it
obj->addComponent<A>();
```

## AsciiAnimation
Used to play animations for a renderer.

```c++
ao->addComponent(string name, vector<AnimationFrame> frames);
ao->addComponent(string name, vector<AnimationFrame> frames, float duration);
```

### Fields
| Type | Name | Description |
| ---- | ---- | ----------- |
| string | name | |
| vector<AnimationFrame> | frames | |
| bool | loop | Loops animation if true |

### Methods
| Return | Method | Arguments | Description |
| ------ | ------ | --------- | ----------- |
| Sprite* | getSprite | - | Returns the sprite for the current frame |
| bool | isPlaying | - | Returns whether the animation is currently playing |
| bool | isReversed | - | Returns whether playback is reversed |
| float | computeDuration | - | Returns the total duration of the animation |
| float | getSpeed | - | Returns the playback speed multiplier |
| int | getFrameCount | - | Returns the number of frames |
| void | addFrame | Sprite* sprite, float duration | Adds a frame with the specified duration |
| void | play | void; bool loop | Starts playback. If `loop` is `true`, the animation repeats. |
| void | reset | - | Resets the playback state to the beginning |
| void | restart | - | Resets and restarts playback |
| void | setReversed | bool value | Sets animation playback reverse status |
| void | setSpeed | float f | Sets the playback speed (`1.0` is normal speed) |
| void | stop | - | Stop playback |

## AsciiBody
Used as a physics body.

```c++
ao->addComponent<AsciiBody>(int x, int y, int width = 1, int height = 1);
```

### Fields
| Type | Name | Description |
| ---- | ---- | ----------- |
| Bounds | bounds | Body bounds |
| bool | isStatic | Makes the body static |
| float | gravityModifier | |

### Methods
| Return | Method | Arguments | Description |
| ------ | ------ | --------- | ----------- |
| Vector2& | getPosition | - | Return body position |
| Vector2& | getSize | - | Return size of body |
| void | setGravityModifier | float f | |
| void | setHeight | float h | |
| void | setStatic | bool value | |
| void | setWidth | float w | |

## AsciiCollider
Detects when two ascii sprites have collided/overlapped.

### Methods
| Return | Method | Arguments | Description |
| ------ | ------ | --------- | ----------- |
| bool | hasContacts | - | Returns if there is any contacts |
| vector<AsciiObject*>& | getContacts | - | Objects that are in collision |
| virtual void | onContact | AsciiCollider *other | Called when another collider collides. Can by overridden. |

## AsciiRenderer
Needed to render sprites!

```c++
ao->addComponent<AsciiRenderer>(const Vector2 &point, const string &sprite);
ao->addComponent<AsciiRenderer>(const Vector2 &point, const Sprite sprite);
ao->addComponent<AsciiRenderer>(const string &sprite);
ao->addComponent<AsciiRenderer>(const Sprite &sprite);
```

### Fields
| Type | Name | Description |
| ---- | ---- | ----------- |
| Sprite | sprite | Sprite which is rendered |
| Sprite* | animationSprite | Current sprite at the playing animation frame. Can be null |
| Vector2 | localPosition | Position relative to `position` |
| Vector2 | position | |
| bool | blink | Set to true to make sprite blink |
| bool | bold | Set to true to make sprite appear bold |

### Methods
| Return | Method | Arguments | Description |
| ------ | ------ | --------- | ----------- |
| AsciiRenderer* | getParent | - | |
| Color | getBgColor | - | Sprite background color |
| Color | getFgColor | - | Sprite color |
| Sprite* | getSprite | - | Get current sprite being displayed |
| bool | hasParent | - | |
| bool | isAnimationPlaying | - | True if any animation is playing |
| bool | isVisible | - | Check is sprite is visible |
| string | getAnimationName | - | Name of playing animation |
| void | clearColor | - | Remove color from sprite |
| void | move | Vector2& delta | Move relative to current position |
| void | moveTo | Vector2& | Moves to specified point |
| void | removeParent | - | |
| void | setColor | Color fg, Color bg = None | Set color of sprite |
| void | setParent | AsciiRenderer* | Set parent renderer (allows `localPosition`) |
| void | setVisible | bool | Set if sprite is visible |
| void | stopAllAnimations | - | Stop any playing animations |


## AudioSource
Plays audio.

```c++
ao->addComponent<AudioSource>(const string &file);
ao->addComponent<AudioSource>(const string &name, const string &file);
```

### Fields
| Type | Name | Description |
| ---- | ---- | ----------- |
| string | name | |

### Methods
| Return | Method | Arguments | Description |
| ------ | ------ | --------- | ----------- |
| const string& | getFilename | Name of audio file |
| float | getVolume | - | Normal volume |
| void | setVolume | float | Set volume multiplier (0-1) |

## Behaviour
Adds behaviour to object.

### Methods
| Return | Method | Arguments | Description |
| ------ | ------ | --------- | ----------- |
| virtual void | lateUpdate | - | Called at the end of each frame |
| virtual void | onDestroy | - | Called when the object is destroyed |
| virtual void | onInput | int k | Called when a key is pressed |
| virtual void | start | - | Called at the beginning of the first frame |
| virtual void | update | - | Called at the beginning of each frame |

## Clickable
Makes sprite clickable.

### Methods
| Return | Method | Arguments | Description |
| ------ | ------ | -------- | ----------- |
| virtual void | onHold | const MouseState& | Called while mouse is held |
| virtual void | onMouseDown | const MouseState& | Called when the sprite is clicked |
| virtual void | onMouseUp | const MouseState& | Called on mouse released |

## ConditionalAction
Adds conditional function.

```c++
ao->addComponent<ConditionalAction>(fn, cond);
```

### Methods
| Return | Method | Arguments | Description |
| ------ | ------ | --------- | ----------- |
| void | setAction | function<void()> | Conditional action |
| void | setCondition | function<bool()> | Condition required to call action |

## Controller
Adds controller to move sprite.

```c++
ao->addController(MovementControlType::WASD);
```

### Control Types
- WASD
- ArrowKeys
- Vim

### Fields
| Type | Name | Description |
| ---- | ---- | ----------- |
| unordered_map<int, function<void()>> | keyFunctionMap | Mapped keys |

### Methods
| Return | Method | Arguments | Description |
| ------ | ------ | --------- | ----------- |
| void | addKey | int, function<void()> | Add controller key |

## Hud
Add text/hud to appear on screen.

```c++
ao->addComponent<Hud>(const string &text, const Vector2 &point);
```

### Fields
| Type | Name | Description |
| ---- | ---- | ----------- |
| Vector2 | position | Position to appear |
| bool | blink | True to make text blink |
| bool | bold | True for bold text |
| string | text | Hud text |

### Methods
| Return | Method | Arguments | Description |
| ------ | ------ | --------- | ----------- |
| Color | getBgColor | - | |
| Color | getFgColor | - | |
| void | centerTextColumn | - | Centers text in terminal |
| void | clearColor | - | |
| void | setColor | Color fg, Color bg = None | Set color of text |
