import os, sys
import requests
import subprocess
import zipfile

from Logger import Log

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
PRMAKE_BIN_PATH = f"{SCRIPT_DIR}\\bin"
PREMAKE_EXE_PATH = f"{SCRIPT_DIR}\\bin\\premake5.exe"
PREMAKE_URL = "https://github.com/premake/premake-core/releases/download/v5.0.0-beta2/premake-5.0.0-beta2-windows.zip"

if (not os.path.exists(PREMAKE_EXE_PATH)):
    Log.Warn(f"No premake binary found at: {PRMAKE_BIN_PATH}")
    user_input = input("Do you want to download premake? (y/n): ")

    if(user_input[0].lower() == 'y'):
        Log.Info("Downloading...")

        os.makedirs(PRMAKE_BIN_PATH, exist_ok=True)

        response = requests.get(PREMAKE_URL)

        if (response.status_code == 200):
            PREMAKE_ZIP = f"{PRMAKE_BIN_PATH}\\premake5.zip"

            with open(PREMAKE_ZIP, 'wb') as file:
                file.write(response.content)
            
            Log.Info("Premake5 zip downloaded!")

            with zipfile.ZipFile(PREMAKE_ZIP, 'r') as zip_ref:
                zip_ref.extractall(PRMAKE_BIN_PATH)
            
            Log.Info("Premake5 extracted!")
        else:
            Log.Error("Failed to download premake!")
            sys.exit()
    else:
        Log.Warn("Cancelling project generation!")
        sys.exit()

project_dir = os.path.abspath(os.path.join(SCRIPT_DIR, ".."))
command = [PREMAKE_EXE_PATH, "vs2022"]

try:
    subprocess.run(command, cwd=project_dir, check=True)
    Log.Info("Project generated successfully! Open The CobaltGameEngine.sln file in the root of the project!")
except subprocess.CalledProcessError as error:
    Log.Error(f"Failed to generate project files with premake: {error.returncode}.")
except FileNotFoundError:
    Log.Error(f"Premake executable not found at {PREMAKE_EXE_PATH}")