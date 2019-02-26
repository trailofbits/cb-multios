[CmdletBinding()]
param (
    [switch] $msvc
)

# $ErrorActionPreference = 'Stop'

$DIR = $PSScriptRoot
$TOOLS = "$DIR\tools"

python -c "import xlsxwriter; import Crypto; import win32api" 2>$null
if (!$?) {
    Write-Error "`nPlease install required python packages`n  > pip install xlsxwriter pycryptodome pypiwin32"
}

"Creating build directory"
mkdir "${DIR}\build"
cd "${DIR}\build"

"Creating Makefiles"
$CMAKE_ARCH = '-AWin32'
$CMAKE_OPTS = '-G "Visual Studio 15 2017"','-DCMAKE_C_COMPILER=clang-cl','-DCMAKE_CXX_COMPILER=clang-cl'
if ($msvc) {
    $CMAKE_OPTS = ""
}

cmake $CMAKE_ARCH $CMAKE_OPTS ..
cmake --build .
