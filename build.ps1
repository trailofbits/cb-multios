[CmdletBinding()]
Param(
  [Parameter(Position=0,Mandatory=$false)]
  [ValidateSet("clang", "msvc")]
  [string]$Compiler="clang",
  [Parameter(Position=1,Mandatory=$false,ValueFromRemainingArguments=$true)]
  [string[]]$ExtraCmakeArgs
)

Write-Host "Preparing to run build script..."
Write-Host ""
Write-Host "Config:"
Write-Host "`tCompiler...........$Compiler"
Write-Host "`tExtra CMake Args:..$ExtraCmakeArgs"
Write-Host ""

if(!$PSScriptRoot){
    $PSScriptRoot = Split-Path $MyInvocation.MyCommand.Path -Parent
}

$DIR = $PSScriptRoot
$TOOLS = Join-Path $DIR "tools"
$BUILD_DIR = Join-Path $DIR "build"

Write-Host "Checking if required python modules are installed..."
& python -c "import xlsxwriter; import Crypto; import win32api" 2>$null
if ($LASTEXITCODE -ne 0) {
    Write-Error "`nPlease install required python packages`n  > pip install xlsxwriter pycryptodome pypiwin32"
    exit 1
}
Write-Host "All python modules installed.`n"

Write-Host "Creating Build Directory..."
New-Item -Path $BUILD_DIR -Type directory | out-null
Push-Location
Set-Location $BUILD_DIR
Write-Host "`tNow in $BUILD_DIR`n"

Write-Host "Creating Build Files..."
if ($Compiler -eq "clang") {
    & cmake -GNinja -DCLANGCL:BOOL=TRUE -DCMAKE_C_COMPILER=clang-cl -DCMAKE_CXX_COMPILER=clang-cl ..
} elseIf ($Compiler -eq "msvc") {
    & cmake ..
} else {
    Write-Error "`tUnrecognized compiler: $Compiler`n"
    exit 1
}

if ($LASTEXITCODE -eq 0)
{
  Write-Host ""
  Write-Host "Building..."
  & cmake --build .
}

Pop-Location
exit $LASTEXITCODE
