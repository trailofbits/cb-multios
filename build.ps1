param (
    [String[]]$build_list
)

$DIR=$PSScriptRoot
$TOOLS="$DIR\tools"

python -c "import xlsxwriter; import Crypto; import win32api" 2>$null
if (!$?) {
    Write-Error "`nPlease install required python packages`n  > pip install xlsxwriter pycrypto pypiwin32"
}

"Creating build directory"
mkdir ${DIR}\build
cd ${DIR}\build

"Creating Makefiles"
$CMAKE_OPTS="-DCMAKE_EXPORT_COMPILE_COMMANDS=ON"

cmake $CMAKE_OPTS ..
cmake --build . -- /m
