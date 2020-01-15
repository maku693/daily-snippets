Set-StrictMode -Version Latest

if (Test-Path "${Env:ProgramFiles(x86)}\Microsoft Visual Studio\Installer\vswhere.exe") {
    Write-Output "vswhere found."
} else {
    Write-Output "vswhere not found."
}
