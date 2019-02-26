[CmdletBinding()]

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
set CFLAGS=-m32
set CXXFLAGS=-m32
cmake -GNinja -DCMAKE_C_COMPILER=clang-cl -DCMAKE_CXX_COMPILER=clang-cl ..
cmake --build .
