@ECHO OFF
ECHO This script compile shaders
ECHO -----------------CALL--------------------
ECHO GameEngine\library\bgfx\.build\win64_vs2017\bin\shadercDebug.exe -f GameEngine\src\GameEngine\Shaders\v_simple.sc -o GameEngine\src\GameEngine\Shaders\v_simple.bin --platform windows --type vertex --verbose -i GameEngine\library\bgfx\src --varyingdef GameEngine\src\GameEngine\Shaders\varying.def.sc
ECHO -----------------------------------------
CALL GameEngine\library\bgfx\.build\win64_vs2017\bin\shadercDebug.exe -f GameEngine\src\GameEngine\Shaders\v_simple.sc -o GameEngine\src\GameEngine\Shaders\v_simple.bin --platform windows --type vertex --verbose -i GameEngine\library\bgfx\src --varyingdef GameEngine\src\GameEngine\Shaders\varying.def.sc
ECHO -----------------END---------------------
ECHO -----------------CALL--------------------
ECHO GameEngine\library\bgfx\.build\win64_vs2017\bin\shadercDebug.exe -f GameEngine\src\GameEngine\Shaders\f_simple.sc -o GameEngine\src\GameEngine\Shaders\f_simple.bin --platform windows --type fragment --verbose -i GameEngine\library\bgfx\src --varyingdef GameEngine\src\GameEngine\Shaders\varying.def.sc
ECHO -----------------------------------------
CALL GameEngine\library\bgfx\.build\win64_vs2017\bin\shadercDebug.exe -f GameEngine\src\GameEngine\Shaders\f_simple.sc -o GameEngine\src\GameEngine\Shaders\f_simple.bin --platform windows --type fragment --verbose -i GameEngine\library\bgfx\src --varyingdef GameEngine\src\GameEngine\Shaders\varying.def.sc
ECHO -----------------END---------------------
PAUSE