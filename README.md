# Teulu

> Bum-barrels twit on bush and tree  
> Scarse bigger then a bumble bee  
> And in a white thorn’s leafy rest  
> It builds its curious pudding-nest  
> Wi hole beside as if a mouse  
> Had built the little barrel house.  
> – John Clare

_Teulu_ is a game about bumbarrels – or _long-tailed tits_ – gathering food
and building a family flock through the four seasons.

Please note that most features listed below are not implemented, but are to
be regarded as statements of intent.


## How to run

The game has only been built and tested under GNU/Linux. To start the game on
GNU/Linux, go to the game directory and write `$ ./teulu`.

Note that the game natively runs windowed in 640x480 resolution. To up scale
the window, use the `-s n` flag, where `n` is an integer upscaling factor,
_e.g._ `$ ./teulu -s 2` to scale the window to 1280x960 pixels.

There is also a `-f` flag to force full screen mode, however, since this may
mess up your display settings it is not recommended. Use at your own peril!

You may need to install some requirements in order to get it to start. See
_Requirements_ below for more information.


## Objective

The objective varies a little during the seasons, but the main objective is
always to eat and stay alive. Different food gives different amounts of
energy and points, and some food may have other effects as well.

### Autumn
Gather food, avoid predators, and make new friends!

### Winter
Gather food, avoid predators, make new friends, and keep them safe and warm!

### Spring
Gather food, avoid predators, make a nest, and bring food to your family!

### Summer
Gather food, avoid predators, bring your family to food, and enjoy the sun!
Don't forget to hydrate!


## Controls

Use _Select_ (left mouse key) to fly towards a the pointer. Holding the
button will lead to continuous flight, double-clicking will result in a
single hop, or a dash if airborne. Flying takes energy, so be smart about it!

Use _Adjust_ (right mouse key) to interact with the environment: eat bugs and
other food and pick up materials. Use _Shift+Adjust_ to catch a bug or pick
up a piece of food without eating it, press again to let go.

Use the call key (default: _C_) to call others in your flock towards you, for
instance if you've found a good food source.

Use the warn key (default: _X_) to warn others in your flock of danger, for
instance if you've spotted a predator. Warning will make you more visible to
predators, which you can use to lure them away.

Others in your flock may call or warn as well, so listen carefully!

Use the sleep key (default: _Z_) to go to roost for the night. The others in
your flock will join you, and once you've all settled the day will end.
Remember that sitting in the middle is warmer than on the edges!

To quit, close the window or press either _Esc_ or _Q_.


## Requirements

The game has so far only been tested on Debian GNU/Linux. It is based on
`SDL-1.2` and may require you to install som dependencies. On a Debian-like
system, this should do the trick:

```console
$ sudo apt-get install libsdl1.2debian libsdl-image1.2 libsdl-gfx1.2-5
```

Additional dependencies for `SDL1.2` are these, though they should not be
needed at the moment:

```console
$ sudo apt-get install libsdl-mixer1.2 libsdl-sound1.2 libsdl-ttf2.0-0 libsdl-net1.2
```

### Build requirements

If you want to build Teulu from source you need the development headers as
well. These can be installed using this command on a Debian-like system:

```console
$ sudo apt-get install libsdl1.2-dev libsdl-image1.2-dev libsdl-gfx1.2-dev
```

Again, there are a few other `SDL1.2` development packages. These should not be
necessary to build Teulu at the moment, but may be required in the future:

```console
$ sudo apt-get install libsdl-mixer1.2-dev libsdl-sound1.2-dev libsdl-ttf2.0-dev libsdl-net1.2-dev
```


## License and disclaimer

Teulu - A game about bumbarrels gathering food and building a family flock

Copyright (C) 2021  Ida-Sofia Skyman (Bumbarrel Computing)

This program is free software: you can redistribute it and/or modify it under
the terms of the GNU General Public License as published by the Free Software
Foundation, either version 3 of the License, or (at your option) any later
version.

This program is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
details.

You should have received a copy of the GNU General Public License along with
this program. If not, see <https://www.gnu.org/licenses/>.


---
