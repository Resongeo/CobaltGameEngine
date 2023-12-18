import os

class ColorCodes():
    RED = '\033[31m'
    GREEN = '\033[32m'
    YELLOW = '\033[33m'
    WHITE = '\033[37m'
    GREY = '\33[90m'
    RESET = '\033[0m'

class Log():
    def __init__(self) -> None:
        os.system("colors")
    
    def Info(message):
        print(f"{ColorCodes.GREEN}[INFO]: {ColorCodes.GREY}{message}{ColorCodes.RESET}")
        
    def Warn(message):
        print(f"{ColorCodes.YELLOW}[WARN]: {ColorCodes.GREY}{message}{ColorCodes.RESET}")
        
    def Error(message):
        print(f"{ColorCodes.RED}[ERROR]: {ColorCodes.GREY}{message}{ColorCodes.RESET}")