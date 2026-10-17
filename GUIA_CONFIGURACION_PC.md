# Guía de Replicación del Entorno Unreal Engine en una Nueva PC

Esta guía describe paso a paso cómo replicar exactamente esta misma configuración (compilación ultrarrápida con `Ctrl + Shift + B`, limpieza de caché, apertura de Unreal y detección de errores) en cualquier otra computadora con **Windows**, para **Antigravity IDE** o **Visual Studio Code**.

---

## 📌 ¿Cómo Funciona este Entorno?

El entorno se divide en dos partes:

1. **Herramientas Globales del Sistema (Se instalan 1 sola vez por PC):**
   Cuatro comandos disponibles en cualquier terminal de Windows:
   - `ue-compile`: Detecta el archivo `.uproject` y compila con el compilador oficial de Unreal Engine (`Build.bat`) en ~2 a 5 segundos.
   - `ue-clean`: Ejecuta `Clean.bat`, elimina archivos intermedios `.obj` y DLLs antiguas para resolver errores de compilación o hot-reload trabado.
   - `ue-open`: Abre el editor de Unreal Engine con tu proyecto cargado en segundo plano.
   - `ue-setup`: Configura automáticamente cualquier proyecto Unreal para Antigravity / VS Code.

2. **Configuración del Proyecto (Se ejecuta con `ue-setup`):**
   Al entrar a cualquier proyecto Unreal y ejecutar `ue-setup`, se generan automáticamente los archivos en `.vscode/`:
   - `tasks.json`: Mapea `Ctrl + Shift + B` a `ue-compile` y registra las tareas de limpieza y editor.
   - `settings.json`: Activa el subrayado de sintaxis y la integración con Error Lens.
   - `c_cpp_properties.json`: Enlaza los include paths de Unreal Engine y del proyecto.

---

## 🛠 Requisitos Previos en la Nueva PC

Antes de configurar los comandos, asegúrate de tener instalado en la nueva máquina:

1. **Unreal Engine 4.27** (o Unreal Engine 5.x) instalado vía Epic Games Launcher (ruta típica: `C:\Program Files\Epic Games\UE_4.27`).
2. **Visual Studio 2022 (Community)** con los siguientes paquetes:
   - Carga de trabajo: *Desarrollo para el escritorio con C++*.
   - Componentes individuales recomendados: *MSVC v143*, *SDK de Windows 10 u 11*, *IDE support for Unreal Engine*.
3. **Antigravity IDE** (o Visual Studio Code) con las siguientes extensiones instaladas:
   - **C/C++** (`ms-vscode.cpptools`) de Microsoft.
   - **Error Lens** (`usernamehw.errorlens`) para ver errores de sintaxis en tiempo real en la misma línea.

---

## 🚀 Paso 1: Instalación Global en la Nueva PC (1 Solo Comando)

En la nueva PC, abre **PowerShell** (no requiere privilegios de administrador) y pega el siguiente bloque completo. Este comando creará los 4 scripts directamente en `%LOCALAPPDATA%\Microsoft\WindowsApps` (carpeta que ya forma parte del `PATH` de Windows por defecto):

