param (
    [String[]]$build_list
)

$DIR=$PSScriptRoot
$TOOLS="$DIR\tools"

python -c "import yaml; import xlsxwriter; import Crypto; import win32api" 2>$null
if (!$?) {
    Write-Error "`nPlease install required python packages`n  > pip install pyyaml xlsxwriter pycrypto pypiwin32"
}

"Running patcher"
python $TOOLS\cb_patcher.py $build_list

"Generating CMakelists"
python ${TOOLS}/makefiles.py

"Creating build directory"
mkdir ${DIR}/build -Force
cd ${DIR}/build

"Creating Makefiles"
$CMAKE_OPTS="-DCMAKE_EXPORT_COMPILE_COMMANDS=ON"

cmake $CMAKE_OPTS ..
cmake --build . -- /m
