[CmdletBinding()]

if(!$PSScriptRoot){
    $PSScriptRoot = Split-Path $MyInvocation.MyCommand.Path -Parent
}

$DIR = $PSScriptRoot
$TOOLS = Join-Path $DIR "tools"
$BUILD_DIR = Join-Path $DIR "build"

Write-Verbose -Message "Checking if required python modules are installed..."
& python -c "import xlsxwriter; import Crypto; import win32api" 2>$null
if ($LASTEXITCODE -ne 0) {
    Write-Error "`nPlease install required python packages`n  > pip install xlsxwriter pycryptodome pypiwin32"
}

Write-Host "Creating Build Directory..."
New-Item -Path $BUILD_DIR -Type directory | out-null
Push-Location
Set-Location $BUILD_DIR

Write-Host "Creating Build Files..."
& cmake -GNinja -DCMAKE_C_COMPILER=clang-cl -DCMAKE_CXX_COMPILER=clang-cl ..

if ($LASTEXITCODE -eq 0)
{
  Write-Host "Building..."
  & ninja
}

Pop-Location
exit $LASTEXITCODE
