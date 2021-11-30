import argparse
import platform
import os
from pathlib import Path
from src.python.terminal import Console
from src.python.terminal import COLOR_RED, COLOR_CYAN, COLOR_GREEN, COLOR_WHITE
from src.python.constants import MODE_CLI, MODE_GUI, MODE_DEFAULT
from src.python.cli.cmd import CommandLine

terminal_console = Console()

def parse_args():
    parsers = argparse.ArgumentParser()
    parsers.add_argument("-g", "--gui", action="store_true", help="Graphical User Interface mode")
    parsers.add_argument("-c", "--cli", action="store_true", help="Command Line Interface mode")
    parsers.add_argument("-b", "--baudrate", action="store", help="Set Baudrate (Default: 9600)")
    parsers.add_argument("-p", "--port", action="store", help="Set Com Port (Default: Auto Detect)")
    
    # parsers.add_argument()
    args = parsers.parse_args()
    return args

def find_home_dir():
    return Path.home()

def platformio_installed():
    home_dir = find_home_dir()
    system_platform = platform.system()
    terminal_console.print_info(f"Your Platform System: {COLOR_CYAN}{system_platform}")
    if system_platform == "Windows":
        platformio_dir = os.path.join(home_dir, "Documents", "PlatformIO")
    elif system_platform == "Linux":
        platformio_dir = os.path.join(home_dir, "Documents", "PlatformIO")
    else:
        terminal_console.print_error("Platform not support")
        return False
    return os.path.isdir(platformio_dir)
        
def main():
    argument = parse_args()
    platformio_isInstalled = platformio_installed()
    if platformio_isInstalled:
        mode = MODE_DEFAULT
        if argument.gui:
            terminal_console.print_info("Mode: GUI")
            mode = MODE_GUI
        elif argument.cli:
            terminal_console.print_info("Mode: CLI")
        else:
            terminal_console.print_info("Mode: Default (CLI)")
            mode = MODE_CLI

        if mode == MODE_CLI:
            commandline = CommandLine()
            commandline.run()
    else:
        terminal_console.quit()

if __name__ == "__main__":
    main()