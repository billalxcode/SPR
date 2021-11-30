import sys
import os
from colorama import Fore

CONSOLE_INFO = 0
CONSOLE_WARN = 1
CONSOLE_ERRR = 2
CONSOLE_NORM = 3

COLOR_WHITE = Fore.WHITE
COLOR_RED = Fore.RED
COLOR_GREEN = Fore.GREEN
COLOR_CYAN = Fore.CYAN
COLOR_RESET = Fore.RESET

class Console:
    def __init__(self, environment = None) -> None:
        self.messages = []
        self.environment = environment

        self.filename = os.path.join(os.getcwd(), "my.log")

    def quit(self, isUser: bool = False, isProgram: bool = True, code: int =0, interrupt: bool = True):
        mode = "User"
        if isProgram:
            mode = "Program"
        elif isUser:
            mode = "User"    

        start = ("\n" if interrupt is True else "")
        self.environment.kill_all()
        self.print_warning(f"{mode} quit...", end="\n", start=start)
        self.save_logs()
        exit(code)

    def save_logs(self):
        with open(self.filename, "a") as File:
            for message in self.messages:
                File.write(message)
            File.close()

    def print_info(self, message: str, start: str = "", end: str = "\n", useFlush: bool = False):
        return self.print_console(message=message, type_message=CONSOLE_INFO, start=start, end=end, useFlush=useFlush)

    def print_error(self, message: str, start: str = "", end: str = "\n", useFlush: bool = False):
        return self.print_console(message=message, type_message=CONSOLE_ERRR, start=start, end=end, useFlush=useFlush)

    def print_warning(self, message: str, start: str = "", end: str = "\n", useFlush: bool = False):
        return self.print_console(message=message, type_message=CONSOLE_WARN, start=start, end=end, useFlush=useFlush)

    def print_console(self, message: str, type_message: int = CONSOLE_INFO, start: str = "", end: str = "\n", useFlush: bool = False):
        output = start
        output_msg = ""
        if type_message == CONSOLE_INFO:
            output += f"{Fore.WHITE}[{Fore.GREEN}INFO{Fore.WHITE}] "
            output_msg += "[INFO] "
        elif type_message == CONSOLE_WARN:
            output += f"{Fore.WHITE}[{Fore.YELLOW}WARN{Fore.WHITE}] "
            output_msg += "[WARN] "
        elif type_message == CONSOLE_ERRR:
            output += f"{Fore.WHITE}[{Fore.RED}ERRR{Fore.WHITE}] "
            output_msg += "[ERRR] "
        elif type_message == CONSOLE_NORM:
            pass
        output += message
        output += end
        output += Fore.RESET
        output_msg += message
        output_msg += end
        self.messages.append(output_msg)
        sys.stdout.write(output)
        if useFlush:
            sys.stdout.flush()
        return True