```powershell
$toolsDir = "$env:LOCALAPPDATA\Microsoft\WindowsApps"

# 1. ue-compile.bat
@'
@echo off
setlocal enabledelayedexpansion

set "UPROJECT_FILE="
set "PROJECT_NAME="

for %%F in (*.uproject) do (
    set "UPROJECT_FILE=%%~fF"
    set "PROJECT_NAME=%%~nF"
)
if not defined UPROJECT_FILE (
    for %%F in (..\*.uproject) do (
        set "UPROJECT_FILE=%%~fF"
        set "PROJECT_NAME=%%~nF"
    )
)
if not defined UPROJECT_FILE (
    echo [ERROR] No se encontro ningun archivo .uproject en el directorio actual ni superior.
    exit /b 1
)

echo ====================================================
echo  Proyecto Unreal detectado: !PROJECT_NAME!
echo  Ubicacion: !UPROJECT_FILE!
echo ====================================================

set "BUILD_BAT="
if exist "C:\Program Files\Epic Games\UE_4.27\Engine\Build\BatchFiles\Build.bat" (
    set "BUILD_BAT=C:\Program Files\Epic Games\UE_4.27\Engine\Build\BatchFiles\Build.bat"
) else (
    for /d %%D in ("C:\Program Files\Epic Games\UE_*") do (
        if exist "%%D\Engine\Build\BatchFiles\Build.bat" (
            set "BUILD_BAT=%%D\Engine\Build\BatchFiles\Build.bat"
        )
    )
)
if not defined BUILD_BAT (
    echo [ERROR] No se encontro Build.bat en C:\Program Files\Epic Games.
    exit /b 1
)

echo Compilando !PROJECT_NAME!Editor (Win64 Development)...
call "!BUILD_BAT!" !PROJECT_NAME!Editor Win64 Development "!UPROJECT_FILE!" -WaitMutex

if %ERRORLEVEL% equ 0 (
    echo.
    echo ====================================================
    echo  [OK] Compilacion completada con EXITO!
    echo ====================================================
    exit /b 0
) else (
    echo.
    echo ====================================================
    echo  [ERROR] Fallo en la compilacion (Codigo %ERRORLEVEL%)
    echo ====================================================
    exit /b %ERRORLEVEL%
)
'@ | Set-Content -Path "$toolsDir\ue-compile.bat" -Encoding ASCII

# 2. ue-clean.bat
@'
@echo off
setlocal enabledelayedexpansion

set "UPROJECT_FILE="
set "PROJECT_DIR="
set "PROJECT_NAME="

for %%F in (*.uproject) do (
    set "UPROJECT_FILE=%%~fF"
    set "PROJECT_DIR=%%~dpF"
    set "PROJECT_NAME=%%~nF"
)
if not defined UPROJECT_FILE (
    for %%F in (..\*.uproject) do (
        set "UPROJECT_FILE=%%~fF"
        set "PROJECT_DIR=%%~dpF"
        set "PROJECT_NAME=%%~nF"
    )
)
if not defined UPROJECT_FILE (
    echo [ERROR] No se encontro ningun archivo .uproject en el directorio actual ni superior.
    exit /b 1
)

echo ====================================================
echo  Limpiando proyecto: !PROJECT_NAME!
echo  Ubicacion: !PROJECT_DIR!
echo ====================================================

set "CLEAN_BAT="
if exist "C:\Program Files\Epic Games\UE_4.27\Engine\Build\BatchFiles\Clean.bat" (
    set "CLEAN_BAT=C:\Program Files\Epic Games\UE_4.27\Engine\Build\BatchFiles\Clean.bat"
) else (
    for /d %%D in ("C:\Program Files\Epic Games\UE_*") do (
        if exist "%%D\Engine\Build\BatchFiles\Clean.bat" (
            set "CLEAN_BAT=%%D\Engine\Build\BatchFiles\Clean.bat"
        )
    )
)

if defined CLEAN_BAT (
    echo Ejecutando Clean.bat de Unreal Engine...
    call "!CLEAN_BAT!" !PROJECT_NAME!Editor Win64 Development "!UPROJECT_FILE!" -WaitMutex
)

if exist "!PROJECT_DIR!Intermediate\Build\Win64" (
    echo Eliminando objetos intermedios (.obj)...
    rd /s /q "!PROJECT_DIR!Intermediate\Build\Win64" 2>nul
)

if exist "!PROJECT_DIR!Binaries\Win64" (
    echo Limpiando DLLs compiladas...
    del /f /q "!PROJECT_DIR!Binaries\Win64\UE4Editor-!PROJECT_NAME!*.*" 2>nul
    del /f /q "!PROJECT_DIR!Binaries\Win64\UnrealEditor-!PROJECT_NAME!*.*" 2>nul
)

echo.
echo ====================================================
echo  [OK] Proyecto limpiado exitosamente!
echo ====================================================
'@ | Set-Content -Path "$toolsDir\ue-clean.bat" -Encoding ASCII

# 3. ue-open.bat
@'
@echo off
setlocal enabledelayedexpansion

set "UPROJECT_FILE="
set "PROJECT_NAME="

for %%F in (*.uproject) do (
    set "UPROJECT_FILE=%%~fF"
    set "PROJECT_NAME=%%~nF"
)
if not defined UPROJECT_FILE (
    for %%F in (..\*.uproject) do (
        set "UPROJECT_FILE=%%~fF"
        set "PROJECT_NAME=%%~nF"
    )
)
if not defined UPROJECT_FILE (
    echo [ERROR] No se encontro ningun archivo .uproject en el directorio actual ni superior.
    exit /b 1
)

set "EDITOR_EXE="
if exist "C:\Program Files\Epic Games\UE_4.27\Engine\Binaries\Win64\UE4Editor.exe" (
    set "EDITOR_EXE=C:\Program Files\Epic Games\UE_4.27\Engine\Binaries\Win64\UE4Editor.exe"
) else (
    for /d %%D in ("C:\Program Files\Epic Games\UE_*") do (
        if exist "%%D\Engine\Binaries\Win64\UE4Editor.exe" (
            set "EDITOR_EXE=%%D\Engine\Binaries\Win64\UE4Editor.exe"
        )
        if exist "%%D\Engine\Binaries\Win64\UnrealEditor.exe" (
            set "EDITOR_EXE=%%D\Engine\Binaries\Win64\UnrealEditor.exe"
        )
    )
)
if not defined EDITOR_EXE (
    echo [ERROR] No se encontro el ejecutable del Editor en C:\Program Files\Epic Games.
    exit /b 1
)

echo Abriendo !PROJECT_NAME! en Unreal Editor...
start "" "!EDITOR_EXE!" "!UPROJECT_FILE!"
'@ | Set-Content -Path "$toolsDir\ue-open.bat" -Encoding ASCII

# 4. ue-setup.bat
@'
@echo off
setlocal enabledelayedexpansion

set "UPROJECT_FILE="
set "PROJECT_NAME="

for %%F in (*.uproject) do (
    set "UPROJECT_FILE=%%~fF"
    set "PROJECT_NAME=%%~nF"
)
if not defined UPROJECT_FILE (
    for %%F in (..\*.uproject) do (
        set "UPROJECT_FILE=%%~fF"
        set "PROJECT_NAME=%%~nF"
    )
)
if not defined UPROJECT_FILE (
    echo [ERROR] No se encontro ningun archivo .uproject en el directorio actual ni superior.
    exit /b 1
)

echo ====================================================
echo  Configurando entorno para: !PROJECT_NAME!
echo ====================================================

if not exist ".vscode" mkdir ".vscode"

:: 1. tasks.json
(
echo {
echo     "version": "2.0.0",
echo     "tasks": [
echo         {
echo             "label": "Compilar Proyecto (Development Editor)",
echo             "type": "shell",
echo             "command": "ue-compile",
echo             "group": {
echo                 "kind": "build",
echo                 "isDefault": true
echo             },
echo             "problemMatcher": "$msCompile",
echo             "presentation": {
echo                 "echo": true,
echo                 "reveal": "always",
echo                 "focus": false,
echo                 "panel": "shared"
echo             }
echo         },
echo         {
echo             "label": "Abrir Unreal Editor",
echo             "type": "shell",
echo             "command": "ue-open",
echo             "problemMatcher": [],
echo             "presentation": {
echo                 "echo": true,
echo                 "reveal": "silent",
echo                 "focus": false,
echo                 "panel": "shared"
echo             }
echo         },
echo         {
echo             "label": "Limpiar Cache (Clean)",
echo             "type": "shell",
echo             "command": "ue-clean",
echo             "problemMatcher": [],
echo             "presentation": {
echo                 "echo": true,
echo                 "reveal": "always",
echo                 "focus": false,
echo                 "panel": "shared"
echo             }
echo         }
echo     ]
echo }
) > ".vscode\tasks.json"
echo [OK] .vscode\tasks.json configurado.

:: 2. settings.json
(
echo {
echo     "C_Cpp.errorSquiggles": "enabled",
echo     "C_Cpp.intelliSenseEngine": "default",
echo     "C_Cpp.intelliSenseEngineFallback": "disabled",
echo     "C_Cpp.intelliSenseUpdateDelay": 300,
echo     "errorLens.enabled": true,
echo     "errorLens.delay": 200,
echo     "files.associations": {
echo         "*.h": "cpp",
echo         "*.cpp": "cpp"
echo     }
echo }
) > ".vscode\settings.json"
echo [OK] .vscode\settings.json configurado.

:: 3. c_cpp_properties.json (si no existe)
if not exist ".vscode\c_cpp_properties.json" (
(
echo {
echo     "configurations": [
echo         {
echo             "name": "Win32",
echo             "intelliSenseMode": "msvc-x64",
echo             "cStandard": "c17",
echo             "cppStandard": "c++17",
echo             "includePath": [
echo                 "${workspaceFolder}/Source/**",
echo                 "${workspaceFolder}/Intermediate/Build/Win64/UE4Editor/Inc/**",
echo                 "C:/Program Files/Epic Games/UE_4.27/Engine/Source/**",
echo                 "C:/Program Files/Epic Games/UE_4.27/Engine/Intermediate/Build/Win64/UE4Editor/Inc/**"
echo             ],
echo             "defines": [
echo                 "UNICODE",
echo                 "_UNICODE",
echo                 "__UNREAL__",
echo                 "UBT_COMPILED_PLATFORM=Win64",
echo                 "WITH_ENGINE=1",
echo                 "WITH_COREUOBJECT=1"
echo             ],
echo             "browse": {
echo                 "path": [
echo                     "${workspaceFolder}/Source",
echo                     "C:/Program Files/Epic Games/UE_4.27/Engine/Source"
echo                 ],
echo                 "limitSymbolsToIncludedHeaders": false
echo             }
echo         }
echo     ],
echo     "version": 4
echo }
) > ".vscode\c_cpp_properties.json"
echo [OK] .vscode\c_cpp_properties.json creado.
) else (
echo [INFO] .vscode\c_cpp_properties.json ya existe, conservado.
)

echo.
echo ====================================================
echo  [OK] Todo listo! Presiona Ctrl + Shift + B para compilar.
echo ====================================================
'@ | Set-Content -Path "$toolsDir\ue-setup.bat" -Encoding ASCII

# 5. Wrappers para Git Bash / MSYS2 / bash (compatibilidad multiplataforma)
@('#!/usr/bin/env sh', 'ue-compile.bat "$@"') -join "`n" | Set-Content -Path "$toolsDir\ue-compile" -NoNewline
@('#!/usr/bin/env sh', 'ue-clean.bat "$@"') -join "`n" | Set-Content -Path "$toolsDir\ue-clean" -NoNewline
@('#!/usr/bin/env sh', 'ue-open.bat "$@"') -join "`n" | Set-Content -Path "$toolsDir\ue-open" -NoNewline
@('#!/usr/bin/env sh', 'ue-setup.bat "$@"') -join "`n" | Set-Content -Path "$toolsDir\ue-setup" -NoNewline

