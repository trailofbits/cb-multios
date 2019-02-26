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
$CMAKE_OPTS = '-GNinja','-DCMAKE_CXX_COMPILER=clang-cl'
if ($msvc) {
    $CMAKE_OPTS = ""
}

cmake $CMAKE_OPTS ..
cmake --build .
