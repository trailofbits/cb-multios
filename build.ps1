param (
    [switch] $msvc
)

$DIR = $PSScriptRoot
$TOOLS = "$DIR\tools"

python -c "import xlsxwriter; import Crypto; import win32api" 2>$null
if (!$?) {
    Write-Error "`nPlease install required python packages`n  > pip install xlsxwriter pycrypto pypiwin32"
}

"Creating build directory"
mkdir "${DIR}\build"
cd "${DIR}\build"

"Creating Makefiles"
$CMAKE_OPTS = "-D CLANGCL:BOOL=TRUE -T LLVM-vs2014"
if ($msvc) {
    $CMAKE_OPTS = ""
}

Start-Process cmake -NoNewWindow -Wait -ArgumentList "$CMAKE_OPTS .."
cmake --build . -- /m
