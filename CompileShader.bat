@ECHO OFF
ECHO This script compile shaders

CALL GameEngine\library\bgfx\.build\win64_vs2017\bin\shadercDebug.exe -f Game\src\Shaders\SC\v_simple.sc -o Game\src\Shaders\BIN\v_simple.bin --platform windows --type vertex --verbose -i GameEngine\library\bgfx\src --varyingdef Game\src\Shaders\SC\varying.def.sc

CALL GameEngine\library\bgfx\.build\win64_vs2017\bin\shadercDebug.exe -f Game\src\Shaders\SC\f_simple.sc -o Game\src\Shaders\BIN\f_simple.bin --platform windows --type fragment --verbose -i GameEngine\library\bgfx\src --varyingdef Game\src\Shaders\SC\varying.def.sc

ECHO done.
PAUSE