Write-Host "Comandos de Unreal Engine instalados globalmente con exito en $toolsDir!" -ForegroundColor Green
```

---

## ⚡ Paso 2: Configurar tu Proyecto Unreal con `ue-setup`

Una vez ejecutado el Paso 1 en la nueva máquina:

1. Abre la carpeta de tu proyecto Unreal (donde está el archivo `.uproject`) en **Antigravity IDE** o **VS Code**.
2. Abre la terminal integrada con:
   <kbd>Ctrl</kbd> + <kbd>`</kbd> (o menú `Terminal` -> `New Terminal`).
3. Escribe y presiona Enter:
   ```cmd
   ue-setup
   ```
4. ¡Listo! Verás en la consola que se generaron:
   - `.vscode/tasks.json`
   - `.vscode/settings.json`
   - `.vscode/c_cpp_properties.json`

---

## 🎮 Paso 3: Flujo de Trabajo y Atajos

| Acción | Atajo / Comando | Descripción |
| :--- | :--- | :--- |
| **Compilar** | <kbd>Ctrl</kbd> + <kbd>Shift</kbd> + <kbd>B</kbd> | Compila el código C++ en ~2-5 seg y muestra errores con números de línea directos. |
| **Limpiar Caché** | Terminal: `ue-clean`<br>o `Ctrl + Shift + P` -> `Tasks: Run Task` -> `Limpiar Cache` | Úsalo si agregas nuevas clases, interfaces `UINTERFACE` o si el linker da `LNK2001`. |
| **Abrir Unreal Editor** | Terminal: `ue-open`<br>o `Ctrl + Shift + P` -> `Tasks: Run Task` -> `Abrir Unreal Editor` | Lanza el editor de Unreal con tu proyecto en segundo plano. |
| **Configurar nuevo proyecto**| Terminal: `ue-setup` | Configura cualquier otro proyecto nuevo en segundos. |

---

## ❓ Preguntas Frecuentes

### ¿El comando `ue-setup` ya configura todo por sí solo?
- **Dentro del proyecto**: **SÍ**. Una vez que los scripts están instalados en la PC, solo necesitas ejecutar `ue-setup` en cualquier proyecto para que configure automáticamente todas las tareas de compilación, el atajo `Ctrl + Shift + B` y la detección de errores.
- **En una PC virgen**: Primero debes correr el script de PowerShell del **Paso 1** una única vez para que Windows reconozca los comandos `ue-compile`, `ue-clean`, `ue-open` y `ue-setup`.

### ¿Qué pasa si Unreal Engine está instalado en otro disco (ej. `D:\Epic Games\UE_4.27`)?
Los scripts detectan automáticamente cualquier instalación en `C:\Program Files\Epic Games\UE_*`. Si lo instalaste en otra unidad, simplemente edita la ruta en `%LOCALAPPDATA%\Microsoft\WindowsApps\ue-compile.bat` (y en `ue-clean.bat` y `ue-open.bat`) indicando la carpeta de tu motor.
