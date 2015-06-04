# SAMP-Race

SA-MP (San Andreas Multiplayer) is a game mode for the PC version of Rockstar Games Grand Theft Auto: San Andreas (tm).

SAMP-Race is a suite of server scripts that aim to provide players a seamless racing experience on SA-MP servers.

## Local development

Clone the repository and copy the SA-MP server files into the root directory. The server.cfg should contain

```
gamemode0 Race 1
filterscripts gl_actions gl_realtime gl_property gl_mapicon ls_elevator attachments skinchanger vspawner test_cmds ls_mall ls_beachside
plugins mysql bcrypt-samp
```

Make sure to change the default RCON password or the server won't start.

To rebuild the mod simply run pawno/compile.bat.

## License

The MIT License (MIT)

Copyright (c) 2015 Marcel Herd

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.